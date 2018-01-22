string = 'Noroff'
print(string)
print(string.capitalize())
print(string.title())
print(string.upper())
print(string.lower())
print(string.swapcase())

print( '\nCentered:\t' , string.center( 30 , '*' ) )
print( '\nUppercase:\t' , string.upper() )
print( '\nJoined:\t\t' , string.join( '**' ) )
print( '\nJustified:\t' ,string.rjust( 30 , '*' ) )
print( '\nReplaced:\t' , string.replace( 'o' , '*' ) )
