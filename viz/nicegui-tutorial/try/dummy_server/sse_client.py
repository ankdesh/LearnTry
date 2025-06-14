import asyncio
import httpx
import json

async def main():
    server_url = "http://localhost:8001/stream-data"
    print(f"Connecting to SSE server at {server_url}...")

    try:
        async with httpx.AsyncClient(timeout=None) as client: # timeout=None for long-lived streams
            async with client.stream("GET", server_url) as response:
                if response.status_code == 200:
                    print("Successfully connected. Waiting for data...\n")
                    async for line in response.aiter_lines():
                        if line.startswith("data:"):
                            json_data_str = line[len("data:"):].strip()
                            if json_data_str:
                                try:
                                    data = json.loads(json_data_str)
                                    print(f"Received: {data}")
                                except json.JSONDecodeError:
                                    print(f"Error decoding JSON: {json_data_str}")
                else:
                    print(f"Error connecting to server: Status {response.status_code}")
    except httpx.ConnectError as e:
        print(f"Connection failed: {e}")

if __name__ == "__main__":
    asyncio.run(main())