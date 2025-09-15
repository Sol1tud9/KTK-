/* Algebraic */
#include "OilSeparator_ThreePhase_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void OilSeparator_ThreePhase_eqFunction_24(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_25(DATA* data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_26(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  {
    OilSeparator_ThreePhase_eqFunction_24(data, threadData);
    threadData->lastEquationSolved = 24;
  }
  {
    OilSeparator_ThreePhase_eqFunction_25(data, threadData);
    threadData->lastEquationSolved = 25;
  }
  {
    OilSeparator_ThreePhase_eqFunction_26(data, threadData);
    threadData->lastEquationSolved = 26;
  }
}
/* for continuous time variables */
int OilSeparator_ThreePhase_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  OilSeparator_ThreePhase_function_savePreSynchronous(data, threadData);
  
  functionAlg_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ALGEBRAICS);
#endif

  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
