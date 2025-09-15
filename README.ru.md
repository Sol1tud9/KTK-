# Modelica Simulation Service

> **Язык**: [English](README.md) | [Русский](README.ru.md)

## Установка и настройка

### 1. Установите OpenModelica
Скачайте и установите OpenModelica с официального сайта: https://openmodelica.org/download/

**Запустите установщик:**
- **Windows**: Дважды кликните на файл `.exe` и следуйте инструкциям.
- **✅ Важно**: Отметьте галочку "Add to PATH" при установке.
- **Linux (Ubuntu/Debian)**: `sudo apt-get install openmodelica`

**Проверьте установку:** `omc --version`
- **Ожидаемый вывод**: `OpenModelica v1.21.0` (или выше)

### 2. Установите необходимые библиотеки Python
Установите необходимые библиотеки с помощью pip: `pip install flask requests OMPython`

### 3. Настройте и запустите сервисы

**Шаг 3.1: Запустите ZMQ сервер**
Откройте новый терминал и выполните команду: `omc --interactive=zmq`
Не закрывайте этот терминал.

**Шаг 3.2: Настройте путь к модели**
В файле `service.py` в переменной `model_path` задайте путь до вашей модели `TankControlSystem.mo`.

*Пример для Windows:* `model_path = r"C:\ktk\models\TankControlSystem.mo"`
*Пример для Linux/Mac:* `model_path = "/home/user/ktk/models/TankControlSystem.mo"`

**Шаг 3.3: Запустите Modelica-сервис (service.py)**
1. Перейдите в директорию проекта: `cd /ваш_путь/modelica_service` (Пример: `cd C:/ktk/modelica_service`)
2. Запустите сервис: `python service.py`
- **Ожидаемый вывод**: `Serving Flask app 'service' Running on http://127.0.0.1:5001`
- Не закрывайте этот терминал.

**Шаг 3.4: Запустите основное приложение (app.py)**
1. Откройте новый терминал и перейдите в директорию `backend`: `cd /ваш_путь/backend` (Пример: `cd C:/ktk/backend`)
2. Запустите основное приложение: `python app.py`
- **Ожидаемый вывод**: `Serving Flask app 'app' Running on http://127.0.0.1:5000`
- Не закрывайте этот терминал.

## Использование
1. Откройте браузер и перейдите по адресу: http://127.0.0.1:5000
2. Задайте нужные параметры и нажмите кнопку **"Запустить симуляцию"**.


## Решение проблем
- **"omc not found"**: Убедитесь, что OpenModelica добавлен в PATH или перезапустите терминал после установки.
- **Ошибки соединения**: Убедитесь, что оба сервиса (шаги 3.3 и 3.4) запущены и ZMQ сервер активен.
- **Модель не найдена**: Проверьте, что путь в `service.py` ведет к правильному расположению вашего `.mo` файла.
