from tkinter import *

root = Tk()

frame_top = Frame(root, height=200, width=200, bg='red')
frame_left = Frame(root, height=200, width=200, bg='yellow')
frame_right = Frame(root, height=200, width=200, bg='blue')
frame_bottom = Frame(root, height=200, width=200, bg='green')
#frame_center = Frame(root)

frame_top.pack(side=TOP, fill= BOTH)
frame_left.pack(side=LEFT, fill= BOTH)
frame_right.pack(side=RIGHT, fill= BOTH)
frame_bottom.pack(side=BOTTOM, fill= BOTH)
#frame_center.pack(side=CENTER)

root.mainloop()
