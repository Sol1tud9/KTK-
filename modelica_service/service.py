from flask import Flask, request, jsonify
from OMPython import OMCSessionZMQ
import threading
import re
import csv
import os

app = Flask(__name__)
omc = OMCSessionZMQ()
lock = threading.Lock()

def parse_simulation_results(stop_time):
    results = []
    try:
        with open('TankControlSystem_res.csv', 'r') as f:
            reader = csv.DictReader(f)
            for row in reader:
                results.append({
                    'time': float(row['time']),
                    'temperature': float(row['temperature']),
                    'heaterPower': float(row['heaterPower']),
                    'error': float(row['error']),
                    'integralError': float(row['integralError']),
                    'derivativeError': float(row['derivativeError'])
                })
        os.remove('TankControlSystem_res.csv')
    except Exception as e:
        print(f"Error reading results: {str(e)}")
    return results

@app.route('/simulate', methods=['POST'])
def handle_simulation():
    try:
        config = request.json
        with lock:
            model_path = r"C:\ktk\models\TankControlSystem.mo"      #ПУТЬ ЗАДАВАТЬ ЗДЕСЬ
            load_res = omc.execute(f'loadFile("{model_path}")')
            
            if "error" in load_res.lower():
                return jsonify({"error": f"Model loading error: {load_res}"}), 400

            params = {
                'tankVolume': config.get('tankVolume', 0.1),          # Объем резервуара (м³)
                'initialTemperature': config.get('initialTemperature', 20),  # Начальная температура (°C)
                'heatCapacity': config.get('heatCapacity', 4180),     # Теплоемкость воды (Дж/кг·°C)
                'density': config.get('density', 1000),               # Плотность воды (кг/м³)
                'heaterPowerMax': config.get('heaterPowerMax', 20000), # Макс. мощность нагревателя (Вт)
                'setpointTemperature': config.get('setpointTemperature', 80), # Целевая температура (°C)
                'heatLossCoeff': config.get('heatLossCoeff', 10),      # Коэффициент теплопотерь (Вт/°C)
                'Kp': config.get('Kp', 1500),                         # Пропорциональный коэффициент
                'Ki': config.get('Ki', 8),                            # Интегральный коэффициент
                'Kd': config.get('Kd', 200)                           # Дифференциальный коэффициент
            }
            
            for param, value in params.items():
                omc.execute(f'setParameterValue(TankControlSystem, {param}, {value})')

            stop_time = config.get('stop_time', 3600)
            sim_res = omc.execute(
                f'simulate(TankControlSystem, stopTime={stop_time}, '
                'outputFormat="csv", numberOfIntervals=500)'
            )

            results = parse_simulation_results(stop_time)
            
            return jsonify({
                "status": "success",
                "time_series": results,
                "config": params,
                "sim_time": stop_time
            })
    
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(port=5001)
