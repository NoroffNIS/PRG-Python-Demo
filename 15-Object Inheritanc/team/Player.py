from Person import *

class Player(Person):
    '''Player class, the players spesificatons'''
    count = 0
    age_limit = 18

    def __init__( self, name ):
        Player.count += 1
        self.name = name
        print('init:', self.name)

    def allowed_to_play(self):
        return self.age_limit >= self.get_age()

    def player_info(self):
        print('Name:\t',self.name)
        print('Age:\t',self.get_age())
        print('Allowed to play:', self.allowed_to_play())
