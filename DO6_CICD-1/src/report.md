1. [Настройка gitlab-runner](#part-1-настройка-gitlab-runner)

2. [Part 2. Сборка](#part-2-сборка)

3. [Part 3. Тест кодстайла](#part-3-тест-кодстайла)

4. [Part 4. Интеграционные тесты](#part-4-интеграционные-тесты)

5. [Part 5. Этап деплоя](#part-5-этап-деплоя)

6. [Part 6. Дополнительно. Уведомления](#part-6-дополнительно-уведомления)



**При выполнения проекта использовались следующие ресурсы:**

[Get Ubuntu Server](https://ubuntu.com/download/server?ref=danielwertheim#architectures)

[Install GitLab Runner](https://docs.gitlab.com/runner/install/linux-repository.html)

[Registering runners](https://docs.gitlab.com/runner/register/)

[Шпаргалка по написанию Gitlab Pipelines](https://www.dmosk.ru/miniinstruktions.php?mini=gitlab-pipeline)

[GitLab CI/CD - Главные Основы создания CI/CD Pipeline](https://www.youtube.com/watch?v=R1a-1JYfiQA&list=PLg5SS_4L6LYuJxTrdU5vzBaVGlZko8Hsy)

## Part 1. Настройка gitlab-runner

**== Задание ==**

- [x] Подними виртуальную машину Ubuntu Server 22.04 LTS.

  ![Ubuntu Server 22.04](screenshots/1.0.png) 

- [x] Скачай и установи на виртуальную машину gitlab-runner.

  ![gitlab-runner](screenshots/1.1.png) 

   ```bash
   # После добавления репозитория GitLab в список источников пакетов APT
   # Устанавливаем gitlab-runner
   sudo apt install gitlab-runner -y
   ```
- [x] Запусти gitlab-runner и зарегистрируй его для использования в текущем проекте (DO6_CICD).

  ![gitlab-runner register](screenshots/1.2.png)

## Part 2. Сборка

**== Задание ==**

- [x] Напиши этап для CI по сборке приложений из проекта `C2_SimpleBashUtils`.

- [x] В файле `gitlab-ci.yml` добавь этап запуска сборки через мейк файл из проекта C2.

- [x] Файлы, полученные после сборки (артефакты), сохрани в произвольную директорию со сроком хранения 30 дней.

![.gitlab-ci.yml](screenshots/2.0.png)

![Pipeline](screenshots/2.1.png)

![build](screenshots/2.2.png)

## Part 3. Тест кодстайла

**== Задание ==**

- [x] Напиши этап для CI, который запускает скрипт кодстайла (clang-format).

- [x] Если кодстайл не прошел, то «зафейли» пайплайн.

- [x] В пайплайне отобрази вывод утилиты clang-format.

![.gitlab-ci.yml](screenshots/3.0.png)

![Pipeline](screenshots/3.1.png)

![codestyle](screenshots/3.2.png)

## Part 4. Интеграционные тесты

**== Задание ==**

- [x] Напиши этап для CI, который запустит интеграционные тесты.

- [x] Для проекта C2_SimpleBashUtils можешь взять свои уже написанные интеграционные тесты.

- [ ] Для проекта из папки code-samples напиши интеграционные тесты самостоятельно. Тесты могут быть написаны на любом языке (c, bash, python и т.д.) и должны вызывать собранное приложение для проверки его работоспособности на разных случаях.

- [x] Запусти этот этап автоматически только при условии, если сборка и тест кодстайла прошли успешно.

- [x] Если тесты не прошли, то «зафейли» пайплайн.

- [x] В пайплайне отобрази вывод, что интеграционные тесты успешно прошли / провалились.

![.gitlab-ci.yml](screenshots/4.0.png)

![Pipeline](screenshots/4.1.png)

![integration_test](screenshots/4.2.png)

## Part 5. Этап деплоя

**== Задание ==**

- [x] Подними вторую виртуальную машину `Ubuntu Server 22.04 LTS`.

![Ubuntu Server 22.04](screenshots/5.0.png)

![netplan vm1](screenshots/5.1.png)

![netplan vm2](screenshots/5.2.png)

![ssh-keygen](screenshots/5.3.png)

![ssh-copy-id](screenshots/5.4.png)

![chmod](screenshots/5.5.png)

- [x] Напиши этап для CD, который «разворачивает» проект на другой виртуальной машине.

- [x] Запусти этот этап вручную при условии, что все предыдущие этапы прошли успешно.

- [x] Напиши bash-скрипт, который при помощи ssh и scp копирует файлы, полученные после сборки (артефакты), в директорию /usr/local/bin второй виртуальной машины.

- [x] В файле gitlab-ci.yml добавь этап запуска написанного скрипта.

- [x] В случае ошибки «зафейли» пайплайн.

- [x] Сохрани дампы образов виртуальных машин.

![gitlab-ci.yml](screenshots/5.6.png)

![bash-скрипт](screenshots/5.7.png)

![Pipeline](screenshots/5.8.png)

![deploy](screenshots/5.9.png)

![/usr/local/bin](screenshots/5.10.png)


## Part 6. Дополнительно. Уведомления

**== Задание ==**

- [x] Настрой уведомления об успешном/неуспешном выполнении пайплайна через бота с именем «[твой nickname] DO6 CI/CD» в Telegram.

![creating a telegram bot.](screenshots/6.0.png)

>Chat ID
>В Telegram найди и начни чат с ботом `@userinfobot`.
>Отправь сообщение `/start`, и бот покажет твой Chat ID.

**На машине, где выполняется GitLab Runner, выполним следующие действия:**

```bash
# Перейдем к пользователю gitlab-runner
sudo -u gitlab-runner -i

# Создадим директорию
mkdir -p secrets

# В этой папке создадим файл telegram_secrets
nano /secrets/telegram_secrets

# Добавим туда следующие строки
TELEGRAM_BOT_TOKEN=ваш_токен_бота
TELEGRAM_CHAT_ID=ваш_чат_ID

# Установим права доступа, чтобы только пользователь gitlab-runner мог читать файл
chmod 600 /home/gitlab-runner/secrets/telegram_secrets

```

![chat_bot_message.sh](screenshots/6.1.png)

![chat_bot_message.sh](screenshots/6.2.png)

![chat_bot_message.sh](screenshots/6.3.png)

>Как видно сообщения приходят бот работает. Первый раз запустил без второй виртуальной машины и deploy завершился неудачей. После поднял виртуальную машину и перезапустил deploy.