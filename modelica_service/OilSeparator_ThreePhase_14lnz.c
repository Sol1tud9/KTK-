/* Linearization */
#include "OilSeparator_ThreePhase_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
const char *OilSeparator_ThreePhase_linear_model_frame()
{
  return "model linearized_model \"OilSeparator_ThreePhase\"\n"
  "  parameter Integer n = 4 \"number of states\";\n"
  "  parameter Integer m = 0 \"number of inputs\";\n"
  "  parameter Integer p = 0 \"number of outputs\";\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[m] = %s;\n"
  "\n"
  "  parameter Real A[n, n] =\n\t[%s];\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] = zeros(p, n);%s\n\n"
  "  parameter Real D[p, m] = zeros(p, m);%s\n\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[m];\n"
  "  output Real y[p];\n"
  "\n"
  "  Real 'x_h_oil' = x[1];\n"
  "  Real 'x_h_water' = x[2];\n"
  "  Real 'x_integralError_oil' = x[3];\n"
  "  Real 'x_integralError_water' = x[4];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "end linearized_model;\n";
}
const char *OilSeparator_ThreePhase_linear_model_datarecovery_frame()
{
  return "model linearized_model \"OilSeparator_ThreePhase\"\n"
  "  parameter Integer n = 4 \"number of states\";\n"
  "  parameter Integer m = 0 \"number of inputs\";\n"
  "  parameter Integer p = 0 \"number of outputs\";\n"
  "  parameter Integer nz = 11 \"data recovery variables\";\n"
  "  parameter Real x0[4] = %s;\n"
  "  parameter Real u0[0] = %s;\n"
  "  parameter Real z0[11] = %s;\n"
  "\n"
  "  parameter Real A[n, n] =\n\t[%s];\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] = zeros(p, n);%s\n\n"
  "  parameter Real D[p, m] = zeros(p, m);%s\n\n"
  "  parameter Real Cz[nz, n] =\n\t[%s];\n\n"
  "  parameter Real Dz[nz, m] = zeros(nz, m);%s\n\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[m];\n"
  "  output Real y[p];\n"
  "  output Real z[nz];\n"
  "\n"
  "  Real 'x_h_oil' = x[1];\n"
  "  Real 'x_h_water' = x[2];\n"
  "  Real 'x_integralError_oil' = x[3];\n"
  "  Real 'x_integralError_water' = x[4];\n"
  "  Real 'z_error_oil' = z[1];\n"
  "  Real 'z_error_water' = z[2];\n"
  "  Real 'z_gasFraction' = z[3];\n"
  "  Real 'z_m_flow_gas_out' = z[4];\n"
  "  Real 'z_m_flow_oil_in' = z[5];\n"
  "  Real 'z_m_flow_oil_out' = z[6];\n"
  "  Real 'z_m_flow_water_in' = z[7];\n"
  "  Real 'z_m_flow_water_out' = z[8];\n"
  "  Real 'z_oil_valve_signal' = z[9];\n"
  "  Real 'z_totalLiquidLevel' = z[10];\n"
  "  Real 'z_water_valve_signal' = z[11];\n"
  "equation\n"
  "  der(x) = A * x + B * u;\n"
  "  y = C * x + D * u;\n"
  "  z = Cz * x + Dz * u;\n"
  "end linearized_model;\n";
}
#if defined(__cplusplus)
}
#endif

