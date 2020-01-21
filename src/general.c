#include <stdio.h>
#include <stdlib.h> // for exit()
#include "../lib/run.h"

int general(FILE *fp, char *caseFolder) {
  fprintf(fp, "Simulation Case:\t\t%s\n", caseFolder);
  fprintf(fp, "OpenFOAM Version:\t\t%s\n", cmd_out("foamVersion"));
  fprintf(fp, "Date and Time:\t\t\t%s\n", cmd_out("date"));
  return EXIT_SUCCESS;
}
