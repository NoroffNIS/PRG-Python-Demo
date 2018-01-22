import pickle, os

if not os.path.isfile('data.dat'):
    data = [0,1]
    data[0] = input('Enter a name:')
    data[1] = input('Enter a address:')
    file = open('data.dat', 'wb')
    pickle.dump(data, file)
    file.close()
else:
    file = open('data.dat', 'rb')
    data = pickle.load(file)
    file.close()
    print('Name:', data[0],'\nAddress:', data[1])
