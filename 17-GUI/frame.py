from tkinter import *

import tkinter.messagebox as box

window = Tk()
window.configure(bg='blue')
window.title( 'Entry Example' )

window.cget('higth')
frame = Frame( window , bg='red', borderwidth=5)
entry = Entry( frame )

def dialog() :
	box.showinfo( 'Greetings' , 'Welcome ' + entry.get() )

btn = Button( window , text = 'Enter Name' , command = dialog )

btn.pack( side = RIGHT , padx = 5 )
entry.pack( side = LEFT )
frame.pack( padx = 20 , pady = 20 )

window.mainloop()
