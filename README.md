# Modelica Simulation Service

> **Language**: [English](README.md) | [Русский](README.ru.md)

## Installation and Setup

### 1. Install OpenModelica
Download and install OpenModelica from the official website: https://openmodelica.org/download/

**Run the installer:**
- **Windows**: Double-click the `.exe` file and follow the instructions.
- **✅ Important**: Check the "Add to PATH" option during installation.
- **Linux (Ubuntu/Debian)**: `sudo apt-get install openmodelica`

**Verify the installation:** `omc --version`
- **Expected output**: `OpenModelica v1.21.0` (or higher)

### 2. Install Python Libraries
Install the required Python libraries using pip: `pip install flask requests OMPython`

### 3. Configure and Run the Services

**Step 3.1: Start the ZMQ Server**
Open a new terminal and run: `omc --interactive=zmq`
Keep this terminal open.

**Step 3.2: Configure the Model Path**
In the file `service.py`, set the `model_path` variable to the path of your `TankControlSystem.mo` model.

*Example for Windows:* `model_path = r"C:\ktk\models\TankControlSystem.mo"`
*Example for Linux/Mac:* `model_path = "/home/user/ktk/models/TankControlSystem.mo"`

**Step 3.3: Run the Modelica Service (service.py)**
1. Navigate to the project directory: `cd /your_path/modelica_service` (Example: `cd C:/ktk/modelica_service`)
2. Start the service: `python service.py`
- **Expected output**: `Serving Flask app 'service' Running on http://127.0.0.1:5001`
- Leave this terminal running.

**Step 3.4: Run the Main Application (app.py)**
1. Open a new terminal and navigate to the backend directory: `cd /your_path/backend` (Example: `cd C:/ktk/backend`)
2. Start the main application: `python app.py`
- **Expected output**: `Serving Flask app 'app' Running on http://127.0.0.1:5000`
- Leave this terminal running.

## Usage
1. Open your web browser and go to: http://127.0.0.1:5000
2. Set the desired parameters and click the **"Run Simulation"** button.


## Troubleshooting
- **"omc not found"**: Make sure OpenModelica is added to PATH or restart your terminal after installation.
- **Connection errors**: Ensure both services (steps 3.3 and 3.4) are running and the ZMQ server is active.
- **Model not found**: Verify the path in `service.py` points to the correct location of your `.mo` file.
