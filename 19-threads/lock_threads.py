import threading
import time
from colorama import Fore

count = 0

def increment(lock, delay,color):

    global count
    print(color, threading.currentThread().getName(), '\t-> Worker_1 starting')

    while count < 100:
        lock.acquire()
        count += 1
        print(color, threading.currentThread().getName(), '\t-> Count is:', count)
        lock.release()
        time.sleep(delay)

lock = threading.Lock()
i=0
colors = [Fore.RED, Fore.GREEN, Fore.CYAN, Fore.YELLOW, Fore.MAGENTA, Fore.WHITE]
for t in range(5):
    i += 1 if i < 5 else 0
    t = threading.Thread(name='T'+str(i), target=increment, args=(lock, 0.1, colors[i]))
    t.start()
