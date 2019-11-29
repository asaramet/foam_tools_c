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

char * ofexec(char *text)
{ // get OpenFOAM executable from OF output
  char *executable;
  if ((executable = strstr(text, "Exec")) == NULL) return NULL;
  if ((executable = strstr(executable, ": ")) == NULL) return NULL;
  executable += 2;
  int i = 0;
  while (! isspace(executable[i])) i++;
  if (i == 0) return NULL;
  return text_segment(executable, 0, i);
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

char * dimensions(char *of_units_list)
{ // text example: [ 0 2 -2 0 0 0 0 ]; should return m^2/s^2
  if (of_units_list[0] != '[') return NULL;
  // strip [] and whitespaces
  of_units_list[strlen(of_units_list) - 2] = '\0';
  of_units_list = remove_whitespaces(of_units_list+1);

  char *nominator = calloc(21, sizeof(char));
  char *denominator = calloc(21, sizeof(char));
  int chr = 0, index = 0;
  while (of_units_list[chr] != '\0') {
    if (of_units_list[chr] == '0') {
      chr++; index++; continue;
    }
    if (of_units_list[chr] == '-') {
      power_to_units(&denominator, index, of_units_list[chr+1]);
      chr = chr+2; index++; continue;
    }
    power_to_units(&nominator, index, of_units_list[chr]);
    chr++; index++;
  }
  if (strlen(nominator) == 0) nominator = "1";
  if (strlen(denominator) == 0) return nominator;

  char *converted = calloc(strlen(nominator) + strlen(denominator) + 1, sizeof(char));
  sprintf(converted, "%s/%s", nominator, denominator);
  return converted; //"m^2/s^2";
}

void power_to_units(char **appendto_list, int index, char power)
{
  const char *units[7] = {"kg", "m", "s", "K", "mol", "A", "cd"};
  char *of_unit = calloc(7, sizeof(char));
  sprintf(of_unit, "%s^%c", units[index], power);
  if (strlen(*appendto_list) == 0) {
    *appendto_list = of_unit;
  } else strcat(*appendto_list, of_unit);
}
