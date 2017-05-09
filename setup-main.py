#/usr/bin/python3
# A program to aid the setup of new Project Euler problems.
from importlib import import_module as imp
import sys, getopt

def load_module(language):
    return {
        "c": imp("setup-c"),
        "python": imp("setup-python"),
    }.get(language.lower(), )

try:
    opts, args = getopt.getopt(sys.argv[1:], "hn:N:l:")
except getopt.GetoptError:
    print("new -n <number> -N <name> -l <language>")
    sys.exit(2)

nflag = Nflag = lflag = False
number = 0
name = language = ""

for opt, arg in opts:
    if opt == '-h':
        printHelp()
        sys.exit()
    elif opt in ("-n", "--number"):
        nflag = True
        number = arg
    elif opt in ("-N", "--name"):
        Nflag = True
        name = arg
    elif opt in ("-l", "--language"):
        lflag = True
        language = arg

# print("language = " + language)
# print("name = " + name)
# print("number = " + str(number))

setup = getattr(load_module(language), "setup", False)

if not setup:
    print("Could not set up " + language + " environment.")
    print("Currently there is no library to set up " + language)
    sys.exit(1)

setup(number, name)
