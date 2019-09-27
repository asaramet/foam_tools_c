#ifndef _STRINGS_H_
#define _STRINGS_H_

char *cut_tail(char *text, char *tail);
int nr_strings(char *text, char *string);
char *text_segment(const char *text, const long start, long end);
long position(const char *text, const char *subtext);

#endif // _STRINGS_H_
