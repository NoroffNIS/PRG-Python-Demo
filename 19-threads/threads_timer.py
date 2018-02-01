import threading
import time
import random
from colorama import Fore
import logging

logging.basicConfig(level=logging.DEBUG, format='(%(threadName)-10s) %(message)s',)

def thread_worker():
    logging.debug('Working running:')
    return

t1 = threading.Timer(3, thread_worker)
t1.setName('T1')
t2 = threading.Timer(3, thread_worker)
t2.setName('T2')
print(Fore.WHITE)
logging.debug('Starting timers')
t1.start()
t2.start()

logging.debug('waiting before canseling %s', t2.getName())
time.sleep(2)
logging.debug('canseling %s', t2.getName())
t2.cancel()
print(Fore.WHITE, 'Done!')
