/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "OilSeparator_ThreePhase_model.h"
#include "simulation/solver/events.h"

/* FIXME these defines are ugly and hard to read, why not use direct function pointers instead? */
#define prefixedName_performSimulation OilSeparator_ThreePhase_performSimulation
#define prefixedName_updateContinuousSystem OilSeparator_ThreePhase_updateContinuousSystem
#include <simulation/solver/perform_simulation.c.inc>

#define prefixedName_performQSSSimulation OilSeparator_ThreePhase_performQSSSimulation
#include <simulation/solver/perform_qss_simulation.c.inc>


/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int OilSeparator_ThreePhase_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 24
type: SIMPLE_ASSIGN
m_flow_gas_out = if gasFraction > 0.0 then m_flow_in * gasFraction else 0.0
*/
void OilSeparator_ThreePhase_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  modelica_boolean tmp0;
  tmp0 = Greater((data->localData[0]->realVars[10] /* gasFraction variable */),0.0);
  (data->localData[0]->realVars[11] /* m_flow_gas_out variable */) = (tmp0?((data->simulationInfo->realParameter[4] /* m_flow_in PARAM */)) * ((data->localData[0]->realVars[10] /* gasFraction variable */)):0.0);
  TRACE_POP
}
/*
equation index: 25
type: SIMPLE_ASSIGN
totalLiquidLevel = h_oil + h_water
*/
void OilSeparator_ThreePhase_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  (data->localData[0]->realVars[17] /* totalLiquidLevel variable */) = (data->localData[0]->realVars[0] /* h_oil STATE(1) */) + (data->localData[0]->realVars[1] /* h_water STATE(1) */);
  TRACE_POP
}
/*
equation index: 26
type: SIMPLE_ASSIGN
highLevelAlarm = totalLiquidLevel > 0.98
*/
void OilSeparator_ThreePhase_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  modelica_boolean tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  tmp2 = 1.0;
  tmp3 = 0.98;
  relationhysteresis(data, &tmp1, (data->localData[0]->realVars[17] /* totalLiquidLevel variable */), 0.98, tmp2, tmp3, 0, Greater, GreaterZC);
  (data->localData[0]->booleanVars[0] /* highLevelAlarm DISCRETE */) = tmp1;
  TRACE_POP
}
/*
equation index: 27
type: SIMPLE_ASSIGN
error_water = h_water - waterLevelSetpoint
*/
void OilSeparator_ThreePhase_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  (data->localData[0]->realVars[9] /* error_water variable */) = (data->localData[0]->realVars[1] /* h_water STATE(1) */) - (data->simulationInfo->realParameter[11] /* waterLevelSetpoint PARAM */);
  TRACE_POP
}
/*
equation index: 28
type: SIMPLE_ASSIGN
$DER.integralError_water = error_water
*/
void OilSeparator_ThreePhase_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  (data->localData[0]->realVars[7] /* der(integralError_water) STATE_DER */) = (data->localData[0]->realVars[9] /* error_water variable */);
  TRACE_POP
}
/*
equation index: 29
type: SIMPLE_ASSIGN
water_valve_signal = Kp_water * error_water + Ki_water * integralError_water
*/
void OilSeparator_ThreePhase_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  (data->localData[0]->realVars[18] /* water_valve_signal variable */) = ((data->simulationInfo->realParameter[3] /* Kp_water PARAM */)) * ((data->localData[0]->realVars[9] /* error_water variable */)) + ((data->simulationInfo->realParameter[1] /* Ki_water PARAM */)) * ((data->localData[0]->realVars[3] /* integralError_water STATE(1,error_water) */));
  TRACE_POP
}
/*
equation index: 30
type: SIMPLE_ASSIGN
m_flow_water_out = max(0.0, water_valve_signal)
*/
void OilSeparator_ThreePhase_eqFunction_30(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,30};
  (data->localData[0]->realVars[15] /* m_flow_water_out variable */) = fmax(0.0,(data->localData[0]->realVars[18] /* water_valve_signal variable */));
  TRACE_POP
}
/*
equation index: 31
type: SIMPLE_ASSIGN
$DER.h_water = (m_flow_water_in - m_flow_water_out) / (separatorVolume * waterDensity)
*/
void OilSeparator_ThreePhase_eqFunction_31(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,31};
  (data->localData[0]->realVars[5] /* der(h_water) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[14] /* m_flow_water_in variable */) - (data->localData[0]->realVars[15] /* m_flow_water_out variable */),((data->simulationInfo->realParameter[8] /* separatorVolume PARAM */)) * ((data->simulationInfo->realParameter[9] /* waterDensity PARAM */)),"separatorVolume * waterDensity",equationIndexes);
  TRACE_POP
}
/*
equation index: 32
type: SIMPLE_ASSIGN
error_oil = h_oil - oilLevelSetpoint
*/
void OilSeparator_ThreePhase_eqFunction_32(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,32};
  (data->localData[0]->realVars[8] /* error_oil variable */) = (data->localData[0]->realVars[0] /* h_oil STATE(1) */) - (data->simulationInfo->realParameter[7] /* oilLevelSetpoint PARAM */);
  TRACE_POP
}
/*
equation index: 33
type: SIMPLE_ASSIGN
$DER.integralError_oil = error_oil
*/
void OilSeparator_ThreePhase_eqFunction_33(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,33};
  (data->localData[0]->realVars[6] /* der(integralError_oil) STATE_DER */) = (data->localData[0]->realVars[8] /* error_oil variable */);
  TRACE_POP
}
/*
equation index: 34
type: SIMPLE_ASSIGN
oil_valve_signal = Kp_oil * error_oil + Ki_oil * integralError_oil
*/
void OilSeparator_ThreePhase_eqFunction_34(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,34};
  (data->localData[0]->realVars[16] /* oil_valve_signal variable */) = ((data->simulationInfo->realParameter[2] /* Kp_oil PARAM */)) * ((data->localData[0]->realVars[8] /* error_oil variable */)) + ((data->simulationInfo->realParameter[0] /* Ki_oil PARAM */)) * ((data->localData[0]->realVars[2] /* integralError_oil STATE(1,error_oil) */));
  TRACE_POP
}
/*
equation index: 35
type: SIMPLE_ASSIGN
m_flow_oil_out = max(0.0, oil_valve_signal)
*/
void OilSeparator_ThreePhase_eqFunction_35(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,35};
  (data->localData[0]->realVars[13] /* m_flow_oil_out variable */) = fmax(0.0,(data->localData[0]->realVars[16] /* oil_valve_signal variable */));
  TRACE_POP
}
/*
equation index: 36
type: SIMPLE_ASSIGN
$DER.h_oil = (m_flow_oil_in - m_flow_oil_out) / (separatorVolume * oilDensity)
*/
void OilSeparator_ThreePhase_eqFunction_36(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,36};
  (data->localData[0]->realVars[4] /* der(h_oil) STATE_DER */) = DIVISION_SIM((data->localData[0]->realVars[12] /* m_flow_oil_in variable */) - (data->localData[0]->realVars[13] /* m_flow_oil_out variable */),((data->simulationInfo->realParameter[8] /* separatorVolume PARAM */)) * ((data->simulationInfo->realParameter[5] /* oilDensity PARAM */)),"separatorVolume * oilDensity",equationIndexes);
  TRACE_POP
}

OMC_DISABLE_OPT
int OilSeparator_ThreePhase_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  OilSeparator_ThreePhase_functionLocalKnownVars(data, threadData);
  OilSeparator_ThreePhase_eqFunction_24(data, threadData);

  OilSeparator_ThreePhase_eqFunction_25(data, threadData);

  OilSeparator_ThreePhase_eqFunction_26(data, threadData);

  OilSeparator_ThreePhase_eqFunction_27(data, threadData);

  OilSeparator_ThreePhase_eqFunction_28(data, threadData);

  OilSeparator_ThreePhase_eqFunction_29(data, threadData);

  OilSeparator_ThreePhase_eqFunction_30(data, threadData);

  OilSeparator_ThreePhase_eqFunction_31(data, threadData);

  OilSeparator_ThreePhase_eqFunction_32(data, threadData);

  OilSeparator_ThreePhase_eqFunction_33(data, threadData);

  OilSeparator_ThreePhase_eqFunction_34(data, threadData);

  OilSeparator_ThreePhase_eqFunction_35(data, threadData);

  OilSeparator_ThreePhase_eqFunction_36(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int OilSeparator_ThreePhase_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/* forwarded equations */
extern void OilSeparator_ThreePhase_eqFunction_27(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_28(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_29(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_30(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_31(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_32(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_33(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_34(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_35(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_36(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  {
    OilSeparator_ThreePhase_eqFunction_27(data, threadData);
    threadData->lastEquationSolved = 27;
  }
  {
    OilSeparator_ThreePhase_eqFunction_28(data, threadData);
    threadData->lastEquationSolved = 28;
  }
  {
    OilSeparator_ThreePhase_eqFunction_29(data, threadData);
    threadData->lastEquationSolved = 29;
  }
  {
    OilSeparator_ThreePhase_eqFunction_30(data, threadData);
    threadData->lastEquationSolved = 30;
  }
  {
    OilSeparator_ThreePhase_eqFunction_31(data, threadData);
    threadData->lastEquationSolved = 31;
  }
  {
    OilSeparator_ThreePhase_eqFunction_32(data, threadData);
    threadData->lastEquationSolved = 32;
  }
  {
    OilSeparator_ThreePhase_eqFunction_33(data, threadData);
    threadData->lastEquationSolved = 33;
  }
  {
    OilSeparator_ThreePhase_eqFunction_34(data, threadData);
    threadData->lastEquationSolved = 34;
  }
  {
    OilSeparator_ThreePhase_eqFunction_35(data, threadData);
    threadData->lastEquationSolved = 35;
  }
  {
    OilSeparator_ThreePhase_eqFunction_36(data, threadData);
    threadData->lastEquationSolved = 36;
  }
}

int OilSeparator_ThreePhase_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  OilSeparator_ThreePhase_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "OilSeparator_ThreePhase_12jac.h"
#include "OilSeparator_ThreePhase_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks OilSeparator_ThreePhase_callback = {
   (int (*)(DATA *, threadData_t *, void *)) OilSeparator_ThreePhase_performSimulation,    /* performSimulation */
   (int (*)(DATA *, threadData_t *, void *)) OilSeparator_ThreePhase_performQSSSimulation,    /* performQSSSimulation */
   OilSeparator_ThreePhase_updateContinuousSystem,    /* updateContinuousSystem */
   OilSeparator_ThreePhase_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   OilSeparator_ThreePhase_initialLinearSystem,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   OilSeparator_ThreePhase_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   OilSeparator_ThreePhase_initializeDAEmodeData,
   OilSeparator_ThreePhase_functionODE,
   OilSeparator_ThreePhase_functionAlgebraics,
   OilSeparator_ThreePhase_functionDAE,
   OilSeparator_ThreePhase_functionLocalKnownVars,
   OilSeparator_ThreePhase_input_function,
   OilSeparator_ThreePhase_input_function_init,
   OilSeparator_ThreePhase_input_function_updateStartValues,
   OilSeparator_ThreePhase_data_function,
   OilSeparator_ThreePhase_output_function,
   OilSeparator_ThreePhase_setc_function,
   OilSeparator_ThreePhase_setb_function,
   OilSeparator_ThreePhase_function_storeDelayed,
   OilSeparator_ThreePhase_function_storeSpatialDistribution,
   OilSeparator_ThreePhase_function_initSpatialDistribution,
   OilSeparator_ThreePhase_updateBoundVariableAttributes,
   OilSeparator_ThreePhase_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   OilSeparator_ThreePhase_functionRemovedInitialEquations,
   OilSeparator_ThreePhase_updateBoundParameters,
   OilSeparator_ThreePhase_checkForAsserts,
   OilSeparator_ThreePhase_function_ZeroCrossingsEquations,
   OilSeparator_ThreePhase_function_ZeroCrossings,
   OilSeparator_ThreePhase_function_updateRelations,
   OilSeparator_ThreePhase_zeroCrossingDescription,
   OilSeparator_ThreePhase_relationDescription,
   OilSeparator_ThreePhase_function_initSample,
   OilSeparator_ThreePhase_INDEX_JAC_A,
   OilSeparator_ThreePhase_INDEX_JAC_B,
   OilSeparator_ThreePhase_INDEX_JAC_C,
   OilSeparator_ThreePhase_INDEX_JAC_D,
   OilSeparator_ThreePhase_INDEX_JAC_F,
   OilSeparator_ThreePhase_INDEX_JAC_H,
   OilSeparator_ThreePhase_initialAnalyticJacobianA,
   OilSeparator_ThreePhase_initialAnalyticJacobianB,
   OilSeparator_ThreePhase_initialAnalyticJacobianC,
   OilSeparator_ThreePhase_initialAnalyticJacobianD,
   OilSeparator_ThreePhase_initialAnalyticJacobianF,
   OilSeparator_ThreePhase_initialAnalyticJacobianH,
   OilSeparator_ThreePhase_functionJacA_column,
   OilSeparator_ThreePhase_functionJacB_column,
   OilSeparator_ThreePhase_functionJacC_column,
   OilSeparator_ThreePhase_functionJacD_column,
   OilSeparator_ThreePhase_functionJacF_column,
   OilSeparator_ThreePhase_functionJacH_column,
   OilSeparator_ThreePhase_linear_model_frame,
   OilSeparator_ThreePhase_linear_model_datarecovery_frame,
   OilSeparator_ThreePhase_mayer,
   OilSeparator_ThreePhase_lagrange,
   OilSeparator_ThreePhase_pickUpBoundsForInputsInOptimization,
   OilSeparator_ThreePhase_setInputData,
   OilSeparator_ThreePhase_getTimeGrid,
   OilSeparator_ThreePhase_symbolicInlineSystem,
   OilSeparator_ThreePhase_function_initSynchronous,
   OilSeparator_ThreePhase_function_updateSynchronous,
   OilSeparator_ThreePhase_function_equationsSynchronous,
   OilSeparator_ThreePhase_inputNames,
   OilSeparator_ThreePhase_dataReconciliationInputNames,
   OilSeparator_ThreePhase_dataReconciliationUnmeasuredVariables,
   NULL,
   NULL,
   NULL,
   NULL,
   -1,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "OilSeparator_ThreePhase"
#define _OMC_LIT_RESOURCE_0_dir_data "C:/ktk/models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,23,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,13,_OMC_LIT_RESOURCE_0_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,2,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir)}};
void OilSeparator_ThreePhase_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &OilSeparator_ThreePhase_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "OilSeparator_ThreePhase";
  data->modelData->modelFilePrefix = "OilSeparator_ThreePhase";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/ktk/models";
  data->modelData->modelGUID = "{83c2f0a9-7fd3-4c3a-be0d-c1ca3bfe6450}";
  #if defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME)
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  #else
  #if defined(_MSC_VER) /* handle joke compilers */
  {
  /* for MSVC we encode a string like char x[] = {'a', 'b', 'c', '\0'} */
  /* because the string constant limit is 65535 bytes */
  static const char contents_init[] =
    #include "OilSeparator_ThreePhase_init.c"
    ;
  static const char contents_info[] =
    #include "OilSeparator_ThreePhase_info.c"
    ;
    data->modelData->initXMLData = contents_init;
    data->modelData->modelDataXml.infoXMLData = contents_info;
  }
  #else /* handle real compilers */
  data->modelData->initXMLData =
  #include "OilSeparator_ThreePhase_init.c"
    ;
  data->modelData->modelDataXml.infoXMLData =
  #include "OilSeparator_ThreePhase_info.c"
    ;
  #endif /* defined(_MSC_VER) */
  #endif /* defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME) */
  data->modelData->modelDataXml.fileName = "OilSeparator_ThreePhase_info.json";
  data->modelData->resourcesDir = NULL;
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 4;
  data->modelData->nVariablesReal = 19;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 1;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 12;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 1;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 1;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 44;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 2;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 8;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  data->modelData->nDelayExpressions = 0;
  data->modelData->nBaseClocks = 0;
  data->modelData->nSpatialDistributions = 0;
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
  data->modelData->nSetcVars = 0;
  data->modelData->ndataReconVars = 0;
  data->modelData->nSetbVars = 0;
  data->modelData->nRelatedBoundaryConditions = 0;
  data->modelData->linearizationDumpLanguage = OMC_LINEARIZE_DUMP_LANGUAGE_MODELICA;
}

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}


#if defined(__MINGW32__) || defined(_MSC_VER)

#if !defined(_UNICODE)
#define _UNICODE
#endif
#if !defined(UNICODE)
#define UNICODE
#endif

#include <windows.h>
char** omc_fixWindowsArgv(int argc, wchar_t **wargv)
{
  char** newargv;
  /* Support for non-ASCII characters
  * Read the unicode command line arguments and translate it to char*
  */
  newargv = (char**)malloc(argc*sizeof(char*));
  for (int i = 0; i < argc; i++) {
    newargv[i] = omc_wchar_to_multibyte_str(wargv[i]);
  }
  return newargv;
}

#define OMC_MAIN wmain
#define OMC_CHAR wchar_t
#define OMC_EXPORT __declspec(dllexport) extern

#else
#define omc_fixWindowsArgv(N, A) (A)
#define OMC_MAIN main
#define OMC_CHAR char
#define OMC_EXPORT extern
#endif

#if defined(threadData)
#undef threadData
#endif
/* call the simulation runtime main from our main! */
#if defined(OMC_DLL_MAIN_DEFINE)
OMC_EXPORT int omcDllMain(int argc, OMC_CHAR **argv)
#else
int OMC_MAIN(int argc, OMC_CHAR** argv)
#endif
{
  char** newargv = omc_fixWindowsArgv(argc, argv);
  /*
    Set the error functions to be used for simulation.
    The default value for them is 'functions' version. Change it here to 'simulation' versions
  */
  omc_assert = omc_assert_simulation;
  omc_assert_withEquationIndexes = omc_assert_simulation_withEquationIndexes;

  omc_assert_warning_withEquationIndexes = omc_assert_warning_simulation_withEquationIndexes;
  omc_assert_warning = omc_assert_warning_simulation;
  omc_terminate = omc_terminate_simulation;
  omc_throw = omc_throw_simulation;

  int res;
  DATA data;
  MODEL_DATA modelData;
  SIMULATION_INFO simInfo;
  data.modelData = &modelData;
  data.simulationInfo = &simInfo;
  measure_time_flag = 0;
  compiledInDAEMode = 0;
  compiledWithSymSolver = 0;
  MMC_INIT(0);
  omc_alloc_interface.init();
  {
    MMC_TRY_TOP()
  
    MMC_TRY_STACK()
  
    OilSeparator_ThreePhase_setupDataStruc(&data, threadData);
    res = _main_initRuntimeAndSimulation(argc, newargv, &data, threadData);
    if(res == 0) {
      res = _main_SimulationRuntime(argc, newargv, &data, threadData);
    }
    
    MMC_ELSE()
    rml_execution_failed();
    fprintf(stderr, "Stack overflow detected and was not caught.\nSend us a bug report at https://trac.openmodelica.org/OpenModelica/newticket\n    Include the following trace:\n");
    printStacktraceMessages();
    fflush(NULL);
    return 1;
    MMC_CATCH_STACK()
    
    MMC_CATCH_TOP(return rml_execution_failed());
  }

  fflush(NULL);
  return res;
}

#ifdef __cplusplus
}
#endif


