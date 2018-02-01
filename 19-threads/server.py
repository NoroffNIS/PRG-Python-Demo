import socket
from threading import Thread
from colorama import Fore

class ClientConnect(Thread):
        def __init__(self, ip, port, color):
            Thread.__init__(self)
            self.ip = ip
            self.port = port
            self.color = color
            self.client_addr = (self.ip,self.port)
            print('Connection from {}:{}'.format(self.client_addr))

        def run(self):
            while True:
                data = conn.recv(1024)
                print('Recived: {!r}'.format(data))
                if data:
                    print('sending data back to {}'.format(self.client_addr))
                    conn.sendall(data)
                else:
                    print('no data from {}'.format(self.client_addr))
                    break

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = (socket.gethostname() , 50000)
s.bind(server_address)
s.listen(1)
colors = [Fore.RED, Fore.GREEN, Fore.CYAN, Fore.YELLOW, Fore.WHITE]
threads = []
i=0
print('Listning on {}:{}'.format(*server_address))
while True:
    conn, (client_ip,client_port) = s.accept()
    try:
        new_client = ClientConnect(client_ip, client_port, colors[i])
        new_client.start()
        threads.append(new_client)
        i += 1 if i<5 else 0
    finally:
        for t in threads:
            t.join()
        print('Closing socket')
        conn.close()
        break
