#include <stdio.h>
#include <stdlib.h> // for exit()
#include <errno.h>
#include <limits.h> // for LONG_MAX
#include "lib/get.h"
#include "lib/run.h"

#if 0
int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage %s <factorial of>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  errno = 0;
  char *p;
  long num = strtol(argv[1], &p, 10);
  if (errno != 0 || *p != '\0' || num > LONG_MAX) {
    /* Check for errors: the string does not represent an integer
       or the integer is larger than long */
    fprintf(stderr, "Wrong argument - %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  printf("Got your factorial for %s\n", argv[1]);
  printf("factorial(%s) = %ld\n", argv[1], factorial(num));
  return 0;
}
#endif

int main(int argc, char const *argv[]) {
  char *foamDictionary = command_stdout("foamDictionary");
  /*
  char *patchSummary = command_stdout("patchSummary");
  printf("%s\n", patchSummary);
  */
  const char *segment = dictionary(foamDictionary, "outlet");
  if (segment != NULL)
    printf("== dictionary(foamDictionary, \"outlet\") ==\n%s\n", segment);

  if ((segment = keyvalue(foamDictionary, "flowVelocity")) != NULL)
    printf("== keyvalue(foamDictionary, \"flowVelocity\") ==\n%s\n", segment);

  if ((segment = cmd_dictionary("foamDictionary", "outlet")) != NULL)
    printf("== cmd_dictionary(\"foamDictionary\", \"outlet\") ==\n%s\n", segment);

  if ((segment = cmd_dictionary("foamDictionary", "keyword")) != NULL)
    printf("== cmd_dictionary(\"foamDictionary\", \"keyword\") ==\n%s\n", segment);

  printf("-=Over and out=-\n");
  return 0;
}
