/* Initialization */
#include "TankControlSystem_model.h"
#include "TankControlSystem_11mix.h"
#include "TankControlSystem_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void TankControlSystem_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
level = levelStart
*/
void TankControlSystem_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[2] /* level STATE(1) */) = (data->simulationInfo->realParameter[15] /* levelStart PARAM */);
  TRACE_POP
}
extern void TankControlSystem_eqFunction_24(DATA *data, threadData_t *threadData);

extern void TankControlSystem_eqFunction_23(DATA *data, threadData_t *threadData);

extern void TankControlSystem_eqFunction_22(DATA *data, threadData_t *threadData);

extern void TankControlSystem_eqFunction_21(DATA *data, threadData_t *threadData);


/*
equation index: 6
type: SIMPLE_ASSIGN
integralError = 0.0
*/
void TankControlSystem_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[1] /* integralError STATE(1,error) */) = 0.0;
  TRACE_POP
}

/*
equation index: 7
type: SIMPLE_ASSIGN
temperature = initialTemperature
*/
void TankControlSystem_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->localData[0]->realVars[9] /* temperature DUMMY_STATE */) = (data->simulationInfo->realParameter[8] /* initialTemperature PARAM */);
  TRACE_POP
}

/*
equation index: 8
type: SIMPLE_ASSIGN
error = setpointTemperature - temperature
*/
void TankControlSystem_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */) = (data->simulationInfo->realParameter[17] /* setpointTemperature PARAM */) - (data->localData[0]->realVars[9] /* temperature DUMMY_STATE */);
  TRACE_POP
}
extern void TankControlSystem_eqFunction_20(DATA *data, threadData_t *threadData);


/*
equation index: 16
type: LINEAR

<var>heaterPower</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void TankControlSystem_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[8] /* heaterPower variable */) };
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving linear system 16 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  
  retValue = solve_linear_system(data, threadData, 0, &aux_x[0]);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,16};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 16 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[8] /* heaterPower variable */) = aux_x[0];

  TRACE_POP
}
extern void TankControlSystem_eqFunction_31(DATA *data, threadData_t *threadData);

extern void TankControlSystem_eqFunction_19(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void TankControlSystem_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  TankControlSystem_eqFunction_1(data, threadData);
  TankControlSystem_eqFunction_24(data, threadData);
  TankControlSystem_eqFunction_23(data, threadData);
  TankControlSystem_eqFunction_22(data, threadData);
  TankControlSystem_eqFunction_21(data, threadData);
  TankControlSystem_eqFunction_6(data, threadData);
  TankControlSystem_eqFunction_7(data, threadData);
  TankControlSystem_eqFunction_8(data, threadData);
  TankControlSystem_eqFunction_20(data, threadData);
  TankControlSystem_eqFunction_16(data, threadData);
  TankControlSystem_eqFunction_31(data, threadData);
  TankControlSystem_eqFunction_19(data, threadData);
  TRACE_POP
}

int TankControlSystem_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  TankControlSystem_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No TankControlSystem_functionInitialEquations_lambda0 function */

int TankControlSystem_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

