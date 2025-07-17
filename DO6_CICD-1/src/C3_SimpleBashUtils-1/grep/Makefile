CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LDFLAGS = -lpcre

TARGET = s21_grep

SRCS = s21_grep.c functions_grep.c
OBJS = s21_grep.o functions_grep.o

all: $(TARGET)

s21_grep: $(OBJS)
	$(CC) $(CFLAGS) -o s21_grep s21_grep.o functions_grep.o $(LDFLAGS)
	rm *.o

s21_grep.o: s21_grep.c functions_grep.h
	$(CC) $(CFLAGS) -c s21_grep.c -o s21_grep.o

functions_grep.o: functions_grep.c functions_grep.h
	$(CC) $(CFLAGS) -c functions_grep.c -o functions_grep.o

clang_format:
	@echo "Running clang-format"
	cp ../../../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm -f .clang-format

clang_check:
	@echo "Running clang-check"
	cp ../../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	rm -f .clang-format

rebuild:
	make clean
	make all

clean:
	rm -f s21_grep s21_grep.o functions_grep.o grep_results.txt