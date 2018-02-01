import threading
import time
from colorama import Fore

def daemon(delay,color):
    print(color, threading.currentThread().getName(),'staring')
    print(color, threading.currentThread().getName(),'sleeping for', delay)
    time.sleep(delay)
    print(color,threading.currentThread().getName(),'done sleeping for', delay)
    print(color, threading.currentThread().getName(),'exiting')

def non_daemon(color):
    print(color, threading.currentThread().getName(),'staring')
    print(color, threading.currentThread().getName(),'exiting')

print()
d = threading.Thread(target=daemon, name='daemon', args=(2,Fore.RED))
d.setDaemon(True)

t = threading.Thread(target=non_daemon, name='non-daemon', args=(Fore.GREEN,))

d.start()
t.start()

d.join()
t.join()

print(Fore.WHITE, threading.currentThread().getName(),'- Done!')
