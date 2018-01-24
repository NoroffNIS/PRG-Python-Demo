class Player():
    '''Player class, the players spesificatons'''
    name = 'Name'
    count = 0

    def __init__( self, name, age ):
        Player.count += 1
        #Player.name = name
        #self.age = age

    def incrase_age(self):
        self.age += 1

    def get_age( self ):
        return self.age

#print('Start!')
#print(Player.name)
