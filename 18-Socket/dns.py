import socket
whois = 'www.noroff.no'#'85.10.255.106'
ip = socket.gethostbyname(whois)
print(ip)
print(socket.gethostbyname_ex(whois))
print(socket.getfqdn(whois))
print(socket.gethostbyaddr(ip))
