import socket
from colorama import Fore

server_addr = (socket.gethostname(), 5000)
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client_addr = (socket.gethostname(), 0)
s.connect(server_addr)

alias = input('Name:')
while True:
    msg = input('{}->'.format(alias))
    if msg != 'Quit':
        s.sendto((alias+'->'+msg).encode('utf-8'), server_addr)
    data , server_addr = s.recvfrom(1024)
    try:
        if data:
            print(Fore.RED, data.decode('utf-8'))
    except:
        pass
