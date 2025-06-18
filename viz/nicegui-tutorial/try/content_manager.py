# content_manager.py

from abc import ABC, abstractmethod
from typing import Dict, Any, List, Optional, Callable
from nicegui import ui
from collections import OrderedDict

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

    @abstractmethod
    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        """
        Creates and places the UI action buttons for this content item.
        This method is called within the content box header.

        Args:
            on_delete (Optional[Callable[[], None]]): A callback to be invoked on deletion.
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

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        ui.button(icon="o_content_copy", on_click=lambda: ui.clipboard.write(self.text) or ui.notify("Text copied!")) \
            .props("flat dense color=purple-400").tooltip("Copy text")
        ui.chip('Selectable', selectable=True, icon='add_card', color='orange').tooltip("Add to context")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete, color="deep-orange-7").props("flat dense").tooltip("Delete this item")

    def render(self) -> str:
        return self.text

class CodeContent(Content):
    """Represents a block of code."""
    def __init__(self, name: str, code: str, language: str = "python"):
        super().__init__(name)
        self.code = code
        self.language = language

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        ui.button(icon="o_code", on_click=lambda: ui.clipboard.write(self.code) or ui.notify("Code copied!")) \
            .props("flat dense color=purple-400").tooltip("Copy code")
        ui.button(icon="o_download", on_click=lambda: ui.download(content=self.code.encode(), filename=f"{self.name}.{self.language}")) \
            .props("flat dense color=purple-400").tooltip("Download code")
        ui.chip('', selectable=True, icon='add_card', color='gray-800').props('text-color=purple-400').tooltip("Add to context")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete, color="deep-orange-7").props("flat dense").tooltip("Delete this item")

    def render(self) -> str:
        return f"```{self.language}\n{self.code}\n```"

class TableContent(Content):
    """Represents tabular data."""
    def __init__(self, name: str, headers: List[str], rows: List[List[Any]]):
        super().__init__(name)
        self.headers = headers
        self.rows = rows

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        def _download_csv():
            csv_content = ",".join(self.headers) + "\n"
            for row in self.rows:
                csv_content += ",".join(map(str, row)) + "\n"
            ui.download(content=csv_content.encode(), filename=f"{self.name}.csv", media_type="text/csv")
        
        ui.button(icon="o_download", on_click=_download_csv).props("flat dense color=purple-400").tooltip("Download table as CSV")
        ui.chip('Selectable', selectable=True, icon='add_card', color='orange').tooltip("Add to context")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete, color="deep-orange-7").props("flat dense").tooltip("Delete this item")

    def render(self) -> Dict[str, Any]:
        return {"headers": self.headers, "rows": self.rows}

class ImageContent(Content):
    """Represents image content."""
    def __init__(self, name: str, source: str, caption: str = ""):
        super().__init__(name)
        self.source = source  # URL or path to the image
        self.caption = caption

    def place_buttons(self, on_delete: Optional[Callable[[], None]] = None) -> None:
        ui.button(icon="o_download", on_click=lambda: ui.download(self.source)).props("flat dense color=purple-400").tooltip("Download image")
        ui.chip('Selectable', selectable=True, icon='add_card', color='orange').tooltip("Add to context")
        if on_delete:
            ui.button(icon="delete_outline", on_click=on_delete, color="deep-orange-7").props("flat dense").tooltip("Delete this item")

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