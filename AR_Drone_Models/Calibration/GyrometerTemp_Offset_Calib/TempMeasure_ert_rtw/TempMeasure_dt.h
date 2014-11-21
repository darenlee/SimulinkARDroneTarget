/*
 * TempMeasure_dt.h
 *
 * Code generation for model "TempMeasure".
 *
 * Model version              : 1.88
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Tue Jul 29 12:58:50 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(IMU_Packets),
  sizeof(int16_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "IMU_Packets",
  "int16_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&TempMeasure_B.HoldForMSamples), 0, 0, 9 },

  { (char_T *)(&TempMeasure_B.DeciVoltstoVolts), 1, 0, 1 },

  { (char_T *)(&TempMeasure_B.IMURead_o2), 6, 0, 1 },

  { (char_T *)(&TempMeasure_B.IfTruewehavegooddataIffalsewe_h[0]), 4, 0, 6 },

  { (char_T *)(&TempMeasure_B.IfTruewehavegooddataIffalsewe_l), 5, 0, 1 },

  { (char_T *)(&TempMeasure_B.Transition_Detect), 8, 0, 5 },

  { (char_T *)(&TempMeasure_B.sf_Chart_p.output), 0, 0, 1 },

  { (char_T *)(&TempMeasure_B.sf_Chart.output), 0, 0, 1 },

  { (char_T *)(&TempMeasure_B.sf_Chart_a.output), 0, 0, 1 },

  { (char_T *)(&TempMeasure_B.sf_Chart_c.output), 0, 0, 1 },

  { (char_T *)(&TempMeasure_B.sf_Chart_j.output), 0, 0, 1 }
  ,

  { (char_T *)(&TempMeasure_DW.Delay1_DSTATE), 0, 0, 4 },

  { (char_T *)(&TempMeasure_DW.Accel1_PWORK.LoggedData), 11, 0, 6 },

  { (char_T *)(&TempMeasure_DW.Delay_DSTATE_c[0]), 4, 0, 18 },

  { (char_T *)(&TempMeasure_DW.Delay_DSTATE_a[0]), 5, 0, 3 },

  { (char_T *)(&TempMeasure_DW.UnitDelay_DSTATE), 8, 0, 5 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_p.sfEvent), 6, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_p.temporalCounter_i1), 7, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_p.is_active_c2_TempMeasure), 3, 0, 2 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_p.isStable), 8, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart.sfEvent), 6, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart.temporalCounter_i1), 7, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart.is_active_c2_TempMeasure), 3, 0, 2 },

  { (char_T *)(&TempMeasure_DW.sf_Chart.isStable), 8, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_a.sfEvent), 6, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_a.temporalCounter_i1), 7, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_a.is_active_c2_TempMeasure), 3, 0, 2 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_a.isStable), 8, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_c.sfEvent), 6, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_c.temporalCounter_i1), 7, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_c.is_active_c2_TempMeasure), 3, 0, 2 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_c.isStable), 8, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_j.sfEvent), 6, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_j.temporalCounter_i1), 7, 0, 1 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_j.is_active_c2_TempMeasure), 3, 0, 2 },

  { (char_T *)(&TempMeasure_DW.sf_Chart_j.isStable), 8, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  36U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&TempMeasure_P.Constant2_Value), 0, 0, 21 },

  { (char_T *)(&TempMeasure_P.DeciVoltstoVolts_Gain), 1, 0, 1 },

  { (char_T *)(&TempMeasure_P.Constant_Value_c), 6, 0, 5 },

  { (char_T *)(&TempMeasure_P.Delay_DelayLength), 7, 0, 5 },

  { (char_T *)(&TempMeasure_P.Constant1_Value_c), 4, 0, 3 },

  { (char_T *)(&TempMeasure_P.Delay_InitialCondition_e), 5, 0, 1 },

  { (char_T *)(&TempMeasure_P.Gain1_Gain), 4, 0, 1 },

  { (char_T *)(&TempMeasure_P.UnitDelay_InitialCondition), 8, 0, 5 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  8U,
  rtPTransitions
};

/* [EOF] TempMeasure_dt.h */
