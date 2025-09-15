/* Algebraic */
#include "TankControlSystem_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void TankControlSystem_eqFunction_21(DATA* data, threadData_t *threadData);
extern void TankControlSystem_eqFunction_22(DATA* data, threadData_t *threadData);
extern void TankControlSystem_eqFunction_23(DATA* data, threadData_t *threadData);
extern void TankControlSystem_eqFunction_24(DATA* data, threadData_t *threadData);
extern void TankControlSystem_eqFunction_32(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  {
    TankControlSystem_eqFunction_21(data, threadData);
    threadData->lastEquationSolved = 21;
  }
  {
    TankControlSystem_eqFunction_22(data, threadData);
    threadData->lastEquationSolved = 22;
  }
  {
    TankControlSystem_eqFunction_23(data, threadData);
    threadData->lastEquationSolved = 23;
  }
  {
    TankControlSystem_eqFunction_24(data, threadData);
    threadData->lastEquationSolved = 24;
  }
  {
    TankControlSystem_eqFunction_32(data, threadData);
    threadData->lastEquationSolved = 32;
  }
}
/* for continuous time variables */
int TankControlSystem_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  TankControlSystem_function_savePreSynchronous(data, threadData);
  
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
