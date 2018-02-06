import threading

for i in range(5):
    print(threading.currentThread().getName(),\
            'Count:',i )
