/* Initialization */
#include "TankLevelControl_model.h"
#include "TankLevelControl_11mix.h"
#include "TankLevelControl_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void TankLevelControl_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
integralError = 0.0
*/
void TankLevelControl_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[1] /* integralError STATE(1,error) */) = 0.0;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
temperature = initialTemperature
*/
void TankLevelControl_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->realVars[7] /* temperature DUMMY_STATE */) = (data->simulationInfo->realParameter[6] /* initialTemperature PARAM */);
  TRACE_POP
}

/*
equation index: 3
type: SIMPLE_ASSIGN
error = setpointTemperature - temperature
*/
void TankLevelControl_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  (data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */) = (data->simulationInfo->realParameter[7] /* setpointTemperature PARAM */) - (data->localData[0]->realVars[7] /* temperature DUMMY_STATE */);
  TRACE_POP
}
extern void TankLevelControl_eqFunction_21(DATA *data, threadData_t *threadData);


/*
equation index: 11
type: LINEAR

<var>heaterPower</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void TankLevelControl_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[6] /* heaterPower variable */) };
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving linear system 11 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  
  retValue = solve_linear_system(data, threadData, 0, &aux_x[0]);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,11};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 11 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[6] /* heaterPower variable */) = aux_x[0];

  TRACE_POP
}
extern void TankLevelControl_eqFunction_19(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void TankLevelControl_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  TankLevelControl_eqFunction_1(data, threadData);
  TankLevelControl_eqFunction_2(data, threadData);
  TankLevelControl_eqFunction_3(data, threadData);
  TankLevelControl_eqFunction_21(data, threadData);
  TankLevelControl_eqFunction_11(data, threadData);
  TankLevelControl_eqFunction_19(data, threadData);
  TRACE_POP
}

int TankLevelControl_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  TankLevelControl_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No TankLevelControl_functionInitialEquations_lambda0 function */

int TankLevelControl_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

