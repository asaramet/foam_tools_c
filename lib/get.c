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

char * keyvalue(char *text, const char *keyword)
{
  char *found;
  long end, newline;
  if ((found = strstr(text, keyword)) == NULL) return NULL;
  if ((newline = position(found, "\n")) == -1) return NULL;
  if ((found = text_segment(found, strlen(keyword), newline)) == NULL) return NULL;
  if ((end = position(found, ";")) == -1) return NULL;
  found = text_segment(found, 0, end);
  int i = 0;
  while (isspace(found[i])) i++; //remove leading spaces
  return found + i;
}

char * paragraph(char *text, const char *start, const char *end)
{
  //char *segment;

  //if ((segment = strstr(text, start)) == NULL) return NULL;
  //return segment;
  return text;
}

char * dictionary(char *text, const char *name)
{
  char *segment, *tail;
  if ((segment = strstr(text, name)) == NULL) return NULL;
  if ((segment = strchr(segment, '{')) == NULL) return NULL;

  long end = 0, flag = 0;
  char *dct = NULL;
  do {
    if ((tail = strchr(segment + flag, '}')) == NULL) break;
    free(dct);
    end = position(segment, tail) + 1;
    dct = text_segment(segment, 0, end);
    flag = strlen(dct);
  } while(nr_strings(dct, "{") != nr_strings(dct, "}"));
  return dct;
}
