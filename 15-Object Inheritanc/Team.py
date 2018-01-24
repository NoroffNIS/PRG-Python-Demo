from Player import *

print('Team A')
player = Player('Jens')
player.set_birtdate('29.05.1989')
print('Name:',player.name)
print('Numer of players:', Player.count)
print('Age:', player.get_age())
