#!/bin/bash

#Папка с текстовыми файлами
TXT_DIR="./txt_files"
#Исполняемый файл вашей программы
MY_CAT="./s21_cat"
#Выходной файл для записи результатов
OUTPUT_FILE="./cat_results.txt"

COUNTER_SUCCESS=0

COUNTER_FAIL=0

#Комбинации флагов
FLAGS=(
    ""
    "-A"
    "-b"
    "-e"
    "-E"
    "-n"
    "-s"
    "-t"
    "-T"
    "-v"
    "-A -b"
    "-A -e"
    "-A -E"
    "-A -n"
    "-A -s"
    "-A -t"
    "-A -T"
    "-A -v"
    "-b -e"
    "-b -E"
    "-b -n"
    "-b -s"
    "-b -t"
    "-b -T"
    "-b -v"
    "-e -E"
    "-e -n"
    "-e -s"
    "-e -t"
    "-e -T"
    "-e -v"
    "-E -n"
    "-E -s"
    "-E -t"
    "-E -T"
    "-E -v"
    "-n -s"
    "-n -t"
    "-n -T"
    "-n -v"
    "-s -t"
    "-s -T"
    "-s -v"
    "-t -T"
    "-t -v"
    "-T -v"
)

#Очистка выходного файла
> "$OUTPUT_FILE"

#Перебор всех текстовых файлов в папке
for file in "$TXT_DIR"/*.txt; do
    # Проверка на существование файла
    [ -e "$file" ] || continue

    # Перебор всех комбинаций флагов
    for flags in "${FLAGS[@]}"; do
        # Запуск стандартной утилиты cat
        cat $flags "$file" > cat_output.txt
        # Запуск вашей утилиты my_cat
        $MY_CAT $flags "$file" > my_cat_output.txt

        # Сравнение результатов
        if diff -q cat_output.txt my_cat_output.txt > /dev/null; then
            comparison="identical"

            ((COUNTER_SUCCESS++))

        else
            comparison="different"
            
            ((COUNTER_FAIL++))
            
        fi
        # Запись результатов в файл
        echo "File: $file" >> "$OUTPUT_FILE"
        echo "Flags: $flags" >> "$OUTPUT_FILE"
        echo "cat output:" >> "$OUTPUT_FILE"
        cat cat_output.txt >> "$OUTPUT_FILE"
        echo "my_cat output:" >> "$OUTPUT_FILE"
        cat my_cat_output.txt >> "$OUTPUT_FILE"
        echo "Comparison: $comparison" >> "$OUTPUT_FILE"
        echo "---------------------------" >> "$OUTPUT_FILE"
        
        
    done
done

# Удаление временных файлов
rm -f cat_output.txt my_cat_output.txt

# Результаты
echo "Results are saved in $OUTPUT_FILE."
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

# Если есть ошибки, вернуть ненулевой код
if [ "$COUNTER_FAIL" -gt 0 ]; then
    exit 1
else
    exit 0
fi