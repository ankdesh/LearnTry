from typing import Callable, Optional, Any, List, Dict, Awaitable
from datetime import datetime
from nicegui import ui


class ChatBox:
    """
    A class-based component for creating a chat input box.
    """

    def __init__(self,
                 on_submit: Callable[[str], Awaitable[None]],
                 action_buttons: Optional[List[Dict[str, Any]]] = None):
        self.on_submit = on_submit
        self.action_buttons_config = action_buttons if action_buttons else []
        self._build()

    def _build(self):
        # Adjusted for embedding: remove shadow and rounding to blend into parent card
        # No shadow, no rounding for seamless integration
        with ui.card().classes('w-full shadow-none rounded-none'):
            with ui.column().classes('w-full gap-0'):  # No gap for tight layout
                self.text_area = ui.textarea(placeholder='Type your message...') \
                    .classes('w-full text-sm') \
                    .props('filled autogrow input-class="h-auto"')  # autogrow is key
                with ui.row().classes('w-full items-center justify-between p-2'):  # Padding for button row
                    # Left-aligned custom action buttons
                    with ui.row().classes('items-center'):
                        for btn_config in self.action_buttons_config:
                            button_props = "flat round dense"

                            btn = ui.button(icon=btn_config.get('icon'),
                                            text=btn_config.get('text'),
                                            on_click=btn_config.get('on_click')) \
                                .props(button_props)

                            if 'tooltip' in btn_config:
                                btn.tooltip(btn_config['tooltip'])
                    # Main Send button (right-aligned)
                    ui.button(icon='send', on_click=self._handle_main_submit) \
                        .props('flat round dense')

    async def _handle_main_submit(self) -> None:
        message = self.text_area.value.strip()
        if not message:
            ui.notify('Cannot send an empty message.', type='warning')
            return

        await self.on_submit(message)
        self.text_area.value = ''  # Clear the input field


class ChatPanelUI:
    """
    Manages the UI for the entire chat panel, including history, input box, and interactions.
    """

    def __init__(self, left_drawer: ui.left_drawer):
        self.left_drawer = left_drawer
        self._build()

    def _add_markdown_message(self, header: str, text: str) -> None:
        """Adds a message with a header and markdown content to the chat panel."""
        with self.chat_messages_container:
            with ui.card().classes('w-full no-shadow border dark:border-gray-700'):
                # Reduced padding for header section
                with ui.card_section().classes('py-0.5 px-1 bg-gray-100 dark:bg-gray-800'):
                    ui.label(header).classes('text-xs font-medium text-gray-600 dark:text-gray-400')
                # Reduced padding for content section
                with ui.card_section().classes('py-1 px-1'):
                    ui.markdown(text).classes('text-sm dark:prose-invert max-w-none')
        # Scroll after adding the message
        ui.timer(0.1, lambda: self.chat_history_scroll_area.scroll_to(percent=1.0, duration=0.1), once=True)

    def _build(self) -> None:
        """Builds the UI elements for the chat panel."""
        with ui.card().classes('w-full h-full shadow-lg rounded-lg p-0 flex flex-col overflow-hidden'):
            # Header for the chat panel with sidebar toggle
            with ui.row().classes(
                'items-center w-full p-2 bg-gray-100 dark:bg-gray-800 border-b dark:border-gray-700 flex-shrink-0 gap-2'
            ):
                ui.button(icon='menu', on_click=self.left_drawer.toggle).props(
                    'flat round dense')
                ui.label("Ankdesh AI Framework").classes(
                    'text-lg font-semibold flex-grow text-center')

            # 1. Chat History Area (should grow).
            # CHANGE: Removed 'h-75%' and added 'h-0'.
            # 'flex-grow' allows this element to expand and fill available vertical space.
            # 'h-0' gives the element a base height of 0, which is a common pattern
            # to ensure 'flex-grow' works predictably and fills all available space.
            self.chat_history_scroll_area = ui.scroll_area().classes('flex-grow w-full h-0')
            with self.chat_history_scroll_area:
                # Removed top padding (pt-0) to eliminate space above the first message.
                self.chat_messages_container = ui.column().classes(
                    'w-full pt-0 px-3 pb-3 space-y-1') # Reduced space between messages
                with self.chat_messages_container:  # Add an initial welcome message from AI
                    self._add_markdown_message(f"AI ({datetime.now().strftime('%H:%M')})",
                                               "Hello! How can I assist you with the content panel today?")
                    self._add_markdown_message(f"AI ({datetime.now().strftime('%H:%M')})",
                                               "This chat window now correctly fills the available height.")

            # 2. ChatBox Area (should not shrink, take its natural height, with a top border)
            chat_box_action_buttons = [
                {'icon': 'add_photo_alternate', 'on_click': self._handle_add_file_action,
                    'tooltip': 'Add file', 'props': {'padding': "xs"}}
            ]
            with ui.element('div').classes('w-full flex-shrink-0 border-t dark:border-gray-700'):
                ChatBox(on_submit=self._display_submission_in_panel,
                        action_buttons=chat_box_action_buttons)

    async def _display_submission_in_panel(self, message: str) -> None:
        """Handles displaying the submitted message and AI response in the chat panel."""
        user_header = f"You ({datetime.now().strftime('%H:%M')})"
        # Display user's message
        self._add_markdown_message(user_header, message)

        # Generic AI response (as ChatBox is now decoupled from ContentManager)
        ai_header = f"AI ({datetime.now().strftime('%H:%M')})"
        message = "\n\n```python\n\n" + open("dummy_server/sample_python.py", "r").read() + "\n\n```"
        
        self._add_markdown_message(ai_header, f"Echo: {message}")

    def _handle_add_file_action(self) -> None:
        """Placeholder action for the 'add file' button within this panel's context."""
        ui.notify(
            '"Add file" button clicked. Implement file upload logic here.', type='info')


def create_chat_display_panel(left_drawer: ui.left_drawer) -> ChatPanelUI:
    """Creates and returns an instance of the ChatPanelUI."""
    return ChatPanelUI(left_drawer)
