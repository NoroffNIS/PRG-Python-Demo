import requests
from threading import Thread
import sys
import time
import getopt
import re
import hashlib
from colorama import Fore
import traceback
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities

def usage():
    print("Usage:")
    print("		-w: url (http://somesite.com/FUZZ)")
    print("		-t: threads")
    print("		-f: dictionary file\n")
    print("example: forzabruta.py -w http://www.targetsite.com/FUZZ -t 5 -f common.txt\n")


class request_performer(Thread):
    def __init__(self, word, url, hidecode):
        Thread.__init__(self)

        try:
            self.word = word.split("\n")[0]
            self.urly = url.replace('FUZZ', self.word)
            self.url = self.urly
            self.hidecode = hidecode
        except Exception as e:
            print('Thread error:',e)

    def md5(self, fname):
        return hashlib.md5(fname).hexdigest()

    def run(self):
        try:
            self.start = time.time()
            self.r = requests.get(self.url)
            self.elaptime = time.time()
            self.totaltime = str(self.elaptime - self.start)
            self.lines = str(self.r.content.count(b'\n'))
            self.chars = str(len(self.r._content))
            self.words = str(len(re.findall(b"\S+", self.r.content)))
            self.code = str(self.r.status_code)
            self.hash = self.md5(self.r.content)

            if self.hidecode != self.code:
                if '200' <= self.code < '300':
                    print('{:.8}'.format(self.totaltime) , "  \t" , Fore.GREEN, self.code ,Fore.WHITE, "\t" , self.chars , "\t" , self.words , "\t" , self.lines , "\t" , self.hash , "\t" , '{:10}'.format(self.word),"\t" , self.url)
                elif '400' <= self.code < '500':
                    print('{:.8}'.format(self.totaltime) , "  \t" , Fore.RED, self.code ,Fore.WHITE,  "\t" , self.chars , "\t" , self.words , "\t" , self.lines , "\t" , self.hash ,  "\t" , '{:10}'.format(self.word),"\t" , self.url)
                elif '300' <= self.code < '400':
                    print('{:.8}'.format(self.totaltime) , "  \t" , Fore.CYAN, self.code ,Fore.WHITE,  "\t" , self.chars , "\t" , self.words , "\t" , self.lines , "\t" , self.hash ,  "\t" , '{:10}'.format(self.word),"\t" , self.url)
            else:
                pass
            i[0] = i[0] - 1  # Here we remove one thread from the counter

        except Exception as e:
            print('Run error', e)

def start(argv):
    if len(sys.argv) < 5:
        usage()
        sys.exit()
    try:
        opts, args = getopt.getopt(argv, "w:f:t:c:")
    except getopt.GetoptError:
        print("Error en arguments")
        sys.exit()
    hidecode = 000
    for opt, arg in opts:
        print(opt,'=',arg)
        if opt == '-w':
                url = arg
        elif opt == '-f':
                dict = arg
        elif opt == '-t':
                threads = int(arg)
        elif opt == '-c':
                hidecode = arg
    try:
        f = open(dict, "r")
        words = f.readlines()
    except:
        print("Failed opening file: " + dict + "\n")
        sys.exit()

    launcher_thread(words, threads, url, hidecode)


def launcher_thread(names, th, url, hidecode):
    global i
    i = []
    resultlist = []
    i.append(0)
    print("-"*130)
    print('{:8}\t{:4}\t{:5}\t{:5}\t{:7}\t{:32}\t{:10}\t{:20}'.format('Time', 'Code','Chars', 'Words','tLines','MD5', 'Site', 'URL'))
    print("-"*130)
    while len(names):
        try:
            if i[0] < th:
                n = names.pop(0)
                i[0] = i[0] + 1
                thread = request_performer(n, url, hidecode)
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
