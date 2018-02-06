import threading
import time
from colorama import Fore

def custumer(cond, color):
    print(color, threading.currentThread().getName(), '\t->  waithing outside the shop')
    t = threading.currentThread()
    with cond:
        cond.wait()
        print(color, threading.currentThread().getName(), '\t->  entering the shop')
        time.sleep(3)
        print(color, threading.currentThread().getName(), '\t->  exiting the shop')
        cond.notify()

def merchant(cond, color):
    print(color, threading.currentThread().getName(), '\t->  preparing the shop')
    time.sleep(3)
    with cond:
        print(color, threading.currentThread().getName(), '\t->  opens the shop')
        #cond.notifyAll()
        cond.notify()

condition = threading.Condition()
c1 = threading.Thread(name='Custumer 1', target=custumer, args=(condition, Fore.RED))
c2 = threading.Thread(name='Custumer 2', target=custumer, args=(condition, Fore.RED))
m = threading.Thread(name='Merchant', target=merchant, args=(condition, Fore.GREEN))

c1.start()
time.sleep(2)
c2.start()
time.sleep(2)
m.start()
