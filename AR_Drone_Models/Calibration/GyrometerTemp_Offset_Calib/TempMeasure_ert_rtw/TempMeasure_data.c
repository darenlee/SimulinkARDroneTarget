/*
 * File: TempMeasure_data.c
 *
 * Code generated for Simulink model 'TempMeasure'.
 *
 * Model version                  : 1.88
 * Simulink Coder version         : 8.6 (R2014a) 27-Dec-2013
 * C/C++ source code generated on : Tue Jul 29 12:58:50 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TempMeasure.h"
#include "TempMeasure_private.h"

/* Block parameters (auto storage) */
P_TempMeasure_T TempMeasure_P = {
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S34>/Constant2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S36>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S36>/Constant'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S31>/Hold For M Samples'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S28>/Constant2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S30>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S30>/Constant'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S25>/Hold For M Samples'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S22>/Constant2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S24>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S24>/Constant'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S19>/Hold For M Samples'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S14>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S14>/Constant'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S10>/Hold For M Samples'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S8>/Delay1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S40>/Constant2'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<S42>/Constant1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S42>/Constant'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S37>/Hold For M Samples'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S37>/Delay'
                                        */
  0.1F,                                /* Computed Parameter: DeciVoltstoVolts_Gain
                                        * Referenced by: '<Root>/Deci-Volts to Volts'
                                        */
  0,                                   /* Computed Parameter: Constant_Value_c
                                        * Referenced by: '<S33>/Constant'
                                        */
  0,                                   /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S27>/Constant'
                                        */
  0,                                   /* Computed Parameter: Constant_Value_pc
                                        * Referenced by: '<S21>/Constant'
                                        */
  0,                                   /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S11>/Constant'
                                        */
  0,                                   /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S39>/Constant'
                                        */
  3U,                                  /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<S31>/Delay'
                                        */
  3U,                                  /* Computed Parameter: Delay_DelayLength_n
                                        * Referenced by: '<S25>/Delay'
                                        */
  3U,                                  /* Computed Parameter: Delay_DelayLength_a
                                        * Referenced by: '<S19>/Delay'
                                        */
  1U,                                  /* Computed Parameter: Delay1_DelayLength
                                        * Referenced by: '<S8>/Delay1'
                                        */
  3U,                                  /* Computed Parameter: Delay_DelayLength_p
                                        * Referenced by: '<S37>/Delay'
                                        */
  23000,                               /* Computed Parameter: Constant1_Value_c
                                        * Referenced by: '<Root>/Constant1'
                                        */
  0,                                   /* Computed Parameter: Delay_InitialCondition_c
                                        * Referenced by: '<S25>/Delay'
                                        */
  0,                                   /* Computed Parameter: Delay_InitialCondition_i
                                        * Referenced by: '<S19>/Delay'
                                        */
  0U,                                  /* Computed Parameter: Delay_InitialCondition_e
                                        * Referenced by: '<S31>/Delay'
                                        */
  29959,                               /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<Root>/Gain1'
                                        */
  0,                                   /* Computed Parameter: UnitDelay_InitialCondition
                                        * Referenced by: '<S36>/Unit Delay'
                                        */
  0,                                   /* Computed Parameter: UnitDelay_InitialCondition_f
                                        * Referenced by: '<S30>/Unit Delay'
                                        */
  0,                                   /* Computed Parameter: UnitDelay_InitialCondition_fz
                                        * Referenced by: '<S24>/Unit Delay'
                                        */
  0,                                   /* Computed Parameter: UnitDelay_InitialCondition_j
                                        * Referenced by: '<S14>/Unit Delay'
                                        */
  0                                    /* Computed Parameter: UnitDelay_InitialCondition_h
                                        * Referenced by: '<S42>/Unit Delay'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
