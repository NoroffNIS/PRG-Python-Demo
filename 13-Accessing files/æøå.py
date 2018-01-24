
nfile = open('norske_bokstaver', 'w+')
norske_bokstaver = 'Norsk: æ ø å - Æ Ø Å\n'
nfile.write(norske_bokstaver)
nfile.close()

nfile = open('norske_bokstaver', 'a+b')
norske_bokstaver_raw = norske_bokstaver.encode('utf-8')
print(norske_bokstaver_raw)
nfile.write(norske_bokstaver_raw)
nfile.close()

nfile = open('norske_bokstaver', 'a+')
norske_bokstaver = norske_bokstaver_raw.decode('utf-8')
nfile.write(norske_bokstaver)
nfile.close()
