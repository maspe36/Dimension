import socket
import threading

ENCODING = "utf-8"
LOCAL_ENDPOINT = "127.0.0.1"

def listen():
    while 1:
        data = sock.recv(4096)
        if data:
            print("Server: " + data.decode(ENCODING))

def listen_to_keypress():
    while 1:
        message = input("Enter text (or Enter to quit): \n")
        if not message:
            break

        sock.sendall((message + "\n").encode(ENCODING))

print("Attempting to connect to the localhost...")
ENDPOINT = LOCAL_ENDPOINT

sock = socket.socket()
port = 8888

sock.connect((ENDPOINT, port))

threading.Thread(target=listen).start()
threading.Thread(target=listen_to_keypress).start()
