file = open('text_file', 'r')
text = ''
for line in file:
    text += line
file.close()
print(text)
e = text.count('e')
a = text.count('a')
nl = text.count('\n')

file = open('text_file', 'a')
file.write('Its {} e\'s in the file!\n'.format(e))
file.write('Its {} a\'s in the file!\n'.format(a))
file.write('Its {} lines in the file!\n'.format(nl))
file.close()
