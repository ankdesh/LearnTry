# header_sidebar_ui.py

from nicegui import ui

def create_collapsible_sidebar() -> ui.left_drawer:
    """
    Creates and configures the collapsible left sidebar (also known as a drawer).

    This sidebar provides top-level navigation and actions, like accessing settings.

    Returns:
        ui.left_drawer: The configured NiceGUI left_drawer component.
    """
    # Define the drawer with a dark background and some padding.
    # It is initialized as closed (`value=False`).
    with ui.left_drawer(value=False).classes('bg-gray-100 dark:bg-gray-800 p-4') as left_drawer:
        
        # Sidebar title
        ui.label('Navigation').classes('text-lg font-semibold mb-2')
        
        # Navigation buttons
        ui.button('Settings', icon='settings', on_click=lambda: ui.notify("Settings clicked!")) \
            .props('flat color=primary').classes('w-full text-left')
        
        # You can add more navigation links here as needed.
        # Example:
        # ui.button('Profile', icon='account_circle', on_click=lambda: ui.notify("Profile clicked!")) \
        #     .props('flat color=primary').classes('w-full text-left')

    return left_drawer