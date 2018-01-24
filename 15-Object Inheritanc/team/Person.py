from datetime import date, datetime

class Person:
    '''Person Class, spesification for a person'''
    name = 'Name'
    address = 'Address'
    birtdate = 'dd-mm-yyyy'
    height = 0

    def __init__(self):
        Person.count += 1

    def set_name(self, name):
        self.name = name

    def set_address(self, address):
        self.addres = address

    def set_heigth(self, height):
        self.height = height

    def set_birtdate(self, birtdate):
        self.birtdate = birtdate
        print('B:', self.birtdate)

    def get_age(self):
        self.born = datetime.strptime(self.birtdate, '%d-%m-%Y')
        self.today = date.today()
        return self.today.year - self.born.year - ((self.today.month, self.today.day) < (self.born.month, self.born.day))
