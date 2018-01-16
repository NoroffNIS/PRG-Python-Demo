count_1 = 0
while count_1 < 3:
    print('Counter outerloop:',count_1)
    count_2 = 0
    while count_2 < 3:
        print('\t\tCounter innerloop:',count_2)
        count_2 +=1
    count_1 += 1

print()

for count_1 in range(3):
    print('Counter outerloop:',count_1)
    for count_2 in range(3):
        print('\t\tCounter innerloop:',count_2)
