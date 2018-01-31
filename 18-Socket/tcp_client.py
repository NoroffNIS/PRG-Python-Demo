import socket

HOST = 'www.noroff.no'
PORT = 80
DATA = b'GET / HTTP/1.1\r\n'

client = socket.socket( socket.AF_INET, socket.SOCK_STREAM)
client.connect(( HOST, PORT ))
client.send(DATA)
response = client.recv(4096)
print(response.decode('utf-8'))
