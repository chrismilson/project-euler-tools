import os
from time import strftime, localtime

def setup(number, name):
    path = "./problems/problem-" + str(number)
    if setupFolder(path):
        print("The problem already existed...")
        print("Try removing the files if you wanted to start from scratch.")
        return

    setupMakefile(path, name)
    setupProgramfiles(path, number, name)

def setupFolder(path):
    if not os.path.exists(path):
        os.makedirs(path)
        print("New folder generated at " + path)
    else:
        return 1
    return 0

# Since this is a python program; we will just use the makefile to execute the
# python code as if it were a bash script.
# If I should change each problem to have a build.sh script instead of a
# makefile please do not hesitate to get in touch with me and inform me of the
# convention.
def setupMakefile(path, name):
    filename = path + "/makefile"
    if not os.path.exists(filename):
        makefile = open(filename, "w")
    else:
        return # makefile already existed and we dont want to change it.

    makefile.write(".PHONY : all\n")
    makefile.write("all : \n")
    makefile.write("\tpython " + name + ".py\n")

    makefile.close()

def setupProgramfiles(path, number, name):
    filename = path + "/" + name + ".py"
    if not os.path.exists(filename):
        programFile = open(filename, "w")
    else:
        return # the file already existed and we dont want to change it.

    programFile.write("\"\"\" Chris Milson " +  strftime("%B %Y", localtime()))
    programFile.write("\n")
    programFile.write("Problem " + str(number) + "\n\n\n\n")
    programFile.write("Answer : \n")
    programFile.write("\"\"\"\n")
