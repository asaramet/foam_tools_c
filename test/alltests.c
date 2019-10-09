#include <stdio.h>
#include <stdlib.h> // for exit()
#include <errno.h>
#include <limits.h> // for LONG_MAX
#include <string.h>
#include "../lib/get.h"
#include "../lib/run.h"
#include "../lib/strings.h"
#include "minunit.h"
#include "outputget.h"

#define handle_error(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

static char * test_strings(char *input, char *output) {
  string_assert(input, output);
  return 0;
}

static char * test_null(char *in, char *out) {
  null_assert(in, out);
  return 0;
}

int tests_run = 0;

static char * all_tests() {
  update_path(strcat(getenv("PWD"), "/test/cmds"));
  char *segment, *output;
  segment = cmd_out("foamDictionary");

  output = boundaryField; // from test/outputget.h
  two_run_test(test_strings, output, dictionary(segment, "boundaryField"));

  output = cascadedField;
  two_run_test(test_strings, output, dictionary(segment, "cascadedField"));

  output = motorBikeGroup;
  two_run_test(test_strings, output, dictionary(segment, "motorBikeGroup"));

  two_run_test(test_strings, "uniform 0.24", keyvalue(segment, "internalField"));
  two_run_test(test_null, NULL, keyvalue(segment, "boundaryField"));
  two_run_test(test_null, NULL, keyvalue(segment, "more"));

  two_run_test(test_strings, "processor", keyvalue(dictionary(segment, "processor"), "type"));

  two_run_test(test_strings, "patchSummary", ofexec(cmd_out("patchSummary")));
  two_run_test(test_strings, "decomposePar", ofexec(cmd_out("decomposePar")));
  two_run_test(test_strings, "simpleFoam", ofexec(cmd_out("simpleFoam")));

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
