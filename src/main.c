#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "initials.h"
#include "../lib/run.h"
#include "../lib/get.h"

static void help(char *progname)
{
  char *text = "\n\tPre-processing an OpenFOAM case\n\n"
  "\tUsage: ";
  printf("%s%s", text, progname);
  text = " [OPTIONS]\n\n\tOPTIONS:\n"
  "\t   _\t\t\tCollect all data into 'report.txt'\n"
  "\t  -h\t\t\tShow this message\n"
  "\t  -i\t\t\tPre-process initial conditions\n"
  "\t  -f [FOLDER PATH]\tSpecify case folder as a string \"FOLDER PATH\""
  ", if -f missing FOLDER PATH = current path\n\n"
  "\tEXAMPLES:\n"
  "\t  Get initial/boundary conditions data from ${HOME}/OpenFOAM/myCase:\n\n"
  "\t    ";
  printf("%s%s", text, progname);
  text = " -i -f ${HOME}/OpenFOAM/myCase\n\n";
  printf("%s", text);
  text = "\t  Collect all data from case ${HOME}/OpenFOAM/myCase into 'report.txt':\n\n"
  "\t    ";
  printf("%s%s", text, progname);
  text = " -f ${HOME}/OpenFOAM/myCase\n\n";
  printf("%s", text);
}

static void report(char *caseFolder)
{
  FILE *fp = fopen("report.txt", "w");

  fprintf(fp, "Simulation Case:\t\t%s\n", caseFolder);
  fprintf(fp, "OpenFOAM Version:\t\t%s\n", cmd_out("foamVersion"));
  fprintf(fp, "Date and Time:\t\t\t%s\n", cmd_out("date"));
  fclose(fp);
}

int main(int argc, char *argv[]) {
  update_path(strcat(getenv("PWD"), "/test/cmds")); // TODO remove this in production
  if (*cmd_out("foamVersion") == EXIT_FAILURE) exit(EXIT_FAILURE);

  char *caseFolder;
  if (argc < 2) caseFolder = getenv("PWD");
  for (int i = 1; i < argc; i++){
    if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--folder") == 0) {
      if ((caseFolder = argv[i+1]) != NULL) break;
    }
    caseFolder = getenv("PWD");
  }

  for (char **pargv = argv+1; *pargv != argv[argc]; pargv++) {
    if (strcmp(*pargv, "-h") == 0 || strcmp(*pargv, "--help") == 0) {
      help(argv[0]);
      return 0;
    } else if (strcmp(*pargv, "-i") == 0) {
      initials(caseFolder);
      return 0;
    }
  }
  report(caseFolder);
  printf("report.txt created!\n");
  return 1;
}
