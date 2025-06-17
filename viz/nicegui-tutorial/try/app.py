# app.py

#!/usr/bin/env python3
import asyncio
import time
from nicegui import ui
from content_manager import ContentManager, TextContent, CodeContent, TableContent, ImageContent
from chat_ui import create_chat_display_panel
from content_panel_ui import create_content_display_panel
from header_sidebar_ui import create_collapsible_sidebar
from ui_manager import UIInterface

# --- Main Application Setup ---

@ui.page('/')
async def main_page():
    """
    The main page of the application, setting up the layout and UI manager.
    """
    # --- Page Configuration ---
    ui.dark_mode(True)
    
    # --- Custom CSS ---
    # Adding global styles for the application.
    ui.add_css('''
        /* Make splitter and its panels fill the available height */
        .nicegui-splitter, .nicegui-splitter .q-splitter__before, .nicegui-splitter .q-splitter__after {
            height: 100%;
            overflow: hidden; /* Hide parent scroll, panels will handle their own */
        }
        /* Ensure cards within splitter panels fill height and allow scrolling */
        .nicegui-splitter .q-splitter__panel .q-card {
            height: 100%;
            display: flex;
            flex-direction: column;
            overflow: auto; /* Allow independent scrolling within each main card */
        }
    ''')

    # --- UI Component Initialization ---

    # 1. Create the collapsible sidebar (left drawer).
    left_drawer = create_collapsible_sidebar()

    # 2. Create the data manager for the content panel.
    content_manager = ContentManager()

    # --- Main Layout: A vertical splitter dividing the screen ---
    # The container ensures the splitter takes up the full screen height.
    with ui.element('div').classes('w-full h-screen flex flex-col'):
        with ui.splitter(value=33).classes('flex-grow') as splitter:
            
            # --- Left Panel: Chat UI ---
            with splitter.before:
                # The chat panel is created and gets a reference to the sidebar toggle.
                chat_panel = create_chat_display_panel(left_drawer)

            # --- Right Panel: Content Display ---
            with splitter.after:
                # The content panel is created with its data manager.
                content_display_panel = create_content_display_panel(content_manager)

    # --- UI Communication Interface ---
    # The UIManager is the single point of contact for any backend logic
    # that needs to interact with the UI.
    ui_manager = UIInterface(chat_panel=chat_panel, content_panel=content_display_panel)

    # Pass the UIManager to the chat panel so it can respond to user input.
    chat_panel.set_ui_manager(ui_manager)

    # --- Load Initial Content using the UIManager ---
    # This demonstrates how to use the new API to populate the content panel.
    
    ui_manager.add_content(TextContent(
        name="Welcome Note", 
        text="Hello! This is the AI Canvas. Interact via the chat on the left. The panels now scroll independently."
    ))

    # Add more content to demonstrate scrolling.
    for i in range(3):
        ui_manager.add_content(TextContent(
            name=f"Item {i+1}", 
            text=f"This is placeholder text for item {i+1} to make the right panel taller."
        ))

    # Add sample code content.
    try:
        with open("app.py", "r") as f:
            ui_manager.add_content(CodeContent(name="Application Code", code=f.read(), language="python"))
    except FileNotFoundError:
        ui_manager.add_content(CodeContent(name="Sample Code", code="print('Hello, World!')", language="python"))

    # Add sample table and image content.
    ui_manager.add_content(TableContent(
        name="Demo Table", 
        headers=["ID", "Item", "Price"], 
        rows=[[1, "Apple", 0.50], [2, "Banana", 0.30]]
    ))
    
    ui_manager.add_content(ImageContent(
        name="Placeholder Image", 
        source="https://picsum.photos/seed/nicegui/600/400", 
        caption="A random placeholder image from picsum.photos."
    ))

# --- Run the Application ---
ui.run()