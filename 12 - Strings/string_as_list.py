string = 'Hello\nthis is a new line'
for letter in string:
    print(letter)

def display(s='Default'):
    '''Display an argumant value'''
    print(s)
'''
string = 'Hello\nthis is a new line'
display(string)
display('\n' in string)

string = r'Hello\nthis is a new line'
display(string)
display('\n' in string)

print('Display:', display.__doc__)
print('Name:', display.__name__)
print('Module:', display.__module__)
print('Defaults:', display.__defaults__)
'''
