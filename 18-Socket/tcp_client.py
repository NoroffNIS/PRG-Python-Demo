import socket

HOST = 'www.google.no'
PORT = 80
DATA = b'GET / HTTP/1.1\r\nHost: google.no\r\n\r\n'#HTTP/1.0 200 OK\r\nContent-Length: %d\r\n\r\n

client = socket.socket( socket.AF_INET, socket.SOCK_STREAM)
client.connect(( HOST, PORT ))
client.send(DATA)
response = client.recv(4096)
print(response.decode('utf-8'))
