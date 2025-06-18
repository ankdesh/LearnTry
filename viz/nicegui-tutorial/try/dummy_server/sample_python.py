import asyncio
import re
from typing import AsyncGenerator, Tuple, Optional, AsyncIterable

async def parse_streamed_data(
    token_stream: AsyncIterable[str],
) -> AsyncGenerator[Tuple[Optional[str], str], None]:
    """
    Parses an asynchronous stream of string tokens to identify sections and their content.

    This async generator processes an incoming stream of text, identifies headers
    formatted as [[ ## Header_Title ## ]], and yields tuples containing the
    current header title and the associated content chunk.

    Args:
        token_stream: An asynchronous iterable that yields strings (tokens).

    Yields:
        A tuple of (str | None, str), where the first element is the identified
        header title (or None if no header has been encountered yet) and the
        second element is the chunk of data belonging to that header.
    """
    # Regex to find a header and extract its title.
    # It looks for "[[ ##", followed by any characters (the title), and then "## ]]".
    # Whitespace around the title is stripped.
    header_pattern = re.compile(r'\[\[\s*##\s*(.*?)\s*##\s*\]\]')

    buffer = ""
    current_header: Optional[str] = None