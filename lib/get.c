#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "get.h"
#include "strings.h"

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
