address_book = {
    'fname':'First name',
    'lname':'Last name',
    'course':{'NIS':['LAW','SEC','RAS'], 'NSA':['PBL', 'IIS', 'OFS']}}

print(address_book['lname'])
tmp_fname = input('Type in you first name ')
tmp_lname = input('Type in you last name')

address_book['fname'] = tmp_fname
address_book['lname'] = tmp_lname
print(address_book.get('course').get('NIS'))
