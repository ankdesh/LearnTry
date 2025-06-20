import base64
import asyncio

from models import (
    SaveFileRequest, ExecuteCppRequest, ExecuteShellRequest
)
from docker_manager import ContainerManager, SystemConfig
from execution_api import ExecutionApi

async def main():
    """The main asynchronous entry point for the application."""
    manager = None
    try:
        print("--- System Setup ---")
        manager = ContainerManager()
        api = ExecutionApi(manager) # Create the API layer
        
        admin_config = SystemConfig()
        admin_config.set_config(image_name="gcc", max_containers=10)

        print("\n--- User 'alice' starts work ---")
        user_id_alice = "alice"
        alice_session_id = "alice_session_123"  # User-defined session ID
        # We still need to create a container and session manually the first time.
        alice_container_obj = await manager.get_or_create_container(user_id_alice)
        alice_session = await alice_container_obj.create_session(session_id=alice_session_id)
        print(f"Alice's new session ID: {alice_session.session_id}")
        
        print("\n--- API-Driven File Operations & Execution ---")

        # 1. Save a file via the API
        cpp_code = '#include <iostream>\nint main() { std::cout << "Hello from API-driven C++!" << std::endl; return 0; }'
        save_request = SaveFileRequest(
            user_id=user_id_alice,
            session_id=alice_session.session_id,
            file_path="main.cpp",
            data_base64=base64.b64encode(cpp_code.encode('utf-8')).decode('utf-8')
        )
        save_result = await api.handle_request(save_request)
        print("API SaveFile Result:", save_result)

        # 2. Execute C++ via the API
        cpp_exec_request = ExecuteCppRequest(
            user_id=user_id_alice,
            session_id=alice_session.session_id,
            source_path="main.cpp",
            output_name="main_exec"
        )
        cpp_exec_result = await api.handle_request(cpp_exec_request)
        print("API C++ Exec Result:", cpp_exec_result)

        # 3. Execute Shell command via the API
        shell_request = ExecuteShellRequest(
            user_id=user_id_alice,
            session_id=alice_session.session_id,
            command="echo 'Hello from API-driven Shell!' && ls -l"
        )
        shell_result = await api.handle_request(shell_request)
        print("API Shell Exec Result:", shell_result.model_dump_json(indent=2))

    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        if manager:
            await manager.shutdown()

if __name__ == "__main__":
    asyncio.run(main())
