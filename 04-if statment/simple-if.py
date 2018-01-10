num = int(input('Type in a number between 0-10:'))
print('Num:', num, 'Type:', type(num))
#print('num < 10 ->', num >= 10)

if num <= 10 and num >= 0:
    print('The', num, 'is less than 10 and greater than 0!')
else:
    print('The', num, 'is out of range!')

print('Program end!')
