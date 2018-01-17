def fy(num):
    if num == 0:
        return 0
    elif num == 1:
        return 1
    else:
        print(num)
        return fy(num-1)

for num in range(10, 0, -1):
    print(fy(num))
