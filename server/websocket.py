import asyncio
import websockets

async def handle_client(websocket, path):
    print("Client connected")
    try:
        async def send_hello_world():
            while True:
                await asyncio.sleep(1)
                message = "FROM_SERVER: Hello, World (from server)"
                await websocket.send(message)

        send_task = asyncio.create_task(send_hello_world())

        async for message in websocket:
            print(f"Received from client: {message}")

            # Process the received message here if needed
            # For example, you can check the identifier and respond accordingly
            if message.startswith("FROM_CLIENT:"):
                response = f"Server received from client: {message[len('FROM_CLIENT:'):]}"
                await websocket.send(response)
                # print(f"Sent to client: {response}")

    except websockets.exceptions.ConnectionClosed:
        print("Client disconnected")

async def main():
    async with websockets.serve(handle_client, "localhost", 8765):
        print("WebSocket server started")
        await asyncio.Future()  # run forever

asyncio.run(main())
