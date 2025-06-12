from nicegui import ui

ui.button("click me", color='red',
          on_click=lambda: ui.label("Clicked"))


ui.button("Link", on_click=lambda: ui.link(
    "link", "https://scholar.google.com/"))

with ui.button("click me", on_click= lambda: badge.set_text( int(badge.text) + 1)):
    badge = ui.badge("0", color='blue').props('floating')

ui.run()
