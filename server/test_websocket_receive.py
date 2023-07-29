# import asyncio
# from websockets.sync.client import connect

# def hello():
#     with connect("ws://localhost:8765") as websocket:
#         websocket.send("Hello world!")
#         # message = websocket.recv()
#         # print(f"Received: {message}")
        
# def receive():
#     with connect("ws://localhost:8765") as websocket:
#         message = websocket.recv()
#         print(f"Received: {message}")

# hello()

# while(True):
#     receive()


import asyncio
import websockets

# This function handles incoming WebSocket connections
async def handle_websocket(websocket, path):
    print("Client connected")
    
    try:
        while True:
            # Receive data from the client (ESP32)
            data = await websocket.recv()
            print(f"Received: {data}")

            # You can add any processing logic here

            # Send a response back to the client (ESP32)
            response = f"Server received: {data}"
            await websocket.send(response)
            print(f"Sent: {response}")

    except websockets.exceptions.ConnectionClosed:
        print("Client disconnected")

# Set up the WebSocket server
start_server = websockets.serve(handle_websocket, "0.0.0.0", 8765)

# Start the server's main event loop
async def server_main():
    await start_server
    print("WebSocket server started")
    await asyncio.Event().wait()

# Run the server
if __name__ == "__main__":
    asyncio.run(server_main())
