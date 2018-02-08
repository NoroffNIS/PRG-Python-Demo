import os

for i in range(0,255):
    targetIP = '172.24.3.'+str(i)
    response = os.system("ping -n 2 " + targetIP)

    print('Response:',response)
    if response == 0:
        print(targetIP, 'is up!')
    else:
        print(targetIP, 'is down!')
