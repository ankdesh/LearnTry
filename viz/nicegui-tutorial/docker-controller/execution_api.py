from typing import Any
from docker_manager import ContainerManager
from models import (
    ApiRequestUnion, SaveFileRequest, ReadFileRequest,
    ExecutePythonRequest, ExecuteCppRequest, ExecuteShellRequest
)

# --- API Layer ---

class ExecutionApi:
    """A single entry point to handle all operational requests."""
    def __init__(self, manager: ContainerManager):
        self.manager = manager

    async def handle_request(self, request: ApiRequestUnion) -> Any:
        """Processes an API request and routes it to the correct function."""
        container_obj = await self.manager.get_or_create_container(request.user_id)
        session = container_obj.get_session(request.session_id)
        if not session:
            raise ValueError(f"Session '{request.session_id}' not found for user '{request.user_id}'.")

        # Type matching to route the request
        if isinstance(request, SaveFileRequest):
            return await session.save_file(request.file_path, request.data_base64)
        
        if isinstance(request, ReadFileRequest):
            return await session.read_file(request.file_path)

        if isinstance(request, (ExecutePythonRequest, ExecuteCppRequest, ExecuteShellRequest)):
            # Pass all model fields as kwargs to the execute method
            return await session.execute(container_obj.docker_container, **request.model_dump())
        
        raise TypeError(f"Unsupported request type: {type(request)}")