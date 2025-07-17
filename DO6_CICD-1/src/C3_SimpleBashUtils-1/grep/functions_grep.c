// functions_grep.c
#include "functions_grep.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(const char *progname) {
  fprintf(stderr,
          "Usage: %s [-e PATTERN] [-i] [-v] [-c] [-l] [-n] [-h] [-s] [-f FILE] "
          "[-o] <file>\n",
          progname);
}

void update_flags(flags *flag) {
  if (flag->file_with_matches_l) {
    flag->count_c = 0;
    flag->only_matching_o = 0;
    flag->no_filename_h = 0;
    flag->line_number_n = 0;
  }
  if (flag->count_c) {
    flag->only_matching_o = 0;
    flag->line_number_n = 0;
  }
}

void parse_arguments(int argc, char *argv[], flags *flags, const char **pattern,
                     const char **pattern_file, int *external_variable) {
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        flags->pattern_e = 1;
        *pattern = optarg;
        break;
      case 'i':
        flags->ignore_case_i = 1;
        break;
      case 'v':
        flags->invert_match_v = 1;
        break;
      case 'c':
        flags->count_c = 1;
        break;
      case 'l':
        flags->file_with_matches_l = 1;
        break;
      case 'n':
        flags->line_number_n = 1;
        break;
      case 'h':
        flags->no_filename_h = 1;
        break;
      case 's':
        flags->suppress_errors_s = 1;
        break;
      case 'f':
        flags->patterns_from_file_f = 1;
        *pattern_file = optarg;
        break;
      case 'o':
        flags->only_matching_o = 1;
        break;
    }
  }
  *external_variable = optind;
  update_flags(flags);
}

grep_pattern *compile_pattern(const char *pattern, int ignore_case) {
  const char *error;
  int erroffset;
  int options = 0;

  if (ignore_case) {
    options |= PCRE_CASELESS;
  }

  grep_pattern *compiled_pattern = malloc(sizeof(grep_pattern));
  if (compiled_pattern == NULL) {
    fprintf(stderr, "Memory allocation error\n");
  } else {
    compiled_pattern->pattern = pattern;
    compiled_pattern->re =
        pcre_compile(pattern, options, &error, &erroffset, NULL);

    if (compiled_pattern->re == NULL) {
      fprintf(stderr, "PCRE compilation failed at offset %d: %s\n", erroffset,
              error);
      free(compiled_pattern);
      compiled_pattern = NULL;
    }
  }

  return compiled_pattern;
}

void free_pattern(grep_pattern **patterns, size_t *count) {
  for (size_t i = 0; i < *count; i++) {
    pcre_free(patterns[i]->re);
    free(patterns[i]);
  }
  free(patterns);
  *count = 0;
}

grep_pattern **load_patterns_from_file(const char *filename, int ignore_case,
                                       size_t *count) {
  FILE *file = fopen(filename, "r");
  int error = 0;
  if (file == NULL) {
    perror("Error opening pattern file");
    error = 1;
  }
  size_t capacity = INITIAL_CAPACITY;
  grep_pattern **patterns = NULL;
  if (!error) {
    patterns = malloc(capacity * sizeof(grep_pattern *));
    if (patterns == NULL) {
      perror("Memory allocation error");
      fclose(file);
      error = 1;
    }
  }
  char line[SIZE];
  while (!error && fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = 0;
    if (*count >= capacity) {
      capacity *= 2;
      patterns = realloc(patterns, capacity * sizeof(grep_pattern *));
      if (patterns == NULL) {
        perror("Memory reallocation error");
        fclose(file);
        error = 1;
      }
    }
    if (!error) {
      patterns[*count] = compile_pattern(line, ignore_case);
      if (patterns[*count] == NULL) {
        fclose(file);
        error = 1;
        free_pattern(patterns, count);
        patterns = NULL;
      } else {
        (*count)++;
      }
    }
  }
  if (!error) {
    fclose(file);
  }

  return patterns;
}

void grep_with_pcre(grep_pattern **patterns, int pattern_count,
                    const char *filename, flags *flags, int flag) {
  int error = 0;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    // if (!flags->suppress_errors_s) perror("Error opening file");
    if (!flags->suppress_errors_s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    }
    return;
  }
  char line[SIZE];
  int line_number = 0;
  int match_count = 0;
  while (!error && fgets(line, sizeof(line), file)) {
    line_number++;
    int matched = 0;
    int breaking = 0;
    for (int i = 0; (i < pattern_count) && !breaking; i++) {
      int ovector[SIZE];
      int rc = pcre_exec(patterns[i]->re, NULL, line, strlen(line), 0, 0,
                         ovector, SIZE);
      if (rc >= 0) {
        matched = 1;
        breaking = 1;
      }
    }
    if (flag && !flags->no_filename_h && matched) {
      printf("%s:", filename);
    }
    if (flags->invert_match_v) {
      matched = !matched;
    }

    if (matched) {
      match_count++;
      if (flags->file_with_matches_l) {
        printf("%s\n", filename);
        fclose(file);
        error = 1;
      } else if (!flags->count_c) {
        if (flags->line_number_n) {
          printf("%d:", line_number);
        }
        if (flags->only_matching_o) {
          for (int j = 0; j < pattern_count; j++) {
            int ovector[SIZE];
            int rc = pcre_exec(patterns[j]->re, NULL, line, strlen(line), 0, 0,
                               ovector, SIZE);
            if (rc >= 0) {
              for (int k = 0; k < rc; k++) {
                printf("%.*s\n", ovector[2 * k + 1] - ovector[2 * k],
                       line + ovector[2 * k]);
              }
            }
          }
        } else {
          printf("%s", line);
        }
      }
    }
  }

  if (!error && flags->count_c) {
    printf("%d\n", match_count);
  }

  if (!error) fclose(file);
}
