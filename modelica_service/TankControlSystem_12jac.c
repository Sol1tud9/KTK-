/* Jacobians 8 */
#include "TankControlSystem_model.h"
#include "TankControlSystem_12jac.h"
#include "simulation/jacobian_util.h"
#include "util/omc_file.h"
/* constant equations */
/* dynamic equations */

/*
equation index: 13
type: SIMPLE_ASSIGN
$DER.temperature.$pDERLSJac0.dummyVarLSJac0 = if level > 0.01 then heaterPower.SeedLSJac0 * heatCapacity * density * tankVolume * level / (heatCapacity * density * tankVolume * level) ^ 2.0 else 0.0
*/
void TankControlSystem_eqFunction_13(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 0;
  const int equationIndexes[2] = {1,13};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_boolean tmp2;
  modelica_real tmp3;
  tmp0 = Greater((data->localData[0]->realVars[2] /* level STATE(1) */),0.01);
  tmp2 = (modelica_boolean)tmp0;
  if(tmp2)
  {
    tmp1 = ((((data->simulationInfo->realParameter[5] /* heatCapacity PARAM */)) * ((data->simulationInfo->realParameter[4] /* density PARAM */))) * ((data->simulationInfo->realParameter[18] /* tankVolume PARAM */))) * ((data->localData[0]->realVars[2] /* level STATE(1) */));
    tmp3 = DIVISION((jacobian->seedVars[0] /* heaterPower.SeedLSJac0 SEED_VAR */) * (((((data->simulationInfo->realParameter[5] /* heatCapacity PARAM */)) * ((data->simulationInfo->realParameter[4] /* density PARAM */))) * ((data->simulationInfo->realParameter[18] /* tankVolume PARAM */))) * ((data->localData[0]->realVars[2] /* level STATE(1) */))),(tmp1 * tmp1),"(heatCapacity * density * tankVolume * level) ^ 2.0");
  }
  else
  {
    tmp3 = 0.0;
  }
  jacobian->tmpVars[0] /* der(temperature.$pDERLSJac0.dummyVarLSJac0) JACOBIAN_TMP_VAR */ = tmp3;
  TRACE_POP
}

/*
equation index: 14
type: SIMPLE_ASSIGN
derivativeError.$pDERLSJac0.dummyVarLSJac0 = heaterPower.SeedLSJac0 / Kd
*/
void TankControlSystem_eqFunction_14(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 1;
  const int equationIndexes[2] = {1,14};
  jacobian->tmpVars[1] /* derivativeError.$pDERLSJac0.dummyVarLSJac0 JACOBIAN_TMP_VAR */ = DIVISION(jacobian->seedVars[0] /* heaterPower.SeedLSJac0 SEED_VAR */,(data->simulationInfo->realParameter[0] /* Kd PARAM */),"Kd");
  TRACE_POP
}

/*
equation index: 15
type: SIMPLE_ASSIGN
$res_LSJac0_1.$pDERLSJac0.dummyVarLSJac0 = (-$DER.temperature.$pDERLSJac0.dummyVarLSJac0) - derivativeError.$pDERLSJac0.dummyVarLSJac0
*/
void TankControlSystem_eqFunction_15(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 2;
  const int equationIndexes[2] = {1,15};
  jacobian->resultVars[0] /* $res_LSJac0_1.$pDERLSJac0.dummyVarLSJac0 JACOBIAN_VAR */ = (-jacobian->tmpVars[0] /* der(temperature.$pDERLSJac0.dummyVarLSJac0) JACOBIAN_TMP_VAR */) - jacobian->tmpVars[1] /* derivativeError.$pDERLSJac0.dummyVarLSJac0 JACOBIAN_TMP_VAR */;
  TRACE_POP
}

OMC_DISABLE_OPT
int TankControlSystem_functionJacLSJac0_constantEqns(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankControlSystem_INDEX_JAC_LSJac0;
  
  TRACE_POP
  return 0;
}

int TankControlSystem_functionJacLSJac0_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankControlSystem_INDEX_JAC_LSJac0;
  TankControlSystem_eqFunction_13(data, threadData, jacobian, parentJacobian);
  TankControlSystem_eqFunction_14(data, threadData, jacobian, parentJacobian);
  TankControlSystem_eqFunction_15(data, threadData, jacobian, parentJacobian);
  TRACE_POP
  return 0;
}
/* constant equations */
/* dynamic equations */

/*
equation index: 28
type: SIMPLE_ASSIGN
derivativeError.$pDERLSJac1.dummyVarLSJac1 = if level > 0.01 then (-heaterPower.SeedLSJac1) * heatCapacity * density * tankVolume * level / (heatCapacity * density * tankVolume * level) ^ 2.0 else 0.0
*/
void TankControlSystem_eqFunction_28(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 0;
  const int equationIndexes[2] = {1,28};
  modelica_boolean tmp4;
  modelica_real tmp5;
  modelica_real tmp6;
  modelica_real tmp7;
  modelica_boolean tmp8;
  modelica_real tmp9;
  tmp5 = 1.0;
  tmp6 = 0.01;
  relationhysteresis(data, &tmp4, (data->localData[0]->realVars[2] /* level STATE(1) */), 0.01, tmp5, tmp6, 6, Greater, GreaterZC);
  tmp8 = (modelica_boolean)tmp4;
  if(tmp8)
  {
    tmp7 = ((((data->simulationInfo->realParameter[5] /* heatCapacity PARAM */)) * ((data->simulationInfo->realParameter[4] /* density PARAM */))) * ((data->simulationInfo->realParameter[18] /* tankVolume PARAM */))) * ((data->localData[0]->realVars[2] /* level STATE(1) */));
    tmp9 = DIVISION(((-jacobian->seedVars[0] /* heaterPower.SeedLSJac1 SEED_VAR */)) * (((((data->simulationInfo->realParameter[5] /* heatCapacity PARAM */)) * ((data->simulationInfo->realParameter[4] /* density PARAM */))) * ((data->simulationInfo->realParameter[18] /* tankVolume PARAM */))) * ((data->localData[0]->realVars[2] /* level STATE(1) */))),(tmp7 * tmp7),"(heatCapacity * density * tankVolume * level) ^ 2.0");
  }
  else
  {
    tmp9 = 0.0;
  }
  jacobian->tmpVars[0] /* derivativeError.$pDERLSJac1.dummyVarLSJac1 JACOBIAN_TMP_VAR */ = tmp9;
  TRACE_POP
}

/*
equation index: 29
type: SIMPLE_ASSIGN
$res_LSJac1_1.$pDERLSJac1.dummyVarLSJac1 = Kd * derivativeError.$pDERLSJac1.dummyVarLSJac1 - heaterPower.SeedLSJac1
*/
void TankControlSystem_eqFunction_29(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 1;
  const int equationIndexes[2] = {1,29};
  jacobian->resultVars[0] /* $res_LSJac1_1.$pDERLSJac1.dummyVarLSJac1 JACOBIAN_VAR */ = ((data->simulationInfo->realParameter[0] /* Kd PARAM */)) * (jacobian->tmpVars[0] /* derivativeError.$pDERLSJac1.dummyVarLSJac1 JACOBIAN_TMP_VAR */) - jacobian->seedVars[0] /* heaterPower.SeedLSJac1 SEED_VAR */;
  TRACE_POP
}

OMC_DISABLE_OPT
int TankControlSystem_functionJacLSJac1_constantEqns(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankControlSystem_INDEX_JAC_LSJac1;
  
  TRACE_POP
  return 0;
}

int TankControlSystem_functionJacLSJac1_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankControlSystem_INDEX_JAC_LSJac1;
  TankControlSystem_eqFunction_28(data, threadData, jacobian, parentJacobian);
  TankControlSystem_eqFunction_29(data, threadData, jacobian, parentJacobian);
  TRACE_POP
  return 0;
}
int TankControlSystem_functionJacH_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int TankControlSystem_functionJacF_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int TankControlSystem_functionJacD_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int TankControlSystem_functionJacC_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int TankControlSystem_functionJacB_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
/* constant equations */
/* dynamic equations */

OMC_DISABLE_OPT
int TankControlSystem_functionJacA_constantEqns(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankControlSystem_INDEX_JAC_A;
  
  TRACE_POP
  return 0;
}

int TankControlSystem_functionJacA_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankControlSystem_INDEX_JAC_A;
  TRACE_POP
  return 0;
}

OMC_DISABLE_OPT
int TankControlSystem_initialAnalyticJacobianLSJac0(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  size_t count;

  FILE* pFile = openSparsePatternFile(data, threadData, "TankControlSystem_JacLSJac0.bin");
  
  initAnalyticJacobian(jacobian, 1, 1, 3, NULL, jacobian->sparsePattern);
  jacobian->sparsePattern = allocSparsePattern(1, 1, 1);
  jacobian->availability = JACOBIAN_AVAILABLE;
  
  /* read lead index of compressed sparse column */
  count = omc_fread(jacobian->sparsePattern->leadindex, sizeof(unsigned int), 1+1, pFile, FALSE);
  if (count != 1+1) {
    throwStreamPrint(threadData, "Error while reading lead index list of sparsity pattern. Expected %d, got %zu", 1+1, count);
  }
  
  /* read sparse index */
  count = omc_fread(jacobian->sparsePattern->index, sizeof(unsigned int), 1, pFile, FALSE);
  if (count != 1) {
    throwStreamPrint(threadData, "Error while reading row index list of sparsity pattern. Expected %d, got %zu", 1, count);
  }
  
  /* write color array */
  /* color 1 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 1, 1, 1);
  
  omc_fclose(pFile);
  
  TRACE_POP
  return 0;
}
OMC_DISABLE_OPT
int TankControlSystem_initialAnalyticJacobianLSJac1(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  size_t count;

  FILE* pFile = openSparsePatternFile(data, threadData, "TankControlSystem_JacLSJac1.bin");
  
  initAnalyticJacobian(jacobian, 1, 1, 2, NULL, jacobian->sparsePattern);
  jacobian->sparsePattern = allocSparsePattern(1, 1, 1);
  jacobian->availability = JACOBIAN_AVAILABLE;
  
  /* read lead index of compressed sparse column */
  count = omc_fread(jacobian->sparsePattern->leadindex, sizeof(unsigned int), 1+1, pFile, FALSE);
  if (count != 1+1) {
    throwStreamPrint(threadData, "Error while reading lead index list of sparsity pattern. Expected %d, got %zu", 1+1, count);
  }
  
  /* read sparse index */
  count = omc_fread(jacobian->sparsePattern->index, sizeof(unsigned int), 1, pFile, FALSE);
  if (count != 1) {
    throwStreamPrint(threadData, "Error while reading row index list of sparsity pattern. Expected %d, got %zu", 1, count);
  }
  
  /* write color array */
  /* color 1 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 1, 1, 1);
  
  omc_fclose(pFile);
  
  TRACE_POP
  return 0;
}
int TankControlSystem_initialAnalyticJacobianH(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TankControlSystem_initialAnalyticJacobianF(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TankControlSystem_initialAnalyticJacobianD(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TankControlSystem_initialAnalyticJacobianC(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TankControlSystem_initialAnalyticJacobianB(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
OMC_DISABLE_OPT
int TankControlSystem_initialAnalyticJacobianA(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  size_t count;

  FILE* pFile = openSparsePatternFile(data, threadData, "TankControlSystem_JacA.bin");
  
  initAnalyticJacobian(jacobian, 3, 3, 0, NULL, jacobian->sparsePattern);
  jacobian->sparsePattern = allocSparsePattern(3, 4, 3);
  jacobian->availability = JACOBIAN_ONLY_SPARSITY;
  
  /* read lead index of compressed sparse column */
  count = omc_fread(jacobian->sparsePattern->leadindex, sizeof(unsigned int), 3+1, pFile, FALSE);
  if (count != 3+1) {
    throwStreamPrint(threadData, "Error while reading lead index list of sparsity pattern. Expected %d, got %zu", 3+1, count);
  }
  
  /* read sparse index */
  count = omc_fread(jacobian->sparsePattern->index, sizeof(unsigned int), 4, pFile, FALSE);
  if (count != 4) {
    throwStreamPrint(threadData, "Error while reading row index list of sparsity pattern. Expected %d, got %zu", 4, count);
  }
  
  /* write color array */
  /* color 1 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 1, 1, 3);
  /* color 2 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 2, 1, 3);
  /* color 3 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 3, 1, 3);
  
  omc_fclose(pFile);
  
  TRACE_POP
  return 0;
}



