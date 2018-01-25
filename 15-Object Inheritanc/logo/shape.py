from brick import *
class Shape(Brick):
    count = 0
    width = 0
    height = 0
    depth = 0

    def __init__(self):
        Shape.count += 1

    def set_width(self, width):
        self.width = width

    def get_width(self):
        return self.width

    def set_height(self, height):
        self.height = height

    def get_height(self):
        return self.height

    def set_depth(self, depth):
        self.depth = depth

    def get_depth(self):
        return self.depth
