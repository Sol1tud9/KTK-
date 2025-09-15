/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "OilSeparator_ThreePhase_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void OilSeparator_ThreePhase_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *OilSeparator_ThreePhase_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"totalLiquidLevel > 0.98"};
  static const int occurEqs0[] = {1,26};
  static const int *occurEqs[] = {occurEqs0};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void OilSeparator_ThreePhase_eqFunction_25(DATA* data, threadData_t *threadData);
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

int OilSeparator_ThreePhase_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  OilSeparator_ThreePhase_eqFunction_25(data, threadData);

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
  
  TRACE_POP
  return 0;
}

int OilSeparator_ThreePhase_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  tmp1 = 1.0;
  tmp2 = 0.98;
  tmp0 = GreaterZC((data->localData[0]->realVars[17] /* totalLiquidLevel variable */), 0.98, tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[0] = (tmp0) ? 1 : -1;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *OilSeparator_ThreePhase_relationDescription(int i)
{
  const char *res[] = {"totalLiquidLevel > 0.98"};
  return res[i];
}

int OilSeparator_ThreePhase_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  
  if(evalforZeroCross) {
    tmp4 = 1.0;
    tmp5 = 0.98;
    tmp3 = GreaterZC((data->localData[0]->realVars[17] /* totalLiquidLevel variable */), 0.98, tmp4, tmp5, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[0] = tmp3;
  } else {
    data->simulationInfo->relations[0] = ((data->localData[0]->realVars[17] /* totalLiquidLevel variable */) > 0.98);
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

