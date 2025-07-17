# Используем базовый образ с Nginx
FROM nginx:latest

# Устанавливаем зависимости для сборки сервера
RUN apt-get update && apt-get install -y \
    gcc \
    libfcgi-dev \
    spawn-fcgi && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Копируем исходники сервера
WORKDIR /app
COPY mini_server.c /app

# Собираем сервер
RUN gcc -o mini_server mini_server.c -lfcgi

# Копируем конфигурационный файл Nginx
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf

# Команды для запуска mini_server и Nginx
CMD ["sh", "-c", "spawn-fcgi -p 8080 /app/mini_server && nginx -g 'daemon off;'"]