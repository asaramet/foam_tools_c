#include <string.h>
#include <stdlib.h>
#include "strings.h"

/* cut tail from text. Return new text without tail */
char * cut_tail(char *text, char *tail)
{
  size_t rlength = strlen(text) - strlen(tail);

  if (strstr(text + rlength, tail) == NULL) {return NULL;} // Check if it's not a tail

  char *result = calloc((rlength + 1), sizeof(char));

  memmove(result, text, rlength);
  return result;
}

/* cut a portion from a text */
char * cut_segment(char *text, char *start, char *end)
{
  return text;
}

/* number of strings in text */
int nr_strings(char *text, char *string)
{
  int nr = 0;
  text = strstr(text, string);
  while (text != NULL) {
    nr++;
    text = strstr(text + strlen(string), string);
  }
  return nr;
}
