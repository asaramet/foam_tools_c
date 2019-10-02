#include <stdio.h>
#include <stdlib.h> // for exit()
#include <errno.h>
#include <limits.h> // for LONG_MAX
#include <string.h>
#include "lib/get.h"
#include "lib/run.h"
#include "lib/strings.h"
#include "test/minunit.h"
#include "test/outputget.h"

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

static char * test_dictionary(char *input, char *output) {
  string_assert(input, output);
  return 0;
}

int tests_run = 0;

static char * all_tests() {
  update_path(strcat(getenv("PWD"), "/test/cmds"));
  char *segment, *output;
  segment = cmd_out("foamDictionary");

  output = boundaryField;
  string_test(test_dictionary, output, dictionary(segment, "boundaryField"));

  output = cascadedField;
  string_test(test_dictionary, output, dictionary(segment, "cascadedField"));

  output = motorBikeGroup;
  string_test(test_dictionary, output, dictionary(segment, "motorBikeGroup"));

  free(segment);
  return 0;
}

int main(int argc, char const *argv[]) {

  char *result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  }
  else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  exit(EXIT_SUCCESS);
}
