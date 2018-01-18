def increment():
    i = 10
    while True:
        yield i
        i -= 1

inc = increment()
print('1',next(inc))
print('2',next(inc))
print('3',next(inc))
print('4',next(inc))
print('5',next(inc))
print('6',next(inc))
