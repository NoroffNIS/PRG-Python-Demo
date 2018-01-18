# a=97 z=123
def alphabet(rot):
    for l in range(26):
        print(chr(l+97), end='')
    print()
    for l in range(26):
        if l+rot < 26:
            print(chr(l+97+rot), end='')
        else:
            print(chr(l+97+rot-26), end='')
    print()
def encrypt(plaintext, rot):
    ciphertext = ''
    for letter in plaintext:
        if ord(letter)+rot < 123:
            #print(letter, 'ascii code:',ord(letter),'+rot', ord(letter)+rot, 'new letter:', chr(ord(letter)+rot))
            ciphertext += chr(ord(letter)+rot)
        else:
            #print(letter, 'ascii code:',ord(letter),'+rot', ord(letter)+rot-26, 'new letter:', chr(ord(letter)+rot-26))
            ciphertext += chr(ord(letter)+rot-26)
    return ciphertext

def decrypt(ciphertext, rot):
    plaintext = ''
    for letter in ciphertext:
        if ord(letter)-rot < 123:
            #print(letter, 'ascii code:',ord(letter),'+rot', ord(letter)+rot, 'new letter:', chr(ord(letter)+rot))
            plaintext += chr(ord(letter)-rot)
        elif ord(letter)-rot > 97:
            #print(letter, 'ascii code:',ord(letter),'+rot', ord(letter)+rot-26, 'new letter:', chr(ord(letter)+rot-26))
            plaintext += chr(ord(letter)-rot+26)
    return plaintext

plaintext = input('Type in a word to encrypt>')
ciphertext = ''
rot = 3
alphabet(rot)
ciphertext = encrypt(plaintext,rot)
print('Plaintext:', plaintext)
print('Ciphertext', ciphertext)
plaintext = decrypt(ciphertext,rot)
print('Plaintext:', plaintext)
print('Ciphertext', ciphertext)
