from shape import *

class Rectangle(Shape):
    name = 'Regtangle'

    def arealR(self):
        self.height = height *34
        return self.height * self.width

    def volumR(self):
        return self.height * self.width * self.depth
