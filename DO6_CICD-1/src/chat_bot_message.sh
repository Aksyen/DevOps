#!/bin/bash

# Считывание токена и Chat ID из файла
source ~/secrets/telegram_secrets

# Проверяем статус текущего job
if [[ "$CI_JOB_STATUS" == "success" ]]; then
  STATUS="SUCCESS"
else
  STATUS="FAILED"
fi

# Формируем сообщение для Telegram
MESSAGE="Pipeline Notification:
Status: *$STATUS*
Stage: *${CI_JOB_STAGE}*
Job: *${CI_JOB_NAME}*
Project: *${CI_PROJECT_NAME}*
Branch: *${CI_COMMIT_REF_NAME}*
Commit: *${CI_COMMIT_SHORT_SHA}*
Author: *${GITLAB_USER_LOGIN}*"

# Отправляем сообщение через Telegram API
curl -s -X POST "https://api.telegram.org/bot${TELEGRAM_BOT_TOKEN}/sendMessage" \
  -d chat_id="${TELEGRAM_CHAT_ID}" \
  -d parse_mode="Markdown" \
  -d text="$MESSAGE"
