#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int number_nonblank_b;
  int number_all_n;
  int squeeze_blank_s;
  int show_ends_e;
  int show_tabs_t;
  int show_nonprinting_v;
} flags;

int checking_command_line_arguments(int argc, char *argv[], flags *name);
void print_with_flags(FILE *file, flags *var, int *line_number);

int main(int argc, char *argv[]) {
  flags argument = {0};
  int line_number = 1;
  int i = checking_command_line_arguments(argc, argv, &argument);
  if (i == argc) {
    printf("No file\n");

  } else {
    while (i < argc) {
      FILE *fp;
      fp = fopen(argv[i], "r");
      if (fp == NULL) {
        perror(argv[i]);
      } else {
        print_with_flags(fp, &argument, &line_number);
        fclose(fp);
      }
      i++;
    }
  }

  return 0;
}

int checking_command_line_arguments(int argc, char *argv[], flags *name) {
  int i;
  for (i = 1; i < argc && argv[i][0] == '-'; i++) {
    if (strchr(argv[i], 'A')) {
      name->show_nonprinting_v = name->show_ends_e = name->show_tabs_t = 1;
    }
    if (strchr(argv[i], 'b') || strstr(argv[i], "--number-nonblank")) {
      name->number_nonblank_b = 1;
      name->number_all_n = 0;
    }
    if ((strchr(argv[i], 'n') || strstr(argv[i], "--number")) &&
        (!name->number_nonblank_b)) {
      name->number_all_n = 1;
    }
    if (strchr(argv[i], 'e')) {
      name->show_nonprinting_v = name->show_ends_e = 1;
    }
    if (strchr(argv[i], 'E')) {
      name->show_ends_e = 1;
    }
    if (strchr(argv[i], 's') || strstr(argv[i], "--squeeze-blank")) {
      name->squeeze_blank_s = 1;
    }
    if (strchr(argv[i], 't')) {
      name->show_nonprinting_v = name->show_tabs_t = 1;
    }
    if (strchr(argv[i], 'T')) {
      name->show_tabs_t = 1;
    }
    if (strchr(argv[i], 'v')) {
      name->show_nonprinting_v = 1;
    }
  }
  return i;
}

void print_with_flags(FILE *file, flags *var, int *line_number) {
  int c;
  int last_char = '\n';
  int empty_line_count = 0;
  while ((c = getc(file)) != EOF) {
    if (var->squeeze_blank_s && c == '\n' && last_char == '\n') {
      if (empty_line_count > 0)
        continue;
      else {
        empty_line_count++;
      }
    } else
      empty_line_count = 0;
    if (var->number_all_n && last_char == '\n') {
      printf("%6d\t", (*line_number)++);
    }
    if (var->number_nonblank_b && last_char == '\n' && c != '\n') {
      printf("%6d\t", (*line_number)++);
    }
    if (var->show_tabs_t && c == '\t') {
      printf("^");
      c = 'I';
    }
    if (var->show_nonprinting_v && c != '\t' && c != '\n') {
      if (c >= 128) {
        c -= 128;
        printf("M-");
      }
      if (c < 32 || c == 127) {
        c ^= 0x40;
        printf("^");
      }
    }
    if (var->show_ends_e && c == '\n') printf("$");
    last_char = c;
    printf("%c", c);
  }
}
