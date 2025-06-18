# test_sse_client_ui.py

import asyncio
import httpx
import json
from nicegui import ui # type: ignore

# Import the UI components and managers from your existing files
from content_manager import ContentManager, CodeContent # Added CodeContent
from chat_ui import create_chat_display_panel
from content_panel_ui import create_content_display_panel
from header_sidebar_ui import create_collapsible_sidebar
from ui_interface import UIInterface

async def sse_data_generator():
    """
    Connects to the SSE server and yields header and token from the received data.
    
    This function contains the logic from your sse_client.py file.
    """
    server_url = "http://localhost:8001/stream-data"
    print(f"Connecting to SSE server at {server_url}...")

    try:
        # Use httpx.AsyncClient to handle the persistent connection
        async with httpx.AsyncClient(timeout=None) as client:
            async with client.stream("GET", server_url) as response:
                if response.status_code == 200:
                    print("Successfully connected to SSE server. Waiting for data...\n")
                    # Process the incoming stream line by line
                    async for line in response.aiter_lines():
                        if line.startswith("data:"):
                            json_data_str = line[len("data:"):]
                            if json_data_str:
                                try:
                                    data = json.loads(json_data_str)
                                    header = data.get("header")
                                    token = data.get("token", "")
                                    if token:
                                        yield header, token # Yield the token as is (now includes newline)
                                except json.JSONDecodeError:
                                    print(f"Error decoding JSON: {json_data_str}")
                                    yield "System Error", f"Received malformed data: {json_data_str}"
                else:
                    error_message = f"Error connecting to server: Status {response.status_code}"
                    print(error_message)
                    yield "System Error", error_message
    except httpx.ConnectError as e:
        error_message = f"Connection to SSE server failed: {e}"
        print(error_message)
        yield "System Error", error_message

@ui.page('/')
async def main_page():
    """
    The main page of the application, which sets up the layout and starts the SSE client.
    """
    # --- Page and UI Configuration ---
    ui.dark_mode(True)
    ui.add_css('''
        .nicegui-splitter, .nicegui-splitter .q-splitter__before, .nicegui-splitter .q-splitter__after {
            height: 100%; overflow: hidden;
        }
        .nicegui-splitter .q-splitter__panel .q-card {
            height: 100%; display: flex; flex-direction: column; overflow: auto;
        }
    ''')

    # --- UI Component Initialization ---
    left_drawer = create_collapsible_sidebar()
    content_manager = ContentManager()

    # --- Main Layout using Splitter ---
    with ui.element('div').classes('w-full h-screen flex flex-col'):
        with ui.splitter(value=33).classes('flex-grow') as splitter:
            with splitter.before:
                chat_panel = create_chat_display_panel(left_drawer)
            with splitter.after:
                content_display_panel = create_content_display_panel(content_manager)

    # --- UI Manager Setup ---
    # This manager provides the clean API for UI interactions
    ui_manager = UIInterface(chat_panel=chat_panel, content_panel=content_display_panel)
    chat_panel.set_ui_manager(ui_manager)

    # --- State for SSE data processing ---
    current_code_content_name: Optional[str] = None
    code_block_counter = 0


    # --- Process data from the SSE Client ---
    # Iterate over the data yielded by the sse_data_generator and update the UI.
    # The loop `for i in range(2)` will run the SSE connection and processing twice for testing.
    for _ in range(2): # Use _ if 'i' is not used
        # Disable chat input and change icon before starting SSE data reception
        ui_manager.chat_panel.chat_box.disable_input()
        try:
            async for header, token in sse_data_generator():
                print (header, "=>", token)
                # if token.find("\n") != -1: # Debug print, can be removed
                #     print ("Found \n")
                if header == "code:python":
                    if current_code_content_name is None:
                        # This is the start of a new Python code block from the stream
                        code_block_counter += 1
                        current_code_content_name = f"Code:Python {code_block_counter}"
                        # Add an initial empty CodeContent box to the right panel
                        ui_manager.add_content(CodeContent(name=current_code_content_name, code="", language="python"))
                    # Stream the token to the currently active code content box
                    ui_manager.update_content(current_code_content_name, token, stream=True)
                elif header == "text":
                    # If we receive a "text" header, it means any previous code block stream has ended.
                    current_code_content_name = None # Reset for the next potential code block
                    ui_manager.stream_to_chat(header, token)
                else: # Handles "System Error" or any other unexpected headers
                    current_code_content_name = None # Reset
                    ui_manager.stream_to_chat(header, token) # Display errors or other info in chat
        finally:
            # Re-enable chat input and revert icon after SSE data reception is complete or an error occurs
            ui_manager.chat_panel.chat_box.enable_input()

# --- Run the UI Application ---
ui.run()