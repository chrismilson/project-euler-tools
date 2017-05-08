#include "setup.h"

char *month(int mnth);

char *month(int mnth) {
  switch(mnth) {
    case 0:  return "January";
    case 1:  return "February";
    case 2:  return "March";
    case 3:  return "April";
    case 4:  return "May";
    case 5:  return "June";
    case 6:  return "July";
    case 7:  return "August";
    case 8:  return "September";
    case 9:  return "October";
    case 10: return "November";
    case 11: return "December";
    default: return "";
  }
}


int generateContainingFolder(int number) {
  // Make the new folder.
  char folderName[80];
  sprintf(folderName, "problems/problem-%d", number);

  if (access(folderName, F_OK) != -1) {
    printf("This Problem already has a folder...\n");
    return 1;
  }

  pid_t pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Did not fork properly.\n");
  } else if (pid == 0) {
    if (execl("/bin/mkdir", "mkdir", folderName, NULL)) {
      fprintf(stderr, "Could not make the folder.\n");
      exit(1);
    }
    exit(0);
  } else if (pid > 0) {
    wait(NULL);
  }
  return 0;
}

int generateMakefile(const char *name, int number, const char *language) {
  // char extension[10];
  // extension = getExtension(language);
  char fileName[80];
  sprintf(fileName, "problems/problem-%d/makefile", number);

  if (access(fileName, F_OK) != -1) {
    printf("This Problem already has a makefile...\n");
    return 1;
  }

  FILE *makefile = fopen(fileName, "w");

  if (!makefile) {
    fprintf(stderr, "Could not generate makefile.\n");
    return 1;
  }

  fprintf(makefile, "FILES = %s.c\n", name);
  fprintf(makefile, "CC = gcc\n");
  fprintf(makefile, "CFLAGS =\n");
  fprintf(makefile, "OBJECTS = $(FILES:%%.c=%%.o)\n");
  fprintf(makefile, "\n");
  fprintf(makefile, ".PHONY : all\n");
  fprintf(makefile, "all : $(OBJECTS)\n");
  fprintf(makefile, "\t@ $(CC) $(CFLAGS) $(OBJECTS) -o app\n");
  fprintf(makefile, "\t@ ./app\n");
  fprintf(makefile, "\t@ rm -rf $(OBJECTS) app\n");
  fprintf(makefile, "\n");
  fprintf(makefile, ".SILENT : $(OBJECTS)\n");
  fprintf(makefile, "$(OBJECTS) :\n");

  fclose(makefile);
  return 0;
}

int generateProgramFiles(const char *name, int number, const char *language) {
  // char extension[10];
  // extension = getExtension(language);
  char fileName[80];
  sprintf(fileName, "problems/problem-%d/%s.c", number, name);

  if (access(fileName, F_OK) != -1) {
    printf("This Problem already has a program file...\n");
    return 1;
  }

  FILE *programfile = fopen(fileName, "w+");

  if (!programfile) {
    fprintf(stderr, "Could not generate program file.\n");
    return 1;
  }

  time_t t = time(NULL);
  struct tm *now = localtime(&t);

  fprintf(programfile, "/* Chris Milson %s ", month(now->tm_mon));
  fprintf(programfile, "%d\n", 1900 + now->tm_year);
  fprintf(programfile, "** Problem %d\n", number);
  fprintf(programfile, "* \n");
  fprintf(programfile, "* \n");
  fprintf(programfile, "* \n");
  fprintf(programfile, "* Answer :\n");
  fprintf(programfile, "*/ \n\n\n\n");

  fprintf(programfile, "#include <stdio.h>\n");
  fprintf(programfile, "#include <stdlib.h>\n");
  fprintf(programfile, "\n");
  fprintf(programfile, "int main(int argc, char **argv) {\n");
  fprintf(programfile, "\t\n");
  fprintf(programfile, "\treturn 0;\n");
  fprintf(programfile, "}");

  fclose(programfile);
  return 0;
}

int initGitRepo(int number) {
  char problem[80];
  sprintf(problem, "problems/problem-%d", number);

  pid_t pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed.\n");
  } else if (pid == 0) { // is the child
    pid_t pid2 = fork();
    if (pid2 < 0) {
      fprintf(stderr, "Second fork failed.\n");
      exit(1);
    } else if (pid2 == 0) { // grandchild
      if (execlp("git", "git", "add", problem, NULL)) {
        fprintf(stderr, "Could not stage changes.\n");
        exit(1);
      }
      exit(0);
    } else if (pid2 > 0) { // is still the child
      wait(NULL);
      sprintf(problem, "\"Init Problem %d\"", number);
      if (execlp("git", "git", "commit", "-m", problem, NULL)) {
        fprintf(stderr, "Could not commit changes.\n");
        exit(1);
      }
      exit(0);
    }
  } else if (pid > 0) { // is the parent
    wait(NULL); // wait for child to exit before continuing.
    return 0;
  }
}
