from shape import *

class Rectangle(Shape):
    name = 'Regtangle'
    
    def areal(self):
        return self.height * self.width

    def volum(self):
        return self.height * self.width * self.depth
