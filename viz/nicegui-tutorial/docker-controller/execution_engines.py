import asyncio
import docker
from abc import ABC, abstractmethod
from typing import Dict, Any
from models import ExecutionResult

# --- Execution Strategy (Strategy & ABC Pattern) ---


class ExecutionEngine(ABC):
    """Abstract base class for execution engines."""

    @abstractmethod
    async def execute(self, container: docker.models.containers.Container, **kwargs) -> Any:
        """
        Execute a command within the given Docker container.

        Args:
        container: The Docker container object.
        **kwargs: Specific arguments for the execution (e.g., script_path, command).

        Returns:
        The result of the execution, typically an ExecutionResult or a dictionary.
        """
        pass


class PythonExecutionEngine(ExecutionEngine):
    """Execution engine for Python scripts."""

    async def execute(self, container: docker.models.containers.Container, **kwargs) -> ExecutionResult:
        """Executes a Python script using `python3`."""
        command = ["python3", kwargs["script_path"]] + kwargs.get("args", [])
        
        # Use asyncio.to_thread for blocking docker exec_run call
        result = await asyncio.to_thread(container.exec_run, command, workdir=kwargs["container_workdir"])
        
        return ExecutionResult(stdout=result.output.decode('utf-8'), stderr="", exit_code=result.exit_code)


class CppExecutionEngine(ExecutionEngine):
    """Execution engine for C++ source files (compile and run)."""

    async def execute(self, container: docker.models.containers.Container, **kwargs) -> Dict[str, Any]:
        """
        Compiles a C++ source file and executes the resulting binary.

        Returns:
        A dictionary containing compilation and execution results.
        """
        compile_cmd = ["g++", kwargs["source_path"],
                       "-o", kwargs["output_name"]]
        
        # Compile the C++ code
        compile_res_docker = await asyncio.to_thread(container.exec_run, compile_cmd, workdir=kwargs["container_workdir"])
        compile_res = ExecutionResult(stdout=compile_res_docker.output.decode(
            'utf-8'), stderr="", exit_code=compile_res_docker.exit_code)

        exec_res = None
        if compile_res.exit_code == 0:
            exec_cmd = [f"./{kwargs['output_name']}"] + kwargs.get("args", [])
            exec_res_docker = await asyncio.to_thread(container.exec_run, exec_cmd, workdir=kwargs["container_workdir"])
        
            # Execute the compiled binary
            exec_res = ExecutionResult(stdout=exec_res_docker.output.decode(
                'utf-8'), stderr="", exit_code=exec_res_docker.exit_code)

        return {"compilation": compile_res.model_dump(), "execution": exec_res.model_dump() if exec_res else None}


class ShellExecutionEngine(ExecutionEngine):
    """Execution engine for arbitrary shell commands."""

    async def execute(self, container: docker.models.containers.Container, **kwargs) -> ExecutionResult:
        result = await asyncio.to_thread(container.exec_run, f"sh -c '{kwargs['command']}'", workdir=kwargs["container_workdir"])
        return ExecutionResult(stdout=result.output.decode('utf-8'), stderr="", exit_code=result.exit_code)
