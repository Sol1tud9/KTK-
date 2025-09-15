/* Jacobians */
static const REAL_ATTRIBUTE dummyREAL_ATTRIBUTE = omc_dummyRealAttribute;

#if defined(__cplusplus)
extern "C" {
#endif

/* Jacobian Variables */
#define TankLevelControl_INDEX_JAC_LSJac0 0
int TankLevelControl_functionJacLSJac0_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *thisJacobian, ANALYTIC_JACOBIAN *parentJacobian);
int TankLevelControl_initialAnalyticJacobianLSJac0(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian);


#define TankLevelControl_INDEX_JAC_LSJac1 1
int TankLevelControl_functionJacLSJac1_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *thisJacobian, ANALYTIC_JACOBIAN *parentJacobian);
int TankLevelControl_initialAnalyticJacobianLSJac1(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian);


#define TankLevelControl_INDEX_JAC_H 2
int TankLevelControl_functionJacH_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *thisJacobian, ANALYTIC_JACOBIAN *parentJacobian);
int TankLevelControl_initialAnalyticJacobianH(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian);


#define TankLevelControl_INDEX_JAC_F 3
int TankLevelControl_functionJacF_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *thisJacobian, ANALYTIC_JACOBIAN *parentJacobian);
int TankLevelControl_initialAnalyticJacobianF(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian);


#define TankLevelControl_INDEX_JAC_D 4
int TankLevelControl_functionJacD_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *thisJacobian, ANALYTIC_JACOBIAN *parentJacobian);
int TankLevelControl_initialAnalyticJacobianD(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian);


#define TankLevelControl_INDEX_JAC_C 5
int TankLevelControl_functionJacC_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *thisJacobian, ANALYTIC_JACOBIAN *parentJacobian);
int TankLevelControl_initialAnalyticJacobianC(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian);


#define TankLevelControl_INDEX_JAC_B 6
int TankLevelControl_functionJacB_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *thisJacobian, ANALYTIC_JACOBIAN *parentJacobian);
int TankLevelControl_initialAnalyticJacobianB(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian);


#define TankLevelControl_INDEX_JAC_A 7
int TankLevelControl_functionJacA_column(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *thisJacobian, ANALYTIC_JACOBIAN *parentJacobian);
int TankLevelControl_initialAnalyticJacobianA(DATA* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian);

#if defined(__cplusplus)
}
#endif

