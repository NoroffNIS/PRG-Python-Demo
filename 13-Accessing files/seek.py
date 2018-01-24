with open('text_file_1', 'r+') as file:
        file.seek(22)
        print('Position:', file.tell())
        print(file.readline())
        file.seek(49)
        print('Position:', file.tell())
        print(file.readlines())
