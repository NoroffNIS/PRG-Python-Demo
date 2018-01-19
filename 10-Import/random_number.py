import random

def compare(guess, secret_number):
    #print(secret_number, '-', type(secret_number))
    #print(guess, '-', type(guess))
    if guess == secret_number:
        print('You guessed correct!')
        return True
    else:
        print('You guessed wrong!')
        return False

def up_or_down(guess, secret_number):
    if guess < secret_number:
        print('Guess higher!')
    else:
        print('Guess lower!')

low = 0
high = 100
secret_number = random.randint(low,high)
round_count = 0
print('The Gussing Game!!')
print('I`m thinking on a number between ', low, ' and', high,'.'\
        'can you guess the number?')

while True:
    round_count += 1
    guess = int(input('Type in the number>'))
    won = compare(guess, secret_number)
    if won:
        print('You did it in', round_count,'times!')
        break
    up_or_down(guess, secret_number)

        
