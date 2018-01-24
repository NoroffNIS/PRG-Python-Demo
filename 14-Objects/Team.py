from Player import *

print('Team A')
player_1 = Player('Jens', 24)
player_2 = Player('Rene', 29)


print('Numer of players:', Player.count)


print('Name:',getattr(player_1, 'name'))
setattr(player_1, 'name', 'Brage')
print('Name:',getattr(player_1, 'name'))
print('hasattr:', hasattr(player_1, 'age'))
print('Age 1:', player_1.get_age())
print('Name:',player_2.name)
print('Age 2:', player_2.get_age())
player_1.incrase_age()
print('Age 1:',player_1.get_age())
print('Age 2:', player_2.get_age())

print('hasattr:', hasattr(player_1, 'age'))
print('delattr:', delattr(player_1, 'age'))
print('hasattr:', hasattr(player_1, 'age'))

'''
player1 = Player()
print(player1.__doc__)
print(player1.name)
player1.name = 'Brage'
print(player1.name)

print(player1.age)
player1.incrase_age()
print(player1.age)
'''
