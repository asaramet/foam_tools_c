#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
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
  "\t  -h\t\t\t\tShow this message\n"
  "\t  -g\t\t\t\tCollect general data\n"
  "\t  -i\t\t\t\tPre-process initial conditions\n"
  "\t  -a\t\t\t\tCollect all data\n"
  "\t  -f [FOLDER PATH]\t\tSpecify case folder as a string [FOLDER PATH]"
  ". If this option is not specified, the app will run on current path ($PWD)\n"
  "\t  -w [REPORT FILE]\t\tSpecify report data file name as a string [REPORT FILE]"
  ". If this option is not specified data will be displayed on standart output (stdout)\n\n"
  "\t NOTE: -w and -f should be specified before any other options!\n\n"
  "\tEXAMPLES:\n"
  "\t  Display initial/boundary conditions data from ${HOME}/OpenFOAM/myCase:\n\n"
  "\t    ";
  printf("%s%s", text, progname);
  text = " -f ${HOME}/OpenFOAM/myCase -i\n\n";
  printf("%s", text);
  text = "\t  Collect all data from case ${HOME}/OpenFOAM/myCase into 'report.txt':\n\n"
  "\t    ";
  printf("%s%s", text, progname);
  text = " -f ${HOME}/OpenFOAM/myCase -w report.txt -a\n\n";
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
  return EXIT_SUCCESS;
}

int do_all(FILE *fp, char *caseFolder) {
  // TODO: check if you need to verify if functions exited with success
  general(fp, caseFolder);
  initials(fp, caseFolder);
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  update_path(strcat(getenv("PWD"), "/test/cmds")); // TODO remove this in production

  if (argc == 1) {
    help(argv[0]);
    return EXIT_FAILURE;
  }

  if (*cmd_out("foamVersion") == EXIT_FAILURE) {
    printf("ERROR: OpenFOAM not found on the system!\n");
    return EXIT_FAILURE;
  }

  FILE *outputFile = stdout; // output to file or stdout
  char *caseFolder = getenv("PWD"); // define caseFolder
  struct stat stats;
  int opt;
  while ((opt = getopt(argc, argv, "hagiw:f:")) != -1) {
    switch (opt) {
      case 'w':
        outputFile = fopen(optarg, "w");
        break;
      case 'f':
        stat(optarg, &stats);
        if (!S_ISDIR(stats.st_mode)) {
          fprintf(stderr, "ERROR: specified folder %s, doesn't exist!\n", optarg);
          fclose(outputFile);
          return EXIT_FAILURE;
        }
        caseFolder = optarg;
        break;
      case 'h':
        help(argv[0]);
        break;
      case 'a':
        do_all(outputFile, caseFolder);
        break;
      case 'g':
        general(outputFile, caseFolder);
        break;
      case 'i':
        initials(outputFile, caseFolder);
        break;
      case '?':
        if (optopt == 'w')
          fprintf(stderr, "ERROR: Output file is not specified with '-%c'.\n", optopt);
        else if (optopt == 'f')
          fprintf(stderr, "ERROR: OpenFOAM case folder is not specified with '-%c'\n", optopt);
        else if (isprint(optopt))
          fprintf(stderr, "ERROR: Unknown option '-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
        fclose(outputFile);
        return EXIT_FAILURE;
      default:
        abort();
    }
  }
  for (int index = optind; index < argc; index++)
    printf("WARNING: Non-option argument, '%s'\n", argv[index]);
  fclose(outputFile);
  return EXIT_SUCCESS;
}
