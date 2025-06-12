from nicegui import ui

ui.label("One")


toggle_image_size = ui.radio(["small", "large"],
                              on_change= lambda : ui.label("Two"))

ui.run()