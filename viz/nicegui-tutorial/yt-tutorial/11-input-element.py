
from nicegui import ui
import multiprocessing
multiprocessing.set_start_method("spawn", force=True)


file_input = ui.input(label= "File Name", placeholder="Enter a File name")

ui.button("Show", on_click= lambda: image.set_source(f"{file_input.value}"))

image = ui.image("").classes("w-48")

ui.run(native=True)