import nmap

nm = nmap.PortScanner()

nm.scan('127.0.0.1', '22-43')
print(nm.command_line())
print(nm.scaninfo())
print(nm.all_hosts())


print(nm['127.0.0.1'].hostnames())
print(nm['127.0.0.1'].all_tcp())
print(nm['127.0.0.1'].all_udp())
print(nm['127.0.0.1'].keys())
print(nm['127.0.0.1']['addresses'])

'''
print('nmap.PortScanner() functions:')
for i in dir(nm):
    if i.startswith('_'):
        pass
    else:
        print(i)

print('nmap[host/ip] functions:')
for i in dir(nm['127.0.0.1']):
    if i.startswith('_'):
        pass
    else:
        print(i)
'''
