from nicegui import ui, native



def update():
    rows.append({'name': name.value, 'age': age.value})
    table.update()
    name.value = ""
    age.value = ""


card = ui.card()

with card:
    with ui.row():
        name = ui.input("Name")
        age = ui.input("Age")
    save = ui.button("Save", on_click= update)



columns = [
    {'label': 'Name', 'field': 'name'},
    {'label': 'Age', 'field': 'age'},
]

rows = [
    {'name': 'Alice', 'age': 18},
    {'name': 'Bob', 'age': 21},
    {'name': 'Carol', 'age': 42},
    {'name': 'Dave', 'age': 31},
] 

table = ui.table(columns=columns, rows=rows)


ui.run(native=True, reload=False, port=native.find_open_port())