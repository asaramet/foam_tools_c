#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "initials.h"
#include "general.h"
#include "../lib/run.h"
#include "../lib/get.h"

static void help(char *progname)
{
  char *text = "\n\tPre-processing an OpenFOAM case\n\n"
  "\tUsage: ";
  printf("%s%s", text, progname);
  text = " [OPTIONS]\n\n\tOPTIONS:\n"
  "\t   _\t\t\t\t\t\tCollect all data into 'report.txt'\n"
  "\t  -h, --help\t\t\t\t\tShow this message\n"
  "\t  -g, --general\t\t\t\t\tShow general data\n"
  "\t  -i, --initials\t\t\t\tPre-process initial conditions\n"
  "\t  -f [FOLDER PATH], --folder [FOLDER PATH]\tSpecify case folder as a string \"FOLDER PATH\""
  ", if -f missing FOLDER PATH = current path\n\n"
  "\t  -w [REPORT FILE], --write [REPORT FILE]\tSpecify report data file name as a string \"REPORT FILE\""
  ", if -w missing REPORT FILE = standart output (stdout)\n"
  "\tEXAMPLES:\n"
  "\t  Get initial/boundary conditions data from ${HOME}/OpenFOAM/myCase:\n\n"
  "\t    ";
  printf("%s%s", text, progname);
  text = " -i -f ${HOME}/OpenFOAM/myCase\n\n";
  printf("%s", text);
  text = "\t  Collect all data from case ${HOME}/OpenFOAM/myCase into 'report.txt':\n\n"
  "\t    ";
  printf("%s%s", text, progname);
  text = " -f ${HOME}/OpenFOAM/myCase -w report.txt\n\n";
  printf("%s", text);
}

// check if it is a valid argument/option
int isOption(char *value) {
  char *options[] = {"-i", "--initials", "-h", "--help", "-f", "--folder", "-w", "--write", NULL};
  int i = 0;
  while (options[i]) {
    if (strcmp(options[i], value) == 0) return 1;
    i++;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  update_path(strcat(getenv("PWD"), "/test/cmds")); // TODO remove this in production

  if (*cmd_out("foamVersion") == EXIT_FAILURE) {
    printf("ERROR: OpenFOAM not found on the system!\n");
    exit(EXIT_FAILURE);
  }

  FILE *outputFile = stdout; // output to file or stdout
  char *caseFolder = getenv("PWD"); // define caseFolder
  for (int i = 1; i < argc; i++){
    if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--write") == 0) {
      if (argv[i+1] == NULL || isOption(argv[i+1]) == 1) {
        printf("ERROR: Output file asked but not specified! Got: %s\n", argv[i+1]);
        exit(EXIT_FAILURE);
      };
      outputFile = fopen(argv[i+1], "w");
    }
    if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--folder") == 0) {
      struct stat stats;
      stat(argv[i+1], &stats);
      if (argv[i+1] == NULL || isOption(argv[i+1]) == 1 || !S_ISDIR(stats.st_mode)) {
        printf("ERROR: Specified case folder, %s, doesn't exist!\n", argv[i+1]);
        fclose(outputFile);
        exit(EXIT_FAILURE);
      }
      caseFolder = argv[i+1];
    }
  }

  for (char **pargv = argv+1; *pargv != argv[argc]; pargv++) {
    if (strcmp(*pargv, "-h") == 0 || strcmp(*pargv, "--help") == 0) {
      help(argv[0]);
      return 0;
    } else if (strcmp(*pargv, "-g") == 0) {
      general(outputFile, caseFolder);
    } else if (strcmp(*pargv, "-i") == 0) {
      initials(outputFile, caseFolder);
    }
  }
  fclose(outputFile);
  return EXIT_SUCCESS;
}
