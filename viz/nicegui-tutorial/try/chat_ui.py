# chat_ui.py

from typing import Optional, List
from datetime import datetime
from nicegui import ui
from nicegui.events import UploadEventArguments
from pathlib import Path
import io
import mimetypes

from file_handlers import FileHandlerFactory
from local_file_picker_ui import LocalFilePicker  # Import from the new file

# Forward declarations for type hinting to avoid circular imports
if False:
    from ui_interface import UIInterface
    from header_sidebar_ui import Sidebar


class ChatBox:
    """
    A class-based component for creating the chat input box at the bottom of the chat panel.
    """

    def __init__(self,
                 chat_panel_ui: 'ChatPanelUI'):  # Pass the parent panel instance
        self.chat_panel_ui = chat_panel_ui  # Store reference to the parent panel
        self._build()

    def _build(self):
        """Builds the chat input area UI."""
        # A card with no shadow or rounding to blend seamlessly into the parent panel.
        with ui.card().classes('w-full shadow-none rounded-none'):
            with ui.column().classes('w-full gap-0'):
                # The text area for user input. 'autogrow' is essential for a good UX.
                self.text_area = ui.textarea(placeholder='Type your message...') \
                    .classes('w-full text-sm')
                self.text_area.on('keydown', self._handle_keydown, throttle=0.05, leading_events=True,
                                  trailing_events=False).props('filled autogrow input-class="h-auto"')

                # A row for action buttons and the main send button.
                with ui.row().classes('w-full items-center justify-between p-2'):
                    # Left-aligned custom action button (File picker).
                    with ui.row().classes('items-center'):  # Container for left-aligned items
                        # Button to open the local file picker dialog
                        self.file_picker_button = ui.button(icon='attach_file', on_click=self._open_file_picker) \
                            .props('flat round dense').tooltip("Attach file")

                    # Right-aligned main send button.
                    self.send_button = ui.button(icon='send', on_click=self._handle_main_submit) \
                        .props('flat round dense')

    async def _handle_main_submit(self) -> None:
        """Handles the click event of the main send button."""

        message = self.text_area.value
        if not message:
            ui.notify('Cannot send an empty message.', type='warning')
            return

        # Call the provided async submit handler.
        await self.chat_panel_ui._handle_user_submission(message)
        # Clear the input field after submission.
        self.text_area.value = ''
        # Refocus for quick follow-up messages.
        self.text_area.run_method('focus')

    async def _handle_on_upload_event(self, e: UploadEventArguments) -> None:
        """Internal handler for ui.upload's on_upload event, calls the provided callback."""
        # This method is no longer used as ui.upload is removed.
        pass

    async def _handle_keydown(self, event: any) -> None:
        """
        Handles keydown events on the textarea.
        Specifically, submits the message if Shift+Enter is pressed.
        """
        # The event object from NiceGUI's on('keydown') is a dictionary-like object.
        if event.args['key'] == 'Enter' and event.args['shiftKey']:
            # Prevent default Enter behavior (adding a newline)
            # event.sender.run_method('preventDefault')
            await self._handle_main_submit()

    async def _open_file_picker(self) -> None:
        """
        Opens the local file picker dialog.
        The LocalFilePicker allows selecting files from the server's filesystem.
        """
        # Start in the user's home directory or current directory as a fallback
        start_dir = Path.home() if Path.home().is_dir() else Path('.')
        picker = LocalFilePicker(str(start_dir), multiple=False)
        # Await the dialog's result (list of selected file paths or None if cancelled)
        result = await picker

        if result:  # Result is a list of paths, or None if cancelled
            await self._handle_file_picker_result(result)

    async def _handle_file_picker_result(self, file_paths: List[str]) -> None:
        """
        Handles the file paths selected via the LocalFilePicker.
        Reads each file's content and passes it to the ChatPanelUI for processing.

        Args:
            file_paths (List[str]): A list of absolute paths to the selected files.
        """
        if not file_paths:
            return

        for file_path_str in file_paths:
            try:
                file_path_obj = Path(file_path_str)
                if not file_path_obj.is_file():
                    ui.notify(
                        f"'{file_path_obj.name}' is not a valid file.", type='warning')
                    continue

                # Read file content into a BytesIO buffer
                with open(file_path_obj, 'rb') as f:
                    file_content_buffer = io.BytesIO(f.read())

                # Guess MIME type from file extension
                content_type, _ = mimetypes.guess_type(file_path_str)
                content_type = content_type or 'application/octet-stream'  # Default if unknown

                # Delegate processing to the parent ChatPanelUI
                await self.chat_panel_ui._process_file_content(file_content_buffer, file_path_obj.name, content_type)
            except Exception as ex:
                ui.notify(
                    f"Could not process file {file_path_obj.name}: {ex}", type='negative')

    def disable_input(self) -> None:
        """Disables the text area and send button, and changes send button icon to indicate loading."""
        self.text_area.props('disable')
        self.send_button.props('disable')
        self.send_button.props(remove='icon=send').props(
            add='icon=hourglass_empty')

    def enable_input(self) -> None:
        """Enables the text area and send button, and reverts send button icon."""
        self.text_area.props(remove='disable')
        self.send_button.props(remove='disable')
        self.send_button.props(
            remove='icon=hourglass_empty').props(add='icon=send')


class ChatPanelUI:
    """
    Manages the UI for the entire chat panel, including message history and the input box.
    """

    def __init__(self, sidebar: 'Sidebar'):
        self.sidebar = sidebar
        self.ui_manager: Optional['UIInterface'] = None

        # State for message streaming
        # Changed from _last_message_header
        self._last_sender_type: Optional[str] = None
        # Holds the text content of the current message being streamed
        self._current_streaming_content: str = ""
        self._current_streaming_element: Optional[ui.markdown] = None

        self._build()

    def set_ui_manager(self, manager: 'UIInterface'):
        """Sets the UI manager to enable communication with other panels."""
        self.ui_manager = manager

    def _build(self) -> None:
        """Builds the primary UI elements for the chat panel."""
        # Removed shadow-lg from the main chat panel card
        with ui.card().classes('w-full h-full rounded-lg p-0 flex flex-col overflow-hidden'):

            # 1. Header with sidebar toggle and title.
            with ui.row().classes('items-center w-full p-2 bg-gray-100 dark:bg-gray-800 border-b dark:border-gray-700 flex-shrink-0'):
                ui.button(icon='menu', on_click=self.sidebar.toggle).props(
                    'flat round dense')
                # Added margin to balance toggle button
                ui.label("Ankdesh AI Framework").classes(
                    'text-lg font-semibold flex-grow text-center mr-8')

            # 2. Scrollable chat history area.
            # 'flex-grow' and 'h-0' are used to make this area fill all available vertical space.
            self.chat_history_scroll_area = ui.scroll_area().classes('flex-grow w-full h-0')
            with self.chat_history_scroll_area:
                self.chat_messages_container = ui.column().classes(
                    'w-full p-3')  # Removed space-y-2, margin added to cards

            # 3. Chat input box area at the bottom.
            with ui.element('div').classes('w-full flex-shrink-0 border-t dark:border-gray-700'):
                self.chat_box = ChatBox(
                    chat_panel_ui=self  # Pass self to ChatBox
                )

    def _scroll_to_bottom(self):
        """Scrolls the chat history to the very bottom."""
        ui.timer(0.1, lambda: self.chat_history_scroll_area.scroll_to(
            percent=1.0, duration=0.1), once=True)

    def add_message(self, message_text: str, sender_type: str) -> None:
        """
        Adds a complete message to the chat panel. This is used for non-streaming content.
        The message appearance is determined by the sender_type.

        This method resets the streaming state.

        Args:
            message_text (str): The text content of the message.
            sender_type (str): Type of the sender ("user", "ai", "system").
        """
        self._last_sender_type = sender_type
        self._current_streaming_content = message_text

        # Determine border color and alignment based on sender type
        if sender_type == "user":
            # Transparent box with thick gray border
            border_color_class = "border-purple-900"
            alignment_class = "mr-auto"  # Align to the left
        elif sender_type == "ai":
            # Transparent box with thick slate border
            border_color_class = "dark:border-teal-900"
            alignment_class = "ml-auto"  # Align to the right
        elif sender_type == "system":
            # Changed to border with color
            border_color_class = "border-red-900"
            alignment_class = "ml-auto"  # Align to the right
        else:
            border_color_class = "border-gray-700"  # Default/fallback border color
            alignment_class = "mr-auto"  # Default to left

        with self.chat_messages_container:
            # Message text is converted to markdown which doesnt print single \n. Hence double
            message_text = message_text.replace('\n', '\n\n')
            # Outer card for the message, with conditional background and margin
            # Removed background color and shadow, added border-2 and border_color_class
            # Changed mx-auto to dynamic alignment_class
            with ui.card().classes(
                f'w-11/12 {alignment_class} rounded-lg mb-1 border-4 border-solid {border_color_class}'
            ):
                # Message content, rendered as Markdown.
                with ui.card_section().classes('p-0'):  # Reduced padding
                    self._current_streaming_element = ui.markdown(
                        message_text).classes('text-sm dark:prose-invert max-w-none')

                # Add like/dislike buttons for AI messages
                if sender_type == "ai":
                    with ui.row().classes('w-full justify-end p-1'):  # Right-aligned row with small padding
                        ui.button(icon='thumb_up', on_click=lambda: ui.notify(
                            'Liked!')).props('flat round dense').tooltip('Like')
                        ui.button(icon='thumb_down', on_click=lambda: ui.notify(
                            'Disliked!')).props('flat round dense').tooltip('Dislike')

        self._scroll_to_bottom()

    def stream_message_chunk(self, token: str, sender_type: str) -> None:
        """
        Streams a chunk (token) of a message to the chat panel.
        - If the `sender_type` is the same as the last message, the `token` is appended.
        - If the `sender_type` is different, a new message box is created.
        """
        if sender_type != self._last_sender_type or self._current_streaming_element is None:
            self._current_streaming_content = ""  # Reset content
            # Pass token as initial message_text
            self.add_message(token, sender_type)
        else:
            self._current_streaming_content += token
            self._current_streaming_element.content = self._current_streaming_content
            self._scroll_to_bottom()

    async def _handle_user_submission(self, message: str) -> None:
        """
        Handles the user's submitted message. Displays it in the chat.
        The simulated AI response has been removed to allow for real backend data.
        """
        if not self.ui_manager:  # Should always be set by the main app
            ui.notify("UI Manager not configured.", type='negative')
            return

        self.ui_manager.add_chat_message(text=message, sender_type="user")

    async def _process_file_content(self, file_content_buffer: io.BytesIO, file_name: str, content_type: str) -> None:
        """
        Processes file content received from the local file picker in ChatBox.
        This involves using a FileHandlerFactory to get an appropriate handler
        based on the file type, then rendering and adding the content via the UIManager.

        Args:
            file_content_buffer (io.BytesIO): The file content as a byte stream.
            file_name (str): The name of the file.
            content_type (str): The MIME type of the file.
        """
        if not self.ui_manager:
            ui.notify("UI Manager not configured for file handling.",
                      type='negative')
            return

        try:
            # Get size from BytesIO buffer
            file_size = len(file_content_buffer.getvalue())
            handler = FileHandlerFactory.get_handler(
                file_content_buffer, file_name, content_type)
            content_obj = await handler.get_content_representation()

            self.ui_manager.add_content(content_obj)
            ui.notify(
                f"File '{file_name}' processed and added to content panel.", type='positive')
        except Exception as e:
            ui.notify(f"Error processing file: {str(e)}", type='negative')


def create_chat_display_panel(sidebar: 'Sidebar') -> ChatPanelUI:
    """
    Factory function to create and return an instance of the ChatPanelUI.
    """
    return ChatPanelUI(sidebar)
