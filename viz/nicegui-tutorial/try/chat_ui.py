# chat_ui.py

from typing import Callable, Optional, Any, List, Dict, Awaitable
from datetime import datetime
from nicegui import ui

# Forward declaration for type hinting to avoid circular import
if False:
    from ui_manager import UIManager


class ChatBox:
    """
    A class-based component for creating the chat input box at the bottom of the chat panel.
    """

    def __init__(self, on_submit: Callable[[str], Awaitable[None]], action_buttons: Optional[List[Dict[str, Any]]] = None):
        self.on_submit = on_submit
        self.action_buttons_config = action_buttons if action_buttons else []
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
                    # Left-aligned custom action buttons (e.g., file upload).
                    with ui.row().classes('items-center'):
                        for btn_config in self.action_buttons_config:
                            btn = ui.button(icon=btn_config.get('icon'), on_click=btn_config.get('on_click')) \
                                .props("flat round dense")
                            if 'tooltip' in btn_config:
                                btn.tooltip(btn_config['tooltip'])

                    # Right-aligned main send button.
                    ui.button(icon='send', on_click=self._handle_main_submit).props(
                        'flat round dense')

    async def _handle_main_submit(self) -> None:
        """Handles the click event of the main send button."""
        message = self.text_area.value.strip()
        if not message:
            ui.notify('Cannot send an empty message.', type='warning')
            return

        # Call the provided async submit handler.
        await self.on_submit(message)
        # Clear the input field after submission.
        self.text_area.value = ''
        # Refocus for quick follow-up messages.
        self.text_area.run_method('focus')

    async def _handle_keydown(self, event: any) -> None:
        """Handles keydown events on the textarea, specifically for Shift+Enter."""
        # The event object from NiceGUI's on('keydown') is a dictionary-like object.
        if event.args['key'] == 'Enter' and event.args['shiftKey']:
            # Prevent default Enter behavior (adding a newline)
            event.sender.run_method('preventDefault')
            await self._handle_main_submit()


class ChatPanelUI:
    """
    Manages the UI for the entire chat panel, including message history and the input box.
    """

    def __init__(self, left_drawer: ui.left_drawer):
        self.left_drawer = left_drawer
        self.ui_manager: Optional['UIManager'] = None

        # State for message streaming
        self._last_message_header: Optional[str] = None
        self._current_streaming_content: str = ""
        self._current_streaming_element: Optional[ui.markdown] = None

        self._build()

    def set_ui_manager(self, manager: 'UIManager'):
        """Sets the UI manager to enable communication with other panels."""
        self.ui_manager = manager

    def _build(self) -> None:
        """Builds the primary UI elements for the chat panel."""
        with ui.card().classes('w-full h-full shadow-lg rounded-lg p-0 flex flex-col overflow-hidden'):
            # 1. Header with sidebar toggle and title.
            with ui.row().classes('items-center w-full p-2 bg-gray-100 dark:bg-gray-800 border-b dark:border-gray-700 flex-shrink-0'):
                ui.button(icon='menu', on_click=self.left_drawer.toggle).props(
                    'flat round dense')
                # Added margin to balance toggle button
                ui.label("Ankdesh AI Framework").classes(
                    'text-lg font-semibold flex-grow text-center mr-8')

            # 2. Scrollable chat history area.
            # 'flex-grow' and 'h-0' are used to make this area fill all available vertical space.
            self.chat_history_scroll_area = ui.scroll_area().classes('flex-grow w-full h-0')
            with self.chat_history_scroll_area:
                self.chat_messages_container = ui.column().classes('w-full p-3 space-y-2')
                # Add an initial welcome message.
                self.add_message(
                    f"AI ({datetime.now().strftime('%H:%M')})",
                    "Hello! I am ready to assist you. How can I help today?"
                )

            # 3. Chat input box area at the bottom.
            chat_box_action_buttons = [
                {'icon': 'add_photo_alternate',
                    'on_click': self._handle_add_file_action, 'tooltip': 'Add file'}
            ]
            with ui.element('div').classes('w-full flex-shrink-0 border-t dark:border-gray-700'):
                ChatBox(on_submit=self._handle_user_submission,
                        action_buttons=chat_box_action_buttons)

    def _scroll_to_bottom(self):
        """Scrolls the chat history to the very bottom."""
        ui.timer(0.1, lambda: self.chat_history_scroll_area.scroll_to(
            percent=1.0, duration=0.1), once=True)

    def add_message(self, header: str, text: str) -> None:
        """
        Adds a complete message to the chat panel. This is used for non-streaming content.

        This method resets the streaming state.
        """
        self._last_message_header = header
        self._current_streaming_content = text

        with self.chat_messages_container:
            with ui.card().classes('w-full no-shadow border dark:border-gray-700'):
                # Message header (e.g., "You" or "AI" with timestamp).
                with ui.card_section().classes('py-1 px-2 bg-gray-100 dark:bg-gray-800'):
                    ui.label(header).classes(
                        'text-xs font-medium text-gray-600 dark:text-gray-400')
                # Message content, rendered as Markdown.
                with ui.card_section().classes('py-2 px-2'):
                    self._current_streaming_element = ui.markdown(
                        text).classes('text-sm dark:prose-invert max-w-none')

        self._scroll_to_bottom()

    def stream_message_chunk(self, header: str, token: str) -> None:
        """
        Streams a chunk (token) of a message. Appends to the last message if the header is the same.
        """
        # If the header has changed, or if there's no active streaming element, create a new message box.
        if header != self._last_message_header or self._current_streaming_element is None:
            self._current_streaming_content = ""  # Reset content
            self.add_message(header, token)
        # Otherwise, append the token to the existing message content and element.
        else:
            self._current_streaming_content += token
            self._current_streaming_element.content = self._current_streaming_content
            self._scroll_to_bottom()

    async def _handle_user_submission(self, message: str) -> None:
        """
        Handles the user's submitted message. Displays it in the chat.
        The simulated AI response has been removed to allow for real backend data.
        """
        if not self.ui_manager:
            ui.notify("UI Manager not configured.", type='negative')
            return

        # 1. Display the user's message immediately.
        user_header = f"You ({datetime.now().strftime('%H:%M')})"
        self.ui_manager.add_chat_message(user_header, message)

    def _handle_add_file_action(self) -> None:
        """Placeholder action for the 'add file' button."""
        ui.notify(
            '"Add file" button clicked. Implement file upload logic here.', type='info')


def create_chat_display_panel(left_drawer: ui.left_drawer) -> ChatPanelUI:
    """
    Factory function to create and return an instance of the ChatPanelUI.
    """
    return ChatPanelUI(left_drawer)
