class player():
    '''Player class, the players spesificatons'''
    name = 'Brad'
    jersey_number = 15
    age = 25

    def incrase_age(self):
        self.age += 1

player1 = player()
print(player1.__doc__)
print(player1.name)
player1.name = 'Brage'
print(player1.name)

print(player1.age)
player1.incrase_age()
print(player1.age)
