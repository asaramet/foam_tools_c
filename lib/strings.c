#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "strings.h"

/* cut tail from text. Return new text without tail */
char *cut_tail(char *text, char *tail)
{
  size_t rlength = strlen(text) - strlen(tail);

  if (strstr(text + rlength, tail) == NULL) {return NULL;} // Check if it's not a tail

  char *result = calloc((rlength + 1), sizeof(char));

  memmove(result, text, rlength);
  return result;
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

/* cut a portion from a text starting at index 'start_index' till index 'end_index'*/
char *text_segment(const char *text, const long start_index, long end_index)
{
  if (end_index < 0) end_index = strlen(text) + end_index;
  if ((end_index - start_index) < 1) return NULL;

  char *data = (char *) calloc(end_index - start_index + 1, sizeof(char));

  memmove(data, text + start_index, end_index - start_index);
  return data;
}

/* position of subtext in text */
long position(const char *text, const char *subtext)
{
  char *got;
  if ((got = strstr(text, subtext)) == NULL) return -1;
  return strlen(text) - strlen(got);
}

char *remove_whitespaces(const char *text)
{
  char *output = calloc(strlen(text), sizeof(char));
  int chr = 0, index = 0;
  while (text[chr] != '\0') {
    if (!isspace(text[chr])) {
      output[index] = text[chr];
      index ++;
    }
    chr++;
  }
  output[index] = '\0';
  return output;
}
