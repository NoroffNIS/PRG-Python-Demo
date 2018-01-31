import socket
import time
from colorama import Fore

colors = [Fore.RED, Fore.GREEN, Fore.CYAN, Fore.YELLOW]
clients = []

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_addr = (socket.gethostname(), 5000)
s.bind(server_addr)
s.setblocking(0)

print(Fore.WHITE, 'Starting server on:', *server_addr)
while True:
    try:
        data , client_addr = s.recvfrom(1024)
        if 'Quit' in str(data):
            print(Fore.LIGHTRED_EX, 'Server shutting down!')
            break
        if client_addr not in clients:
            clients.append(client_addr)
        print(colors[clients.index(client_addr)],time.ctime(time.time()),\
                '::',str(client_addr), ':', data.decode('utf-8'))
        for client in clients:
            if client != client_addr:
                s.sendto(data, client)

    except:
        pass

print(Fore.LIGHTRED_EX, 'Server shutting down!')
s.close()
