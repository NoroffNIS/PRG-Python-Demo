class Player:
    '''Player class, the players spesificatons'''
    name = 'Name'
    count = 0

    def __init__( self, name, age):
        Player.count += 1
        self.name = name
        self.age = age

    def incrase_age( self ):
        self.age += 1

    def get_age( self ):
        return self.age

    def __del__(self):
        print('Player object deleted!')
        
class Coach:
    name = 'name'
#print('Start!')
#print(Player.name)
