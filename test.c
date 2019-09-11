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

  const char *segment = dictionary(foamDictionary, "outlet");
  if (segment != NULL) {
    printf("%s\n", segment);
  }

  const char *flowVelocity = keyvalue(foamDictionary, "flowVelocity");
  if (flowVelocity != NULL) {
    printf("%s\n", flowVelocity);
  }

  printf("-=Over and out=-\n");
  return 0;
}
