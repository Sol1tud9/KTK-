model TankControlSystem
  parameter Real tankVolume = 0.1 "Объем резервуара (м³)";        
  parameter Real initialTemperature = 20 "Начальная температура (℃)";
  parameter Real ambientTemperature = 20 "Температура окружения (℃)";
  parameter Real heatCapacity = 4180 "Теплоемкость (Дж/кг·℃)";
  parameter Real density = 1000 "Плотность (кг/м³)";
  parameter Real heaterPowerMax = 20000 "Максимальная мощность нагревателя (Вт)";  
  parameter Real setpointTemperature = 80 "Целевая температура (℃)";
  parameter Real heatLossCoeff = 10 "Коэффициент теплопотерь (Вт/℃)";

  parameter Real Kp = 1500 "Пропорциональный коэффициент";       
  parameter Real Ki = 8 "Интегральный коэффициент";            
  parameter Real Kd = 200 "Дифференциальный коэффициент";       
  
  Real temperature(start = initialTemperature) "Текущая температура";
  Real heaterPower "Мощность нагревателя";
  Real error "Ошибка регулирования";
  Real integralError(start = 0) "Интеграл ошибки";
  Real derivativeError "Производная ошибки";

initial equation
  temperature = initialTemperature;
  integralError = 0;

equation   // Уравнение теплового баланса
  der(temperature) = (heaterPower - heatLossCoeff*(temperature - ambientTemperature)) 
                    / (heatCapacity * density * tankVolume);

  // Расчет ошибки
  error = setpointTemperature - temperature;
  derivativeError = der(error);

  // Anti-windup механизм
  if heaterPower < heaterPowerMax and heaterPower > 0 then
    der(integralError) = error;  
  else
    der(integralError) = 0;      
  end if;

  // ПИД-регулятор с ограничениями
  heaterPower = min(max(Kp*error + Ki*integralError + Kd*derivativeError, 0), heaterPowerMax);

  annotation(
    experiment(
      StartTime = 0,
      StopTime = 3600,     
      Interval = 0.1,
      Tolerance = 1e-6,
      __Dymola_Algorithm = "Dassl"));
end TankControlSystem;
