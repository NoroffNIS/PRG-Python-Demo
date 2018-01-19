def ms_to_km():
    ms = float(input('type in a m/s speed>'))
    km_h = ms * 3.6
    print(ms,'m/s in km/h is:', km_h)

def km_to_ms(km_h):
    ms = km_h / 3.6
    return ms

while True:
    choise = input('Enter 1 for km/t or 2 for m/s, and 0 to quit>')
    if choise == '1':
        km_h = float(input('type in a km/h speed>'))
        ms = km_to_ms(km_h)
        print(km_h,'km/h in m/s is:', ms)
    elif choise == '2':
        ms_to_km()
    elif choise == '0':
        break
    else:
        print('Invalid input! try again!')
