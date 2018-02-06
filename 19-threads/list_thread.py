import threading
from multiprocessing import Queue
import time
from colorama import Fore

numbers = []
for i in range(100):
    numbers.append(i)

def thread_worker(queue, color):
    while not queue.empty():
        print(color, 'Working:', threading.currentThread().getName(), '--', queue.get())
        time.sleep(0.1)

def build_worker_pool(queue, size):
  workers = []
  colors = [Fore.RED, Fore.GREEN, Fore.CYAN, Fore.YELLOW, Fore.WHITE]
  for i in range(size):
    worker = threading.Thread(target=thread_worker, args=(queue, colors[i]))
    worker.start()
    workers.append(worker)
  return workers

queue = Queue()
# Add the urls to process
for number in numbers:
    queue.put(number)

worker_threads = build_worker_pool(queue, 4)

for worker in worker_threads:
    worker.join()
