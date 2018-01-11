to_do_list = []
input_value = ''
while input_value != 'exit':
    input_value = input(
    'Type in what to add to to-do list. \nExit the operation with "exit">')
    if input_value != 'exit':
        to_do_list.append(input_value)
        print('Added', input_value, 'to the to-do list')
    else:
        print('To-do list input is ending!')

print('To-do list: ', to_do_list)
print('Program ended!')
