from Player import *
#for attr in dir(Coach):
#    print(attr)

player = Player('Roar', 34)
print(id(player))

player2 = Player('Arne', 32)
print(id(player2))
del player2
