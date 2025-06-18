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

    # Process each token from the input stream.
    async for token in token_stream:
        buffer += token

        # Continuously process the buffer in case a single token contains
        # multiple headers or a mix of content and headers.
        while True:
            # Search for the next header in our current buffer.
            match = header_pattern.search(buffer)

            if match:
                # A header was found.
                # The content before the header belongs to the previous section.
                pre_header_content = buffer[:match.start()]
                if pre_header_content:
                    yield (current_header, pre_header_content)

                # A new section begins. Update the current header.
                current_header = match.group(1).strip()

                # The buffer for the next iteration is whatever remains after the header.
                buffer = buffer[match.end():]
            else:
                # No more headers in the current buffer.
                # We break the inner loop to wait for the next token.
                break

    # After the stream has ended, there might be leftover content in the buffer.
    # This content belongs to the last known header.
    if buffer:
        yield (current_header, buffer)


async def example_usage():
    """Demonstrates how to use the parse_streamed_data generator."""

    # Simulate a network stream that sends data in chunks (tokens).
    # This stream includes various edge cases.
    async def dummy_stream():
        stream_data = [
            "This is some initial content before any header.",
            "[[ ## Section 1 ## ]]This is the first part of section 1.",
            " Here is the second part.",
            "[[ ## Section 2 ##]]", # Header without surrounding spaces
            "Content for section 2.",
            "[[ ## Section 3", # A split header
            " ## ]]Content for section 3.",
            " This section has multiple parts.",
            "[[ ## Section 4 ## ]]First part of S4.[_[[ ## Section 5 ## ]]S5 content.",
        ]
        for chunk in stream_data:
            yield chunk
            await asyncio.sleep(0.1) # Simulate network delay

    print("--- Starting Stream Parsing Example ---")
    print("Parsing a simulated stream with various edge cases...\n")

    # Use the parser on the simulated stream.
    parsed_stream = parse_streamed_data(dummy_stream())

    # Asynchronously iterate through the parsed (header, content) tuples.
    async for header, content in parsed_stream:
        print(f"Header: {header if header else 'None'}")
        print(f"Content: '{content}'")
        print("-" * 20)

    print("\n--- Stream Parsing Finished ---")


if __name__ == "__main__":
    # In a real application, you would integrate this with your
    # framework's event loop (e.g., FastAPI, aiohttp).
    asyncio.run(example_usage())
