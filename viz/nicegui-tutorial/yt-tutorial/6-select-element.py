from nicegui import ui

nums = ["1","2"]

select_nums = ui.select(nums, 
                        on_change= lambda: num_image.set_source(f"{select_nums.value}.png"))

num_image = ui.image("").classes("w-48")

ui.run()