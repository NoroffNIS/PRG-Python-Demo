string1 = 'Burger'
string2 = 'Frites'
var = 12.12367
print('{1} and {0} = {2:22.9f}'.format(string1, string2, var))
string3 = '{1} and {0} = {2:012.3f}'.format(string1, string2, var)

string4 = string3.replace('e','*')
print(string4)

snacks = '%s and %s %-13d  '%(string1, string2, var)
print(snacks)
