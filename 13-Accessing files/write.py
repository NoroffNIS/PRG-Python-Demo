file = open('text_file', 'wb')
text = 'I have a problem\n'
text += 'I decide to bring it to stack overflow\n'
text += 'I awkwardly write down my question\n'
text += 'I realize that the question doesn\'t make any sense\n'
text += 'I take 15 minutes to rethink how to ask my question\n'
text += 'I realize that I\'m attacking the problem from a wrong direction entirely.\n'
text += 'I start from scratch and find my solution quickly.\n'
text += 'ÆØÅ'
file.write(text)
file.close()
print('Done!')
