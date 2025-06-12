from nicegui import ui

# Check if both checkboxes are selected, display a warning are remove images
def update_image():
    if cb_1.value and cb_2.value:
        ui.notify("Warning: Both checkboxes selected!")
        num_image.set_source("")
    elif cb_1.value:
        num_image.set_source("1.png")
    elif cb_2.value:
        num_image.set_source("2.png")
    else:
        num_image.set_source("")
        

cb_1 = ui.checkbox("1", on_change= update_image)
cb_2 = ui.checkbox("2", on_change= update_image)


num_image = ui.image("").classes("w-48")

ui.run()