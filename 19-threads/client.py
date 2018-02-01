import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = (socket.gethostname(), 50000)
s.connect((socket.gethostname(), 50000))
print('Connection to {}'.format(server_address))

try:
    msg = b'Hello'
    s.sendall(msg)
    recived = 0
    expexted = len(msg)
    while recived < expexted:
        data = s.recv(1024)
        recived += len(data)
        if data:
            print('Received', repr(data))
        else:
            print('Received no data')
finally:
    print('Closing socket!')
    s.close()
