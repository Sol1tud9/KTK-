/* Initialization */
#include "OilSeparator_ThreePhase_model.h"
#include "OilSeparator_ThreePhase_11mix.h"
#include "OilSeparator_ThreePhase_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void OilSeparator_ThreePhase_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
integralError_oil = $START.integralError_oil
*/
void OilSeparator_ThreePhase_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->realVars[2] /* integralError_oil STATE(1,error_oil) */) = (data->modelData->realVarsData[2] /* integralError_oil STATE(1,error_oil) */).attribute .start;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
integralError_water = $START.integralError_water
*/
void OilSeparator_ThreePhase_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->realVars[3] /* integralError_water STATE(1,error_water) */) = (data->modelData->realVarsData[3] /* integralError_water STATE(1,error_water) */).attribute .start;
  TRACE_POP
}

/*
equation index: 3
type: SIMPLE_ASSIGN
m_flow_oil_in = m_flow_in * oilFraction
*/
void OilSeparator_ThreePhase_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  (data->localData[0]->realVars[12] /* m_flow_oil_in variable */) = ((data->simulationInfo->realParameter[4] /* m_flow_in PARAM */)) * ((data->simulationInfo->realParameter[6] /* oilFraction PARAM */));
  TRACE_POP
}

/*
equation index: 4
type: SIMPLE_ASSIGN
m_flow_water_in = m_flow_in * waterFraction
*/
void OilSeparator_ThreePhase_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[14] /* m_flow_water_in variable */) = ((data->simulationInfo->realParameter[4] /* m_flow_in PARAM */)) * ((data->simulationInfo->realParameter[10] /* waterFraction PARAM */));
  TRACE_POP
}

/*
equation index: 7
type: LINEAR

<var>h_water</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void OilSeparator_ThreePhase_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[1] /* h_water STATE(1) */) };
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving linear system 7 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  
  retValue = solve_linear_system(data, threadData, 0, &aux_x[0]);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,7};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 7 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[1] /* h_water STATE(1) */) = aux_x[0];

  TRACE_POP
}
extern void OilSeparator_ThreePhase_eqFunction_29(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_30(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_31(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_28(DATA *data, threadData_t *threadData);


/*
equation index: 14
type: LINEAR

<var>h_oil</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void OilSeparator_ThreePhase_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[0] /* h_oil STATE(1) */) };
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving linear system 14 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  
  retValue = solve_linear_system(data, threadData, 1, &aux_x[0]);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,14};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 14 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[0] /* h_oil STATE(1) */) = aux_x[0];

  TRACE_POP
}
extern void OilSeparator_ThreePhase_eqFunction_34(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_35(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_36(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_33(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_25(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_26(DATA *data, threadData_t *threadData);


/*
equation index: 21
type: SIMPLE_ASSIGN
gasFraction = 1.0 - oilFraction - waterFraction
*/
void OilSeparator_ThreePhase_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  (data->localData[0]->realVars[10] /* gasFraction variable */) = 1.0 - (data->simulationInfo->realParameter[6] /* oilFraction PARAM */) - (data->simulationInfo->realParameter[10] /* waterFraction PARAM */);
  TRACE_POP
}
extern void OilSeparator_ThreePhase_eqFunction_24(DATA *data, threadData_t *threadData);


/*
equation index: 23
type: ALGORITHM

  assert(oilFraction + waterFraction <= 1.01, "Сумма долей нефти и воды не может быть больше 1");
*/
void OilSeparator_ThreePhase_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  modelica_boolean tmp0;
  static const MMC_DEFSTRINGLIT(tmp1,84,"Сумма долей нефти и воды не может быть больше 1");
  static int tmp2 = 0;
  {
    tmp0 = LessEq((data->simulationInfo->realParameter[6] /* oilFraction PARAM */) + (data->simulationInfo->realParameter[10] /* waterFraction PARAM */),1.01);
    if(!tmp0)
    {
      {
        const char* assert_cond = "(oilFraction + waterFraction <= 1.01)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"C:/ktk/models/OilSeparator_ThreePhase.mo",49,3,49,134,0};
          infoStreamPrintWithEquationIndexes(LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp1)));
          data->simulationInfo->needToReThrow = 1;
        } else {
          FILE_INFO info = {"C:/ktk/models/OilSeparator_ThreePhase.mo",49,3,49,134,0};
          omc_assert_withEquationIndexes(threadData, info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp1)));
        }
      }
    }
  }
  TRACE_POP
}
OMC_DISABLE_OPT
void OilSeparator_ThreePhase_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  OilSeparator_ThreePhase_eqFunction_1(data, threadData);
  OilSeparator_ThreePhase_eqFunction_2(data, threadData);
  OilSeparator_ThreePhase_eqFunction_3(data, threadData);
  OilSeparator_ThreePhase_eqFunction_4(data, threadData);
  OilSeparator_ThreePhase_eqFunction_7(data, threadData);
  OilSeparator_ThreePhase_eqFunction_29(data, threadData);
  OilSeparator_ThreePhase_eqFunction_30(data, threadData);
  OilSeparator_ThreePhase_eqFunction_31(data, threadData);
  OilSeparator_ThreePhase_eqFunction_28(data, threadData);
  OilSeparator_ThreePhase_eqFunction_14(data, threadData);
  OilSeparator_ThreePhase_eqFunction_34(data, threadData);
  OilSeparator_ThreePhase_eqFunction_35(data, threadData);
  OilSeparator_ThreePhase_eqFunction_36(data, threadData);
  OilSeparator_ThreePhase_eqFunction_33(data, threadData);
  OilSeparator_ThreePhase_eqFunction_25(data, threadData);
  OilSeparator_ThreePhase_eqFunction_26(data, threadData);
  OilSeparator_ThreePhase_eqFunction_21(data, threadData);
  OilSeparator_ThreePhase_eqFunction_24(data, threadData);
  OilSeparator_ThreePhase_eqFunction_23(data, threadData);
  TRACE_POP
}

int OilSeparator_ThreePhase_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  OilSeparator_ThreePhase_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No OilSeparator_ThreePhase_functionInitialEquations_lambda0 function */

int OilSeparator_ThreePhase_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

