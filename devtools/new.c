/* Chris Milson May 2017
**
* This is a program to help set up new problems; going through the ever
* expanding list of problems is becoming a task in itself.
*
* The idea is that I will be able to do
*
*   ./new 15 "name"
*
* and I will be greeted by a nice new folder containing everything I need.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "setup.h"

int main(int argc, char **argv) {
  int c = 0;
  // n - number
  int number;
  int nflag = 0;
  // N - name
  char *name = NULL;
  int Nflag = 0;
  // l - language (optional - defaults to c)
  char *language = NULL;
  int lflag = 0;
  // c - commit tag
  int cflag = 0;

  while ((c = getopt(argc, argv, "n:N:l::c")) != -1) {
    switch (c) {
      case 'n':
        nflag = 1;
        number = atoi(optarg);
        break;
      case 'N':
        Nflag = 1;
        name = optarg;
        break;
      case 'l':
        lflag = 1;
        language = optarg;
        break;
      case 'c':
        cflag = 1;
        break;
      default:
        printf("Something went wrong...\n");
        return 1;
    }
  }

  // Check that the arguments have been entered.
  if (!nflag) {
    printf("You need to give a number.\n");
    printf("Use -n \"number\"\n");
    return 1;
  }
  if (!Nflag) {
    printf("You need to give a name.\n");
    printf("Use -N \"name\"\n");
    return 1;
  }
  if (!lflag) {
    language = "c";
  }

  // Set up the necessary files.
  generateContainingFolder(number);

  generateMakefile(name, number, language);

  generateProgramFiles(name, number, language);

  if (cflag) {
    initGitRepo(number);
  }
}
