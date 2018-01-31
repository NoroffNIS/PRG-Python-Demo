import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('172.24.1.66' , 50000)
s.bind(server_address)
s.listen(1)
print('Listning on {}:{}'.format(*server_address))

while True:
    conn, client_addr = s.accept()
    try:
        print('Connection from {}'.format(client_addr))
        while True:
            data = conn.recv(1024)
            print('Recived: {!r}'.format(data))
            if data:
                print('sending data back to {}'.format(client_addr))
                conn.sendall(data)
            else:
                print('no data from {}'.format(client_addr))
                break
    finally:
        print('Closing socket')
        conn.close()
        break
