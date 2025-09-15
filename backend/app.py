from flask import Flask, request, jsonify, send_from_directory
from flask_socketio import SocketIO, emit
import requests
import threading
import time
import json


app = Flask(__name__, static_folder='../static')
socketio = SocketIO(app, cors_allowed_origins="*", async_mode='threading')


simulation_running = False
simulation_paused = False
simulation_thread = None
simulation_params = {}
current_time = 0
stop_time = 3600
simulation_data = [] 
time_speed = 1.0
seek_request = None 
state_lock = threading.Lock()


MODEL_INFO_CACHE = {}


def get_model_parameters(model_name):
    """Получает и кэширует список параметров для модели."""
    if model_name in MODEL_INFO_CACHE:
        return MODEL_INFO_CACHE[model_name]
    try:
        resp = requests.get(f'http://localhost:5000/get_model_info', params={'model_name': model_name}, timeout=5)
        if resp.status_code == 200:
            params = [p['name'] for p in resp.json().get('parameters', [])]
            MODEL_INFO_CACHE[model_name] = params
            return params
    except Exception:
        pass
    return []


@app.route('/')
def index():
    return send_from_directory(app.static_folder, 'index.html')


@app.route('/<path:path>')
def static_file(path):
    return send_from_directory(app.static_folder, path)


@app.route('/get_model_info')
def proxy_model_info():
    model_name = request.args.get('model_name')
    if not model_name:
        return jsonify({'error': 'model_name is required'}), 400
    try:
        resp = requests.get('http://localhost:5001/get_model_info', params={'model_name': model_name}, timeout=5)
        return (resp.content, resp.status_code, resp.headers.items())
    except Exception as e:
        return jsonify({'error': str(e)}), 500


def simulate_step():
    global simulation_running, simulation_params, current_time, simulation_data, time_speed, seek_request, state_lock
   
    try:
        with state_lock:
            local_seek_request = seek_request
            seek_request = None
            params = simulation_params.copy()
            params['current_time'] = current_time
            params['time_speed'] = time_speed


        if local_seek_request is not None:
            
            with state_lock:
                current_time = local_seek_request
                simulation_data = [data for data in simulation_data if data['time'] <= current_time]
           
            params['current_time'] = local_seek_request
            params['seek'] = True
           
            try:
                reset_response = requests.post('http://localhost:5001/initialize_model', json=params, timeout=10)
                if reset_response.status_code != 200:
                    socketio.emit('simulation_error', {'error': 'Не удалось сбросить состояние симуляции'})
                    return False
            except Exception as e:
                socketio.emit('simulation_error', {'error': f'Ошибка при перемотке: {str(e)}'})
                return False
       
        params['seek'] = False
        response = requests.post('http://localhost:5001/simulate_step', json=params, timeout=5)
       
        if response.status_code == 200:
            step_data = response.json().get('step_data', {})
            with state_lock:
                simulation_data.append(step_data)
                current_time += params.get('step_interval', 0.1) * time_speed
           
            socketio.emit('simulation_data', step_data)


            
            if step_data.get('highAlarm') or step_data.get('lowAlarm'):
                with state_lock:
                    if simulation_running:
                        simulation_running = False
                        socketio.emit('simulation_ended', {'message': 'Аварийная остановка: сработал датчик уровня.'})
                return False
           
            return True
        else:
            socketio.emit('simulation_error', {'error': 'Ошибка шага симуляции'})
            return False
           
    except Exception as e:
        socketio.emit('simulation_error', {'error': str(e)})
        return False


def simulation_loop():
    global simulation_running, current_time, stop_time, time_speed, simulation_paused


    while True:
        with state_lock:
            if not simulation_running: break
            paused = simulation_paused
            time_has_ended = current_time >= stop_time
            speed = time_speed


        if paused:
            time.sleep(0.1)
            continue
           
        if time_has_ended:
            with state_lock:
                simulation_running = False
            socketio.emit('simulation_ended', {'message': 'Симуляция завершена'})
            break


        if not simulate_step():
            with state_lock:
                simulation_running = False
            break
       
        sleep_time = max(0.01, 0.1 / speed)
        time.sleep(sleep_time)




@socketio.on('start_simulation')
def handle_start_simulation(data=None):
    """Socket.IO: Запуск симуляции."""
    if data is None:
        emit('simulation_error', {'error': 'Нет данных для запуска симуляции'})
        return
       
    global simulation_running, simulation_thread, simulation_params, current_time, stop_time, simulation_data, time_speed, simulation_paused
   
    with state_lock:
        if simulation_running: return


    model_name = data.get('model_name')
    if not model_name:
        emit('simulation_error', {'error': 'Не предоставлено имя модели'})
        return


    model_params = get_model_parameters(model_name)
    if not model_params:
        emit('simulation_error', {'error': f'Не удалось получить параметры модели {model_name}'})
        return


    try:
        with state_lock:
            simulation_params = {k: v for k, v in data.items()}
            stop_time = float(data.get('stop_time', 3600))
            current_time = 0
            simulation_data = []
            time_speed = float(data.get('time_speed', 1.0))
       
        init_response = requests.post('http://localhost:5001/initialize_model', json=simulation_params, timeout=10)
        if init_response.status_code != 200:
            emit('simulation_error', {'error': f'Не удалось инициализировать модель: {init_response.text}'})
            return


        with state_lock:
            simulation_running = True
            simulation_paused = False
            simulation_thread = threading.Thread(target=simulation_loop)
            simulation_thread.daemon = True
            simulation_thread.start()
       
        emit('simulation_started', {'message': 'Симуляция успешно запущена', 'current_time': current_time, 'stop_time': stop_time})
    except Exception as e:
        emit('simulation_error', {'error': str(e)})


@socketio.on('update_parameters')
def handle_update_parameters(data):
    global simulation_params, state_lock
    with state_lock:
        for param, value in data.items():
            simulation_params[param] = value
    try:
        requests.post('http://localhost:5001/update_parameters', json=data, timeout=5)
    except Exception as e:
        emit('simulation_error', {'error': str(e)})


@socketio.on('stop_simulation')
def handle_stop_simulation():
    global simulation_running, simulation_paused, state_lock
    with state_lock:
        if simulation_running:
            simulation_running = False
            simulation_paused = False
            emit('simulation_ended', {'message': 'Симуляция остановлена пользователем'})


@socketio.on('set_time_speed')
def handle_set_time_speed(data):
    global time_speed, state_lock
    with state_lock:
        time_speed = float(data.get('speed', 1.0))


@socketio.on('seek_time')
def handle_seek_time(data):
    global seek_request, state_lock
    with state_lock:
        seek_request = float(data['time'])
        emit('time_seeked', {'time': seek_request})


@socketio.on('pause_simulation')
def handle_pause_simulation():
    global simulation_paused, simulation_running, state_lock
    with state_lock:
        if simulation_running and not simulation_paused:
            simulation_paused = True
            emit('simulation_paused', {'message': 'Симуляция приостановлена'})


@socketio.on('resume_simulation')
def handle_resume_simulation():
    global simulation_paused, simulation_running, state_lock
    with state_lock:
        if simulation_running and simulation_paused:
            simulation_paused = False
            emit('simulation_resumed', {'message': 'Симуляция возобновлена'})


@socketio.on('update_stop_time')
def handle_update_stop_time(data):
    global stop_time, state_lock
    with state_lock:
        new_stop_time = float(data.get('stop_time', stop_time))
        if new_stop_time >= current_time:
            stop_time = new_stop_time
            emit('stop_time_updated', {'stop_time': stop_time})


@app.route('/get_full_data', methods=['GET'])
def get_full_data():
    global simulation_data, state_lock
    with state_lock:
        data = simulation_data[:]
    return jsonify({"data": data})


if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000, debug=True)
