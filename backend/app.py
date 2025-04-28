from flask import Flask, request, jsonify, send_from_directory
import requests

app = Flask(__name__, static_folder='../static')

@app.route('/')
def index():
    return send_from_directory(app.static_folder, 'index.html')

@app.route('/<path:path>')
def static_file(path):
    return send_from_directory(app.static_folder, path)

@app.route('/simulate', methods=['POST'])
def simulate():
    try:
        data = request.json
        required_params = [
            'tankVolume', 'initialTemperature', 'heatCapacity',
            'density', 'heaterPowerMax', 'setpointTemperature',
            'Kp', 'Ki', 'Kd', 'stop_time', 'heatLossCoeff'  
        ]
        
        if not all(key in data for key in required_params):
            return jsonify({"error": "Missing required parameters"}), 400
        
        config = {
            "tankVolume": float(data['tankVolume']),
            "initialTemperature": float(data['initialTemperature']),
            "heatCapacity": float(data['heatCapacity']),
            "density": float(data['density']),
            "heaterPowerMax": float(data['heaterPowerMax']),
            "setpointTemperature": float(data['setpointTemperature']),
            "heatLossCoeff": float(data['heatLossCoeff']),
            "Kp": float(data['Kp']),
            "Ki": float(data['Ki']),
            "Kd": float(data['Kd']),
            "stop_time": float(data['stop_time'])
        }
        
        response = requests.post(
            'http://localhost:5001/simulate',
            json=config,
            timeout=30
        )
        
        return response.json()
    
    except requests.exceptions.Timeout:
        return jsonify({"error": "Simulation timeout"}), 504
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(port=5000)
