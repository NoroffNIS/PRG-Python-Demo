import threading
import time
from colorama import Fore

def worker_1(e, color):
    print(color, threading.currentThread().getName(), '\t-> Worker_1 starting')
    event_is_set = e.wait()
    print(color, threading.currentThread().getName(), '\t-> Worker_1 event is:', event_is_set)

def worker_2(e,time, color):
    while not e.isSet():
        print(color, threading.currentThread().getName(), '\t-> Worker_2 starting')
        event_is_set = e.wait(time)
        print(color, threading.currentThread().getName(), '\t-> Worker_2 event is:', event_is_set)
        if event_is_set:
            print(color, threading.currentThread().getName(), '\t-> Worker_2 prossesing')
        else:
            print(color, threading.currentThread().getName(), '\t-> Worker_2 doing other work')

e = threading.Event()

t1 = threading.Thread(target=worker_1, name='t1-Block', args=(e,Fore.RED))
t1.start()
t2 = threading.Thread(target=worker_2, name='t2-nBlock', args=(e,2,Fore.GREEN))
t2.start()

print(Fore.WHITE, threading.currentThread().getName(), '\t-> Waithing before calling Event.set()')
time.sleep(6)
e.set()
print(Fore.WHITE, threading.currentThread().getName(), '\t-> Event is set')
