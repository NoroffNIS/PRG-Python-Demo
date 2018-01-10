num = input('Type in a number between 0-10:')
print(num.isdigit())
if num.isdigit():
    num = int(num)
else:
    print('Program end!')
    SystemExit()

print('Num:', num, 'Type:', type(num))
#print('num < 10 ->', num >= 10)

if num >= 0 and num <=10:
    print('The', num, 'is less than 10!')

print('Program end!')
