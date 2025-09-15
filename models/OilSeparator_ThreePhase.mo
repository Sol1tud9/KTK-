model OilSeparator_ThreePhase "Сепаратор нефти с тремя фазами (нефть, вода, газ) с регулированием уровня"

  // Параметры процесса
  parameter Real oilFraction = 0.6 "Доля нефти во входящей смеси (0..1)";
  parameter Real waterFraction = 0.2 "Доля воды во входящей смеси (0..1)";
  
  parameter Real oilDensity = 850 "Плотность нефти (кг/м³)";
  parameter Real waterDensity = 1000 "Плотность воды (кг/м³)";
  
  parameter Real separatorVolume = 1.0 "Объём сепаратора (м³)";
  parameter Real m_flow_in = 1.0 "Массовый расход на входе (кг/с)";

  // Параметры управления
  // Управление уровнем нефти (ПИ-регулятор)
  parameter Real oilLevelSetpoint = 0.5 "Заданный уровень нефти (доля)";
  parameter Real oil_Kp = 100 "Пропорциональный коэф. для уровня нефти";
  parameter Real oil_Ki = 10 "Интегральный коэф. для уровня нефти";

  // Управление уровнем воды (Пропорциональный слив)
  parameter Real waterLevelSetpoint = 0.3 "Уровень воды для начала слива (доля)";
  parameter Real water_Kp = 200 "Пропорциональный коэф. для слива воды";

  // Переменные состояния
  Real h_oil(start=0.5) "Уровень нефти (доля)";
  Real h_water(start=0.1) "Уровень воды (доля)";
  Real oil_integralError(start=0) "Интеграл ошибки уровня нефти";
  
  // Расчетные переменные
  Real oil_error "Ошибка уровня нефти";
  Real m_flow_oil "Выходной поток нефти (кг/с)";
  Real m_flow_water "Выходной поток воды (кг/с)";
  Real m_flow_gas "Выходной поток газа (кг/с)";е
  Real gasFraction = 1 - oilFraction - waterFraction;

initial equation 
  // Начальные условия определяются атрибутом 'start' у переменных

equation 
  // Массовый расход газа на выходе
  m_flow_gas = gasFraction * m_flow_in;

  // -- ПИ-регулятор уровня нефти --
  oil_error = oilLevelSetpoint - h_oil;
  der(oil_integralError) = oil_error;
  m_flow_oil = oil_Kp * oil_error + oil_Ki * oil_integralError;
  
  // Ограничение, чтобы поток не был отрицательным
  if m_flow_oil < 0 then
    m_flow_oil = 0;
  end if;

  // -- Пропорциональный регулятор уровня воды (слив) --
  // Вода сливается, только если уровень превышает заданный
  m_flow_water = if h_water > waterLevelSetpoint then
      water_Kp * (h_water - waterLevelSetpoint)
    else 
      0;
  end if;
  
  // -- Динамика уровней --
  // Изменение уровня нефти
  if h_oil <= 0 and (m_flow_in * oilFraction - m_flow_oil) < 0 then
    der(h_oil) = 0;
  else
    der(h_oil) = (m_flow_in * oilFraction - m_flow_oil) / (separatorVolume * oilDensity);
  end if;

  // Изменение уровня воды
  if h_water <= 0 and (m_flow_in * waterFraction - m_flow_water) < 0 then
    der(h_water) = 0;
  else
    der(h_water) = (m_flow_in * waterFraction - m_flow_water) / (separatorVolume * waterDensity);
  end if;

  // Простое ограничение, чтобы общий уровень не превышал 1
  if h_oil + h_water >= 1 and der(h_oil) > 0 then
     der(h_oil) = 0;
  end if;
  if h_oil + h_water >= 1 and der(h_water) > 0 then
     der(h_water) = 0;
  end if;

end OilSeparator_ThreePhase;
