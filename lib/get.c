#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "get.h"
#include "strings.h"

#define BUFFSIZE 128

#if 0
void remove_spaces(char *string)
{
  char *temp = string;
  do while (isspace(*string)) string++;
  while ((*temp++ = *string++));
}
#endif

char * remove_leading_spaces(char *string)
{
  while (isspace(*string)) string++;
  return string;
}

char * dictionary(char *text, const char *name)
{ // get dictionary (name) data from text
  char *segment, *tail, *got;

  if ((segment = strstr(text, name) )== NULL) return NULL;
  if ((segment = strstr(segment, "{")) == NULL ) return NULL;
  if ((tail = strstr(segment, "}")) == NULL ) return NULL;

  got = cut_tail(segment + 1, tail);
  if (strstr(got, "{") == NULL) { return got; }

  char *result = calloc(strlen(segment), sizeof(char));
  int flag = 1;
  while (flag != 0) {
    flag += nr_strings(got, "{");
    strcat(result, got);
    strncat(result, tail, 1);
    strcat(result, "\n");
    segment = segment + 2 + strlen(got);
    tail = strstr(segment, "}");
    got = cut_tail(segment, tail);
    flag--;
  }
  return cut_tail(result, strrchr(result, '}'));
}

char * keyvalue(char *text, char *keyword)
{
  char *segment;
  if ((segment = strstr(text, keyword)) != NULL) {
    char *tail = strstr(segment, ";");
    return remove_leading_spaces(cut_tail(segment, tail) + strlen(keyword));
  }
  return NULL;
}

char * paragraph(char *text, char *start, char *end)
{
  //char *segment;

  //if ((segment = strstr(text, start)) == NULL) return NULL;
  //return segment;
  return text;
}

char * cmd_dictionary(char *bash, const char *name)
{ // get dictionary from stdout of bash command (bash)
  FILE *fp;
  char streamline[BUFFSIZE];
  int flag = 0;
  char *output;

  if ((fp = popen(bash, "r")) == NULL) return NULL;

  while (fgets(streamline, BUFFSIZE, fp) != NULL) {
    if (strstr(streamline, name) != NULL && flag == 0) {
      flag = 1;
      continue;
    }
    if (strstr(streamline, "{") != NULL && flag == 1) {
      flag = 2;
      output = "";
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
  pclose(fp);
  return flag == 1 ? output : NULL;
}
