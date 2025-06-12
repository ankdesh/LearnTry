from nicegui import ui, events

name = ui.input("Name")
age = ui.input("Age")

save_button = ui.button("Save", icon="save",color="green" , on_click= lambda:save())

dict_list = []

def save():
    new_dict = {'id': name.value, 'age': age.value}
    dict_list.append(new_dict)
    tree.update()
    name.value = ""
    age.value = ""



# tree = ui.tree(
#     [
#         {'id': 'Topic', 'Name' : 'Name', 'children': [dict_list]}
#     ]
# )

# tree.add_slot('default-header', 'name')
#tree.add_slot('default-body', 'Age')

tree = ui.tree(
    [
        {'id':'Top', 'children': dict_list}
    ], label_key='id', on_select=lambda e: ui.notify(e.value)
)


tree.add_slot('default-header', '''
    <span :props="props"><strong>{{ props.node.id }}</strong></span>
''')
tree.add_slot('default-body', '''
    <span :props="props">Age: "{{ props.node.age }}"</span>
''')


# ui.tree([
#     {'id': 'numbers', 'children': [{'id': '1'}, {'id': '2'}]},
#     {'id': 'letters', 'children': [{'id': 'A'}, {'id': 'B'}]},
# ], label_key='id', on_select=lambda e: ui.notify(e.value))

ui.run()