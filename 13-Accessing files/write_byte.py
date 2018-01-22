file = open('text_file', 'wb')
text = b'I have a problem\n'
text += b'I decide to bring it to stack overflow\n'
text += b'I awkwardly write down my question\n'
text += b'I realize that the question doesn\'t make any sense\n'
text += b'I take 15 minutes to rethink how to ask my question\n'
text += b'I realize that I\'m attacking the problem from a wrong direction entirely.\n'
text += b'I start from scratch and find my solution quickly.\n'
file.write(text)
file.close()
print('Done!')
