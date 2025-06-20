import os
import shutil
import base64
import uuid
import docker
import asyncio
import aiofiles
from typing import Dict, Any, Optional

from execution_engines import PythonExecutionEngine, CppExecutionEngine, ShellExecutionEngine, ExecutionEngine

# --- Configuration (Singleton Pattern) ---

class SystemConfig:
    """
    A singleton class to hold the system's configuration.
    """
    _instance = None
    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            cls._instance = super(SystemConfig, cls).__new__(cls)
        return cls._instance
    def __init__(self, image_name="ubuntu:22.04", disk_quota_gb=5, max_containers=50):
        if not hasattr(self, '_initialized'):
            self.settings = {"image_name": image_name, "disk_quota_gb": disk_quota_gb, "max_containers": max_containers}
            self._initialized = True
    def set_config(self, **kwargs: Any) -> None:
        for key, value in kwargs.items():
            if key in self.settings: self.settings[key] = value
        print("Configuration updated:", self.settings)
    def get_config(self) -> Dict[str, Any]:
        return self.settings

# --- Core Logic Classes ---

class Session:
    def __init__(self, user_id: str, session_id: str, host_workspace_path: str):
        self.user_id = user_id
        self.session_id = session_id
        self.host_working_dir = os.path.join(host_workspace_path, self.session_id)
        self.container_working_dir = f"/workspace/{self.session_id}"
        self.engines: Dict[str, ExecutionEngine] = {"python": PythonExecutionEngine(), "cpp": CppExecutionEngine(), "shell": ShellExecutionEngine()}

    async def _async_init(self):
        await asyncio.to_thread(os.makedirs, self.host_working_dir, exist_ok=True)
        print(f"Session '{self.session_id}' created at host path '{self.host_working_dir}'")

    async def save_file(self, file_path: str, data_base64: str) -> Dict[str, str]:
        full_path = os.path.join(self.host_working_dir, file_path)
        await asyncio.to_thread(os.makedirs, os.path.dirname(full_path), exist_ok=True)
        try:
            data = await asyncio.to_thread(base64.b64decode, data_base64)
            async with aiofiles.open(full_path, 'wb') as f: await f.write(data)
            return {"status": "success", "file_path": full_path}
        except Exception as e: return {"status": "error", "message": str(e)}

    async def read_file(self, file_path: str) -> Optional[str]:
        full_path = os.path.join(self.host_working_dir, file_path)
        try:
            async with aiofiles.open(full_path, 'rb') as f:
                content = await f.read()
                return base64.b64encode(content).decode('utf-8')
        except FileNotFoundError: return None

    async def execute(self, container: docker.models.containers.Container, operation: str, **kwargs) -> Any:
        engine = self.engines.get(operation)
        if not engine: raise ValueError(f"Unsupported operation type: {operation}")
        kwargs['container_workdir'] = self.container_working_dir
        return await engine.execute(container, **kwargs)

class Container:
    def __init__(self, user_id: str, docker_container: docker.models.containers.Container, host_workspace_path: str):
        self.user_id = user_id
        self.docker_container = docker_container
        self.host_workspace_path = host_workspace_path
        self.sessions: Dict[str, Session] = {}
        print(f"Container '{self.docker_container.short_id}' initialized for user '{self.user_id}'.")

    async def create_session(self, session_id: str) -> Session:
        session = Session(self.user_id, session_id, self.host_workspace_path)
        await session._async_init()
        self.sessions[session_id] = session
        return session

    def get_session(self, session_id: str) -> Optional[Session]:
        return self.sessions.get(session_id)

    async def delete_session(self, session_id: str) -> bool:
        session = self.get_session(session_id)
        if session:
            await asyncio.to_thread(shutil.rmtree, session.host_working_dir, ignore_errors=True)
            del self.sessions[session_id]
            return True
        return False

class ContainerManager:
    HOST_BASE_PATH = os.path.abspath("./user_workspaces")
    def __init__(self):
        self.containers: Dict[str, Container] = {}
        self.config = SystemConfig()
        try:
            self.client = docker.from_env()
            self.client.ping()
        except docker.errors.DockerException as e: raise RuntimeError("Docker is not running.") from e
        os.makedirs(self.HOST_BASE_PATH, exist_ok=True)
        print("ContainerManager initialized with Docker client.")

    async def get_or_create_container(self, user_id: str) -> Container:
        if user_id in self.containers: return self.containers[user_id]
        running_containers = await asyncio.to_thread(self.client.containers.list, filters={'label': f"user_id={user_id}"})
        if running_containers:
            docker_container = running_containers[0]
        else:
            if len(self.containers) >= self.config.get_config()['max_containers']: raise Exception("Max containers reached.")
            user_workspace_path = os.path.join(self.HOST_BASE_PATH, user_id)
            await asyncio.to_thread(os.makedirs, user_workspace_path, exist_ok=True)
            print(f"Creating new Docker container for user '{user_id}'...")
            docker_container = await asyncio.to_thread(self.client.containers.run, self.config.get_config()['image_name'], detach=True, command="tail -f /dev/null", volumes={user_workspace_path: {'bind': '/workspace', 'mode': 'rw'}}, labels={'user_id': user_id})
        
        container = Container(user_id, docker_container, os.path.join(self.HOST_BASE_PATH, user_id))
        self.containers[user_id] = container
        return container

    async def shutdown(self):
        print("\n--- Shutting Down System ---")
        tasks = []
        for user_id, container_obj in self.containers.items():
            async def stop_and_remove():
                try:
                    await asyncio.to_thread(container_obj.docker_container.stop)
                    await asyncio.to_thread(container_obj.docker_container.remove)
                    print(f"Cleaned up container for {user_id}")
                except Exception as e: print(f"Error cleaning up for {user_id}: {e}")
            tasks.append(stop_and_remove())
        await asyncio.gather(*tasks)