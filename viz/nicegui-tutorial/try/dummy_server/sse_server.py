import asyncio
import json
import os
import re # Import the regex module
from typing import AsyncGenerator

from fastapi import FastAPI, Request
from fastapi.responses import StreamingResponse
import uvicorn

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
REASON_FILE = os.path.join(CURRENT_DIR, "sample_reason.txt")
PYTHON_FILE = os.path.join(CURRENT_DIR, "sample_python.py")

app = FastAPI()

async def file_event_generator(file_path: str, header_name: str, request: Request) -> AsyncGenerator[str, None]:
    """
    Reads a file word by word (including newlines) and yields SSE formatted events.
    """
    try:
        with open(file_path, 'r') as f:
            content = f.read() # Read the entire content

        # Use regex to find words (sequences of non-whitespace) and newlines
        # r'\S+|\n' matches either one or more non-whitespace characters (\S+) OR a newline character (\n)
        tokens = re.findall(r'\S+|\n', content)

        for token in tokens:
            if await request.is_disconnected():
                print(f"Client disconnected while reading {os.path.basename(file_path)}")
                break
            json_payload = json.dumps({"header": header_name, "token": token+" "})
            yield f"data: {json_payload}\n\n"
            await asyncio.sleep(0.001) # Small delay to simulate streaming and allow client to process
    except FileNotFoundError:
        json_payload = json.dumps({"header": header_name, "token": f"Error: File {os.path.basename(file_path)} not found."})
        yield f"data: {json_payload}\n\n"
    except Exception as e:
        print(f"Error reading file {file_path}: {e}")
        json_payload = json.dumps({"header": header_name, "token": f"Error processing file {os.path.basename(file_path)}."})
        yield f"data: {json_payload}\n\n"

@app.get("/stream-data")
async def stream_data(request: Request) -> StreamingResponse:
    async def event_stream():
        async for event in file_event_generator(REASON_FILE, "text", request):
            yield event
        async for event in file_event_generator(PYTHON_FILE, "code:python", request):
            yield event
    return StreamingResponse(event_stream(), media_type="text/event-stream")

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8001)