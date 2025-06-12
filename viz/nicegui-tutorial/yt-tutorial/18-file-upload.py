from nicegui import ui, events

def uploads(e:events.UploadEventArguments):
    text = e.content.read().decode("utf-8")
    markdown.set_content(text)

markdown = ui.markdown("Choose a file to upload",)

ui.upload(on_upload=uploads, on_rejected=lambda: ui.notify("File rejected"))

ui.run()