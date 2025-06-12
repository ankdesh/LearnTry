from nicegui import ui, events

name = ui.input("Name")
age = ui.input("Age")


def update():
    rows.append({'name': name.value, 'age': age.value})
    table.update()
    name.value = ""
    age.value = ""

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





ui.run()