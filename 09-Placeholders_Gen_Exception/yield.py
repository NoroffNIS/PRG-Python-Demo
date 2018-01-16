def increment():
    i = 0
    while True:
        print('i:', i)
        yield i
        i += 1
        print('i:', i)

inc = increment()

print(next(inc))
print(next(inc))
print(next(inc))
print(next(inc))
