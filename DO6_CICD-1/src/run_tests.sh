#!/bin/bash

set -e  # Прерывать выполнение при любой ошибке

echo "Running cat_tests.sh..."
cd C3_SimpleBashUtils-1/cat/
bash cat_tests.sh

echo "Running grep_tests.sh..."
cd ../grep/
bash grep_tests.sh

echo "All integration tests passed successfully!"