import asyncio
import websockets

async def send_hello_world(websocket):
    while True:
        await asyncio.sleep(1)
        message = "FROM_CLIENT: Hello, World (from client)"
        await websocket.send(message)

async def read_websocket(url):
    async with websockets.connect(url) as websocket:
        print(f"Connected to {url}")

        send_task = asyncio.create_task(send_hello_world(websocket))

        try:
            async for message in websocket:
                if message.startswith("FROM_SERVER:"):
                    print(f"Received from server: {message[len('FROM_SERVER:'):]}")

        except websockets.exceptions.ConnectionClosedOK:
            print("WebSocket connection closed")

if __name__ == "__main__":
    # Replace 'ws://localhost:8765' with the server WebSocket address
    websocket_url = 'ws://localhost:8765'

    asyncio.get_event_loop().run_until_complete(read_websocket(websocket_url))
