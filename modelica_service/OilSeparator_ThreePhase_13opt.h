#if defined(__cplusplus)
  extern "C" {
#endif
  int OilSeparator_ThreePhase_mayer(DATA* data, modelica_real** res, short*);
  int OilSeparator_ThreePhase_lagrange(DATA* data, modelica_real** res, short *, short *);
  int OilSeparator_ThreePhase_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int OilSeparator_ThreePhase_setInputData(DATA *data, const modelica_boolean file);
  int OilSeparator_ThreePhase_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif