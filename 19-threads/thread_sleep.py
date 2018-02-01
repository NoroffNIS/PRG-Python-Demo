import threading
import time
import random
from colorama import Fore

def thread_worker(delay,color):
    print(color, 'Working:',\
        threading.currentThread().getName())
    print(color,threading.currentThread().getName(),'sleeping for', delay)
    time.sleep(delay)
    print(color,threading.currentThread().getName(),'done sleeping for', delay)
    return

colors = [Fore.RED, Fore.GREEN, Fore.CYAN, Fore.YELLOW, Fore.WHITE]
print()
for i in range(5):
    delay = random.randint(1,4)
    threading.Thread(target=thread_worker, args=(delay,colors[i])).start()
