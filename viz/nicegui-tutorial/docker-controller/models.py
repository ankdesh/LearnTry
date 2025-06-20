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
    """Base model for all API requests, ensuring user and session context."""
    user_id: str
    session_id: str

class SaveFileRequest(ApiRequest):
    operation: str = "save_file"
    file_path: str
    data_base64: str

class ReadFileRequest(ApiRequest):
    operation: str = "read_file"
    file_path: str

class ExecutePythonRequest(ApiRequest):
    operation: str = "python"
    script_path: str
    args: List[str] = Field(default_factory=list)

class ExecuteCppRequest(ApiRequest):
    operation: str = "cpp"
    source_path: str
    output_name: str
    args: List[str] = Field(default_factory=list)

class ExecuteShellRequest(ApiRequest):
    operation: str = "shell"
    command: str

# A Union of all possible request types for the main API endpoint
ApiRequestUnion = Union[
    SaveFileRequest, ReadFileRequest, ExecutePythonRequest, ExecuteCppRequest, ExecuteShellRequest
]