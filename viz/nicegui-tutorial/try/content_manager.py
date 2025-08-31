# content_manager.py

from abc import ABC, abstractmethod
from typing import Dict, Any, List, Optional, Callable, Tuple
from nicegui import ui
from collections import OrderedDict
import httpx
import os
import mimetypes

# --- Module-level Constants ---

LANGUAGE_TO_EXTENSION: Dict[str, str] = {
    "python": ".py",
    "javascript": ".js",
    "html": ".html",
    "css": ".css",
    "json": ".json",
    "text": ".txt",
    "markdown": ".md",
}

# --- Abstract Base Class for Content ---


class Content(ABC):
    """
    Abstract base class for all types of content that can be displayed.
    Each content type must have a name and define how it renders and what
    action buttons it provides.
    """

    def __init__(self, name: str):
        """
        Args:
            name (str): The unique name for this piece of content.
        """
        self.name = name
        self.is_modified: bool = False

    @abstractmethod
    def place_buttons(self,
                      on_delete: Optional[Callable[[], None]] = None,
                      on_edit: Optional[Callable[[], None]] = None) -> None:
        """
        Creates and places the UI action buttons for this content item.
        This method is called within the content box header.

        Args:
            on_delete (Optional[Callable[[], None]]): A callback to be invoked on deletion.
            on_edit (Optional[Callable[[], None]]): A callback to be invoked for editing.
        """
        pass

    @abstractmethod
    def edit_ui(self, refresh_ui_callback: Callable[[], None]) -> None:
        """
        Creates and shows a dialog for editing the content.
        The dialog should call refresh_ui_callback after changes are saved.
        """
        pass

    @abstractmethod
    def render(self) -> Any:
        """
        Returns a renderable representation of the content.
        This could be a string (for Markdown) or a dictionary (for tables/images).
        """
        pass

# --- Concrete Content Implementations ---


class TextContent(Content):
    """Represents plain text or Markdown content."""

    def __init__(self, name: str, text: str):
        super().__init__(name)
        self.text = text

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None, on_edit: Optional[Callable[[], None]] = None) -> None:
        ui.button(icon="o_content_copy", on_click=lambda: ui.clipboard.write(self.text) or ui.notify("Text copied!")) \
            .props("flat dense color=purple-400").tooltip("Copy text")
        ui.chip('', selectable=True, icon='add_card',
                color='gray-800').props('text-color=purple-400').tooltip("Add to context")
        if on_edit:
            ui.button(icon="o_edit", on_click=on_edit).props(
                "flat dense color=blue-400").tooltip("Edit text")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete,
                      color="deep-orange-7").props("flat dense").tooltip("Delete this item")

    def edit_ui(self, refresh_ui_callback: Callable[[], None]) -> None:
        with ui.dialog() as dialog, ui.card().style('min-width: 600px; max-width: 80vw;'):
            with ui.row().classes("w-full items-center justify-between p-3 border-b dark:border-gray-700"):
                ui.label(f"Edit: {self.name}").classes("text-lg font-semibold")
                with ui.row().classes("gap-2"):
                    def save_changes():
                        self.text = text_area.value
                        self.is_modified = True
                        refresh_ui_callback()
                        dialog.close()
                        ui.notify(f"'{self.name}' updated.", type="positive")
                    ui.button("Save", on_click=save_changes, color="positive")
                    ui.button("Cancel", on_click=dialog.close,
                              color="grey").props("flat")

            with ui.card_section().classes("p-0 w-full"):  # Ensure card section itself tries to be full width
                text_area = ui.textarea(label="Content", value=self.text).props(
                    "w-full outlined autogrow min-lines=10").style("min-height: 300px;")
        dialog.open()

    def render(self) -> str:
        return self.text


class CodeContent(Content):
    """Represents a block of code."""

    def __init__(self, name: str, code: str, language: str = "python"):
        super().__init__(name)
        self.code = code
        self.language = language

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None, on_edit: Optional[Callable[[], None]] = None) -> None:
        def _download_code():
            lang_lower = self.language.lower() if self.language else ""
            ext = LANGUAGE_TO_EXTENSION.get(
                lang_lower, f".{lang_lower}" if lang_lower else ".txt")
            file_name = f"{self.name}{ext}"
            ui.download(self.code.encode(), filename=file_name)

        ui.button(icon="play_arrow", on_click=lambda: ui.notify("Executing code... (not implemented)")).props(
            "flat dense color=green-400").tooltip("Execute code")
        ui.button(icon="o_code", on_click=lambda: ui.clipboard.write(self.code) or ui.notify("Code copied!")) \
            .props("flat dense color=purple-400").tooltip("Copy code")
        ui.button(icon="o_download", on_click=_download_code).props(
            "flat dense color=purple-400").tooltip("Download code")
        ui.chip('', selectable=True, icon='add_card',
                color='gray-800').props('text-color=purple-400').tooltip("Add to context")
        if on_edit:
            ui.button(icon="o_edit", on_click=on_edit).props(
                "flat dense color=blue-400").tooltip("Edit code")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete,
                      color="deep-orange-7").props("flat dense").tooltip("Delete this item")

    def edit_ui(self, refresh_ui_callback: Callable[[], None]) -> None:
        with ui.dialog() as dialog, ui.card().style('min-width: 700px; max-width: 80vw;'):
            with ui.row().classes("w-full items-center justify-between p-3 border-b dark:border-gray-700"):
                ui.label(f"Edit Code: {self.name} ({self.language})").classes(
                    "text-lg font-semibold")
                with ui.row().classes("gap-2"):
                    def save_changes():
                        self.code = code_area.value
                        self.is_modified = True
                        refresh_ui_callback()
                        dialog.close()
                        ui.notify(f"'{self.name}' updated.", type="positive")
                    ui.button("Save", on_click=save_changes, color="positive")
                    ui.button("Cancel", on_click=dialog.close,
                              color="grey").props("flat")

            with ui.card_section().classes("p-0 w-full"):  # Ensure card section itself tries to be full width
                code_area = ui.textarea(label="Code", value=self.code).props(
                    "w-full outlined autogrow").style("min-height: 400px; font-family: monospace;")
        dialog.open()

    def render(self) -> str:
        return f"```{self.language}\n{self.code}\n```"


class TableContent(Content):
    """Represents tabular data."""

    def __init__(self, name: str, headers: List[str], rows: List[List[Any]]):
        super().__init__(name)
        self.headers = headers
        self.rows = rows

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None, on_edit: Optional[Callable[[], None]] = None) -> None:
        def _download_csv():
            csv_content = ",".join(self.headers) + "\n"
            for row in self.rows:
                csv_content += ",".join(map(str, row)) + "\n"
            ui.download(csv_content.encode(),
                        filename=f"{self.name}.csv", media_type="text/csv")

        ui.button(icon="o_download", on_click=_download_csv).props(
            "flat dense color=purple-400").tooltip("Download table as CSV")
        ui.chip('', selectable=True, icon='add_card',
                color='gray-800').props('text-color=purple-400').tooltip("Add to context")
        if on_edit:
            # Placeholder: Table editing can be complex.
            ui.button(icon="o_edit", on_click=on_edit).props(
                "flat dense color=blue-400").tooltip("Edit table (not fully implemented)")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete,
                      color="deep-orange-7").props("flat dense").tooltip("Delete this item")

    def edit_ui(self, refresh_ui_callback: Callable[[], None]) -> None:
        ui.notify("Full editing for TableContent is not yet implemented. Basic refresh will occur if data changes externally.", type="info")
        # For a real implementation, you might edit self.headers/self.rows and then call refresh_ui_callback.

    def render(self) -> Dict[str, Any]:
        return {"headers": self.headers, "rows": self.rows}


class ImageContent(Content):
    """Represents image content."""

    def __init__(self, name: str, source: str, caption: str = ""):
        super().__init__(name)
        self.source = source  # URL or path to the image
        self.caption = caption

    async def _trigger_download(self):
        """Handles the download logic for the image."""
        base_filename = self.name
        source_url_path = self.source
        final_ext = ""

        # Try to get extension from the source string itself
        _, ext_from_source = os.path.splitext(source_url_path)
        known_image_extensions = ['.jpg', '.jpeg',
                                  '.png', '.gif', '.bmp', '.webp', '.svg']

        if ext_from_source.lower() in known_image_extensions:
            final_ext = ext_from_source

        if source_url_path.startswith(('http://', 'https://')):
            try:
                async with httpx.AsyncClient() as client:
                    response = await client.get(source_url_path, follow_redirects=True)
                    response.raise_for_status()

                image_bytes = response.content
                content_type = response.headers.get('content-type')

                if not final_ext and content_type:  # If URL had no extension, try Content-Type
                    guessed_ext = mimetypes.guess_extension(content_type)
                    if guessed_ext and guessed_ext.lower() in known_image_extensions:
                        final_ext = guessed_ext

                if not final_ext:  # Fallback extension if still unknown
                    final_ext = ".png"  # Default to .png if type is truly unknown
                    ui.notify(
                        "Could not determine image type, defaulting to .png extension.", type="warning")

                filename_to_use = f"{base_filename}{final_ext}"
                media_type_to_use = content_type if content_type else 'application/octet-stream'

                ui.download(image_bytes, filename=filename_to_use,
                            media_type=media_type_to_use)
                ui.notify(
                    f"Downloading '{filename_to_use}'...", type="positive")

            except httpx.HTTPStatusError as e:
                ui.notify(
                    f"Error fetching image ({e.response.status_code}): {e.request.url}", type="negative")
            except httpx.RequestError as e:
                ui.notify(
                    f"Network error fetching image: {e.request.url}", type="negative")
            except Exception as e:
                ui.notify(
                    f"An unexpected error occurred during image download: {str(e)}", type="negative")
        else:
            # Assume local path accessible by NiceGUI
            if not final_ext:
                final_ext = ".png"  # Default for local files if no extension
                ui.notify(
                    "Local image path has no extension, assuming .png.", type="warning")
            filename_to_use = f"{base_filename}{final_ext}"
            ui.download(src=source_url_path, filename=filename_to_use)
            ui.notify(
                f"Preparing download for '{filename_to_use}'...", type="positive")

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None, on_edit: Optional[Callable[[], None]] = None) -> None:
        ui.button(icon="o_download", on_click=self._trigger_download).props(
            "flat dense color=purple-400").tooltip("Download image")
        ui.chip('', selectable=True, icon='add_card',
                color='gray-800').props('text-color=purple-400').tooltip("Add to context")
        if on_edit:
            ui.button(icon="o_edit", on_click=on_edit).props(
                "flat dense color=blue-400").tooltip("Edit image details")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete,
                      color="deep-orange-7").props("flat dense").tooltip("Delete this item")

    def edit_ui(self, refresh_ui_callback: Callable[[], None]) -> None:
        with ui.dialog() as dialog, ui.card().style('min-width: 500px; max-width: 80vw;'):
            ui.label(f"Edit Image Details: {self.name}").classes(
                "text-lg font-semibold mb-2")
            source_input = ui.input(
                label="Image Source (URL/Path)", value=self.source).props("w-full outlined")
            caption_input = ui.textarea(label="Caption", value=self.caption).props(
                "w-full outlined autogrow")

            with ui.row().classes("w-full justify-end mt-4 gap-2"):
                ui.button("Cancel", on_click=dialog.close,
                          color="grey").props("flat")

                def save_changes():
                    self.source = source_input.value
                    self.caption = caption_input.value
                    self.is_modified = True
                    refresh_ui_callback()
                    dialog.close()
                    ui.notify(f"'{self.name}' updated.", type="positive")
                ui.button("Save", on_click=save_changes, color="positive")
        dialog.open()

    def render(self) -> Dict[str, str]:
        return {"source": self.source, "caption": self.caption}

# --- Content Manager ---


class ContentManager:
    """
    Manages a collection of Content objects in an ordered dictionary.
    This class handles the data layer, completely separate from the UI.
    """

    def __init__(self):
        self._contents: OrderedDict[str, Content] = OrderedDict()

    def add_content(self, content_item: Content) -> None:
        """Adds a new content item, overwriting if the name exists."""
        if not isinstance(content_item, Content):
            raise TypeError("item must be an instance of Content.")
        self._contents[content_item.name] = content_item

    def get_content(self, name: str) -> Optional[Content]:
        """Retrieves a content item by its name."""
        return self._contents.get(name)

    def remove_content(self, name: str) -> bool:
        """Removes a content item by name. Returns True if successful."""
        if name in self._contents:
            del self._contents[name]
            return True
        return False

    def get_all_content(self) -> Dict[str, Content]:
        """Returns a copy of all managed content items."""
        return self._contents.copy()
