/* Linear Systems */
#include "OilSeparator_ThreePhase_model.h"
#include "OilSeparator_ThreePhase_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* linear systems */

/*
equation index: 12
type: SIMPLE_ASSIGN
error_oil = h_oil - oilLevelSetpoint
*/
void OilSeparator_ThreePhase_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  (data->localData[0]->realVars[8] /* error_oil variable */) = (data->localData[0]->realVars[0] /* h_oil STATE(1) */) - (data->simulationInfo->realParameter[7] /* oilLevelSetpoint PARAM */);
  TRACE_POP
}

void residualFunc14(RESIDUAL_USERDATA* userData, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = userData->data;
  threadData_t *threadData = userData->threadData;
  const int equationIndexes[2] = {1,14};
  ANALYTIC_JACOBIAN* jacobian = NULL;
  (data->localData[0]->realVars[0] /* h_oil STATE(1) */) = xloc[0];
  /* local constraints */
  OilSeparator_ThreePhase_eqFunction_12(data, threadData);
  res[0] = (data->localData[0]->realVars[0] /* h_oil STATE(1) */) + (-(data->simulationInfo->realParameter[7] /* oilLevelSetpoint PARAM */)) - (data->localData[0]->realVars[8] /* error_oil variable */);
  TRACE_POP
}
OMC_DISABLE_OPT
void initializeStaticLSData14(DATA* data, threadData_t* threadData, LINEAR_SYSTEM_DATA* linearSystemData, modelica_boolean initSparsePattern)
{
  const int indices[1] = {
    0 /* h_oil */
  };
  for (int i = 0; i < 1; ++i) {
    linearSystemData->nominal[i] = data->modelData->realVarsData[indices[i]].attribute.nominal;
    linearSystemData->min[i]     = data->modelData->realVarsData[indices[i]].attribute.min;
    linearSystemData->max[i]     = data->modelData->realVarsData[indices[i]].attribute.max;
  }
}


/*
equation index: 5
type: SIMPLE_ASSIGN
error_water = h_water - waterLevelSetpoint
*/
void OilSeparator_ThreePhase_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->realVars[9] /* error_water variable */) = (data->localData[0]->realVars[1] /* h_water STATE(1) */) - (data->simulationInfo->realParameter[11] /* waterLevelSetpoint PARAM */);
  TRACE_POP
}

void residualFunc7(RESIDUAL_USERDATA* userData, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = userData->data;
  threadData_t *threadData = userData->threadData;
  const int equationIndexes[2] = {1,7};
  ANALYTIC_JACOBIAN* jacobian = NULL;
  (data->localData[0]->realVars[1] /* h_water STATE(1) */) = xloc[0];
  /* local constraints */
  OilSeparator_ThreePhase_eqFunction_5(data, threadData);
  res[0] = (data->localData[0]->realVars[1] /* h_water STATE(1) */) + (-(data->simulationInfo->realParameter[11] /* waterLevelSetpoint PARAM */)) - (data->localData[0]->realVars[9] /* error_water variable */);
  TRACE_POP
}
OMC_DISABLE_OPT
void initializeStaticLSData7(DATA* data, threadData_t* threadData, LINEAR_SYSTEM_DATA* linearSystemData, modelica_boolean initSparsePattern)
{
  const int indices[1] = {
    1 /* h_water */
  };
  for (int i = 0; i < 1; ++i) {
    linearSystemData->nominal[i] = data->modelData->realVarsData[indices[i]].attribute.nominal;
    linearSystemData->min[i]     = data->modelData->realVarsData[indices[i]].attribute.min;
    linearSystemData->max[i]     = data->modelData->realVarsData[indices[i]].attribute.max;
  }
}

/* Prototypes for the strict sets (Dynamic Tearing) */

/* Global constraints for the casual sets */
/* function initialize linear systems */
void OilSeparator_ThreePhase_initialLinearSystem(int nLinearSystems, LINEAR_SYSTEM_DATA* linearSystemData)
{
  /* linear systems */
  assertStreamPrint(NULL, nLinearSystems > 1, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[1].equationIndex = 14;
  linearSystemData[1].size = 1;
  linearSystemData[1].nnz = 0;
  linearSystemData[1].method = 1;   /* Symbolic Jacobian available */
  linearSystemData[1].residualFunc = residualFunc14;
  linearSystemData[1].strictTearingFunctionCall = NULL;
  linearSystemData[1].analyticalJacobianColumn = OilSeparator_ThreePhase_functionJacLSJac1_column;
  linearSystemData[1].initialAnalyticalJacobian = OilSeparator_ThreePhase_initialAnalyticJacobianLSJac1;
  linearSystemData[1].jacobianIndex = 1 /*jacInx*/;
  linearSystemData[1].setA = NULL;  //setLinearMatrixA14;
  linearSystemData[1].setb = NULL;  //setLinearVectorb14;
  linearSystemData[1].initializeStaticLSData = initializeStaticLSData14;
  
  assertStreamPrint(NULL, nLinearSystems > 0, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[0].equationIndex = 7;
  linearSystemData[0].size = 1;
  linearSystemData[0].nnz = 0;
  linearSystemData[0].method = 1;   /* Symbolic Jacobian available */
  linearSystemData[0].residualFunc = residualFunc7;
  linearSystemData[0].strictTearingFunctionCall = NULL;
  linearSystemData[0].analyticalJacobianColumn = OilSeparator_ThreePhase_functionJacLSJac0_column;
  linearSystemData[0].initialAnalyticalJacobian = OilSeparator_ThreePhase_initialAnalyticJacobianLSJac0;
  linearSystemData[0].jacobianIndex = 0 /*jacInx*/;
  linearSystemData[0].setA = NULL;  //setLinearMatrixA7;
  linearSystemData[0].setb = NULL;  //setLinearVectorb7;
  linearSystemData[0].initializeStaticLSData = initializeStaticLSData7;
}

#if defined(__cplusplus)
}
#endif

