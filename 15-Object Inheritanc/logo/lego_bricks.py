from rectangle import *
from triagnle import *

class LegoBrick(Rectangle, Triangle):
    h = 10
    b = 10/2
    set_width = b
    set_height = h

    def area_Brick():
        return arealR() + arealT()


lego_b_R = Rectangle()
lego_b_R.set_width(20)
lego_b_R.set_height(20)
lego_b_R.set_depth(20)
lego_b_R.nbrick = 6
lego_b_R.color = 'Red'
print(lego_b_R.name)
print('\tAreal:',lego_b_R.areal())
print('\tVolum:',lego_b_R.volum())
print('\tBricks:',lego_b_R.nbrick)
print('\tColor:',lego_b_R.color)


print('')
lego_b_T = Triangle()
lego_b_T.set_width(20)
lego_b_T.set_height(20)
lego_b_T.set_depth(20)
print(lego_b_T.name)
print('\tAreal:',lego_b_T.areal())
print('\tVolum:',lego_b_T.volum())
