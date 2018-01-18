import re
text = 'The module defines several functions, constants, and an exception.\
 Some of the functions are simplified versions of the full featured methods \
 for compiled regular expressions. Most non-trivial applications always use \
 the compiled form. Changed in version 3.6: Flag constants are now instances \
 of RegexFlag, which is a subclass of'



pattern = re.compile(r's{2}')
matches = pattern.match(text)

for match in matches.group():
    print(match)
