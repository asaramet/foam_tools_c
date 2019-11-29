#ifndef _GET_H_
#define _GET_H_

char * dictionary(char *text, const char *name);
char * keyvalue(char *text, const char *keyword);
char * paragraph(char *text, const char *start, const char *end);
char * ofexec(char *text);
char * dimensions(char *text);
void power_to_units(char **appendto_list, int index, char power);

#endif // _GET_H_
