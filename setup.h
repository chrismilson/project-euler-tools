#ifndef MAKEFILES_H
#define MAKEFILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int generateContainingFolder(int number);

int generateMakefile(const char *name, int number, const char *language);

int generateProgramFiles(const char *name, int number, const char *language);

int initGitRepo(int number);

#endif
