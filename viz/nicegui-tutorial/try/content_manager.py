from abc import ABC, abstractmethod
from typing import Dict, Any, List, Optional, Callable
from nicegui import ui
from collections import OrderedDict

class Content(ABC):
    """
    Base class for different types of content.
    """
    def __init__(self, name: str):
        self.name = name

    @abstractmethod
    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        """
        Creates and places the UI buttons for this content in the current NiceGUI context.
        Subclasses should implement this to define their specific buttons.
        :param on_delete: An optional callback function to be invoked when the delete button is clicked.
        """
        pass

    @abstractmethod
    def render(self) -> Any:
        """
        Abstract method to render the content.
        Subclasses should implement this to return a renderable representation
        (e.g., a string for Markdown, a NiceGUI element, etc.).
        """
        pass

class TextContent(Content):
    """
    Represents plain text or Markdown content.
    """
    def __init__(self, name: str, text: str):
        super().__init__(name)
        self.text = text

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        def _copy_text():
            ui.clipboard.write(self.text)
            ui.notify("Text copied!")
        ui.button(icon="o_content_copy", on_click=_copy_text).props("flat dense color=purple-400").tooltip("Copy text")
        ui.switch(on_change=lambda e: ui.notify(f"Text visibility toggled: {e.value}")).props("dense").tooltip("Add to context")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete, color="deep-orange-7").props("flat dense").tooltip("Delete this item")

    def render(self) -> str:
        return self.text

class CodeContent(Content):
    """
    Represents code content.
    """
    def __init__(self, name: str, code: str, language: str = "python"):
        super().__init__(name)
        self.code = code
        self.language = language

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        def _copy_code():
            ui.clipboard.write(self.code)
            ui.notify("Code copied!")

        ui.button(icon="o_code", on_click=_copy_code).props("flat dense color=purple-400").tooltip("Copy code")
        ui.button(icon="o_download", on_click=_copy_code).props("flat dense color=purple-400").tooltip("Download code")
        ui.switch(on_change=lambda e: ui.notify(f"Code visibility toggled: {e.value}")).props("dense").tooltip("Add to context")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete, color="deep-orange-7").props("flat dense").tooltip("Delete this item")
        # Example: ui.button("Download", icon="download", on_click=lambda: ui.download(content=self.code, filename=f"{self.name}.{self.language}")).props("flat dense")

    def render(self) -> str:
        # For NiceGUI, this might be rendered within a ui.markdown or a custom component
        return f"```{self.language}\n{self.code}\n```"

class TableContent(Content):
    """
    Represents tabular data.
    """
    def __init__(self, name: str, headers: List[str], rows: List[List[Any]]):
        super().__init__(name)
        self.headers = headers
        self.rows = rows

    def render(self) -> Dict[str, Any]:
        # This could be structured for ui.table or converted to Markdown
        return {"headers": self.headers, "rows": self.rows}

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        def _download_csv():
            csv_content = ",".join(self.headers) + "\n"
            for row in self.rows:
                csv_content += ",".join(map(str, row)) + "\n"
            ui.download(content=csv_content.encode(), filename=f"{self.name}.csv", media_type="text/csv")
            ui.notify("CSV download started.")
        ui.button(icon="o_download", on_click=_download_csv).props("flat dense color=purple-400").tooltip("Download table as CSV")
        ui.switch(on_change=lambda e: ui.notify(f"Table visibility toggled: {e.value}")).props("flat dense").tooltip("Add to context")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete, color="deep-orange-7").props("flat dense").tooltip("Delete this item")

class ImageContent(Content):
    """
    Represents image content.
    """
    def __init__(self, name: str, source: str, caption: str = ""):
        super().__init__(name)
        self.source = source # URL or path to the image
        self.caption = caption

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        def _download_image():
            ui.download(self.source)
            ui.notify("Image download initiated.")
        ui.button(icon="o_download", on_click=_download_image).props("flat dense color=purple-400").tooltip("Download image")
        ui.button(icon="o_image", on_click=_download_image).props("flat dense color=purple-400").tooltip("View image") # Added tooltip
        ui.switch(on_change=lambda e: ui.notify(f"Image visibility toggled: {e.value}")).props("dense").tooltip("Add to context")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete, color="deep-orange-7").props("flat dense").tooltip("Delete this item")

    def render(self) -> Dict[str, str]:
        # This could be structured for ui.image
        return {"source": self.source, "caption": self.caption}


class ContentManager:
    """
    Manages a collection of Content objects.
    """
    def __init__(self):
        self._contents: OrderedDict[str, Content] = OrderedDict()

    def add_content(self, content_item: Content) -> None:
        """
        Adds a new content item to the manager.
        If content with the same name exists, it will be overwritten.
        """
        if not isinstance(content_item, Content):
            raise TypeError("item must be an instance of Content.")
        self._contents[content_item.name] = content_item
        print(f"Content '{content_item.name}' added.") # For debugging

    def get_content(self, name: str) -> Content | None:
        """
        Retrieves a content item by its name.
        Returns None if the content is not found.
        """
        return self._contents.get(name)

    def remove_content(self, name: str) -> bool:
        """
        Removes a content item by its name.
        Returns True if the item was removed, False otherwise.
        """
        if name in self._contents:
            del self._contents[name]
            print(f"Content '{name}' removed.") # For debugging
            return True
        print(f"Content '{name}' not found for removal.") # For debugging
        return False

    def list_content_names(self) -> List[str]:
        """
        Returns a list of names of all managed content items.
        """
        return list(self._contents.keys())

    def get_all_content(self) -> Dict[str, Content]:
        """
        Returns all content items.
        """
        return self._contents.copy()