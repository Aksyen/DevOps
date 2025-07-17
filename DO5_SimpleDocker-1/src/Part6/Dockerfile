# Базовый образ с последней версией Nginx
FROM nginx:latest

# Устанавливаем рабочую директорию в контейнере
WORKDIR /app

# Копируем исходный код мини-сервера в контейнер
COPY mini_server.c /app

# Копируем конфигурационные файлы Nginx в соответствующие директории
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
COPY ./nginx/mime.types /etc/nginx/mime.types

# Устанавливаем необходимые пакеты и настраиваем права доступа
RUN apt-get update && apt-get install -y \
    gcc \
    libfcgi-dev \
    spawn-fcgi && \
    chown -R nginx:nginx /etc/nginx/nginx.conf && \
    chown -R nginx:nginx /var/cache/nginx && \
    chown -R nginx:nginx /app && \
    touch /var/run/nginx.pid && \
    chown -R nginx:nginx /var/run/nginx.pid && \
    rm -rf /var/lib/apt/lists/*
    
# Компилируем mini_server из исходного кода
RUN gcc -o mini_server mini_server.c -lfcgi

# Удаляем файлы с привилегированными флагами (setuid/setgid) для повышения безопасности
RUN find / -perm /6000 -type f -exec chmod a-s {} \; || true

# Переходим на пользователя nginx для выполнения всех последующих операций
USER nginx

# Открываем порты 81 и 8080 для работы приложения
EXPOSE 81
EXPOSE 8080

# Добавляем проверку состояния контейнера (healthcheck)
HEALTHCHECK --interval=30s --timeout=5s --retries=3 CMD \
  curl -f http://127.0.0.1:81/status || exit 1

# Запускаем mini_server как FastCGI приложение и Nginx
CMD ["sh", "-c", "spawn-fcgi -p 8080 /app/mini_server && nginx -g 'daemon off;'"]

