/* Linear Systems */
#include "TankLevelControl_model.h"
#include "TankLevelControl_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* linear systems */

/*
equation index: 14
type: SIMPLE_ASSIGN
derivativeError = (heaterPower - (Kp * error + Ki * integralError)) / Kd
*/
void TankLevelControl_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  (data->localData[0]->realVars[5] /* derivativeError variable */) = DIVISION_SIM((data->localData[0]->realVars[6] /* heaterPower variable */) - (((data->simulationInfo->realParameter[2] /* Kp PARAM */)) * ((data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */)) + ((data->simulationInfo->realParameter[1] /* Ki PARAM */)) * ((data->localData[0]->realVars[1] /* integralError STATE(1,error) */))),(data->simulationInfo->realParameter[0] /* Kd PARAM */),"Kd",equationIndexes);
  TRACE_POP
}

void residualFunc18(RESIDUAL_USERDATA* userData, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = userData->data;
  threadData_t *threadData = userData->threadData;
  const int equationIndexes[2] = {1,18};
  ANALYTIC_JACOBIAN* jacobian = NULL;
  (data->localData[0]->realVars[6] /* heaterPower variable */) = xloc[0];
  /* local constraints */
  TankLevelControl_eqFunction_14(data, threadData);
  res[0] = (data->localData[0]->realVars[6] /* heaterPower variable */) + (((data->simulationInfo->realParameter[4] /* heatCapacity PARAM */)) * (((data->simulationInfo->realParameter[3] /* density PARAM */)) * ((data->simulationInfo->realParameter[8] /* tankVolume PARAM */)))) * ((data->simulationInfo->realParameter[6] /* initialTemperature PARAM */) - (data->localData[0]->realVars[7] /* temperature DUMMY_STATE */) + (data->localData[0]->realVars[5] /* derivativeError variable */));
  TRACE_POP
}
OMC_DISABLE_OPT
void initializeStaticLSData18(DATA* data, threadData_t* threadData, LINEAR_SYSTEM_DATA* linearSystemData, modelica_boolean initSparsePattern)
{
  const int indices[1] = {
    6 /* heaterPower */
  };
  for (int i = 0; i < 1; ++i) {
    linearSystemData->nominal[i] = data->modelData->realVarsData[indices[i]].attribute.nominal;
    linearSystemData->min[i]     = data->modelData->realVarsData[indices[i]].attribute.min;
    linearSystemData->max[i]     = data->modelData->realVarsData[indices[i]].attribute.max;
  }
}


/*
equation index: 5
type: SIMPLE_ASSIGN
$DER.temperature = (heaterPower + (initialTemperature - temperature) * heatCapacity * density * tankVolume) / (tankVolume * density * heatCapacity)
*/
void TankLevelControl_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->realVars[4] /* der(temperature) DUMMY_DER */) = DIVISION_SIM((data->localData[0]->realVars[6] /* heaterPower variable */) + ((data->simulationInfo->realParameter[6] /* initialTemperature PARAM */) - (data->localData[0]->realVars[7] /* temperature DUMMY_STATE */)) * (((data->simulationInfo->realParameter[4] /* heatCapacity PARAM */)) * (((data->simulationInfo->realParameter[3] /* density PARAM */)) * ((data->simulationInfo->realParameter[8] /* tankVolume PARAM */)))),(((data->simulationInfo->realParameter[8] /* tankVolume PARAM */)) * ((data->simulationInfo->realParameter[3] /* density PARAM */))) * ((data->simulationInfo->realParameter[4] /* heatCapacity PARAM */)),"tankVolume * density * heatCapacity",equationIndexes);
  TRACE_POP
}
/*
equation index: 6
type: SIMPLE_ASSIGN
derivativeError = (heaterPower - (Kp * error + Ki * integralError)) / Kd
*/
void TankLevelControl_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[5] /* derivativeError variable */) = DIVISION_SIM((data->localData[0]->realVars[6] /* heaterPower variable */) - (((data->simulationInfo->realParameter[2] /* Kp PARAM */)) * ((data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */)) + ((data->simulationInfo->realParameter[1] /* Ki PARAM */)) * ((data->localData[0]->realVars[1] /* integralError STATE(1,error) */))),(data->simulationInfo->realParameter[0] /* Kd PARAM */),"Kd",equationIndexes);
  TRACE_POP
}

void residualFunc11(RESIDUAL_USERDATA* userData, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = userData->data;
  threadData_t *threadData = userData->threadData;
  const int equationIndexes[2] = {1,11};
  ANALYTIC_JACOBIAN* jacobian = NULL;
  (data->localData[0]->realVars[6] /* heaterPower variable */) = xloc[0];
  /* local constraints */
  TankLevelControl_eqFunction_5(data, threadData);

  /* local constraints */
  TankLevelControl_eqFunction_6(data, threadData);
  res[0] = (-(data->localData[0]->realVars[4] /* der(temperature) DUMMY_DER */)) - (data->localData[0]->realVars[5] /* derivativeError variable */);
  TRACE_POP
}
OMC_DISABLE_OPT
void initializeStaticLSData11(DATA* data, threadData_t* threadData, LINEAR_SYSTEM_DATA* linearSystemData, modelica_boolean initSparsePattern)
{
  const int indices[1] = {
    6 /* heaterPower */
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
void TankLevelControl_initialLinearSystem(int nLinearSystems, LINEAR_SYSTEM_DATA* linearSystemData)
{
  /* linear systems */
  assertStreamPrint(NULL, nLinearSystems > 1, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[1].equationIndex = 18;
  linearSystemData[1].size = 1;
  linearSystemData[1].nnz = 0;
  linearSystemData[1].method = 1;   /* Symbolic Jacobian available */
  linearSystemData[1].residualFunc = residualFunc18;
  linearSystemData[1].strictTearingFunctionCall = NULL;
  linearSystemData[1].analyticalJacobianColumn = TankLevelControl_functionJacLSJac1_column;
  linearSystemData[1].initialAnalyticalJacobian = TankLevelControl_initialAnalyticJacobianLSJac1;
  linearSystemData[1].jacobianIndex = 1 /*jacInx*/;
  linearSystemData[1].setA = NULL;  //setLinearMatrixA18;
  linearSystemData[1].setb = NULL;  //setLinearVectorb18;
  linearSystemData[1].initializeStaticLSData = initializeStaticLSData18;
  
  assertStreamPrint(NULL, nLinearSystems > 0, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[0].equationIndex = 11;
  linearSystemData[0].size = 1;
  linearSystemData[0].nnz = 0;
  linearSystemData[0].method = 1;   /* Symbolic Jacobian available */
  linearSystemData[0].residualFunc = residualFunc11;
  linearSystemData[0].strictTearingFunctionCall = NULL;
  linearSystemData[0].analyticalJacobianColumn = TankLevelControl_functionJacLSJac0_column;
  linearSystemData[0].initialAnalyticalJacobian = TankLevelControl_initialAnalyticJacobianLSJac0;
  linearSystemData[0].jacobianIndex = 0 /*jacInx*/;
  linearSystemData[0].setA = NULL;  //setLinearMatrixA11;
  linearSystemData[0].setb = NULL;  //setLinearVectorb11;
  linearSystemData[0].initializeStaticLSData = initializeStaticLSData11;
}

#if defined(__cplusplus)
}
#endif

