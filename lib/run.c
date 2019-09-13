#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "run.h"

#define BUFFSIZE 128

char * command_stdout(char *cmd)
{
  FILE *fp;
  char streamline[BUFFSIZE];
  char *out;// = (char*) malloc(sizeof(char));
  char *old = (char*) malloc(sizeof(char));

  if ((fp = popen(cmd, "r")) == NULL) {
    exit(EXIT_FAILURE);
  }

  while (fgets(streamline, BUFFSIZE, fp) != NULL) { // read a line from the stream
    //out = malloc((strlen(old) + strlen(streamline)) * sizeof(char));
    if (strstr(streamline, "/*--") == NULL) {
      out = calloc((strlen(old) + strlen(streamline)), sizeof(char));
      memmove(out, old, strlen(old));
      strcat(out, streamline);
      old = out;
    }
  }

  pclose(fp);
  return out;
}
