user_input = input('Type in a number')
try:
    binary = 2**user_input
    print(binary)
except TypeError as msg:
    print('There is an error in the input!')
    print(msg)
