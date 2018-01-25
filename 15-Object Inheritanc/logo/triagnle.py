from shape import *

class Triangle(Shape):
    name = 'Triangle'

    def areal(self):
        return (self.height * self.width)/2

    def volum(self):
        self.base = self.areal()
        return self.base * self.depth
