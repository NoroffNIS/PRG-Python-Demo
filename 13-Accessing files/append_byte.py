file = open('text_file', 'rb')
text = ''
for line in file:
    text += line
file.close()
print(text)

e = text.count('e')
a = text.count('a')
nl = text.count('\n')

file_a = open('text_file', 'a')
file_a.write('Its {} e\'s in the file!\n'.format(e))
file_a.write('Its {} a\'s in the file!\n'.format(a))
file_a.write('Its {} lines in the file!\n'.format(nl))
file_a.write('ÆØÅ')
file_a.close()
