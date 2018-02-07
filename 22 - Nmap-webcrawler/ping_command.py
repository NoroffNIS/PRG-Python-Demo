import os

for i in range(0,255):
    targetIP = '172.24.1.'+str(i)
    response = os.system("ping -n 1 " + targetIP)

    print('Response:',response)
    if response == 0:
        print(targetIP, 'is up!')
    else:
        print(targetIP, 'is down!')
