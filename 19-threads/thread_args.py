import threading
import time

def thread_worker(i):
    print(i, '= Working:',\
        threading.currentThread().getName())
    return

def thread_worker_2(number=0, delay=0):
    print(number, '= Working_2:',\
        threading.currentThread().getName())
    time.sleep(delay)
    return

for i in range(5):
    threading.Thread(target=thread_worker, args=(i,)).start()
    threading.Thread(target=thread_worker_2, kwargs={'number':i, 'delay':1}).start()
