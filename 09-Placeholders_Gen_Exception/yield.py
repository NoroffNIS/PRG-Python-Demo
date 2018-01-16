def increment():
    i = 0
    while True:
        yield i
        i += 1

inc = increment()

print(next(inc))
print(next(inc))
print(next(inc))
    
