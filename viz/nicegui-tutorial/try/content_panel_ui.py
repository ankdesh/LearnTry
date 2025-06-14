from typing import Any, Dict, Callable, Optional
from nicegui import ui
from content_manager import Content, ContentManager, TextContent, CodeContent, TableContent, ImageContent

class ContentBox:
    """
    Represents a single collapsable UI box for displaying a content item.
    """
    def __init__(self, name: str, content_item: Content, on_delete: Callable[[str], None]):
        self.name = name
        self.content_item = content_item
        self.on_delete = on_delete
        self.ui_element: Optional[ui.element] = None # The specific content UI (markdown, table, image)
        self.expansion: Optional[ui.expansion] = None
        self.body_container: Optional[ui.card_section] = None
        self._build()

    def _build(self) -> None:
        """Builds the UI for this content box."""
        with ui.expansion(icon='article').classes("w-full rounded-lg shadow").props('hide-expand-icon') as self.expansion:
            self.expansion.props('header-class="bg-transparent rounded-t-lg flex items-center justify-between px-2 h-10 border-b border-gray-300 dark:border-gray-600"')
            with self.expansion.add_slot('header'):
                with ui.row().classes("w-full flex-grow items-center justify-between"):
                    ui.label(self.name).classes("font-semibold text-sm dark:text-gray-200")
                    with ui.row().classes("items-center"):
                        self.content_item.place_buttons(on_delete=lambda: self.on_delete(self.name))

            self.body_container = ui.card_section().classes("w-full bg-gray-500 dark:bg-gray-800")
            with self.body_container:
                self._render_specific_content()

    def _render_specific_content(self) -> None:
        """Renders the actual content into the body container."""
        if not self.body_container: return
        self.body_container.clear()

        with self.body_container:
            if isinstance(self.content_item, TextContent):
                self.ui_element = ui.markdown(self.content_item.render()).classes("w-full prose dark:prose-invert max-w-none text-sm")
            elif isinstance(self.content_item, CodeContent):
                self.ui_element = ui.markdown(self.content_item.render()).classes("w-full prose dark:prose-invert max-w-none text-xs")
            elif isinstance(self.content_item, TableContent):
                table_data = self.content_item.render()
                self.ui_element = ui.table(
                    columns=[{'name': col, 'label': col, 'field': col, 'align': 'left'} for col in table_data['headers']],
                    rows=[dict(zip(table_data['headers'], row_data)) for row_data in table_data['rows']]
                ).classes("w-full text-xs")
            elif isinstance(self.content_item, ImageContent):
                image_data = self.content_item.render()
                with ui.column().classes('items-center w-full'):
                    self.ui_element = ui.image(image_data['source']).props('fit=contain').classes('max-w-full md:max-w-lg rounded h-auto w-auto max-h-96')
                    if image_data['caption']:
                        ui.label(image_data['caption']).classes("text-xs text-gray-500 mt-1")
            else:
                self.ui_element = ui.label(f"Unsupported content type: {type(self.content_item)}").classes("text-red-500")

    def update_content(self, new_data: Any, stream: bool = False) -> None:
        """Updates the content within this box."""
        if isinstance(self.content_item, (TextContent, CodeContent)) and stream:
            if isinstance(self.content_item, TextContent): self.content_item.text += str(new_data)
            elif isinstance(self.content_item, CodeContent): self.content_item.code += str(new_data)
            if self.ui_element: # Should be a markdown element
                self.ui_element.content = self.content_item.render()
        else:
            if isinstance(self.content_item, TextContent): self.content_item.text = str(new_data)
            elif isinstance(self.content_item, CodeContent): self.content_item.code = str(new_data)
            # For other types or non-streaming, re-render the specific content
            self._render_specific_content()
        ui.notify(f"Content '{self.name}' updated.", type="positive")

class ContentPanelUI:
    """
    Displays a list of contents from a ContentManager, each in a collapsable box.
    """
    def __init__(self, content_manager: ContentManager):
        self.content_manager = content_manager
        self.content_boxes: Dict[str, ContentBox] = {} # To store ContentBox instances
        self._build()

    def _build(self) -> None:
        """Build the UI elements for the content panel."""
        with ui.column().classes('w-full h-full'):
            self.content_area = ui.element('div').classes('w-full space-y-2') # This div will hold all content expansion panels
            self.refresh_display()

    def refresh_display(self) -> None:
        """Refreshes the entire content display based on the ContentManager."""
        self.content_area.clear()
        self.content_boxes.clear()
        with self.content_area:
            all_content = self.content_manager.get_all_content()
            if not all_content:
                ui.label("No content to display yet.").classes("text-gray-500 p-4")
                return
            for name, content_item in all_content.items():
                self._create_content_box(name, content_item)

    def _create_content_box(self, name: str, content: Content) -> None:
        """Creates a collapsable box for a single content item."""
        # ContentBox now handles its own UI creation within the current context (self.content_area)
        content_box_instance = ContentBox(name, content, on_delete=self.delete_content_item)
        self.content_boxes[name] = content_box_instance

    def update_content_box(self, name: str, new_data: Any, stream: bool = False) -> None:
        """Updates a specific content box."""
        box_to_update = self.content_boxes.get(name)
        if not box_to_update:
            ui.notify(f"Content '{name}' not found for update.", type="warning"); return
        
        # Ensure the content item in ContentManager is also updated if ContentBox modifies it
        # This is important if ContentBox directly mutates its self.content_item
        # For now, assume ContentBox's update_content handles the UI and internal Content item.
        # If ContentBox.update_content needs to signal back to ContentManager, that's a further refinement.
        
        # The ContentManager's item should also be updated if the update logic is complex
        # or if the `new_data` is the complete new state.
        # For simplicity, let's assume `ContentBox.update_content` also updates `box_to_update.content_item`
        
        box_to_update.update_content(new_data, stream)

    def delete_content_item(self, name: str) -> None:
        """Deletes a content item and its UI box."""
        if self.content_manager.remove_content(name):
            box_to_remove = self.content_boxes.pop(name, None)
            if box_to_remove and box_to_remove.expansion and box_to_remove.expansion.parent_slot:
                box_to_remove.expansion.parent_slot.parent.remove(box_to_remove.expansion)
                # box_to_remove.expansion.delete() # Or use delete() if available and preferred
            ui.notify(f"Content '{name}' deleted.", type="positive")
        else:
            ui.notify(f"Failed to delete content '{name}'.", type="warning")

def create_content_display_panel(content_manager: ContentManager) -> ContentPanelUI:
    """Creates the right panel for displaying content."""
    with ui.card().classes('w-full h-full shadow-lg rounded-lg p-4 overflow-auto'):
        return ContentPanelUI(content_manager)