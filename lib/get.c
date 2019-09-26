#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "get.h"
#include "strings.h"

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define error_null(msg) \
  do { perror(msg); return NULL; } while (0)

char * remove_leading_spaces(char *string)
{
  while (isspace(*string)) string++;
  return string;
}

char * keyvalue(char *streamline, const char *keyword)
{
  char *segment;
  if ((segment = strstr(streamline, keyword)) != NULL) {
    char *tail = strstr(segment, ";");
    return remove_leading_spaces(cut_tail(segment, tail) + strlen(keyword));
  }
  return NULL;
}

char * paragraph(char *text, const char *start, const char *end)
{
  //char *segment;

  //if ((segment = strstr(text, start)) == NULL) return NULL;
  //return segment;
  return text;
}

char * cmd_dictionary(char *bash, const char *name)
{ // get dictionary from stdout of a shell command (bash)
  FILE *fp;
  char *streamline = NULL;
  size_t len = 0;
  int flag = 0;
  char *output;

  if ((fp = popen(bash, "r")) == NULL) error_null("Error running bash command");

  while (getline(&streamline, &len, fp) != -1) {
    if (strstr(streamline, name) != NULL && flag == 0) {
      flag = 1;
      output = "";
      continue;
    }
    if (strstr(streamline, "{") != NULL && flag == 1) {
      flag = 2;
      continue;
    }
    if (flag > 1 && strstr(streamline, "{") != NULL) flag++;
    if (flag > 1  && strstr(streamline, "}") != NULL) flag--;
    if (flag == 1 && strstr(streamline, "}") != NULL) break;

    if (flag > 1) {
      char *temp = calloc((strlen(output) + strlen(streamline)), sizeof(char));
      memmove(temp, output, strlen(output));
      strcat(temp, streamline);
      output = temp;
    }
  }
  free(streamline);
  pclose(fp);
  return flag == 1 ? output : NULL;
}

char * dictionary(char *text, const char *name)
{
  if (strstr(text, name) == NULL) return NULL;
  return NULL;
}
