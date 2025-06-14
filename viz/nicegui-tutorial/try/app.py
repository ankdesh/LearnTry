#!/usr/bin/env python3
from typing import Optional

from nicegui import ui

from content_manager import ContentManager, TextContent, CodeContent, TableContent, ImageContent # ImageContent was missing
from chat_ui import create_chat_display_panel # Changed from ChatPanelUI
from content_panel_ui import ContentPanelUI, create_content_display_panel
from header_sidebar_ui import create_header_and_sidebar


# --- Main Application ---
@ui.page('/')
def main_page():
    """The main page of the application, demonstrating the splitter layout."""

    # Enable dark mode
    ui.dark_mode(True) # Use True for auto, or a specific value

    left_drawer = create_header_and_sidebar()

    ui.add_css('''
        /* Ensure the splitter takes up available height */
        .nicegui-splitter {
            width: 100%;
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


    # --- Content Management ---
    content_manager = ContentManager()

    # --- Splitter Layout ---
    # CHANGE: Replaced 'min-h-screen' with 'h-screen' and added 'pt-[50px]'.
    # 'h-screen' makes the container exactly the height of the viewport.
    # 'pt-[50px]' adds padding at the top to prevent the fixed header from overlapping the content.
    # This ensures the splitter has a clearly defined, maximized space to occupy.
    with ui.element('div').classes(
        'w-full h-screen flex flex-col box-border pt-[50px]'
    ) as splitter_container:
        with ui.splitter(value=33).props('unit="%"').classes('w-full flex-grow') as splitter: # flex-grow makes splitter fill the container
            with splitter.before:
                create_chat_display_panel() # Use the new factory function

            with splitter.after:
                content_panel = create_content_display_panel(content_manager)

    # Example initial content
    content_manager.add_content(TextContent(name="Welcome Note", text="Hello! This is the AI Canvas. Interact via the chat on the left."))
    # NOTE: You may need to adjust this path to be correct for your system.
    try:
        with open("app.py", "r") as f:
            content_manager.add_content(CodeContent(name="Sample Python", code=f.read(), language="python"))
    except FileNotFoundError:
         content_manager.add_content(CodeContent(name="Sample Python", code="print('Hello, World!')", language="python"))

    content_manager.add_content(TableContent(name="Demo Table", headers=["ID", "Item", "Price"], rows=[[1, "Apple", 0.5], [2, "Banana", 0.3]]))
    content_manager.add_content(ImageContent(name="Placeholder Image", source="https://picsum.photos/seed/nicegui/600/400", caption="A random placeholder image."))

    content_panel.refresh_display()


# Start the NiceGUI application.
ui.run()
