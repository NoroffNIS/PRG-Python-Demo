from tkinter import *

def getCond(par):
    first = par
    print(first)

root = Tk()
root.title('First window')
first = ''
names = ['1','2','3','4','5','6']
for item in names:
    Button(root, text=str(item), command=lambda i=item: getCond(i)).pack()
Button(root, text='Exit', command=exit).pack()
root.mainloop()
