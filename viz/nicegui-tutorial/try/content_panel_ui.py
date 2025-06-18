# content_panel_ui.py
from typing import Any, Dict, Callable, Optional
from nicegui import ui
from content_manager import Content, ContentManager, TextContent, CodeContent, TableContent, ImageContent

class ContentBox:
    """
    Represents a single collapsible UI box for displaying one content item.
    This version is designed for displaying read-only content and supports auto-scrolling for streaming updates.
    """
    def __init__(self, name: str, content_item: Content, on_delete: Callable[[str], None]):
        """
        Args:
            name (str): The unique name/identifier for the content.
            content_item (Content): The data object for the content.
            on_delete (Callable[[str], None]): Callback function to invoke when the delete button is clicked.
        """
        self.name = name
        self.content_item = content_item
        self.on_delete = on_delete

        # --- NEW: References to UI elements for dynamic updates ---
        self.scroll_area: Optional[ui.scroll_area] = None
        self.content_element: Optional[ui.element] = None
        # For images, which have multiple parts
        self.image_element: Optional[ui.image] = None
        self.caption_element: Optional[ui.label] = None
        
        self._build()

    def _build(self) -> None:
        """Builds the static UI structure for this content box."""
        with ui.expansion(icon='article').classes("w-full rounded-lg shadow").props('hide-expand-icon') as self.expansion:
            # Header with title and action buttons
            self.expansion.props('header-class="bg-transparent rounded-t-lg flex items-center justify-between px-2 h-10 border-b border-gray-300 dark:border-gray-600"')
            with self.expansion.add_slot('header'):
                with ui.row().classes("w-full flex-grow items-center justify-between"):
                    ui.label(self.name).classes("font-semibold text-sm dark:text-gray-200")
                    with ui.row().classes("items-center"):
                        self.content_item.place_buttons(on_delete=lambda: self.on_delete(self.name))

            # Content Body - created once
            body_container = ui.card_section().classes("w-full bg-gray-500 dark:bg-gray-800 p-2")
            with body_container:
                # This method now creates the elements instead of re-rendering them
                self._create_content_display()

    def _create_content_display(self) -> None:
        """
        Creates the specific content display elements (markdown, table, etc.) just once.
        """
        content_item = self.content_item
        
        # Use a scroll_area for all content types to handle overflow and enable programmatic scrolling
        self.scroll_area = ui.scroll_area().style('height: 600px;')

        with self.scroll_area:
            if isinstance(content_item, (TextContent, CodeContent)):
                # For text and code, the content element is a markdown renderer
                self.content_element = ui.markdown(content_item.render()).classes("w-full prose dark:prose-invert max-w-none text-xs")
            
            elif isinstance(content_item, TableContent):
                table_data = content_item.render()
                # For tables, the content element is the table itself
                self.content_element = ui.table(
                    columns=[{'name': col, 'label': col, 'field': col, 'align': 'left'} for col in table_data['headers']],
                    rows=[dict(zip(table_data['headers'], row_data)) for row_data in table_data['rows']]
                ).classes("w-full text-xs")

            elif isinstance(content_item, ImageContent):
                image_data = content_item.render()
                # For images, we build a column containing the image and caption
                with ui.column().classes('items-center w-full'):
                    self.image_element = ui.image(image_data['source']).props('fit=contain').classes('max-w-full md:max-w-lg rounded h-auto w-auto max-h-96')
                    self.caption_element = ui.label(image_data['caption']).classes("text-xs text-gray-500 mt-1")
            else:
                self.content_element = ui.label(f"Unsupported content type: {type(content_item)}").classes("text-red-500")

    def update_content(self, new_data: Any, stream: bool = False) -> None:
        """
        Updates the content within this box by modifying the existing UI elements.
        This method now handles the auto-scrolling.
        """
        self.expansion.value = True # Ensure the box is open to see the update
        content_item = self.content_item

        # Update the data model first
        if isinstance(content_item, TextContent):
            content_item.text = f"{content_item.text}{new_data}" if stream else new_data
        elif isinstance(content_item, CodeContent):
            content_item.code = f"{content_item.code}{new_data}" if stream else new_data
        elif isinstance(content_item, ImageContent) and isinstance(new_data, dict):
            content_item.source = new_data.get('source', content_item.source)
            content_item.caption = new_data.get('caption', content_item.caption)
        
        # Now, update the UI elements with the new data
        if isinstance(content_item, (TextContent, CodeContent)) and self.content_element:
            self.content_element.set_content(content_item.render())
        
        elif isinstance(content_item, ImageContent):
            if self.image_element: self.image_element.set_source(content_item.source)
            if self.caption_element: self.caption_element.set_text(content_item.caption)

        # Finally, scroll to the bottom of the content area
        if self.scroll_area:
            self.scroll_area.scroll_to(percent=1.0)


class ContentPanelUI:
    """
    Displays a list of contents from a ContentManager, each in its own collapsible ContentBox.
    """
    def __init__(self, content_manager: ContentManager):
        self.content_manager = content_manager
        self.content_boxes: Dict[str, ContentBox] = {}
        self.content_area: Optional[ui.element] = None
        self._build()

    def _build(self) -> None:
        """Builds the main container for all content boxes."""
        with ui.column().classes('w-full h-full'):
            self.content_area = ui.element('div').classes('w-full space-y-2 p-4')
            self.refresh_display()

    def refresh_display(self) -> None:
        """Clears and rebuilds the entire content display from the ContentManager."""
        if not self.content_area:
            return
            
        self.content_area.clear()
        self.content_boxes.clear()
        with self.content_area:
            all_content = self.content_manager.get_all_content()
            if not all_content:
                ui.label("No content to display yet.").classes("text-gray-500 p-4")
                return
            
            for name, content_item in all_content.items():
                self.content_boxes[name] = ContentBox(name, content_item, on_delete=self.delete_content_item)

    def update_content_box(self, name: str, new_data: Any, stream: bool = False) -> None:
        """Finds and updates a specific content box."""
        box_to_update = self.content_boxes.get(name)
        if box_to_update:
            box_to_update.update_content(new_data, stream)
        else:
            ui.notify(f"Content '{name}' not found for update.", type="warning")

    def delete_content_item(self, name: str) -> None:
        """Deletes a content item from the manager and its corresponding UI box."""
        if self.content_manager.remove_content(name):
            self.refresh_display()
            ui.notify(f"Content '{name}' deleted.", type="positive")
        else:
            ui.notify(f"Failed to delete content '{name}'.", type="warning")


def create_content_display_panel(content_manager: ContentManager) -> ContentPanelUI:
    """Factory function to create the right panel for displaying content."""
    with ui.card().classes('w-full h-full shadow-lg rounded-lg p-0 overflow-auto'):
        panel_ui = ContentPanelUI(content_manager)
        return panel_ui