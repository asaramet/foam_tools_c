#include <stdio.h>
#include <stdlib.h> // for exit()
#include <errno.h>
#include <limits.h> // for LONG_MAX
#include "lib/get.h"
#include "lib/run.h"

int initials() {
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
