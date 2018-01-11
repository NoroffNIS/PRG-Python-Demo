count = 0
while count <= 10:
    count +=1
    if count == 2:
        continue
    elif count == 5:
        pass
    elif count == 9:
        break
    else:
        print('Number ', count)

    print('loop round:', count)

print('end!')
