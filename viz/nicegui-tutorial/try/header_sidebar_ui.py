from nicegui import ui

def create_header_and_sidebar() -> ui.left_drawer:
    """Creates the application header and the collapsible left sidebar."""
    
    # --- Collapsible Sidebar (Left Drawer) ---
    with ui.left_drawer(value=False).classes('bg-gray-100 dark:bg-gray-800 p-4') as left_drawer:
        ui.label('Navigation').classes('text-lg font-semibold mb-2')
        ui.button('Settings', icon='settings', on_click=lambda: ui.notify("Settings clicked!")) \
            .props('flat color=primary').classes('w-full text-left')

    # --- Header ---
    with ui.header(elevated=True).classes('items-center justify-between transparent fixed top-0 left-0 right-0 h-[50px] px-4'):
        with ui.row().classes('items-center'):
            ui.button(icon='menu', on_click=left_drawer.toggle).props('flat round dense color=white')
            ui.label('Ankdesh AI Framework').classes('text-xl font-bold ml-2 text-white')
    
    return left_drawer