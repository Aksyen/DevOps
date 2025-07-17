#!/bin/bash

# Паттерны и файлы для тестирования
patterns=("hello" "end$" "^foo")
files=("file1.txt" "file2.txt")
flags_single=("-e" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o")
flags_double=("-ei" "-ev" "-ec" "-el" "-en" "-eh" "-es" "-eo" "-iv" "-ic" "-il" "-in" "-ih" "-is" "-io" "-vc" "-vl" "-vn" "-vh" "-vs" "-vo" "-cl" "-cn" "-ch" "-cs" "-co" "-ln" "-lh" "-ls" "-lo" "-nh" "-ns" "-no")

OUTPUT_FILE="./grep_results.txt"

COUNTER_SUCCESS=0
COUNTER_FAIL=0

# Функция для запуска и сравнения команд
compare_results() {
    local flag=$1
    local pattern=$2
    local file=$3

    # Выполнение grep
    grep_result=$(grep $flag "$pattern" $file 2>&1)
    #grep_exit_code=$?

    # Выполнение my_grep
    my_grep_result=$(./s21_grep $flag "$pattern" $file 2>&1)
    #my_grep_exit_code=$?

    # Запись результатов
    echo "Flag: $flag, Pattern: $pattern, File: $file" >> "$OUTPUT_FILE"
    echo "grep result:" >> "$OUTPUT_FILE"
    echo "$grep_result" >> "$OUTPUT_FILE"
    #echo "Exit code: $grep_exit_code" >> "$OUTPUT_FILE"
    echo "my_grep result:" >> "$OUTPUT_FILE"
    echo "$my_grep_result" >> "$OUTPUT_FILE"
    #echo "Exit code: $my_grep_exit_code" >> "$OUTPUT_FILE"

    # Сравнение результатов
    #if [ "$grep_result" == "$my_grep_result" ] && [ $grep_exit_code -eq $my_grep_exit_code ]; then
    if [ "$grep_result" == "$my_grep_result" ]; then
        echo "Results match" >> "$OUTPUT_FILE"
        ((COUNTER_SUCCESS++))
    else
        echo "Results differ" >> "$OUTPUT_FILE"
        ((COUNTER_FAIL++))
    fi

    echo "----------------------------" >> "$OUTPUT_FILE"
}

# Очистка файла результатов
#echo "" > "$OUTPUT_FILE"

# Тестирование одиночных флагов
for flag in "${flags_single[@]}"; do
    for pattern in "${patterns[@]}"; do
        for file in "${files[@]}"; do
            compare_results "$flag" "$pattern" "$file"
        done
    done
done

# Тестирование двойных флагов
for flag in "${flags_double[@]}"; do
    for pattern in "${patterns[@]}"; do
        for file in "${files[@]}"; do
            compare_results "$flag" "$pattern" "$file"
        done
    done
done

# Результаты
echo "Testing complete. Results saved in "$OUTPUT_FILE"."
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

# Если есть ошибки, вернуть ненулевой код
if [ "$COUNTER_FAIL" -gt 0 ]; then
    exit 1
else
    exit 0
fi