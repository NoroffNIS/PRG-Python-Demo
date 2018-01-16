user_input = input('Programming at Noroff')
try:
    binary = 2**user_input
    print(binary)
except TypeError as msg:
    print('There is an error in the input!')
    print(msg)
