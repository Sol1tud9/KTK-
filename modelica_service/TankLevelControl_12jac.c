/* Jacobians 8 */
#include "TankLevelControl_model.h"
#include "TankLevelControl_12jac.h"
#include "simulation/jacobian_util.h"
#include "util/omc_file.h"
/* constant equations */
/* dynamic equations */

/*
equation index: 8
type: SIMPLE_ASSIGN
$DER.temperature.$pDERLSJac0.dummyVarLSJac0 = heaterPower.SeedLSJac0 * tankVolume * density * heatCapacity / (tankVolume * density * heatCapacity) ^ 2.0
*/
void TankLevelControl_eqFunction_8(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 0;
  const int equationIndexes[2] = {1,8};
  modelica_real tmp0;
  tmp0 = ((data->simulationInfo->realParameter[8] /* tankVolume PARAM */)) * (((data->simulationInfo->realParameter[3] /* density PARAM */)) * ((data->simulationInfo->realParameter[4] /* heatCapacity PARAM */)));
  jacobian->tmpVars[0] /* der(temperature.$pDERLSJac0.dummyVarLSJac0) JACOBIAN_TMP_VAR */ = (jacobian->seedVars[0] /* heaterPower.SeedLSJac0 SEED_VAR */) * (((data->simulationInfo->realParameter[8] /* tankVolume PARAM */)) * (((data->simulationInfo->realParameter[3] /* density PARAM */)) * (DIVISION((data->simulationInfo->realParameter[4] /* heatCapacity PARAM */),(tmp0 * tmp0),"(tankVolume * density * heatCapacity) ^ 2.0"))));
  TRACE_POP
}

/*
equation index: 9
type: SIMPLE_ASSIGN
derivativeError.$pDERLSJac0.dummyVarLSJac0 = heaterPower.SeedLSJac0 / Kd
*/
void TankLevelControl_eqFunction_9(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 1;
  const int equationIndexes[2] = {1,9};
  jacobian->tmpVars[1] /* derivativeError.$pDERLSJac0.dummyVarLSJac0 JACOBIAN_TMP_VAR */ = DIVISION(jacobian->seedVars[0] /* heaterPower.SeedLSJac0 SEED_VAR */,(data->simulationInfo->realParameter[0] /* Kd PARAM */),"Kd");
  TRACE_POP
}

/*
equation index: 10
type: SIMPLE_ASSIGN
$res_LSJac0_1.$pDERLSJac0.dummyVarLSJac0 = (-$DER.temperature.$pDERLSJac0.dummyVarLSJac0) - derivativeError.$pDERLSJac0.dummyVarLSJac0
*/
void TankLevelControl_eqFunction_10(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 2;
  const int equationIndexes[2] = {1,10};
  jacobian->resultVars[0] /* $res_LSJac0_1.$pDERLSJac0.dummyVarLSJac0 JACOBIAN_VAR */ = (-jacobian->tmpVars[0] /* der(temperature.$pDERLSJac0.dummyVarLSJac0) JACOBIAN_TMP_VAR */) - jacobian->tmpVars[1] /* derivativeError.$pDERLSJac0.dummyVarLSJac0 JACOBIAN_TMP_VAR */;
  TRACE_POP
}

OMC_DISABLE_OPT
int TankLevelControl_functionJacLSJac0_constantEqns(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankLevelControl_INDEX_JAC_LSJac0;
  
  TRACE_POP
  return 0;
}

int TankLevelControl_functionJacLSJac0_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankLevelControl_INDEX_JAC_LSJac0;
  TankLevelControl_eqFunction_8(data, threadData, jacobian, parentJacobian);
  TankLevelControl_eqFunction_9(data, threadData, jacobian, parentJacobian);
  TankLevelControl_eqFunction_10(data, threadData, jacobian, parentJacobian);
  TRACE_POP
  return 0;
}
/* constant equations */
/* dynamic equations */

/*
equation index: 16
type: SIMPLE_ASSIGN
derivativeError.$pDERLSJac1.dummyVarLSJac1 = heaterPower.SeedLSJac1 / Kd
*/
void TankLevelControl_eqFunction_16(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 0;
  const int equationIndexes[2] = {1,16};
  jacobian->tmpVars[0] /* derivativeError.$pDERLSJac1.dummyVarLSJac1 JACOBIAN_TMP_VAR */ = DIVISION(jacobian->seedVars[0] /* heaterPower.SeedLSJac1 SEED_VAR */,(data->simulationInfo->realParameter[0] /* Kd PARAM */),"Kd");
  TRACE_POP
}

/*
equation index: 17
type: SIMPLE_ASSIGN
$res_LSJac1_1.$pDERLSJac1.dummyVarLSJac1 = heaterPower.SeedLSJac1 + heatCapacity * density * tankVolume * derivativeError.$pDERLSJac1.dummyVarLSJac1
*/
void TankLevelControl_eqFunction_17(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int baseClockIndex = 0;
  const int subClockIndex = 1;
  const int equationIndexes[2] = {1,17};
  jacobian->resultVars[0] /* $res_LSJac1_1.$pDERLSJac1.dummyVarLSJac1 JACOBIAN_VAR */ = jacobian->seedVars[0] /* heaterPower.SeedLSJac1 SEED_VAR */ + ((data->simulationInfo->realParameter[4] /* heatCapacity PARAM */)) * (((data->simulationInfo->realParameter[3] /* density PARAM */)) * (((data->simulationInfo->realParameter[8] /* tankVolume PARAM */)) * (jacobian->tmpVars[0] /* derivativeError.$pDERLSJac1.dummyVarLSJac1 JACOBIAN_TMP_VAR */)));
  TRACE_POP
}

OMC_DISABLE_OPT
int TankLevelControl_functionJacLSJac1_constantEqns(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankLevelControl_INDEX_JAC_LSJac1;
  
  TRACE_POP
  return 0;
}

int TankLevelControl_functionJacLSJac1_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankLevelControl_INDEX_JAC_LSJac1;
  TankLevelControl_eqFunction_16(data, threadData, jacobian, parentJacobian);
  TankLevelControl_eqFunction_17(data, threadData, jacobian, parentJacobian);
  TRACE_POP
  return 0;
}
int TankLevelControl_functionJacH_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int TankLevelControl_functionJacF_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int TankLevelControl_functionJacD_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int TankLevelControl_functionJacC_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int TankLevelControl_functionJacB_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
/* constant equations */
/* dynamic equations */

OMC_DISABLE_OPT
int TankLevelControl_functionJacA_constantEqns(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankLevelControl_INDEX_JAC_A;
  
  TRACE_POP
  return 0;
}

int TankLevelControl_functionJacA_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  int index = TankLevelControl_INDEX_JAC_A;
  TRACE_POP
  return 0;
}

OMC_DISABLE_OPT
int TankLevelControl_initialAnalyticJacobianLSJac0(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  size_t count;

  FILE* pFile = openSparsePatternFile(data, threadData, "TankLevelControl_JacLSJac0.bin");
  
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
int TankLevelControl_initialAnalyticJacobianLSJac1(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  size_t count;

  FILE* pFile = openSparsePatternFile(data, threadData, "TankLevelControl_JacLSJac1.bin");
  
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
int TankLevelControl_initialAnalyticJacobianH(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TankLevelControl_initialAnalyticJacobianF(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TankLevelControl_initialAnalyticJacobianD(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TankLevelControl_initialAnalyticJacobianC(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
int TankLevelControl_initialAnalyticJacobianB(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  jacobian->availability = JACOBIAN_NOT_AVAILABLE;
  return 1;
}
OMC_DISABLE_OPT
int TankLevelControl_initialAnalyticJacobianA(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  size_t count;

  FILE* pFile = openSparsePatternFile(data, threadData, "TankLevelControl_JacA.bin");
  
  initAnalyticJacobian(jacobian, 2, 2, 0, NULL, jacobian->sparsePattern);
  jacobian->sparsePattern = allocSparsePattern(2, 3, 2);
  jacobian->availability = JACOBIAN_ONLY_SPARSITY;
  
  /* read lead index of compressed sparse column */
  count = omc_fread(jacobian->sparsePattern->leadindex, sizeof(unsigned int), 2+1, pFile, FALSE);
  if (count != 2+1) {
    throwStreamPrint(threadData, "Error while reading lead index list of sparsity pattern. Expected %d, got %zu", 2+1, count);
  }
  
  /* read sparse index */
  count = omc_fread(jacobian->sparsePattern->index, sizeof(unsigned int), 3, pFile, FALSE);
  if (count != 3) {
    throwStreamPrint(threadData, "Error while reading row index list of sparsity pattern. Expected %d, got %zu", 3, count);
  }
  
  /* write color array */
  /* color 1 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 1, 1, 2);
  /* color 2 with 1 columns */
  readSparsePatternColor(threadData, pFile, jacobian->sparsePattern->colorCols, 2, 1, 2);
  
  omc_fclose(pFile);
  
  TRACE_POP
  return 0;
}



