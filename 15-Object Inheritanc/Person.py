from datetime import date, datetime

class Person:
    '''Person Class, spesification for a person'''
    name = 'Name'
    address = 'Address'
    birtdate = 'dd.mm.yyyy'
    height = 0

    def set_name(self, name):
        Person.name = name

    def set_address(self, address):
        Person.addres = address

    def set_heigth(self, height):
        Person.height = height

    def set_birtdate(self, birtdate):
        Person.birthdate = birtdate
        print('B:', Person.birtdate)

    def get_age(self):
        self.born = datetime.strptime(Person.birtdate, '%d.%m.%Y')
        self.today = date.today()
        return self.today.year - self.born.year - ((self.today.month, self.today.day) < (self.born.month, self.born.day))
