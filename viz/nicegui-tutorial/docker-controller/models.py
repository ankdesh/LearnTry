from pydantic import BaseModel, model_validator, Field
from typing import List, Union
 
# --- Data Models (Pydantic) ---

class ExecutionResult(BaseModel):
    """A Pydantic model to standardize execution results."""
    stdout: str
    stderr: str
    exit_code: int
    status: str = "success"

    @model_validator(mode='after')
    def set_status(self) -> 'ExecutionResult':
        if self.exit_code != 0: self.status = "failure"
        else: self.status = "success"
        return self

# --- API Request Models ---

class ApiRequest(BaseModel):
    """Base model for all API requests, ensuring user and session context.
    
    All API request models should inherit from this class to include user_id and session_id.
    """
    user_id: str
    session_id: str

class SaveFileRequest(ApiRequest):
    """Request model for saving a file in a user's session workspace."""
    operation: str = "save_file"
    file_path: str
    data_base64: str

class ReadFileRequest(ApiRequest):
    """Request model for reading a file from a user's session workspace."""
    operation: str = "read_file"
    file_path: str

class ExecutePythonRequest(ApiRequest):
    """Request model for executing a Python script in a user's session container."""
    operation: str = "python"
    script_path: str
    args: List[str] = Field(default_factory=list)

class ExecuteCppRequest(ApiRequest):
    """Request model for compiling and executing a C++ source file."""
    operation: str = "cpp"
    source_path: str
    output_name: str
    args: List[str] = Field(default_factory=list)

class ExecuteShellRequest(ApiRequest):
    """Request model for executing a shell command in a user's session container."""
    operation: str = "shell"
    command: str

# A Union of all possible request types for the main API endpoint
ApiRequestUnion = Union[
 SaveFileRequest,
 ReadFileRequest,
 ExecutePythonRequest,
 ExecuteCppRequest,
 ExecuteShellRequest
]