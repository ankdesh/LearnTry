from nicegui import ui

label = ui.label('Ankdesh')

toggle_text = ui.toggle(['text-1', 'text-2', 'text-3'], value='text-2',
                        on_change=lambda e: label.set_text("You chose: " + e.value))


ui.image("/home/ankdesh/Downloads/ChatGPT.png").classes('w-64')


ui.run()