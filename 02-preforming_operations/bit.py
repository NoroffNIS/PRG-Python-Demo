a = 10
b = 4

print('a =', a, 'b=', b)
print('a =', bin(a), 'b=', bin(b))
#OR
a = a | b
print('a =', a, 'b=', b)
print('a =', bin(a), 'b=', bin(b))
#AND
a = 10
b = 4
a = a & b
print('a =', a, 'b=', b)
print('a =', bin(a), 'b=', bin(b))
print('--------')
#NOT
a = 10
b = 5
a = ~b
print('a =', a, 'b=', b)
print('a =', bin(a), 'b=', bin(b))

#Shift left by 2
print('a =', a, 'b=', b)
print('a =', bin(a), 'b=', bin(b))
a = a << 2
print('a =', bin(a), 'b=', bin(b))
print('a =', a, 'b=', b)

print('a =', a, 'b=', b)
print('a =', bin(a), 'b=', bin(b))
a = a >> 2
print('a =', bin(a), 'b=', bin(b))
print('a =', a, 'b=', b)
