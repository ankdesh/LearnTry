#!/usr/bin/env python3
from typing import Optional

from nicegui import ui

from content_manager import ContentManager, TextContent, CodeContent, TableContent, ImageContent # ImageContent was missing
from chat_ui import create_chat_display_panel # Changed from ChatPanelUI
from content_panel_ui import ContentPanelUI, create_content_display_panel
from header_sidebar_ui import create_collapsible_sidebar # Updated import


# --- Main Application ---
@ui.page('/')
def main_page():
    """The main page of the application, demonstrating the splitter layout."""

    # Enable dark mode
    ui.dark_mode(True) # Use True for auto, or a specific value

    ui.add_css('''
        /* Ensure the splitter takes up available height */
        .nicegui-splitter {
            height: 100%; /* Changed from width to height for clarity */
        }

        /* Make both splitter panels independent */
        .nicegui-splitter .q-splitter__before,
        .nicegui-splitter .q-splitter__after {
            overflow: auto; /* Allow independent scrolling */
            height: 100%;   /* Ensure panels take full height of the splitter */
        }

        /* Ensure cards within splitter slots fill height if desired */
       .nicegui-splitter .q-splitter__panel .q-card {
            height: 100%;
            display: flex;
            flex-direction: column;
        }
       .nicegui-splitter .q-splitter__panel .q-card .nicegui-column {
            flex-grow: 1; /* Allows column to fill card height */
        }
        /* Ensure expansion items fill width */
        .q-expansion-item {
            width: 100%;
        }
        /* Globally reduce icon sizes */
        .q-icon {
            font-size: 26px !important; /* Or 1rem, 0.875rem, etc. */
        }
        /* Make dense switches more compact to better match 16px icon sizes */
        /* Default dense q-toggle height is 20px. Aiming for ~16px. */
        .q-toggle--dense {
            height: 16px !important; /* Overall component height */
        }
        .q-toggle--dense .q-toggle__track {
            height: 10px !important; /* Track height (default dense: 14px) */
            width: 24px !important;  /* Track width (default dense: 30px, adjust as needed) */
        }
        .q-toggle--dense .q-toggle__thumb {
            height: 14px !important; /* Thumb size (default dense: 14px) */
            width: 14px !important;
        }
    ''')



    # Create the sidebar (no header will be created by this function now)
    left_drawer = create_collapsible_sidebar()

    # --- Content Management ---
    content_manager = ContentManager()

    # --- Splitter Layout ---
    # The 'h-screen' and 'flex' properties on the container are essential.
    with ui.element('div').classes('w-full h-screen flex flex-col'):
        with ui.splitter(value=33).classes('flex-grow') as splitter: # flex-grow makes splitter fill container
            with splitter.before:
                create_chat_display_panel(left_drawer)

            with splitter.after:
                display_panel = create_content_display_panel(content_manager)

    # Example initial content
    content_manager.add_content(TextContent(name="Welcome Note", text="Hello! This is the AI Canvas. Interact via the chat on the left. The panels now scroll independently."))
    # Add more content to demonstrate scrolling
    for i in range(3):
        content_manager.add_content(TextContent(name=f"Item {i+1}", text=f"This is placeholder text for item {i+1} to make the right panel taller."))

    # NOTE: You may need to adjust this path to be correct for your system.
    try:
        with open("app.py", "r") as f:
            content_manager.add_content(CodeContent(name="Sample Python", code=f.read(), language="python"))
    except FileNotFoundError:
         content_manager.add_content(CodeContent(name="Sample Python", code="print('Hello, World!')", language="python"))

    content_manager.add_content(TableContent(name="Demo Table", headers=["ID", "Item", "Price"], rows=[[1, "Apple", 0.5], [2, "Banana", 0.3]]))
    content_manager.add_content(ImageContent(name="Placeholder Image", source="https://picsum.photos/seed/nicegui/600/400", caption="A random placeholder image."))

    display_panel.refresh_display()
    
    # Initial refresh is now handled by the ContentPanelUI constructor,
    # but if you add content after creation, you might need to find the instance and call refresh.
    # For this setup, we let the UI build and then add content. The UI will reflect the state at creation.
    # To see the dynamically added content above, we'd need to get the panel instance and call refresh.
    # This is a more advanced topic not covered by the current structure.
    # The content added here will be visible on the next refresh/interaction that triggers one.


# Start the NiceGUI application.
ui.run()