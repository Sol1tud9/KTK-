/* Linear Systems */
#include "TankControlSystem_model.h"
#include "TankControlSystem_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* linear systems */

/*
equation index: 26
type: SIMPLE_ASSIGN
derivativeError = if level > 0.01 then ((-inletFlowRate) * density * heatCapacity * (inletTemperature - temperature) - heatLossCoeff * (ambientTemperature - temperature) - heaterPower) / (heatCapacity * density * tankVolume * level) else 0.0
*/
void TankControlSystem_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  tmp1 = 1.0;
  tmp2 = 0.01;
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[2] /* level STATE(1) */), 0.01, tmp1, tmp2, 6, Greater, GreaterZC);
  (data->localData[0]->realVars[7] /* derivativeError variable */) = (tmp0?DIVISION_SIM(((-(data->simulationInfo->realParameter[9] /* inletFlowRate PARAM */))) * (((data->simulationInfo->realParameter[4] /* density PARAM */)) * (((data->simulationInfo->realParameter[5] /* heatCapacity PARAM */)) * ((data->simulationInfo->realParameter[10] /* inletTemperature PARAM */) - (data->localData[0]->realVars[9] /* temperature DUMMY_STATE */)))) - (((data->simulationInfo->realParameter[6] /* heatLossCoeff PARAM */)) * ((data->simulationInfo->realParameter[3] /* ambientTemperature PARAM */) - (data->localData[0]->realVars[9] /* temperature DUMMY_STATE */))) - (data->localData[0]->realVars[8] /* heaterPower variable */),((((data->simulationInfo->realParameter[5] /* heatCapacity PARAM */)) * ((data->simulationInfo->realParameter[4] /* density PARAM */))) * ((data->simulationInfo->realParameter[18] /* tankVolume PARAM */))) * ((data->localData[0]->realVars[2] /* level STATE(1) */)),"heatCapacity * density * tankVolume * level",equationIndexes):0.0);
  TRACE_POP
}

void residualFunc30(RESIDUAL_USERDATA* userData, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = userData->data;
  threadData_t *threadData = userData->threadData;
  const int equationIndexes[2] = {1,30};
  ANALYTIC_JACOBIAN* jacobian = NULL;
  (data->localData[0]->realVars[8] /* heaterPower variable */) = xloc[0];
  /* local constraints */
  TankControlSystem_eqFunction_26(data, threadData);
  res[0] = ((data->simulationInfo->realParameter[0] /* Kd PARAM */)) * ((data->localData[0]->realVars[7] /* derivativeError variable */)) + ((data->simulationInfo->realParameter[1] /* Ki PARAM */)) * ((data->localData[0]->realVars[1] /* integralError STATE(1,error) */)) + ((data->simulationInfo->realParameter[2] /* Kp PARAM */)) * ((data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */)) - (data->localData[0]->realVars[8] /* heaterPower variable */);
  TRACE_POP
}
OMC_DISABLE_OPT
void initializeStaticLSData30(DATA* data, threadData_t* threadData, LINEAR_SYSTEM_DATA* linearSystemData, modelica_boolean initSparsePattern)
{
  const int indices[1] = {
    8 /* heaterPower */
  };
  for (int i = 0; i < 1; ++i) {
    linearSystemData->nominal[i] = data->modelData->realVarsData[indices[i]].attribute.nominal;
    linearSystemData->min[i]     = data->modelData->realVarsData[indices[i]].attribute.min;
    linearSystemData->max[i]     = data->modelData->realVarsData[indices[i]].attribute.max;
  }
}


/*
equation index: 10
type: SIMPLE_ASSIGN
$DER.temperature = if level > 0.01 then (heaterPower - ((-inletFlowRate) * density * heatCapacity * (inletTemperature - temperature) - heatLossCoeff * (ambientTemperature - temperature))) / (heatCapacity * density * tankVolume * level) else 0.0
*/
void TankControlSystem_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  modelica_boolean tmp0;
  tmp0 = Greater((data->localData[0]->realVars[2] /* level STATE(1) */),0.01);
  (data->localData[0]->realVars[6] /* der(temperature) DUMMY_DER */) = (tmp0?DIVISION_SIM((data->localData[0]->realVars[8] /* heaterPower variable */) - (((-(data->simulationInfo->realParameter[9] /* inletFlowRate PARAM */))) * (((data->simulationInfo->realParameter[4] /* density PARAM */)) * (((data->simulationInfo->realParameter[5] /* heatCapacity PARAM */)) * ((data->simulationInfo->realParameter[10] /* inletTemperature PARAM */) - (data->localData[0]->realVars[9] /* temperature DUMMY_STATE */)))) - (((data->simulationInfo->realParameter[6] /* heatLossCoeff PARAM */)) * ((data->simulationInfo->realParameter[3] /* ambientTemperature PARAM */) - (data->localData[0]->realVars[9] /* temperature DUMMY_STATE */)))),((((data->simulationInfo->realParameter[5] /* heatCapacity PARAM */)) * ((data->simulationInfo->realParameter[4] /* density PARAM */))) * ((data->simulationInfo->realParameter[18] /* tankVolume PARAM */))) * ((data->localData[0]->realVars[2] /* level STATE(1) */)),"heatCapacity * density * tankVolume * level",equationIndexes):0.0);
  TRACE_POP
}
/*
equation index: 11
type: SIMPLE_ASSIGN
derivativeError = (heaterPower - (Kp * error + Ki * integralError)) / Kd
*/
void TankControlSystem_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  (data->localData[0]->realVars[7] /* derivativeError variable */) = DIVISION_SIM((data->localData[0]->realVars[8] /* heaterPower variable */) - (((data->simulationInfo->realParameter[2] /* Kp PARAM */)) * ((data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */)) + ((data->simulationInfo->realParameter[1] /* Ki PARAM */)) * ((data->localData[0]->realVars[1] /* integralError STATE(1,error) */))),(data->simulationInfo->realParameter[0] /* Kd PARAM */),"Kd",equationIndexes);
  TRACE_POP
}

void residualFunc16(RESIDUAL_USERDATA* userData, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = userData->data;
  threadData_t *threadData = userData->threadData;
  const int equationIndexes[2] = {1,16};
  ANALYTIC_JACOBIAN* jacobian = NULL;
  (data->localData[0]->realVars[8] /* heaterPower variable */) = xloc[0];
  /* local constraints */
  TankControlSystem_eqFunction_10(data, threadData);

  /* local constraints */
  TankControlSystem_eqFunction_11(data, threadData);
  res[0] = (-(data->localData[0]->realVars[6] /* der(temperature) DUMMY_DER */)) - (data->localData[0]->realVars[7] /* derivativeError variable */);
  TRACE_POP
}
OMC_DISABLE_OPT
void initializeStaticLSData16(DATA* data, threadData_t* threadData, LINEAR_SYSTEM_DATA* linearSystemData, modelica_boolean initSparsePattern)
{
  const int indices[1] = {
    8 /* heaterPower */
  };
  for (int i = 0; i < 1; ++i) {
    linearSystemData->nominal[i] = data->modelData->realVarsData[indices[i]].attribute.nominal;
    linearSystemData->min[i]     = data->modelData->realVarsData[indices[i]].attribute.min;
    linearSystemData->max[i]     = data->modelData->realVarsData[indices[i]].attribute.max;
  }
}

/* Prototypes for the strict sets (Dynamic Tearing) */

/* Global constraints for the casual sets */
/* function initialize linear systems */
void TankControlSystem_initialLinearSystem(int nLinearSystems, LINEAR_SYSTEM_DATA* linearSystemData)
{
  /* linear systems */
  assertStreamPrint(NULL, nLinearSystems > 1, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[1].equationIndex = 30;
  linearSystemData[1].size = 1;
  linearSystemData[1].nnz = 0;
  linearSystemData[1].method = 1;   /* Symbolic Jacobian available */
  linearSystemData[1].residualFunc = residualFunc30;
  linearSystemData[1].strictTearingFunctionCall = NULL;
  linearSystemData[1].analyticalJacobianColumn = TankControlSystem_functionJacLSJac1_column;
  linearSystemData[1].initialAnalyticalJacobian = TankControlSystem_initialAnalyticJacobianLSJac1;
  linearSystemData[1].jacobianIndex = 1 /*jacInx*/;
  linearSystemData[1].setA = NULL;  //setLinearMatrixA30;
  linearSystemData[1].setb = NULL;  //setLinearVectorb30;
  linearSystemData[1].initializeStaticLSData = initializeStaticLSData30;
  
  assertStreamPrint(NULL, nLinearSystems > 0, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[0].equationIndex = 16;
  linearSystemData[0].size = 1;
  linearSystemData[0].nnz = 0;
  linearSystemData[0].method = 1;   /* Symbolic Jacobian available */
  linearSystemData[0].residualFunc = residualFunc16;
  linearSystemData[0].strictTearingFunctionCall = NULL;
  linearSystemData[0].analyticalJacobianColumn = TankControlSystem_functionJacLSJac0_column;
  linearSystemData[0].initialAnalyticalJacobian = TankControlSystem_initialAnalyticJacobianLSJac0;
  linearSystemData[0].jacobianIndex = 0 /*jacInx*/;
  linearSystemData[0].setA = NULL;  //setLinearMatrixA16;
  linearSystemData[0].setb = NULL;  //setLinearVectorb16;
  linearSystemData[0].initializeStaticLSData = initializeStaticLSData16;
}

#if defined(__cplusplus)
}
#endif

