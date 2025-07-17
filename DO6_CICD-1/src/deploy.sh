#!/bin/bash

# Переменные
TARGET_USER="lioncoco"  # Пользователь на второй машине
TARGET_HOST="10.20.0.20"  # IP второй машины
TARGET_DIR="/usr/local/bin"  # Директория для установки
SOURCE_DIR="$(pwd)/C3_SimpleBashUtils-1"  # Директория с артефактами

# Проверка подключения
echo "Connecting to $TARGET_HOST as $TARGET_USER..."
ssh "$TARGET_USER@$TARGET_HOST" "echo 'Connected to $TARGET_HOST'"

# Копирование исполняемых файлов
echo "Copying files..."
scp "$SOURCE_DIR/cat/s21_cat" "$TARGET_USER@$TARGET_HOST:$TARGET_DIR/s21_cat" || { echo "Error while copying 21_cat"; exit 1; }
scp "$SOURCE_DIR/grep/s21_grep" "$TARGET_USER@$TARGET_HOST:$TARGET_DIR/s21_grep" || { echo "Error while copying 21_grep"; exit 1; }

# Проверка файлов на целевой машине
echo "Verifying files on target machine..."
ssh "$TARGET_USER@$TARGET_HOST" "ls -l $TARGET_DIR/s21_cat $TARGET_DIR/s21_grep"

echo "Deployment complete!"
