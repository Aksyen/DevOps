1. [Готовый докер](#part-1-готовый-докер)

2. [Операции с контейнером](#part-2-операции-с-контейнером)

3. [Мини веб-сервер](#part-3-мини-веб-сервер)

4. [Свой докер](#part-4-свой-докер)

5. [Dockle](#part-5-dockle)

6. [Базовый Docker Compose](#part-6-базовый-docker-compose)

**При выполнения проекта использовались следующие ресурсы**

[Справочный материал по Docker](https://docs.docker.com/)

[Установка Docker Engine на Ubuntu](https://docs.docker.com/engine/install/ubuntu/)

[Docker для начинающих + практический опыт](https://stepik.org/course/123300/syllabus)


## Part 1. Готовый докер  

**== Задание ==**

- [x] Возьми официальный докер-образ с nginx и выкачай его при помощи `docker pull`.

    ![docker pull nginx](screenshots/1.0.png)  

- [x] Проверь наличие докер-образа через `docker images`.

    ![docker images](screenshots/1.1.png)  

- [x] Запусти докер-образ через `docker run -d [image_id|repository]`. 

    ![docker run](screenshots/1.2.png)  

- [x] Проверь, что образ запустился через docker ps.

    ![docker ps](screenshots/1.3.png)  

- [x] Посмотри информацию о контейнере через `docker inspect [container_id|container_name]`.

    ![docker inspect](screenshots/1.4.png)  


- [x] По выводу команды определи и помести в отчёт размер контейнера, список замапленных портов и ip контейнера.
размер контейнера:  

    >В последних версиях Docker команда `docker inspect` больше не отображает размеры контейнера. Для определения размера контейнера следует использовать другие подходы. Вот несколько способов, как это сделать:

    ```bash

    docker ps -s    # показывает список запущенных контейнеров с указанием их размера

    docker system df    # показывает использование дискового пространства Docker, включая размеры контейнеров, образов и volume
    
    ```

    **docker ps -s**

    ![docker ps -s](screenshots/1.5.png)  

    **docker system df**

    ![docker system df](screenshots/1.6.png)  

    **список замапленных портов**  

    ![inspect ports](screenshots/1.7.png)   

    **ip контейнера**

    ![inspect ip](screenshots/1.8.png)  

    **inspect | grep**

    ![ports, ip](screenshots/1.9.png)  

- [x] Останови докер контейнер через `docker stop [container_id|container_name]`.

    ![docker stop](screenshots/1.10.png)  

- [x] Проверь, что контейнер остановился через `docker ps`.

    ![docker ps](screenshots/1.11.png)  

- [x] Запусти докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду `run`.

    ![docker run -p 80:80 -p 443:443 nginx](screenshots/1.12.png)  

    **docker ps**

    ![docker ps](screenshots/1.13.png)  

- [x] Проверь, что в браузере по адресу localhost:80 доступна стартовая страница nginx. 

    ![xdg-open http://localhost:80](screenshots/1.14.png)  

    ![http://localhost:80](screenshots/1.15.png)  

- [x] Перезапусти докер контейнер через `docker restart [container_id|container_name]`.

    ![](screenshots/1.16.png)  

- [x] Проверь любым способом, что контейнер запустился.

    ![docker ps](screenshots/1.17.png)  

## Part 2. Операции с контейнером

**== Задание ==**

- [x] Прочитай конфигурационный файл `nginx.conf` внутри докер контейнера через команду `exec`.

    ```bash
    docker exec -i [container_id|container_name] cat /etc/nginx/nginx.conf  
    # Эта команда покажет содержимое конфигурационного файла прямо в терминале.
    
    ```

    ![docker exec](screenshots/2.0.png)  


- [x] Создай на локальной машине файл `nginx.conf`.


    ![./nginx.conf](screenshots/2.1.png)  

- [x] Настрой в нем по пути /status отдачу страницы статуса сервера nginx.

    ![/status](screenshots/2.2.png)  

- [x] Скопируй созданный файл nginx.conf внутрь докер-образа через команду `docker cp`. 

    ![docker cp](screenshots/2.3.png)  

- [x] Перезапусти nginx внутри докер-образа через команду exec. 

    ![docker exec reload](screenshots/2.4.png)  

- [x] Проверь, что по адресу `localhost:80/status` отдается страничка со статусом сервера nginx.  

    ![localhost:80/status](screenshots/2.5.png)  

- [x] Экспортируй контейнер в файл `container.tar` через команду `export`. 

    ![container.tar](screenshots/2.6.png)  

- [x] Останови контейнер. 
  
    ![docker stop](screenshots/2.7.png)  

- [x] Удали образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры.

    ![docker rmi](screenshots/2.8.png)  

- [x] Удали остановленный контейнер.

    ![docker rm](screenshots/2.9.png)  

- [x] Импортируй контейнер обратно через команду `import`.  

    ![docker import](screenshots/2.10.png)  

- [x] Запусти импортированный контейнер.

    ![docker run new images](screenshots/2.11.png)  

- [x] Проверь, что по адресу `localhost:80/status` отдается страничка со статусом сервера nginx.

    ![localhost:80/status 2](screenshots/2.12.png)  


## Part 3. Мини веб-сервер  

**== Задание ==**

- [x] Напиши мини-сервер на C и FastCgi, который будет возвращать простейшую страничку с надписью `Hello World!`.  

    ![Hello World!](screenshots/3.0.png)  

- [x] Запусти написанный мини-сервер через `spawn-fcgi` на порту `8080`. 

    >для запуска мини веб-сервера на FastCGI понадобились утилиты: `spawn-fcgi` и `libfcgi-dev` 

    ```bash
    sudo apt install libfcgi-dev
        # Устанавливает заголовочные файлы (fcgi_stdio.h) и библиотеку FastCGI.
    sudo apt install spawn-fcgi
        # Утилита, чтобы запустить сервер как FastCGI-приложение
    ```

    Скомпилируем написанный мини-сервер

    ![mini_server](screenshots/3.1.png)  

    Запускаем сервер на порту 8080  

    ![spawn-fcgi -p 8080](screenshots/3.2.png)  

- [x] Напиши свой `nginx.conf`, который будет проксировать все запросы с `81` порта на `127.0.0.1:8080`. 

    ![настройки nginx.conf](screenshots/3.3.png)   

    ![sudo nginx](screenshots/3.4.png)

    ![nginx status](screenshots/3.5.png)

- [x] Проверь, что в браузере по localhost:81 отдается написанная тобой страничка.

    ![server's working](screenshots/3.6.png)  

- [x] Положи файл nginx.conf по пути ./nginx/nginx.conf (это понадобится позже). 

    ![tree](screenshots/3.7.png)  


## Part 4. Свой докер  

**== Задание ==**

- [x] Напиши свой докер-образ, который:

    1) собирает исходники мини сервера на `FastCgi` из [Части 3](#part-3-мини-веб-сервер);

    2) запускает его на `8080` порту;

    3) копирует внутрь образа написанный `./nginx/nginx.conf`;

    4) запускает nginx..

    ![Dockerfile](screenshots/4.0.png)  


- [x] Собери написанный докер-образ через `docker build` при этом указав имя и тег.

    ![docker build](screenshots/4.1.png)  

- [x] Проверь через docker images, что все собралось корректно. 

    ![docker images](screenshots/4.2.png)  

- [x] Запусти собранный докер-образ с маппингом `81` порта на 80 на локальной машине и маппингом папки `./nginx` внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а [(см. Часть 2)](#part-2-операции-с-контейнером).  

    ![docker run](screenshots/4.3.png)  

- [x] Проверь, что по `localhost:80` доступна страничка написанного мини сервера.

    ![localhost:80](screenshots/4.4.png)  

- [x] Допиши в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx.  

    ![nginx.conf](screenshots/4.5.png)  

- [x] Перезапусти докер-образ.  

    Поскольку папка `nginx` была смонтирована в контейнер, изменения в конфигурации автоматически подхватятся.

    ![docker restart](screenshots/4.6.png)  

- [x] Проверь, что теперь по `localhost:80/status` отдается страничка со статусом `nginx` 

    ![localhost:80/status](screenshots/4.7.png) 

## Part 5. **Dockle**  

**== Задание ==** 

- [x] Просканируй образ из предыдущего задания через `dockle [image_id|repository]`. 

    ![dockle](screenshots/5.0.png)  

- [x] Исправь образ так, чтобы при проверке через dockle не было ошибок и предупреждений. 

    FATAL: CIS-DI-0010 – Do not store credential in environment variables/files

    >Dockle ругается на переменную NGINX_GPGKEYS внутри официального образа nginx, ошибочно считая, что там хранятся «секретные» данные. На самом деле это публичные GPG-ключи, необходимые для проверки пакетов при установке Nginx. Поэтому почти всегда эту проверку безопасно игнорировать.

    CIS-DI-0001: Create a user for the container

    >Нужно создать пользователя для запуска приложения вместо root.

    INFO - CIS-DI-0005: Enable Content trust for Docker

	>Для решения этой проблемы используем `export DOCKER_CONTENT_TRUST=1 before` перед `docker pull/build`

    CIS-DI-0006: Add HEALTHCHECK instruction

    >Добавим инструкцию HEALTHCHECK в Dockerfile:

    CIS-DI-0008: Confirm safety of setuid/setgid files

    >Это предупреждение о наличии setuid/setgid файлов. В большинстве случаев это нормально для базового образа.
    Решение: Если эти файлы не нужны, их можно удалить или изменить права доступа.


    ![Dockerfile](screenshots/5.1.png)  

    ![dockle](screenshots/5.2.png)  

## Part 6. Базовый **Docker Compose**

**== Задание ==**

- [x] Напиши файл docker-compose.yml, с помощью которого:

    1) Подними докер-контейнер из [Части 5](#part-5-dockle) (он должен работать в локальной сети, т. е. не нужно использовать инструкцию `EXPOSE` и мапить порты на локальную машину).

    2) Подними докер-контейнер с nginx, который будет проксировать все запросы с `8080` порта на `81` порт первого контейнера.

    3) Замапь 8080 порт второго контейнера на 80 порт локальной машины.

    ![docker-compose.yml](screenshots/6.0.png)  

    ![nginx.conf](screenshots/6.1.png)  

- [x] Останови все запущенные контейнеры. 

    ![stop](screenshots/6.2.png)  

- [x] Собери и запусти проект с помощью команд `docker-compose build` и `docker-compose up`. 

    ![docker-compose build](screenshots/6.3.png)  

    ![docker-compose up -d](screenshots/6.4.png)  

    ![docker ps](screenshots/6.5.png)  

- [x] Проверь, что в браузере по localhost:80 отдается написанная тобой страничка, как и ранее. 

    ![curl](screenshots/6.6.png)

---

![ready](screenshots/6.7.png)