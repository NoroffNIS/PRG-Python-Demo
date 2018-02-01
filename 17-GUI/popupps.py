from tkinter import *
import tkinter.messagebox as box
import inspect

all_functions = inspect.getmembers(box, inspect.isfunction)
root = Tk()

def popup(object):
    object(str(object.__name__), str(object.__doc__))

for func in all_functions:
    f = getattr(box, func[0])
    Button(root, text=str(f.__name__), command=lambda i=f:popup(i)).pack(side=LEFT)

root.mainloop()
