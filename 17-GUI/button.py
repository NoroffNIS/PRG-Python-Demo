from tkinter import *
root = Tk()
root.title('First window')
counter = 0

vtext = StringVar()
vtext.set('Hello world!')

def switch_bg():
    if root.cget('bg') == 'red':
        root.configure(bg = 'gray')
    else:
        root.configure(bg = 'red')

def count():
    global counter
    counter += 1
    vtext.set(str(counter))

label = Label(root, textvariable=vtext)
btn_switch = Button(root, text='Switch!', command=switch_bg)
btn_count = Button(root, text='Count!', command=count)
btn_exit = Button(root, text='Exit!', command=exit)

label.pack(padx = 100, pady = 20)
btn_switch.pack(padx = 100, pady=40)
btn_switch.pack(padx = 50, pady=60)
btn_count.pack(padx = 75, pady=60)
btn_exit.pack(padx = 100, pady=60)

root.mainloop()
