# header_sidebar_ui.py

from nicegui import ui
from typing import Dict, List
from config_manager import ConfigManager

class Sidebar:
    """
    Manages the state and UI of the collapsible left sidebar.
    This class holds references to the agent checkboxes to query their state.
    """
    def __init__(self):
        self.agent_checkboxes: Dict[str, ui.checkbox] = {}
        self._build()

    def _build(self) -> None:
        """Builds the sidebar UI components."""
        with ui.left_drawer(value=False).classes('bg-gray-100 dark:bg-gray-800 p-4') as self.drawer:
            # Sidebar title
            ui.label('Navigation').classes('text-lg font-semibold mb-2')

            # Navigation buttons
            ui.button('Settings', icon='settings', on_click=lambda: ui.notify("Settings clicked!")) \
                .props('flat color=primary').classes('w-full text-left')

            config_manager = ConfigManager()

            # Display agents from config
            ui.separator()
            ui.label('Agents').classes('text-lg font-semibold mt-4 mb-2')
            agents = config_manager.get("Agents", {})
            if agents:
                for agent_name in agents.keys():
                    with ui.row().classes('items-center w-full justify-between'):
                        ui.label(agent_name).classes('text-sm')
                        # Store the checkbox in the dictionary, keyed by agent name
                        self.agent_checkboxes[agent_name] = ui.checkbox().props('dense')
            else:
                ui.label("No agents configured.").classes('text-sm text-gray-500')

    def get_selected_agents(self) -> List[str]:
        """Returns a list of agent names that are currently selected (checked)."""
        return [name for name, checkbox in self.agent_checkboxes.items() if checkbox.value]

    def toggle(self) -> None:
        """Toggles the visibility of the sidebar drawer."""
        self.drawer.toggle()

def create_collapsible_sidebar() -> Sidebar:
    """
    Factory function to create and return an instance of the Sidebar.
    """
    return Sidebar()