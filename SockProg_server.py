import socket
import threading
import datetime
# Dictionary to store connected clients
clients = {}

def handle_client(client_socket, client_name):
    # Broadcast the new user joining message
    time_obj = datetime.datetime.now()
    time = time_obj.time()
    clients[client_name] = client_socket
    broadcast(f"Server: time={time} {client_name} has joined. Member count={len(clients)} ")

    # Add the client to the dictionary
    #clients[client_name] = client_socket

    while True:
        try:
            # Receive message from the client
            message = client_socket.recv(1024).decode()
            if message == "quit" :
                raise NameError 
                # Broadcast the message to all clients
            else : 
                broadcast(f"{client_name}: {message}")
        except:
            # If an error occurs, assume the client has disconnected
            print(f"{client_name} disconnected.")
            del clients[client_name]
            broadcast(f"Server: time={time} {client_name} has left. Member count={len(clients)}")
            break

def broadcast(message):
    # Broadcast the message to all connected clients
    for client_name, client_socket in clients.items():
        try:
            client_socket.send(message.encode())
        except:
            # If an error occurs, assume the client has disconnected
            del clients[client_name]
            print(f"{client_name} left the chat room.")

# Create a TCP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to a specific address and port
host = '127.0.0.1'  # localhost
port = 12345
server_socket.bind((host, port))

# Listen for incoming connections
server_socket.listen()

print(f"Chat room server listening on {host}:{port}")

while True:
    # Accept a connection
    client_socket, client_address = server_socket.accept()

    # Receive the client's login name
    client_name = client_socket.recv(1024).decode()

    # Start a new thread to handle the client
    client_handler = threading.Thread(target=handle_client, args=(client_socket, client_name))
    client_handler.start()
