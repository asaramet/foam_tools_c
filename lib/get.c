#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "get.h"
#include "strings.h"

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

  if ((segment = strstr(text, name) )== NULL) { return NULL; }
  if ((segment = strstr(segment, "{")) == NULL ) { return NULL; }
  if ((tail = strstr(segment, "}")) == NULL ) { return NULL; }

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
