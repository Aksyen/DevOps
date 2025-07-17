#include <stdio.h>
#include <stdlib.h>

#include "functions_grep.h"

int main(int argc, char *argv[]) {
  flags flags = {0};
  const char *pattern_str = NULL;
  const char *pattern_file = NULL;
  grep_pattern **patterns = NULL;
  size_t pattern_count = 0;
  int result = 0;
  int my_optind;

  parse_arguments(argc, argv, &flags, &pattern_str, &pattern_file, &my_optind);

  if (!flags.pattern_e && !flags.patterns_from_file_f) {
    if (my_optind < argc) {
      pattern_str = argv[my_optind++];
    } else {
      usage(argv[0]);
      result = 1;
    }
  }

  if (!result && pattern_file) {
    patterns = load_patterns_from_file(pattern_file, flags.ignore_case_i,
                                       &pattern_count);
  } else if (pattern_str) {
    patterns = malloc(sizeof(grep_pattern *));
    if (patterns != NULL) {
      patterns[0] = compile_pattern(pattern_str, flags.ignore_case_i);
      if (patterns[0] != NULL) {
        pattern_count = 1;
      } else {
        free(patterns);
        patterns = NULL;
        result = 1;
      }
    }
  }

  if (!result) {
    int i = my_optind;
    int flag = 0;
    if (argc - i > 1) {
      flag = 1;
    }

    for (; i < argc; i++) {
      const char *filename = argv[i];
      grep_with_pcre(patterns, pattern_count, filename, &flags, flag);
    }
    free_pattern(patterns, &pattern_count);
  } else {
    usage(argv[0]);
    result = 1;
  }

  return result;
}
