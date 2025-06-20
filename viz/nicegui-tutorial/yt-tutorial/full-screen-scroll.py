from nicegui import ui

with ui.row().classes('w-screen h-screen no-wrap border-2 border-gray-300'): # Added border for visual emphasis
    with ui.scroll_area().classes('w-full h-full'):
        with ui.column().classes('w-full'):
            for i in range(100):
                ui.label(f'Line {i+1}').classes('text-lg p-2')

ui.run()