import threading

def thread_worker():
    print('Working:',\
        threading.currentThread().getName())
    return

for i in range(5):
    threading.Thread(target=thread_worker).start()
