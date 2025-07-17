#ifndef FUNCTIONS_GREP_H
#define FUNCTIONS_GREP_H

#include <pcre.h>

#define SIZE 1024
#define INITIAL_CAPACITY 10

typedef struct {
  int pattern_e;
  int ignore_case_i;
  int invert_match_v;
  int count_c;
  int file_with_matches_l;
  int line_number_n;
  int no_filename_h;
  int suppress_errors_s;
  int patterns_from_file_f;
  int only_matching_o;
} flags;

typedef struct {
  pcre *re;
  const char *pattern;
} grep_pattern;

void usage(const char *progname);
void update_flags(flags *flag);
void parse_arguments(int argc, char *argv[], flags *flags, const char **pattern,
                     const char **pattern_file, int *external_variable);
grep_pattern *compile_pattern(const char *pattern, int ignore_case);
void free_pattern(grep_pattern **patterns, size_t *count);
grep_pattern **load_patterns_from_file(const char *filename, int ignore_case,
                                       size_t *count);
void grep_with_pcre(grep_pattern **patterns, int pattern_count,
                    const char *filename, flags *flags, int flag);

#endif  // FUNCTIONS_GREP_H
