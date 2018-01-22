with open('text_file_1', 'r+') as file:
    file.seek(20)
    print('Position:', file.tell())
    print(file.read())
    file.seek(49)
    print('Position:', file.tell())
    print(file.read())
