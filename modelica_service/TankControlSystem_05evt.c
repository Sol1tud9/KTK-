/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "TankControlSystem_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void TankControlSystem_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *TankControlSystem_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"level <= levelLowAlarm",
  "level <= levelLowWarning and level > levelLowAlarm",
  "level >= levelHighWarning and level < levelHighAlarm",
  "level >= levelHighAlarm",
  "level > 0.01"};
  static const int occurEqs0[] = {1,24};
  static const int occurEqs1[] = {1,23};
  static const int occurEqs2[] = {1,22};
  static const int occurEqs3[] = {1,21};
  static const int occurEqs4[] = {1,-1};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2,occurEqs3,occurEqs4};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void TankControlSystem_eqFunction_19(DATA* data, threadData_t *threadData);

int TankControlSystem_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  TankControlSystem_eqFunction_19(data, threadData);
  
  TRACE_POP
  return 0;
}

int TankControlSystem_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_boolean tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_boolean tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  modelica_boolean tmp18;
  modelica_real tmp19;
  modelica_real tmp20;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  tmp1 = 1.0;
  tmp2 = fabs((data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */));
  tmp0 = LessEqZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */), tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[0] = (tmp0) ? 1 : -1;

  tmp4 = 1.0;
  tmp5 = fabs((data->simulationInfo->realParameter[14] /* levelLowWarning PARAM */));
  tmp3 = LessEqZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[14] /* levelLowWarning PARAM */), tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  tmp7 = 1.0;
  tmp8 = fabs((data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */));
  tmp6 = GreaterZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */), tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[1] = ((tmp3 && tmp6)) ? 1 : -1;

  tmp10 = 1.0;
  tmp11 = fabs((data->simulationInfo->realParameter[12] /* levelHighWarning PARAM */));
  tmp9 = GreaterEqZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[12] /* levelHighWarning PARAM */), tmp10, tmp11, data->simulationInfo->storedRelations[3]);
  tmp13 = 1.0;
  tmp14 = fabs((data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */));
  tmp12 = LessZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */), tmp13, tmp14, data->simulationInfo->storedRelations[4]);
  gout[2] = ((tmp9 && tmp12)) ? 1 : -1;

  tmp16 = 1.0;
  tmp17 = fabs((data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */));
  tmp15 = GreaterEqZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */), tmp16, tmp17, data->simulationInfo->storedRelations[5]);
  gout[3] = (tmp15) ? 1 : -1;

  tmp19 = 1.0;
  tmp20 = 0.01;
  tmp18 = GreaterZC((data->localData[0]->realVars[2] /* level STATE(1) */), 0.01, tmp19, tmp20, data->simulationInfo->storedRelations[6]);
  gout[4] = (tmp18) ? 1 : -1;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *TankControlSystem_relationDescription(int i)
{
  const char *res[] = {"level <= levelLowAlarm",
  "level <= levelLowWarning",
  "level > levelLowAlarm",
  "level >= levelHighWarning",
  "level < levelHighAlarm",
  "level >= levelHighAlarm",
  "level > 0.01"};
  return res[i];
}

int TankControlSystem_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp21;
  modelica_real tmp22;
  modelica_real tmp23;
  modelica_boolean tmp24;
  modelica_real tmp25;
  modelica_real tmp26;
  modelica_boolean tmp27;
  modelica_real tmp28;
  modelica_real tmp29;
  modelica_boolean tmp30;
  modelica_real tmp31;
  modelica_real tmp32;
  modelica_boolean tmp33;
  modelica_real tmp34;
  modelica_real tmp35;
  modelica_boolean tmp36;
  modelica_real tmp37;
  modelica_real tmp38;
  modelica_boolean tmp39;
  modelica_real tmp40;
  modelica_real tmp41;
  
  if(evalforZeroCross) {
    tmp22 = 1.0;
    tmp23 = fabs((data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */));
    tmp21 = LessEqZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */), tmp22, tmp23, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[0] = tmp21;

    tmp25 = 1.0;
    tmp26 = fabs((data->simulationInfo->realParameter[14] /* levelLowWarning PARAM */));
    tmp24 = LessEqZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[14] /* levelLowWarning PARAM */), tmp25, tmp26, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[1] = tmp24;

    tmp28 = 1.0;
    tmp29 = fabs((data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */));
    tmp27 = GreaterZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */), tmp28, tmp29, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[2] = tmp27;

    tmp31 = 1.0;
    tmp32 = fabs((data->simulationInfo->realParameter[12] /* levelHighWarning PARAM */));
    tmp30 = GreaterEqZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[12] /* levelHighWarning PARAM */), tmp31, tmp32, data->simulationInfo->storedRelations[3]);
    data->simulationInfo->relations[3] = tmp30;

    tmp34 = 1.0;
    tmp35 = fabs((data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */));
    tmp33 = LessZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */), tmp34, tmp35, data->simulationInfo->storedRelations[4]);
    data->simulationInfo->relations[4] = tmp33;

    tmp37 = 1.0;
    tmp38 = fabs((data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */));
    tmp36 = GreaterEqZC((data->localData[0]->realVars[2] /* level STATE(1) */), (data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */), tmp37, tmp38, data->simulationInfo->storedRelations[5]);
    data->simulationInfo->relations[5] = tmp36;

    tmp40 = 1.0;
    tmp41 = 0.01;
    tmp39 = GreaterZC((data->localData[0]->realVars[2] /* level STATE(1) */), 0.01, tmp40, tmp41, data->simulationInfo->storedRelations[6]);
    data->simulationInfo->relations[6] = tmp39;
  } else {
    data->simulationInfo->relations[0] = ((data->localData[0]->realVars[2] /* level STATE(1) */) <= (data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */));

    data->simulationInfo->relations[1] = ((data->localData[0]->realVars[2] /* level STATE(1) */) <= (data->simulationInfo->realParameter[14] /* levelLowWarning PARAM */));

    data->simulationInfo->relations[2] = ((data->localData[0]->realVars[2] /* level STATE(1) */) > (data->simulationInfo->realParameter[13] /* levelLowAlarm PARAM */));

    data->simulationInfo->relations[3] = ((data->localData[0]->realVars[2] /* level STATE(1) */) >= (data->simulationInfo->realParameter[12] /* levelHighWarning PARAM */));

    data->simulationInfo->relations[4] = ((data->localData[0]->realVars[2] /* level STATE(1) */) < (data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */));

    data->simulationInfo->relations[5] = ((data->localData[0]->realVars[2] /* level STATE(1) */) >= (data->simulationInfo->realParameter[11] /* levelHighAlarm PARAM */));

    data->simulationInfo->relations[6] = ((data->localData[0]->realVars[2] /* level STATE(1) */) > 0.01);
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

