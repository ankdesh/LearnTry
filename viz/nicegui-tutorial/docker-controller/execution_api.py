from typing import Any
from docker_manager import ContainerManager
from models import (
    ApiRequestUnion, SaveFileRequest, ReadFileRequest,
    ExecutePythonRequest, ExecuteCppRequest, ExecuteShellRequest
)

# --- API Layer ---

class ExecutionApi:
    """
    Provides a single entry point to handle various operational requests
    by routing them to the appropriate session and execution engine.
    """

    def __init__(self, manager: ContainerManager):
        """
        Initializes the ExecutionApi with a ContainerManager.

        Args:
        manager: The ContainerManager instance to interact with Docker containers.
        """
        self.manager = manager

    async def handle_request(self, request: ApiRequestUnion) -> Any:
        """
        Processes an API request by getting the user's container and session,
        then routing the request to the correct session method or execution engine.

        Args:
        request: An instance of any model in ApiRequestUnion.

        Returns:
        The result of the specific operation.

        Raises:
        ValueError: If the session ID is not found for the user.
        TypeError: If the request type is unsupported.
        """
        # Get or create the container for the user
        container_obj = await self.manager.get_or_create_container(request.user_id)

        # Get the specific session for the user
        session = container_obj.get_session(request.session_id)
        if not session:
            raise ValueError(
                f"Session '{request.session_id}' not found for user '{request.user_id}'.")

        # Type matching to route the request
        if isinstance(request, SaveFileRequest):
            return await session.save_file(request.file_path, request.data_base64)

        if isinstance(request, ReadFileRequest):
            return await session.read_file(request.file_path)

        # For execution requests, pass the container object and all request fields
        # (including user_id, session_id, and engine-specific args) to the session's execute method
        if isinstance(request, (ExecutePythonRequest, ExecuteCppRequest, ExecuteShellRequest)):
            # Pass all model fields as kwargs to the execute method
            return await session.execute(container_obj.docker_container, **request.model_dump())

        raise TypeError(f"Unsupported request type: {type(request)}")
