import sys, os
from subprocess import call

filename = "./new"

tool = open(filename, "w") # not worried whether it exists or not.

tool.write("#!/bin/bash\n")

tool.write("python3 devtools/setup-main.py \"$@\"")

call(["chmod", "+x", "./new"])
