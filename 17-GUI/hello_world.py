from tkinter import *

root = Tk()
root.title('First window')

label = Label(root, text='Hello world!', bg='yellow')
label.pack(padx = 200, pady = 50)

root.mainloop()
