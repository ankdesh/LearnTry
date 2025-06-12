from nicegui import ui

ui.label("2-textelement")

ui.link("Ankur's Google scholar homepage",
        "https://scholar.google.com/citations?user=K0U8JcUAAAAJ&hl=en")

ui.chat_message("Hello from Ankur", name = "Ankur", stamp = "now")
ui.chat_message("Hello from Agent", name = "Agent", stamp = "now")

ui.markdown(" ### This is Markdown !! ")

ui.mermaid("""
graph TD
    A-->B
    A-->C
    B-->D
    C-->D
""")

ui.html("<head> This is <strong> HTML </strong> </head>")


ui.run()