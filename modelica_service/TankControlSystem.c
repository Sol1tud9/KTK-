/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "TankControlSystem_model.h"
#include "simulation/solver/events.h"

/* FIXME these defines are ugly and hard to read, why not use direct function pointers instead? */
#define prefixedName_performSimulation TankControlSystem_performSimulation
#define prefixedName_updateContinuousSystem TankControlSystem_updateContinuousSystem
#include <simulation/solver/perform_simulation.c.inc>

#define prefixedName_performQSSSimulation TankControlSystem_performQSSSimulation
#include <simulation/solver/perform_qss_simulation.c.inc>


/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int TankControlSystem_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankControlSystem_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankControlSystem_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankControlSystem_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankControlSystem_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int TankControlSystem_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankControlSystem_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankControlSystem_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankControlSystem_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankControlSystem_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 19
type: SIMPLE_ASSIGN
$DER.level = (inletFlowRate - outletFlowRate) / tankVolume
*/
void TankControlSystem_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  (data->localData[0]->realVars[5] /* der(level) STATE_DER */) = DIVISION_SIM((data->simulationInfo->realParameter[9] /* inletFlowRate PARAM */) - (data->simulationInfo->realParameter[16] /* outletFlowRate PARAM */),(data->simulationInfo->realParameter[18] /* tankVolume PARAM */),"tankVolume",equationIndexes);
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
$DER.integralError = error
*/
void TankControlSystem_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  (data->localData[0]->realVars[4] /* der(integralError) STATE_DER */) = (data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */);
  TRACE_POP
}
/*
equation index: 21
type: SIMPLE_ASSIGN
highAlarm = level >= levelHighAlarm
*/
void TankControlSystem_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  tmp1 = 1.0;
  tmp2 = fabs((data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */));
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */), tmp1, tmp2, 5, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[0] /* highAlarm DISCRETE */) = tmp0;
  TRACE_POP
}
/*
equation index: 22
type: SIMPLE_ASSIGN
highWarning = level >= levelHighWarning and level < levelHighAlarm
*/
void TankControlSystem_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  tmp4 = 1.0;
  tmp5 = fabs((data->simulationInfo->realParameter[12] /* levelHighWarning PARAM */));
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[12] /* levelHighWarning PARAM */), tmp4, tmp5, 3, GreaterEq, GreaterEqZC);
  tmp7 = 1.0;
  tmp8 = fabs((data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */));
  relationhysteresis(data, &tmp6, (data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */), tmp7, tmp8, 4, Less, LessZC);
  (data->localData[0]->booleanVars[1] /* highWarning DISCRETE */) = (tmp3 && tmp6);
  TRACE_POP
}
/*
equation index: 23
type: SIMPLE_ASSIGN
lowWarning = level <= levelLowWarning and level > levelLowAlarm
*/
void TankControlSystem_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_boolean tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  tmp10 = 1.0;
  tmp11 = fabs((data->simulationInfo->realParameter[14] /* levelLowWarning PARAM */));
  relationhysteresis(data, &tmp9, (data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[14] /* levelLowWarning PARAM */), tmp10, tmp11, 1, LessEq, LessEqZC);
  tmp13 = 1.0;
  tmp14 = fabs((data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */));
  relationhysteresis(data, &tmp12, (data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */), tmp13, tmp14, 2, Greater, GreaterZC);
  (data->localData[0]->booleanVars[3] /* lowWarning DISCRETE */) = (tmp9 && tmp12);
  TRACE_POP
}
/*
equation index: 24
type: SIMPLE_ASSIGN
lowAlarm = level <= levelLowAlarm
*/
void TankControlSystem_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  modelica_boolean tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  tmp16 = 1.0;
  tmp17 = fabs((data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */));
  relationhysteresis(data, &tmp15, (data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */), tmp16, tmp17, 0, LessEq, LessEqZC);
  (data->localData[0]->booleanVars[2] /* lowAlarm DISCRETE */) = tmp15;
  TRACE_POP
}
/*
equation index: 25
type: SIMPLE_ASSIGN
temperature = setpointTemperature - error
*/
void TankControlSystem_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  (data->localData[0]->realVars[9] /* temperature DUMMY_STATE */) = (data->simulationInfo->realParameter[17] /* setpointTemperature PARAM */) - (data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */);
  TRACE_POP
}
/*
equation index: 30
type: LINEAR

<var>heaterPower</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void TankControlSystem_eqFunction_30(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,30};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[8] /* heaterPower variable */) };
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving linear system 30 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  
  retValue = solve_linear_system(data, threadData, 1, &aux_x[0]);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,30};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 30 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[8] /* heaterPower variable */) = aux_x[0];

  TRACE_POP
}
/*
equation index: 31
type: SIMPLE_ASSIGN
$DER.error = derivativeError
*/
void TankControlSystem_eqFunction_31(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,31};
  (data->localData[0]->realVars[3] /* der(error) STATE_DER */) = (data->localData[0]->realVars[7] /* derivativeError variable */);
  TRACE_POP
}
/*
equation index: 32
type: SIMPLE_ASSIGN
$DER.temperature = -derivativeError
*/
void TankControlSystem_eqFunction_32(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,32};
  (data->localData[0]->realVars[6] /* der(temperature) DUMMY_DER */) = (-(data->localData[0]->realVars[7] /* derivativeError variable */));
  TRACE_POP
}

OMC_DISABLE_OPT
int TankControlSystem_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  TankControlSystem_functionLocalKnownVars(data, threadData);
  TankControlSystem_eqFunction_19(data, threadData);

  TankControlSystem_eqFunction_20(data, threadData);

  TankControlSystem_eqFunction_21(data, threadData);

  TankControlSystem_eqFunction_22(data, threadData);

  TankControlSystem_eqFunction_23(data, threadData);

  TankControlSystem_eqFunction_24(data, threadData);

  TankControlSystem_eqFunction_25(data, threadData);

  TankControlSystem_eqFunction_30(data, threadData);

  TankControlSystem_eqFunction_31(data, threadData);

  TankControlSystem_eqFunction_32(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int TankControlSystem_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/* forwarded equations */
extern void TankControlSystem_eqFunction_19(DATA* data, threadData_t *threadData);
extern void TankControlSystem_eqFunction_20(DATA* data, threadData_t *threadData);
extern void TankControlSystem_eqFunction_25(DATA* data, threadData_t *threadData);
extern void TankControlSystem_eqFunction_30(DATA* data, threadData_t *threadData);
extern void TankControlSystem_eqFunction_31(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  {
    TankControlSystem_eqFunction_19(data, threadData);
    threadData->lastEquationSolved = 19;
  }
  {
    TankControlSystem_eqFunction_20(data, threadData);
    threadData->lastEquationSolved = 20;
  }
  {
    TankControlSystem_eqFunction_25(data, threadData);
    threadData->lastEquationSolved = 25;
  }
  {
    TankControlSystem_eqFunction_30(data, threadData);
    threadData->lastEquationSolved = 30;
  }
  {
    TankControlSystem_eqFunction_31(data, threadData);
    threadData->lastEquationSolved = 31;
  }
}

int TankControlSystem_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  TankControlSystem_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "TankControlSystem_12jac.h"
#include "TankControlSystem_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks TankControlSystem_callback = {
   (int (*)(DATA *, threadData_t *, void *)) TankControlSystem_performSimulation,    /* performSimulation */
   (int (*)(DATA *, threadData_t *, void *)) TankControlSystem_performQSSSimulation,    /* performQSSSimulation */
   TankControlSystem_updateContinuousSystem,    /* updateContinuousSystem */
   TankControlSystem_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   TankControlSystem_initialLinearSystem,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   TankControlSystem_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   TankControlSystem_initializeDAEmodeData,
   TankControlSystem_functionODE,
   TankControlSystem_functionAlgebraics,
   TankControlSystem_functionDAE,
   TankControlSystem_functionLocalKnownVars,
   TankControlSystem_input_function,
   TankControlSystem_input_function_init,
   TankControlSystem_input_function_updateStartValues,
   TankControlSystem_data_function,
   TankControlSystem_output_function,
   TankControlSystem_setc_function,
   TankControlSystem_setb_function,
   TankControlSystem_function_storeDelayed,
   TankControlSystem_function_storeSpatialDistribution,
   TankControlSystem_function_initSpatialDistribution,
   TankControlSystem_updateBoundVariableAttributes,
   TankControlSystem_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   TankControlSystem_functionRemovedInitialEquations,
   TankControlSystem_updateBoundParameters,
   TankControlSystem_checkForAsserts,
   TankControlSystem_function_ZeroCrossingsEquations,
   TankControlSystem_function_ZeroCrossings,
   TankControlSystem_function_updateRelations,
   TankControlSystem_zeroCrossingDescription,
   TankControlSystem_relationDescription,
   TankControlSystem_function_initSample,
   TankControlSystem_INDEX_JAC_A,
   TankControlSystem_INDEX_JAC_B,
   TankControlSystem_INDEX_JAC_C,
   TankControlSystem_INDEX_JAC_D,
   TankControlSystem_INDEX_JAC_F,
   TankControlSystem_INDEX_JAC_H,
   TankControlSystem_initialAnalyticJacobianA,
   TankControlSystem_initialAnalyticJacobianB,
   TankControlSystem_initialAnalyticJacobianC,
   TankControlSystem_initialAnalyticJacobianD,
   TankControlSystem_initialAnalyticJacobianF,
   TankControlSystem_initialAnalyticJacobianH,
   TankControlSystem_functionJacA_column,
   TankControlSystem_functionJacB_column,
   TankControlSystem_functionJacC_column,
   TankControlSystem_functionJacD_column,
   TankControlSystem_functionJacF_column,
   TankControlSystem_functionJacH_column,
   TankControlSystem_linear_model_frame,
   TankControlSystem_linear_model_datarecovery_frame,
   TankControlSystem_mayer,
   TankControlSystem_lagrange,
   TankControlSystem_pickUpBoundsForInputsInOptimization,
   TankControlSystem_setInputData,
   TankControlSystem_getTimeGrid,
   TankControlSystem_symbolicInlineSystem,
   TankControlSystem_function_initSynchronous,
   TankControlSystem_function_updateSynchronous,
   TankControlSystem_function_equationsSynchronous,
   TankControlSystem_inputNames,
   TankControlSystem_dataReconciliationInputNames,
   TankControlSystem_dataReconciliationUnmeasuredVariables,
   NULL,
   NULL,
   NULL,
   NULL,
   -1,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "TankControlSystem"
#define _OMC_LIT_RESOURCE_0_dir_data "C:/ktk/models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,17,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,13,_OMC_LIT_RESOURCE_0_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,2,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir)}};
void TankControlSystem_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &TankControlSystem_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "TankControlSystem";
  data->modelData->modelFilePrefix = "TankControlSystem";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/ktk/models";
  data->modelData->modelGUID = "{6eb94a54-d9d2-41e3-928b-a64684dc9809}";
  #if defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME)
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  #else
  #if defined(_MSC_VER) /* handle joke compilers */
  {
  /* for MSVC we encode a string like char x[] = {'a', 'b', 'c', '\0'} */
  /* because the string constant limit is 65535 bytes */
  static const char contents_init[] =
    #include "TankControlSystem_init.c"
    ;
  static const char contents_info[] =
    #include "TankControlSystem_info.c"
    ;
    data->modelData->initXMLData = contents_init;
    data->modelData->modelDataXml.infoXMLData = contents_info;
  }
  #else /* handle real compilers */
  data->modelData->initXMLData =
  #include "TankControlSystem_init.c"
    ;
  data->modelData->modelDataXml.infoXMLData =
  #include "TankControlSystem_info.c"
    ;
  #endif /* defined(_MSC_VER) */
  #endif /* defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME) */
  data->modelData->modelDataXml.fileName = "TankControlSystem_info.json";
  data->modelData->resourcesDir = NULL;
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 3;
  data->modelData->nVariablesReal = 10;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 4;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 19;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 5;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 7;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 33;
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
  
    TankControlSystem_setupDataStruc(&data, threadData);
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


