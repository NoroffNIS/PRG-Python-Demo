numbers = [1,2,3,4,5,6,7,8,9,10]
print('Output:',end=' ')
for number in numbers:
    print(number, end=',')

print()

char = ['B', 'O', 'K']
fruits = ['Banana', 'Orange', 'Kiwi']
print('Output:',end=' ')
for fruit in fruits:
    print(fruit, end=', ')

print()

char = ['B', 'O', 'K', 'L']
fruits = ['Banana', 'Orange', 'Kiwi']
print('Output:')
for item in zip(char, fruits):
    print(item)

print()

fruits = ['Banana', 'Orange', 'Kiwi']
print('Output:')
for item in enumerate(fruits):
    print(item)


fruits_dict = {'Banana':'Yellow', 'Orange':'Orange', 'Kiwi':'Green'}
print('Output:')
for fruit, color in fruits_dict.items():
    print(fruit, 'is', color,'!')
