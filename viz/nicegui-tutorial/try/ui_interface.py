# ui_manager.py

from typing import Any, Optional
from content_manager import Content
from chat_ui import ChatPanelUI
from content_panel_ui import ContentPanelUI as ContentDisplayPanel

class UIInterface:
    """
    Acts as a central controller for all UI interactions.

    This class provides a clean and simple interface for the application's backend
    logic to communicate with the UI components, such as the chat panel and the
    content display panel. It decouples the business logic from the UI implementation.
    """

    def __init__(self, chat_panel: ChatPanelUI, content_panel: ContentDisplayPanel):
        """
        Initializes the UIManager.

        Args:
            chat_panel (ChatPanelUI): An instance of the chat panel UI.
            content_panel (ContentDisplayPanel): An instance of the content display panel UI.
        """
        if not isinstance(chat_panel, ChatPanelUI):
            raise TypeError("chat_panel must be an instance of ChatPanelUI")
        if not isinstance(content_panel, ContentDisplayPanel):
            raise TypeError("content_panel must be an instance of ContentDisplayPanel")
            
        self.chat_panel = chat_panel
        self.content_panel = content_panel

    # --- Chat Panel Interface ---

    def add_chat_message(self, header: str, text: str) -> None:
        """
        Adds a complete, non-streaming message to the chat panel.

        Args:
            header (str): The header for the message (e.g., "AI", "User").
            text (str): The full content of the message.
        """
        self.chat_panel.add_message(header, text)

    def stream_to_chat(self, header: str, token: str) -> None:
        """
        Streams a token to the chat panel.

        If the header is the same as the last message, the token is appended.
        If the header is different, a new message box is created.

        This fulfills the request for an API to send messages one token at a time
        in the format: {"header": header_name, "token": word}.

        Args:
            header (str): The header for the message.
            token (str): The word or chunk of text to be streamed.
        """
        self.chat_panel.stream_message_chunk(header, token)

    # --- Content Panel Interface ---

    def add_content(self, content_item: Content) -> None:
        """
        Adds a new content item to the right-hand content panel.

        Args:
            content_item (Content): The content object (e.g., TextContent, CodeContent) to add.
        """
        self.content_panel.content_manager.add_content(content_item)
        self.content_panel.refresh_display()

    def remove_content(self, name: str) -> None:
        """
        Removes a content item from the panel by its unique name.

        Args:
            name (str): The name of the content item to remove.
        """
        # The UI deletion logic is handled within the ContentPanelUI itself
        # when its on_delete callback is triggered. This method provides an
        # external way to trigger that same removal process.
        self.content_panel.delete_content_item(name)

    def update_content(self, name: str, new_data: Any, stream: bool = False) -> None:
        """
        Updates an existing content item in the panel.

        Args:
            name (str): The name of the content item to update.
            new_data (Any): The new data for the content.
            stream (bool): If True, appends the data (for text/code). Defaults to False.
        """
        self.content_panel.update_content_box(name, new_data, stream)

    def get_content(self, name: str) -> Optional[Content]:
        """
        Retrieves a content item from the content manager.

        Args:
            name (str): The name of the content item to retrieve.

        Returns:
            Optional[Content]: The content object if found, otherwise None.
        """
        return self.content_panel.content_manager.get_content(name)