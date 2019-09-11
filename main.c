#include <stdio.h>
#include <string.h>
#include "initials.h"

void help(char *progname)
{
  char *text = "\n\tPre-processing an OpenFOAM case\n\n"
  "\tUsage: ";
  printf("%s%s", text, progname);
  text = " [OPTIONS]\n\n\tOPTIONS:\n"
  "\t  -h\t\t\tShow this message\n"
  "\t  -i\t\t\tPre-process initial conditions\n"
  "\t  -f [FOLDER PATH]\tSpecify case folder as a string \"FOLDER PATH\"\n\n"
  "\tEXAMPLES:\n"
  "\t  Get initial/boundary conditions data from ${HOME}/OpenFOAM/myCase:\n\n"
  "\t    ";
  printf("%s%s", text, progname);
  text = " -i -f ${HOME}/OpenFOAM/myCase\n\n";
  printf("%s", text);
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("ERROR: Missing arguments!\n");
    help(argv[0]);
    return 1;
  }

  for (char **pargv = argv+1; *pargv != argv[argc]; pargv++) {
    if (strcmp(*pargv, "-h") == 0 || strcmp(*pargv, "--help") == 0) {
      help(argv[0]);
      return 0;
    } else if (strcmp(*pargv, "-i") == 0) {
      initials();
      return 0;
    }
  }
  printf("ERROR: Wrong arguments!\n");
  help(argv[0]);
  return 1;
}
