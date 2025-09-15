from flask import Flask, request, jsonify
from flask_cors import CORS
from OMPython import OMCSessionZMQ
import threading
import re
import csv
import os
import time
import math
import atexit
import json


app = Flask(__name__)
CORS(app)
omc = OMCSessionZMQ()
lock = threading.Lock()


model_state = {}
current_model_name = ""


PARAM_REGEX = re.compile(r"parameter\s+\w+\s+(\w+)\s*(?:=\s*([^;]+))?\s*\"([^\"]*)\"")


def _perform_tank_step(state, step_interval):
    new_state = state.copy()


    temp = new_state['temperature']
    error = new_state['setpointTemperature'] - temp
    prev_error = new_state.get('error', error)
    derivativeError = (error - prev_error) / step_interval if step_interval > 0 else 0
    integralError = new_state['integralError']
    heaterPower = new_state['Kp'] * error + new_state['Ki'] * integralError + new_state['Kd'] * derivativeError


    if (0 < heaterPower < new_state['heaterPowerMax']):
        integralError += error * step_interval


    heaterPower = max(0, min(heaterPower, new_state['heaterPowerMax']))
   
    level = new_state['level']
    mass = level * new_state['tankVolume'] * new_state['density']
    if mass > 1e-6:
        heat_from_inlet = new_state['inletFlowRate'] * new_state['density'] * new_state['heatCapacity'] * (new_state['inletTemperature'] - temp)
        heat_loss = new_state['heatLossCoeff'] * (temp - new_state['ambientTemperature'])
        dT = step_interval * (heaterPower + heat_from_inlet - heat_loss) / (mass * new_state['heatCapacity'])
        new_state['temperature'] += dT
   
    level_change_rate = (new_state['inletFlowRate'] - new_state['outletFlowRate']) / new_state['tankVolume'] if new_state['tankVolume'] > 0 else 0
    level += level_change_rate * step_interval
    new_state['level'] = max(0, min(1.0, level))


    new_state.update({
        'heaterPower': heaterPower, 'error': error, 'integralError': integralError, 'derivativeError': derivativeError,
        'highAlarm': new_state['level'] >= new_state['levelHighAlarm'],
        'highWarning': (new_state['level'] >= new_state['levelHighWarning']) and (new_state['level'] < new_state['levelHighAlarm']),
        'lowWarning': (new_state['level'] <= new_state['levelLowWarning']) and (new_state['level'] > new_state['levelLowAlarm']),
        'lowAlarm': new_state['level'] <= new_state['levelLowAlarm'],
        'current_time': new_state['current_time'] + step_interval
    })
    return new_state


def _perform_separator_step(state, step_interval):
    new_state = state.copy()


    h_oil = new_state['h_oil']
    h_water = new_state['h_water']
   
    oil_error = new_state['oilLevelSetpoint'] - h_oil
    new_state['oil_integralError'] += oil_error * step_interval
    m_flow_oil = new_state['oil_Kp'] * oil_error + new_state['oil_Ki'] * new_state['oil_integralError']
    m_flow_oil = max(0, m_flow_oil)
   
    m_flow_water = 0
    if h_water > new_state['waterLevelSetpoint']:
        m_flow_water = new_state['water_Kp'] * (h_water - new_state['waterLevelSetpoint'])
    m_flow_water = max(0, m_flow_water)
   
    gasFraction = 1.0 - new_state['oilFraction'] - new_state['waterFraction']
    m_flow_gas = gasFraction * new_state['m_flow_in']
   
    oil_denom = new_state['separatorVolume'] * new_state['oilDensity']
    water_denom = new_state['separatorVolume'] * new_state['waterDensity']
   
    dh_oil = (new_state['m_flow_in'] * new_state['oilFraction'] - m_flow_oil) / oil_denom if oil_denom > 1e-6 else 0
    dh_water = (new_state['m_flow_in'] * new_state['waterFraction'] - m_flow_water) / water_denom if water_denom > 1e-6 else 0
   
    if (h_oil <= 0 and dh_oil < 0) or (h_oil + h_water >= 1 and dh_oil > 0): dh_oil = 0
    if (h_water <= 0 and dh_water < 0) or (h_oil + h_water >= 1 and dh_water > 0): dh_water = 0


    new_state['h_oil'] += dh_oil * step_interval
    new_state['h_water'] += dh_water * step_interval


    new_state.update({
        'm_flow_oil': m_flow_oil, 'm_flow_water': m_flow_water, 'm_flow_gas': m_flow_gas,
        'oil_error': oil_error, 'current_time': new_state['current_time'] + step_interval
    })
    return new_state


def cleanup_resources():
    global omc
    if omc:
        print("Closing OMC session...")
        omc.sendExpression("quit()")


atexit.register(cleanup_resources)


def parse_model_parameters(model_name):
    model_path = os.path.join(os.path.dirname(__file__), '..', 'models', f"{model_name}.mo")
    params = []
    if not os.path.isfile(model_path):
        return params
    try:
        with open(model_path, 'r', encoding='utf-8') as f:
            for line in f:
                match = PARAM_REGEX.search(line)
                if match:
                    name, default, comment = match.groups()
                    try:
                        default_val = float(default.strip()) if default else None
                    except (ValueError, TypeError):
                        default_val = default
                    params.append({'name': name, 'default': default_val, 'comment': comment})
    except Exception:
        pass
    return params


@app.route('/get_model_info', methods=['GET'])
def get_model_info():
    model_name = request.args.get('model_name')
    if not model_name:
        return jsonify({'error': 'model_name is required'}), 400
    params = parse_model_parameters(model_name)
    return jsonify({ 'model_name': model_name, 'parameters': params })


@app.route('/initialize_model', methods=['POST'])
def handle_initialize_model():
    global model_state, current_model_name
    try:
        config = request.json or {}
        model_name = config.get('model_name')
        if not model_name:
            return jsonify({"error": "No model_name provided"}), 400


        current_model_name = model_name
       
        
        defaults = {p['name']: p['default'] for p in parse_model_parameters(model_name)}
        provided_params = {k: v for k, v in config.items() if k not in ['model_name', 'step_interval', 'current_time', 'seek']}
        state = {**defaults, **provided_params}
        state.setdefault('current_time', config.get('current_time', 0))


        
        if model_name == 'TankControlSystem':
            state.update({'temperature': state.get('initialTemperature', 20), 'integralError': 0, 'derivativeError': 0, 'heaterPower': 0, 'level': state.get('levelStart', 0.5)})
        elif model_name == 'OilSeparator_ThreePhase':
            state.update({'h_oil': 0.5, 'h_water': 0.1, 'oil_integralError': 0})


        
        seek_time = config.get('current_time', 0)
        temp_state = state.copy()
        if seek_time > 0:
            step_interval = config.get('step_interval', 0.1)
            num_steps = int(seek_time / step_interval)
            for _ in range(num_steps):
                if model_name == 'TankControlSystem':
                    temp_state = _perform_tank_step(temp_state, step_interval)
                elif model_name == 'OilSeparator_ThreePhase':
                    temp_state = _perform_separator_step(temp_state, step_interval)
        with lock:
            model_state = temp_state
        return jsonify({"status": "success", "initial_state": model_state})
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@app.route('/update_parameters', methods=['POST'])
def handle_update_parameters():
    global model_state
    try:
        config = request.json
        if not config: return jsonify({"error": "No configuration provided"}), 400
        with lock:
            for param, value in config.items():
                if param in model_state:
                    model_state[param] = value
        return jsonify({ "status": "success", "message": "Parameters updated" })
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@app.route('/simulate_step', methods=['POST'])
def handle_simulate_step():
    global model_state, current_model_name
    try:
        config = request.json
        step_interval = config.get('step_interval', 0.1)
       
        with lock:
            
            for param, value in config.items():
                if param in model_state:
                    model_state[param] = value
           
            
            if current_model_name == 'TankControlSystem':
                model_state = _perform_tank_step(model_state, step_interval)
                step_data = create_step_data_tank(model_state)
            elif current_model_name == 'OilSeparator_ThreePhase':
                model_state = _perform_separator_step(model_state, step_interval)
                step_data = create_step_data_separator(model_state)
            else:
                step_data = {}


        return jsonify({ "status": "success", "step_data": step_data })
    except Exception as e:
        return jsonify({"error": str(e)}), 500


def create_step_data_tank(state):
    
    return {
        'time': state['current_time'],
        'temperature': state['temperature'], 'heaterPower': state['heaterPower'],
        'error': state['error'], 'integralError': state['integralError'], 'derivativeError': state['derivativeError'],
        'setpointTemperature': state['setpointTemperature'], 'level': state['level'],
        'levelHighAlarm': state.get('levelHighAlarm'), 'levelLowAlarm': state.get('levelLowAlarm'),
        'levelHighWarning': state.get('levelHighWarning'), 'levelLowWarning': state.get('levelLowWarning'),
        'highAlarm': bool(state['highAlarm']), 'highWarning': bool(state['highWarning']),
        'lowWarning': bool(state['lowWarning']), 'lowAlarm': bool(state['lowAlarm'])
    }


def create_step_data_separator(state):
    
    return {
        'time': state['current_time'],
        'h_oil': state['h_oil'], 'h_water': state['h_water'],
        'oilLevelSetpoint': state['oilLevelSetpoint'], 'waterLevelSetpoint': state['waterLevelSetpoint'],
        'm_flow_in': state['m_flow_in'],
        'm_flow_oil': state['m_flow_oil'], 'm_flow_water': state['m_flow_water'], 'm_flow_gas': state['m_flow_gas'],
        'oil_error': state['oil_error']
    }


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5001)
