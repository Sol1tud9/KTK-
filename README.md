Устанавливаем OpenModelica с официального сайта: https://openmodelica.org/download/
Запустите установщик:<br>
Windows: Дважды кликните на .exe, следуйте инструкциям.<br>
✅ Важно: Отметьте галочку "Add to PATH" при установке.<br>

Linux (Ubuntu/Debian):<br>
bash<br>
```sudo apt-get install openmodelica```<br>
Проверьте версию:<br>
```omc --version```<br>
Ожидаемый вывод: OpenModelica v1.21.0 (или выше)<br>

Библиотеки, которые также нужно установить: ```pip install flask requests OMPython```<br>
ZMQ сервер: ```omc --interactive=zmq```<br>
в переменной model_path (service.py) задайте путь до модели TankLevelControl (пример ```model_path = r"C:\ktk\models\TankControlSystem.mo"```)<br>
Перейдите к директиории проекта ```cd /ваш_путь/modelica_service``` (пример: ```cd C:/ktk/modelica_service```) -> запустите ```python service.py```
Ожидаемый вывод service.py:<br>
Serving Flask app 'service'<br>
Running on http://127.0.0.1:5001<br>

Также app.py ```cd /ваш_путь/backend``` (пример: ```cd C:/ktk/backend```) -> запустите ```python app.py```
Serving Flask app 'app'<br>
Running on http://127.0.0.1:5000<br>

Откройте браузер и перейдите по адресу http://127.0.0.1:5000<br>

Задайте нужные параметры и нажмите кнопку "Запустить симуляцию"

 

