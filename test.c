#include <stdio.h>
#include <stdlib.h> // for exit()
#include <errno.h>
#include <limits.h> // for LONG_MAX
#include "lib/get.h"
#include "lib/run.h"

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char const *argv[]) {
  char *segment;

  if ((segment = dictionary("foamDictionary", "outlet")) != NULL)
    printf("== dictionary(\"foamDictionary\", \"outlet\") ==\n%s\n", segment);

  if ((segment = dictionary("foamDictionary", "keyword")) != NULL)
    printf("== dictionary(\"foamDictionary\", \"keyword\") ==\n%s\n", segment);

  /*segment = cmd_out("foamDictionary");
  printf("== cmd_out(\"foamDictionary\") ==\n%s\n", segment);*/

  printf("-=Over and out=-\n");

  free(segment);
  exit(EXIT_SUCCESS);
}
