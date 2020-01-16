#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "run.h"

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

char *cmd_out(char *command)
{
  FILE *cmdpt = popen(command, "r");
  if (cmdpt == NULL) handle_error("Failed popen");


  char *data = (char *) calloc(1, sizeof(char));
  char *streamline = NULL;
  size_t dlength, slength, strlength = 0;


  while(getline(&streamline, &strlength, cmdpt) != -1) {

    dlength = strlen(data);
    slength = strlen(streamline);
    if ((data = (char *) realloc(data, (dlength + slength + sizeof(char)))) == NULL) {
      free(data);
      free(streamline);
      pclose(cmdpt);
      handle_error("realloc failure");
    }
    memmove(data+dlength, streamline, slength + sizeof(char));
    free(streamline);
    strlength = 0;
  }

  pclose(cmdpt);
  return data;
}

int update_path(char *folder)
{
  char *oldPath;
  oldPath = getenv("PATH") == NULL ? "" : getenv("PATH");

  char *path = calloc(strlen(oldPath) + strlen(folder) + 2, sizeof(char));

  memmove(path, folder, strlen(folder));
  strcat(path, ":");
  strcat(path, oldPath);

  return setenv("PATH", path, 1);
}
