/* minunit */
#define mu_assert(message, test) do { if (!test) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

#define string_assert(str1, str2) do { if (strcmp(str1, str2) != 0) return str1; } while(0)
#define string_test(test, arg1, arg2) do { char *message = test(arg1, arg2); tests_run++; \
                              if (message) { printf("ERROR!:\n"); return message; } } while (0)

extern int tests_run;
