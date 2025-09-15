/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "OilSeparator_ThreePhase_model.h"
#if defined(__cplusplus)
extern "C" {
#endif


/*
equation index: 37
type: SIMPLE_ASSIGN
$START.h_water = waterLevelSetpoint
*/
static void OilSeparator_ThreePhase_eqFunction_37(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,37};
  (data->modelData->realVarsData[1] /* h_water STATE(1) */).attribute .start = (data->simulationInfo->realParameter[11] /* waterLevelSetpoint PARAM */);
    (data->localData[0]->realVars[1] /* h_water STATE(1) */) = (data->modelData->realVarsData[1] /* h_water STATE(1) */).attribute .start;
    infoStreamPrint(LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[1].info /* h_water */.name, (modelica_real) (data->localData[0]->realVars[1] /* h_water STATE(1) */));
  TRACE_POP
}

/*
equation index: 38
type: SIMPLE_ASSIGN
$START.h_oil = oilLevelSetpoint
*/
static void OilSeparator_ThreePhase_eqFunction_38(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,38};
  (data->modelData->realVarsData[0] /* h_oil STATE(1) */).attribute .start = (data->simulationInfo->realParameter[7] /* oilLevelSetpoint PARAM */);
    (data->localData[0]->realVars[0] /* h_oil STATE(1) */) = (data->modelData->realVarsData[0] /* h_oil STATE(1) */).attribute .start;
    infoStreamPrint(LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[0].info /* h_oil */.name, (modelica_real) (data->localData[0]->realVars[0] /* h_oil STATE(1) */));
  TRACE_POP
}
OMC_DISABLE_OPT
int OilSeparator_ThreePhase_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating min-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* max ******************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating max-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* nominal **************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating nominal-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* start ****************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating primary start-values");
  OilSeparator_ThreePhase_eqFunction_37(data, threadData);

  OilSeparator_ThreePhase_eqFunction_38(data, threadData);
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  TRACE_POP
  return 0;
}

void OilSeparator_ThreePhase_updateBoundParameters_0(DATA *data, threadData_t *threadData);
extern void OilSeparator_ThreePhase_eqFunction_21(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_4(DATA *data, threadData_t *threadData);

extern void OilSeparator_ThreePhase_eqFunction_3(DATA *data, threadData_t *threadData);


/*
equation index: 42
type: ALGORITHM

  assert(waterFraction >= 0.0 and waterFraction <= 1.0, "Variable violating min/max constraint: 0.0 <= waterFraction <= 1.0, has value: " + String(waterFraction, "g"));
*/
OMC_DISABLE_OPT
static void OilSeparator_ThreePhase_eqFunction_42(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,42};
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  static const MMC_DEFSTRINGLIT(tmp2,79,"Variable violating min/max constraint: 0.0 <= waterFraction <= 1.0, has value: ");
  modelica_string tmp3;
  modelica_metatype tmpMeta4;
  static int tmp5 = 0;
  if(!tmp5)
  {
    tmp0 = GreaterEq((data->simulationInfo->realParameter[10] /* waterFraction PARAM */),0.0);
    tmp1 = LessEq((data->simulationInfo->realParameter[10] /* waterFraction PARAM */),1.0);
    if(!(tmp0 && tmp1))
    {
      tmp3 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[10] /* waterFraction PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta4 = stringAppend(MMC_REFSTRINGLIT(tmp2),tmp3);
      {
        const char* assert_cond = "(waterFraction >= 0.0 and waterFraction <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"C:/ktk/models/OilSeparator_ThreePhase.mo",5,3,5,104,0};
          infoStreamPrintWithEquationIndexes(LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta4));
        } else {
          FILE_INFO info = {"C:/ktk/models/OilSeparator_ThreePhase.mo",5,3,5,104,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta4));
        }
      }
      tmp5 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 43
type: ALGORITHM

  assert(oilFraction >= 0.0 and oilFraction <= 1.0, "Variable violating min/max constraint: 0.0 <= oilFraction <= 1.0, has value: " + String(oilFraction, "g"));
*/
OMC_DISABLE_OPT
static void OilSeparator_ThreePhase_eqFunction_43(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,43};
  modelica_boolean tmp6;
  modelica_boolean tmp7;
  static const MMC_DEFSTRINGLIT(tmp8,77,"Variable violating min/max constraint: 0.0 <= oilFraction <= 1.0, has value: ");
  modelica_string tmp9;
  modelica_metatype tmpMeta10;
  static int tmp11 = 0;
  if(!tmp11)
  {
    tmp6 = GreaterEq((data->simulationInfo->realParameter[6] /* oilFraction PARAM */),0.0);
    tmp7 = LessEq((data->simulationInfo->realParameter[6] /* oilFraction PARAM */),1.0);
    if(!(tmp6 && tmp7))
    {
      tmp9 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[6] /* oilFraction PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta10 = stringAppend(MMC_REFSTRINGLIT(tmp8),tmp9);
      {
        const char* assert_cond = "(oilFraction >= 0.0 and oilFraction <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"C:/ktk/models/OilSeparator_ThreePhase.mo",4,3,4,104,0};
          infoStreamPrintWithEquationIndexes(LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta10));
        } else {
          FILE_INFO info = {"C:/ktk/models/OilSeparator_ThreePhase.mo",4,3,4,104,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta10));
        }
      }
      tmp11 = 1;
    }
  }
  TRACE_POP
}
OMC_DISABLE_OPT
void OilSeparator_ThreePhase_updateBoundParameters_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  OilSeparator_ThreePhase_eqFunction_21(data, threadData);
  OilSeparator_ThreePhase_eqFunction_4(data, threadData);
  OilSeparator_ThreePhase_eqFunction_3(data, threadData);
  OilSeparator_ThreePhase_eqFunction_42(data, threadData);
  OilSeparator_ThreePhase_eqFunction_43(data, threadData);
  TRACE_POP
}
OMC_DISABLE_OPT
int OilSeparator_ThreePhase_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  OilSeparator_ThreePhase_updateBoundParameters_0(data, threadData);
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

