count = 0
bit = 0
addverb = ''
while count < 41:
    bit = 2**count
    if bit <1024:
        output = bit
        addverb = 'Byte'
    elif bit <1048576:
        output = bit/1024
        addverb = 'Kilobyte'
    elif bit < 1073741824:
        output = bit/1048576
        addverb = 'Megabyte'
    elif bit < 1099511627776 :
        output = bit/1073741824
        addverb = 'Gigabyte'
    else:
        output = bit
        addverb = 'Byte'

    print(count,' -- ', output,addverb)
    count +=1
