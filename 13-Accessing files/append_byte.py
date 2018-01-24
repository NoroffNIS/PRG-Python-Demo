file = open('text_file', 'rb')
text = b''
for line in file:
    text += line
file.close()
print(text)

e = text.count(b'e')
a = text.count(b'a')
nl = text.count(b'\n')

file_a = open('text_file', 'ab')
file_a.write(b'Its {} e\'s in the file!\n'.format(e))
file_a.write(b'Its {} a\'s in the file!\n'.format(a))
file_a.write(b'Its {} lines in the file!\n'.format(nl))
file_a.close()
