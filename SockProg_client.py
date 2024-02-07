import socket
import threading

def receive_messages(client_socket):
    while True:
        try:
            # Receive and print messages from the server
            message = client_socket.recv(1024).decode()
            print(message)
        except:
            # If an error occurs, assume the server has disconnected
            print("Server disconnected.")
            break

# Create a TCP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the chat room server
host = '127.0.0.1'  # localhost
port = 12345
client_socket.connect((host, port))

# Get the user's login name
login_name = input("Enter your login name: ")

# Send the login name to the server
client_socket.send(login_name.encode())

# Start a thread to receive messages from the server
receive_thread = threading.Thread(target=receive_messages, args=(client_socket,))
receive_thread.start()

# Main loop to send messages to the server
while True:
    message = input()
    client_socket.send(message.encode())
    if message == "quit" : 
        client_socket.close() 
