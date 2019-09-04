#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "run.h"

#define BUFSIZE 128

char * command_stdout(char *cmd)
{
  FILE *fp;
  char streamline[BUFSIZE];
  char *out = (char*) malloc(sizeof(char));
  char *old;

  if ((fp = popen(cmd, "r")) == NULL) {
    exit(EXIT_FAILURE);
  }

  while (fgets(streamline, BUFSIZE, fp) != NULL) { // read a line from the stream
    old = out;
    //out = malloc((strlen(old) + strlen(streamline)) * sizeof(char));
    out = calloc((strlen(old) + strlen(streamline)), sizeof(char));
    memmove(out, old, strlen(old));
    strcat(out, streamline);
  }

  pclose(fp);
  return out;
}
