model TankControlSystem

  parameter Real tankVolume = 0.1 "Объем резервуара (м^3)";

  parameter Real initialTemperature = 20 "Начальная температура жидкости (℃)";

  parameter Real heatCapacity = 4180 "Теплоемкость жидкости (Дж/кг·℃)";

  parameter Real density = 1000 "Плотность жидкости (кг/m^3)";

  parameter Real heaterPowerMax = 15000 "Максимальная мощность нагревателя (Вт)";

  parameter Real setpointTemperature = 80 "Заданная температура (℃)";

  parameter Real inletTemperature = 20 "Температура притока (℃)";
  parameter Real ambientTemperature = 20 "Температура окружающей среды (℃)";
  parameter Real heatLossCoeff = 10 "Коэффициент теплопотерь (Вт/°C)";

  parameter Real Kp = 1500 "Коэффициент пропорциональности ПИД-регулятора";

  parameter Real Ki = 8 "Интегральный коэффициент ПИД-регулятора";

  parameter Real Kd = 200 "Дифференциальный коэффициент ПИД-регулятора";

  parameter Real levelHighAlarm = 0.095 "Верхний аварийный уровень (доля от объема)";
  parameter Real levelHighWarning = 0.085 "Верхний предупредительный уровень (доля от объема)";
  parameter Real levelLowWarning = 0.015 "Нижний предупредительный уровень (доля от объема)";
  parameter Real levelLowAlarm = 0.005 "Нижний аварийный уровень (доля от объема)";
  
  parameter Real levelStart = 0.05 "Начальный уровень (доля от объема)";

  parameter Real inletFlowRate = 0.0001 "Расход на входе (м^3/с)";
  parameter Real outletFlowRate = 0.0 "Расход на выходе (м^3/с)";

  Real temperature "Текущая температура жидкости (℃)";

  Real heaterPower "Мощность нагревателя (Вт)";

  Real error "Ошибка регулирования";

  Real integralError "Интеграл ошибки";

  Real derivativeError "Производная ошибки";

  Real level "Текущий уровень жидкости (доля от объема)";
  Boolean highAlarm "Верхний аварийный сигнал";
  Boolean highWarning "Верхний предупредительный сигнал";
  Boolean lowWarning "Нижний предупредительный сигнал";
  Boolean lowAlarm "Нижний аварийный сигнал";

initial equation

  temperature = initialTemperature;

  integralError = 0;

  level = levelStart;

equation

  // Уравнение теплового баланса
  // Изменение температуры зависит от мощности нагревателя, тепла от притока и теплопотерь
  if level > 0.01 then
    der(temperature) = (heaterPower + inletFlowRate * density * heatCapacity * (inletTemperature - temperature) - heatLossCoeff * (temperature - ambientTemperature)) / (level * tankVolume * density * heatCapacity);
  else
    der(temperature) = 0;
  end if;

  error = setpointTemperature - temperature;

  der(integralError) = error;

  derivativeError = der(error);

  heaterPower = Kp * error + Ki * integralError + Kd * derivativeError;

  // Ограничение мощности нагревателя
  if heaterPower > heaterPowerMax then
    heaterPower = heaterPowerMax;
  elseif heaterPower < 0 then
    heaterPower = 0;
  end if;

  // Динамика уровня
  der(level) = (inletFlowRate - outletFlowRate) / tankVolume;

  // Сигналы уставок
  highAlarm = (level >= levelHighAlarm);
  highWarning = (level >= levelHighWarning) and (level < levelHighAlarm);
  lowWarning = (level <= levelLowWarning) and (level > levelLowAlarm);
  lowAlarm = (level <= levelLowAlarm);
end TankControlSystem;
