import os
import shutil
import base64
import docker
import asyncio
import aiofiles
from typing import Dict, Any, Optional

from execution_engines import PythonExecutionEngine, CppExecutionEngine, ShellExecutionEngine, ExecutionEngine

# --- Configuration (Singleton Pattern) ---
# Although not strictly a singleton enforced by the class itself,
# it's intended to be used as a single instance throughout the application.
class SystemConfig:
    """
    Manages system-wide configuration settings for the Docker controller.
    Intended to be instantiated once.
    """

    def __init__(self, image_name="gcc:latest", disk_quota_gb=5, max_containers=50, host_base_path=os.path.abspath("./user_workspaces")):
        self.settings = {
            "image_name": image_name, 
            "disk_quota_gb": disk_quota_gb, 
            "max_containers": max_containers,
            "host_base_path": host_base_path
        }

    def get_config(self) -> Dict[str, Any]:
        """Returns the current system configuration settings."""
        return self.settings

# --- Core Logic Classes ---

class Session:
    """
    Represents a user's interactive session within a Docker container.
    
    Each session has its own dedicated working directory on the host,
    which is mounted into the container.
    """
    def __init__(self, user_id: str, session_id: str, host_workspace_path: str):
        """
        Initializes a Session object.
        
        Args:
        user_id: The ID of the user this session belongs to.
        session_id: A unique identifier for this session.
        host_workspace_path: The base path on the host for user workspaces.
        """
        self.user_id = user_id
        self.session_id = session_id
        self.host_working_dir = os.path.join(host_workspace_path, self.session_id)
        self.container_working_dir = f"/workspace/{self.session_id}"
        self.engines: Dict[str, ExecutionEngine] = {"python": PythonExecutionEngine(), "cpp": CppExecutionEngine(), "shell": ShellExecutionEngine()}

    async def _async_init(self):
        """Performs asynchronous initialization for the session (e.g., creating directories)."""
        await asyncio.to_thread(os.makedirs, self.host_working_dir, exist_ok=True)
        print(f"Session '{self.session_id}' created at host path '{self.host_working_dir}'")

    async def save_file(self, file_path: str, data_base64: str) -> Dict[str, str]:
        """
        Saves base64 encoded data to a file within the session's working directory.
        
        Args:
        file_path: The path to the file relative to the session's working directory.
        data_base64: The file content encoded in base64.
        
        Returns:
        A dictionary indicating the status ("success" or "error") and the file path
        or an error message.
        """
 # Ensure the directory structure exists on the host
        full_path = os.path.join(self.host_working_dir, file_path)
        await asyncio.to_thread(os.makedirs, os.path.dirname(full_path), exist_ok=True)
        try:
            data = await asyncio.to_thread(base64.b64decode, data_base64)
            async with aiofiles.open(full_path, 'wb') as f: await f.write(data)
            return {"status": "success", "file_path": full_path}
        except Exception as e: return {"status": "error", "message": str(e)}

    async def read_file(self, file_path: str) -> Optional[str]:
        """
        Reads a file from the session's working directory and returns its base64 encoded content.
        
        Args:
        file_path: The path to the file relative to the session's working directory.
        
        Returns:
        The base64 encoded content of the file, or None if the file is not found.
        """
        full_path = os.path.join(self.host_working_dir, file_path)
        try:
            async with aiofiles.open(full_path, 'rb') as f:
                content = await f.read()
                return base64.b64encode(content).decode('utf-8')
        except FileNotFoundError: return None

    async def execute(self, container: docker.models.containers.Container, operation: str, **kwargs) -> Any:
        """
        Executes a command or script within the container using the appropriate engine.
        
        Args:
        container: The Docker container object associated with the user.
        operation: The type of operation (e.g., "python", "cpp", "shell").
        **kwargs: Additional arguments required by the specific execution engine.
        
        Returns:
        The result of the execution.
        
        Raises:
        ValueError: If the requested operation type is not supported.
        """
        engine = self.engines.get(operation)
        if not engine: raise ValueError(f"Unsupported operation type: {operation}")
        kwargs['container_workdir'] = self.container_working_dir
 # Delegate execution to the specific engine
        return await engine.execute(container, **kwargs)

class Container:
    def __init__(self, user_id: str, docker_container: docker.models.containers.Container, host_workspace_path: str):
        self.user_id = user_id
        self.docker_container = docker_container
        self.host_workspace_path = host_workspace_path
        """
        Represents a Docker container assigned to a specific user.
        
        Manages sessions within this container and the user's workspace on the host.
        """
        self.sessions: Dict[str, Session] = {}
        print(f"Container '{self.docker_container.short_id}' initialized for user '{self.user_id}'.")

    async def create_session(self, session_id: str) -> Session:
        """
        Creates a new session for the user within this container.
        
        Args:
        session_id: A unique identifier for the new session.
        
        Returns:
        The newly created Session object.
        """
        session = Session(self.user_id, session_id, self.host_workspace_path)
        await session._async_init()
        self.sessions[session_id] = session
        return session

    def get_session(self, session_id: str) -> Optional[Session]:
        """
        Retrieves an existing session by its ID.
        
        Args:
        session_id: The ID of the session to retrieve.
        Returns: The Session object, or None if not found.
        """
        return self.sessions.get(session_id)

    async def delete_session(self, session_id: str) -> bool:
        session = self.get_session(session_id)
        if session:
            await asyncio.to_thread(shutil.rmtree, session.host_working_dir, ignore_errors=True)
            del self.sessions[session_id]
            return True
        return False

class ContainerManager:
    """
    Manages Docker containers for different users.
    
    Ensures each user has a dedicated container and handles container creation,
    retrieval, and shutdown.
    """
    def __init__(self):
        """Initializes the ContainerManager and connects to the Docker daemon."""
        self.containers: Dict[str, Container] = {}
        self.config = SystemConfig()
        self.host_base_path = self.config.get_config()['host_base_path']
        try:
            self.client = docker.from_env()
        
        # Verify Docker connection
            self.client.ping()
        except docker.errors.DockerException as e: raise RuntimeError("Docker is not running.") from e
 
        # Ensure the base directory for user workspaces exists
        os.makedirs(self.host_base_path, exist_ok=True)
        print("ContainerManager initialized with Docker client.")

    async def get_or_create_container(self, user_id: str) -> Container:
        """
        Retrieves an existing container for a user or creates a new one if none exists.
        
        Args:
        user_id: The ID of the user.
        
        Returns:
        The Container object for the user.
        
        Raises:
        Exception: If the maximum number of containers has been reached.
        """
        
        # Return existing container if available in memory
        if user_id in self.containers: return self.containers[user_id]
        
        # Check if a container for this user is already running but not in memory
        running_containers = await asyncio.to_thread(self.client.containers.list, filters={'label': f"user_id={user_id}"})
        if running_containers:
            docker_container = running_containers[0]
        else:
        
        # Create a new container if max containers limit is not reached
            if len(self.containers) >= self.config.get_config()['max_containers']: raise Exception("Max containers reached.")
            user_workspace_path = os.path.join(self.host_base_path, user_id)
            await asyncio.to_thread(os.makedirs, user_workspace_path, exist_ok=True)
            print(f"Creating new Docker container for user '{user_id}'...")
            
            # Run a new container, detach, mount user workspace, and label it
            docker_container = await asyncio.to_thread(self.client.containers.run, self.config.get_config()['image_name'], detach=True, command="tail -f /dev/null", volumes={user_workspace_path: {'bind': '/workspace', 'mode': 'rw'}}, labels={'user_id': user_id})
        
        container = Container(user_id, docker_container, os.path.join(self.host_base_path, user_id))
        self.containers[user_id] = container
        return container

    async def shutdown(self):
        """
        Stops and removes all managed Docker containers.
        Cleans up resources during application shutdown.
        """
        print("\n--- Shutting Down System ---")
        tasks = []
        for user_id, container_obj in self.containers.items():
        # Create a task for each container to stop and remove it
            async def stop_and_remove():
                try:
                    await asyncio.to_thread(container_obj.docker_container.stop)
                    await asyncio.to_thread(container_obj.docker_container.remove)
                    print(f"Cleaned up container for {user_id}")
                except Exception as e: print(f"Error cleaning up for {user_id}: {e}")
            tasks.append(stop_and_remove())
        await asyncio.gather(*tasks)
        print("All containers stopped and removed.")