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

char * keyvalue(char *streamline, const char *keyword)
{
  /*
  char *segment;
  if ((segment = strstr(streamline, keyword)) != NULL) {
    char *tail = strstr(segment, ";");
    return remove_leading_spaces(cut_tail(segment, tail) + strlen(keyword));
  }
  */
  return NULL;
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

  long end = 0;
  long flag = 0;
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
