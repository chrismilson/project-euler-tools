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
    else:
        return 1
    return 0

def setupMakefile(path, name):
    filename = path + "/makefile"
    if not os.path.exists(filename):
        makefile = open(filename, "w")
    else:
        return # makefile already existed and we dont want to change it.

    makefile.write("FILES = " + name + ".c\n")
    makefile.write("CC = gcc\n")
    makefile.write("CFLAGS = \n")
    makefile.write("OBJECTS = $(FILES:%.c=%.o)\n")
    makefile.write("\n")
    makefile.write(".PHONY : all\n")
    makefile.write("all : $(OBJECTS)\n")
    makefile.write("\t@ $(CC) $(CFLAGS) $(OBJECTS) -o app\n")
    makefile.write("\t@ ./app\n")
    makefile.write("\t@ rm -rf $(OBJECTS) app\n")
    makefile.write("\n")
    makefile.write(".SILENT : $(OBJECTS)\n")
    makefile.write("$(OBJECTS) :\n")

    makefile.close()

def setupProgramfiles(path, number, name):
    filename = path + "/" + name + ".c"
    if not os.path.exists(filename):
        programFile = open(filename, "w")
    else:
        return # the file already existed and we dont want to change it.

    programFile.write("/* Chris Milson " + strftime("%B %Y", localtime()))
    programFile.write("\n")
    programFile.write("** Problem " + str(number) + "\n")
    programFile.write("* \n")
    programFile.write("* \n")
    programFile.write("* \n")
    programFile.write("* Answer :\n")
    programFile.write("*/ \n\n")
    programFile.write("/*\n**\n*/\n\n")
    programFile.write("#include <stdio.h>\n")
    programFile.write("#include <stdlib.h>\n")
    programFile.write("\n")
    programFile.write("int main(int argc, char **argv) {\n")
    programFile.write("\t\n")
    programFile.write("\treturn 0;\n")
    programFile.write("}")
