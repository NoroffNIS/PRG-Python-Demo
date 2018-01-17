num_global = 4

def addition():
    global num_local
    global num_global
    num_local = 6
    num_global += 4
    print(num_local, '--',num_global)

addition()
print(num_local, '--',num_global)
