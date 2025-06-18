# content_panel_ui.py
from typing import Any, Dict, Callable, Optional
from nicegui import ui
from content_manager import Content, ContentManager, TextContent, CodeContent, TableContent, ImageContent

class ContentBox:
    """
    Represents a single collapsible UI box for displaying one content item
    (e.g., a piece of text, a code block, or a table).
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

        self._build()

    def _build(self) -> None:
        """Builds the UI for this content box using a NiceGUI expansion element."""
        # The main container is a `ui.expansion` which provides the collapsible behavior.
        with ui.expansion(icon='article').classes("w-full rounded-lg shadow").props('hide-expand-icon') as self.expansion:
            # --- Custom Header ---
            # We use the 'header' slot to create a custom layout with a title and action buttons.
            self.expansion.props('header-class="bg-transparent rounded-t-lg flex items-center justify-between px-2 h-10 border-b border-gray-300 dark:border-gray-600"')
            with self.expansion.add_slot('header'):
                with ui.row().classes("w-full flex-grow items-center justify-between"):
                    # Content title on the left.
                    ui.label(self.name).classes("font-semibold text-sm dark:text-gray-200")
                    
                    # Action buttons on the right.
                    with ui.row().classes("items-center"):
                        # Delegate button creation to the content item itself.
                        self.content_item.place_buttons(on_delete=lambda: self.on_delete(self.name))

            # --- Content Body ---
            # The body is a card section that will hold the rendered content.
            self.body_container = ui.card_section().classes("w-full bg-gray-500 dark:bg-gray-800 p-2")
            with self.body_container:
                self._render_specific_content()

    def _render_specific_content(self) -> None:
        """Renders the actual content (text, code, table, etc.) into the body container."""
        if not self.body_container:
            return
        
        self.body_container.clear()
        content_item = self.content_item

        with self.body_container:
            if isinstance(content_item, TextContent):
                # Apply scrolling and max-height to the markdown container for text
                with ui.element('div').style('max-height: 600px; overflow-y: auto;'):
                    ui.markdown(content_item.render()).classes("w-full prose dark:prose-invert max-w-none text-sm")
            elif isinstance(content_item, CodeContent):
                # Apply scrolling and max-height to the markdown container for code
                with ui.element('div').style('max-height: 600px; overflow-y: auto;'):
                    ui.markdown(content_item.render()).classes("w-full prose dark:prose-invert max-w-none text-xs")
            elif isinstance(content_item, TableContent):
                table_data = content_item.render()
                # Table itself can be scrollable if it overflows its container
                with ui.element('div').style('max-height: 600px; overflow-y: auto;'):
                    ui.table(
                        columns=[{'name': col, 'label': col, 'field': col, 'align': 'left'} for col in table_data['headers']],
                        rows=[dict(zip(table_data['headers'], row_data)) for row_data in table_data['rows']]
                    ).classes("w-full text-xs")
            elif isinstance(content_item, ImageContent):
                image_data = content_item.render()
                # Image container with max-height for very tall images
                with ui.column().classes('items-center w-full').style('max-height: 600px; overflow-y: auto;'):
                    ui.image(image_data['source']).props('fit=contain').classes('max-w-full md:max-w-lg rounded h-auto w-auto max-h-96')
                    if image_data['caption']:
                        ui.label(image_data['caption']).classes("text-xs text-gray-500 mt-1")
            else:
                ui.label(f"Unsupported content type: {type(content_item)}").classes("text-red-500")

    def update_content(self, new_data: Any, stream: bool = False) -> None:
        """
        Updates the content within this box. Re-renders the content area.
        """
        self.expansion.value = True

        content_item = self.content_item

        if isinstance(content_item, TextContent):
            content_item.text = f"{content_item.text}{new_data}" if stream else new_data
        elif isinstance(content_item, CodeContent):
            content_item.code = f"{content_item.code}{new_data}" if stream else new_data
        elif isinstance(content_item, ImageContent):
            if not stream and isinstance(new_data, dict):
                content_item.source = new_data.get('source', content_item.source)
                content_item.caption = new_data.get('caption', content_item.caption)
        # For TableContent, if new_data is a full replacement (e.g., new headers/rows)
        # it would be handled here, then re-rendered.

        self._render_specific_content() # Re-render the content area


class ContentPanelUI:
    """
    Displays a list of contents from a ContentManager, each in its own collapsible ContentBox.
    """
    def __init__(self, content_manager: ContentManager):
        self.content_manager = content_manager
        self.content_boxes: Dict[str, ContentBox] = {}  # Stores ContentBox instances by name
        self.content_area: Optional[ui.element] = None
        self.scrollable_card_element: Optional[ui.card] = None # To store reference to the scrollable card
        self._build()

    def _build(self) -> None:
        """Builds the main container for all content boxes."""
        # A column to hold all the content expansion panels.
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
            
            # Create a ContentBox for each item in the manager.
            for name, content_item in all_content.items():
                self.content_boxes[name] = ContentBox(name, content_item, on_delete=self.delete_content_item)

    def update_content_box(self, name: str, new_data: Any, stream: bool = False) -> None:
        """Finds and updates a specific content box."""
        box_to_update = self.content_boxes.get(name)
        if box_to_update:
            box_to_update.update_content(new_data, stream) # This will also expand it
 
        else:
            ui.notify(f"Content '{name}' not found for update.", type="warning")

    def delete_content_item(self, name: str) -> None:
        """Deletes a content item from the manager and its corresponding UI box."""
        if self.content_manager.remove_content(name):
            # After removing from the data manager, refresh the whole display.
            # This is simpler and more robust than trying to surgically remove one element.
            self.refresh_display()
            ui.notify(f"Content '{name}' deleted.", type="positive")
        else:
            ui.notify(f"Failed to delete content '{name}'.", type="warning")


def create_content_display_panel(content_manager: ContentManager) -> ContentPanelUI:
    """Factory function to create the right panel for displaying content."""
    # The parent card handles the overall look and scrolling for the entire panel.    
    with ui.card().classes('w-full h-full shadow-lg rounded-lg p-0 overflow-auto') as scrollable_card:
        panel_ui = ContentPanelUI(content_manager)
        # panel_ui.scrollable_card_element = scrollable_card # Store reference if needed for more complex scrolling, not strictly necessary for scrollIntoView on child
        return panel_ui