CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
TARGET = s21_cat
all: $(TARGET)


$(TARGET): s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

clang_format:
	@echo "Running clang-format"
	cp ../../../materials/linters/.clang-format .clang-format
	clang-format -i *.c
	rm -f .clang-format

clang_check:
	@echo "Running clang-check"
	cp ../../../materials/linters/.clang-format .clang-format
	clang-format -n *.c
	rm -f .clang-format

rebuild:
	make clean
	make all

clean:
	rm -f s21_cat cat_results.txt
