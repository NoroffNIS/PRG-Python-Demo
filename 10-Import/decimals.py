from decimal import *

item = 0.7
rate = 1.05

tax = item * rate
total = item + tax
print('Total: {:0.2f} \nItem: {:0.2f}'.format(total, tax))


item = Decimal(0.7)
rate = Decimal(1.05)

tax = item * rate
total = item + tax
print('Total: {:0.2f} \nItem: {:0.2f}'.format(total, tax))
