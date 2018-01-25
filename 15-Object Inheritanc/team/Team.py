from Player import *

print('Team A')
player1 = Player('Jens')
player1.set_birtdate('29-05-1989')
player2 = Player('Brage')
player2.set_birtdate('29-05-2000')

player2.player_info(player1)
player1.player_info(player2)
