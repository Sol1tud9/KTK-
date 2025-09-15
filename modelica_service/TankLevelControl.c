/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "TankLevelControl_model.h"
#include "simulation/solver/events.h"

/* FIXME these defines are ugly and hard to read, why not use direct function pointers instead? */
#define prefixedName_performSimulation TankLevelControl_performSimulation
#define prefixedName_updateContinuousSystem TankLevelControl_updateContinuousSystem
#include <simulation/solver/perform_simulation.c.inc>

#define prefixedName_performQSSSimulation TankLevelControl_performQSSSimulation
#include <simulation/solver/perform_qss_simulation.c.inc>


/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int TankLevelControl_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankLevelControl_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankLevelControl_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankLevelControl_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankLevelControl_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int TankLevelControl_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankLevelControl_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankLevelControl_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankLevelControl_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int TankLevelControl_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 13
type: SIMPLE_ASSIGN
temperature = setpointTemperature - error
*/
void TankLevelControl_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  (data->localData[0]->realVars[7] /* temperature DUMMY_STATE */) = (data->simulationInfo->realParameter[7] /* setpointTemperature PARAM */) - (data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */);
  TRACE_POP
}
/*
equation index: 18
type: LINEAR

<var>heaterPower</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void TankLevelControl_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { (data->localData[1]->realVars[6] /* heaterPower variable */) };
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving linear system 18 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  
  retValue = solve_linear_system(data, threadData, 1, &aux_x[0]);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,18};
    throwStreamPrintWithEquationIndexes(threadData, omc_dummyFileInfo, indexes, "Solving linear system 18 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  (data->localData[0]->realVars[6] /* heaterPower variable */) = aux_x[0];

  TRACE_POP
}
/*
equation index: 19
type: SIMPLE_ASSIGN
$DER.error = derivativeError
*/
void TankLevelControl_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  (data->localData[0]->realVars[2] /* der(error) STATE_DER */) = (data->localData[0]->realVars[5] /* derivativeError variable */);
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
$DER.temperature = -derivativeError
*/
void TankLevelControl_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  (data->localData[0]->realVars[4] /* der(temperature) DUMMY_DER */) = (-(data->localData[0]->realVars[5] /* derivativeError variable */));
  TRACE_POP
}
/*
equation index: 21
type: SIMPLE_ASSIGN
$DER.integralError = error
*/
void TankLevelControl_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  (data->localData[0]->realVars[3] /* der(integralError) STATE_DER */) = (data->localData[0]->realVars[0] /* error STATE(1,derivativeError) */);
  TRACE_POP
}

OMC_DISABLE_OPT
int TankLevelControl_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  TankLevelControl_functionLocalKnownVars(data, threadData);
  TankLevelControl_eqFunction_13(data, threadData);

  TankLevelControl_eqFunction_18(data, threadData);

  TankLevelControl_eqFunction_19(data, threadData);

  TankLevelControl_eqFunction_20(data, threadData);

  TankLevelControl_eqFunction_21(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int TankLevelControl_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/* forwarded equations */
extern void TankLevelControl_eqFunction_13(DATA* data, threadData_t *threadData);
extern void TankLevelControl_eqFunction_18(DATA* data, threadData_t *threadData);
extern void TankLevelControl_eqFunction_19(DATA* data, threadData_t *threadData);
extern void TankLevelControl_eqFunction_21(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  {
    TankLevelControl_eqFunction_13(data, threadData);
    threadData->lastEquationSolved = 13;
  }
  {
    TankLevelControl_eqFunction_18(data, threadData);
    threadData->lastEquationSolved = 18;
  }
  {
    TankLevelControl_eqFunction_19(data, threadData);
    threadData->lastEquationSolved = 19;
  }
  {
    TankLevelControl_eqFunction_21(data, threadData);
    threadData->lastEquationSolved = 21;
  }
}

int TankLevelControl_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  TankLevelControl_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "TankLevelControl_12jac.h"
#include "TankLevelControl_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks TankLevelControl_callback = {
   (int (*)(DATA *, threadData_t *, void *)) TankLevelControl_performSimulation,    /* performSimulation */
   (int (*)(DATA *, threadData_t *, void *)) TankLevelControl_performQSSSimulation,    /* performQSSSimulation */
   TankLevelControl_updateContinuousSystem,    /* updateContinuousSystem */
   TankLevelControl_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   TankLevelControl_initialLinearSystem,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   TankLevelControl_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   TankLevelControl_initializeDAEmodeData,
   TankLevelControl_functionODE,
   TankLevelControl_functionAlgebraics,
   TankLevelControl_functionDAE,
   TankLevelControl_functionLocalKnownVars,
   TankLevelControl_input_function,
   TankLevelControl_input_function_init,
   TankLevelControl_input_function_updateStartValues,
   TankLevelControl_data_function,
   TankLevelControl_output_function,
   TankLevelControl_setc_function,
   TankLevelControl_setb_function,
   TankLevelControl_function_storeDelayed,
   TankLevelControl_function_storeSpatialDistribution,
   TankLevelControl_function_initSpatialDistribution,
   TankLevelControl_updateBoundVariableAttributes,
   TankLevelControl_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   TankLevelControl_functionRemovedInitialEquations,
   TankLevelControl_updateBoundParameters,
   TankLevelControl_checkForAsserts,
   TankLevelControl_function_ZeroCrossingsEquations,
   TankLevelControl_function_ZeroCrossings,
   TankLevelControl_function_updateRelations,
   TankLevelControl_zeroCrossingDescription,
   TankLevelControl_relationDescription,
   TankLevelControl_function_initSample,
   TankLevelControl_INDEX_JAC_A,
   TankLevelControl_INDEX_JAC_B,
   TankLevelControl_INDEX_JAC_C,
   TankLevelControl_INDEX_JAC_D,
   TankLevelControl_INDEX_JAC_F,
   TankLevelControl_INDEX_JAC_H,
   TankLevelControl_initialAnalyticJacobianA,
   TankLevelControl_initialAnalyticJacobianB,
   TankLevelControl_initialAnalyticJacobianC,
   TankLevelControl_initialAnalyticJacobianD,
   TankLevelControl_initialAnalyticJacobianF,
   TankLevelControl_initialAnalyticJacobianH,
   TankLevelControl_functionJacA_column,
   TankLevelControl_functionJacB_column,
   TankLevelControl_functionJacC_column,
   TankLevelControl_functionJacD_column,
   TankLevelControl_functionJacF_column,
   TankLevelControl_functionJacH_column,
   TankLevelControl_linear_model_frame,
   TankLevelControl_linear_model_datarecovery_frame,
   TankLevelControl_mayer,
   TankLevelControl_lagrange,
   TankLevelControl_pickUpBoundsForInputsInOptimization,
   TankLevelControl_setInputData,
   TankLevelControl_getTimeGrid,
   TankLevelControl_symbolicInlineSystem,
   TankLevelControl_function_initSynchronous,
   TankLevelControl_function_updateSynchronous,
   TankLevelControl_function_equationsSynchronous,
   TankLevelControl_inputNames,
   TankLevelControl_dataReconciliationInputNames,
   TankLevelControl_dataReconciliationUnmeasuredVariables,
   NULL,
   NULL,
   NULL,
   NULL,
   -1,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "TankLevelControl"
#define _OMC_LIT_RESOURCE_0_dir_data "C:/ktk/models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,16,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,13,_OMC_LIT_RESOURCE_0_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,2,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir)}};
void TankLevelControl_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &TankLevelControl_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "TankLevelControl";
  data->modelData->modelFilePrefix = "TankLevelControl";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "C:/ktk/models";
  data->modelData->modelGUID = "{1122df71-cfbc-4a1a-8181-91a5c6e65ca8}";
  #if defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME)
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  #else
  #if defined(_MSC_VER) /* handle joke compilers */
  {
  /* for MSVC we encode a string like char x[] = {'a', 'b', 'c', '\0'} */
  /* because the string constant limit is 65535 bytes */
  static const char contents_init[] =
    #include "TankLevelControl_init.c"
    ;
  static const char contents_info[] =
    #include "TankLevelControl_info.c"
    ;
    data->modelData->initXMLData = contents_init;
    data->modelData->modelDataXml.infoXMLData = contents_info;
  }
  #else /* handle real compilers */
  data->modelData->initXMLData =
  #include "TankLevelControl_init.c"
    ;
  data->modelData->modelDataXml.infoXMLData =
  #include "TankLevelControl_info.c"
    ;
  #endif /* defined(_MSC_VER) */
  #endif /* defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME) */
  data->modelData->modelDataXml.fileName = "TankLevelControl_info.json";
  data->modelData->resourcesDir = NULL;
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 2;
  data->modelData->nVariablesReal = 8;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 0;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 9;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 0;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 0;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 22;
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
  
    TankLevelControl_setupDataStruc(&data, threadData);
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


