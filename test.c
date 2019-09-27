#include <stdio.h>
#include <stdlib.h> // for exit()
#include <errno.h>
#include <limits.h> // for LONG_MAX
#include <string.h>
#include "lib/get.h"
#include "lib/run.h"
#include "lib/strings.h"

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char const *argv[]) {
  char *segment;

  segment = cmd_out("foamDictionary");
  /*printf("== cmd_out(\"foamDictionary\") ==\n%s\n", segment);*/

  printf("segment length: %ld\n", strlen(segment));
  printf("== cut_segment ==\n%s\n", text_segment(segment, 0, 8));
  printf("== position(segment, \"keyword\"):\t%ld\n", position(segment, "keyword"));
  printf("== segment+position(segment,\"keyword\") ==\n%s\n", segment+position(segment, "keyword"));

  printf("== dictionary(segment, \"boundaryField\") ==\n%s\n", dictionary(segment, "boundaryField"));
  printf("== dictionary(segment, \"keyword\") ==\n%s\n", dictionary(segment, "keyword"));
  printf("== dictionary(segment, \"outlet\") ==\n%s\n", dictionary(segment, "outlet"));
  printf("== dictionary(segment, \"upperWall\") ==\n%s\n", dictionary(segment, "upperWall"));

  printf("-=Over and out=-\n");

  free(segment);
  exit(EXIT_SUCCESS);
}
