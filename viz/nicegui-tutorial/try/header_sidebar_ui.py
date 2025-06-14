from nicegui import ui

def create_collapsible_sidebar() -> ui.left_drawer:
    """Creates the collapsible left sidebar."""
    
    # --- Collapsible Sidebar (Left Drawer) ---
    with ui.left_drawer(value=False).classes('bg-gray-100 dark:bg-gray-800 p-4') as left_drawer:
        ui.label('Navigation').classes('text-lg font-semibold mb-2')
        ui.button('Settings', icon='settings', on_click=lambda: ui.notify("Settings clicked!")) \
            .props('flat color=primary').classes('w-full text-left')
    
    return left_drawer