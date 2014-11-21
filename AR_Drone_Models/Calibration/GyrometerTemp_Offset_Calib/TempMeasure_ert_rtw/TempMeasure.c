/*
 * File: TempMeasure.c
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
#include "TempMeasure_dt.h"

/* Named constants for Chart: '<S12>/Chart' */
#define TempMeasure_CALL_EVENT         (-1)
#define TempMeasure_IN_Begin_State     ((uint8_T)1U)
#define TempMeasure_IN_Begin_State0    ((uint8_T)2U)
#define TempMeasure_IN_End_State       ((uint8_T)3U)
#define TempMeasure_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

/* Block signals (auto storage) */
B_TempMeasure_T TempMeasure_B;

/* Block states (auto storage) */
DW_TempMeasure_T TempMeasure_DW;

/* Real-time model */
RT_MODEL_TempMeasure_T TempMeasure_M_;
RT_MODEL_TempMeasure_T *const TempMeasure_M = &TempMeasure_M_;
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to "remember" which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void TempMeasure_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(TempMeasure_M, 1));
  eventFlags[2] = ((boolean_T)rtmStepTask(TempMeasure_M, 2));
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (TempMeasure_M->Timing.TaskCounters.TID[1])++;
  if ((TempMeasure_M->Timing.TaskCounters.TID[1]) > 3) {/* Sample time: [0.01s, 0.0s] */
    TempMeasure_M->Timing.TaskCounters.TID[1] = 0;
  }

  (TempMeasure_M->Timing.TaskCounters.TID[2])++;
  if ((TempMeasure_M->Timing.TaskCounters.TID[2]) > 39) {/* Sample time: [0.1s, 0.0s] */
    TempMeasure_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * Initial conditions for atomic system:
 *    '<S12>/Chart'
 *    '<S22>/Chart'
 *    '<S28>/Chart'
 *    '<S34>/Chart'
 *    '<S40>/Chart'
 */
void TempMeasure_Chart_Init(DW_Chart_TempMeasure_T *localDW)
{
  localDW->sfEvent = TempMeasure_CALL_EVENT;
  localDW->temporalCounter_i1 = 0U;
  localDW->is_active_c2_TempMeasure = 0U;
  localDW->is_c2_TempMeasure = TempMeasure_IN_NO_ACTIVE_CHILD;
}

/*
 * Output and update for atomic system:
 *    '<S12>/Chart'
 *    '<S22>/Chart'
 *    '<S28>/Chart'
 *    '<S34>/Chart'
 *    '<S40>/Chart'
 */
void TempMeasure_Chart(boolean_T rtu_if_transition, real_T rtu_HoldDataTicks,
  B_Chart_TempMeasure_T *localB, DW_Chart_TempMeasure_T *localDW)
{
  /* Gateway: CheckSum Pre-Processing/Accelerometer Processing/CheckSum Correction/Generate Sample Holding Pulse/Chart */
  localDW->sfEvent = TempMeasure_CALL_EVENT;
  if (localDW->temporalCounter_i1 < MAX_uint32_T) {
    localDW->temporalCounter_i1++;
  }

  /* During: CheckSum Pre-Processing/Accelerometer Processing/CheckSum Correction/Generate Sample Holding Pulse/Chart */
  if (localDW->is_active_c2_TempMeasure == 0U) {
    /* Entry: CheckSum Pre-Processing/Accelerometer Processing/CheckSum Correction/Generate Sample Holding Pulse/Chart */
    localDW->is_active_c2_TempMeasure = 1U;

    /* Entry Internal: CheckSum Pre-Processing/Accelerometer Processing/CheckSum Correction/Generate Sample Holding Pulse/Chart */
    /* Transition: '<S13>:3' */
    localDW->is_c2_TempMeasure = TempMeasure_IN_Begin_State0;

    /* Entry 'Begin_State0': '<S13>:15' */
    localB->output = 0.0;
  } else {
    switch (localDW->is_c2_TempMeasure) {
     case TempMeasure_IN_Begin_State:
      /* During 'Begin_State': '<S13>:2' */
      if (localDW->temporalCounter_i1 >= (uint32_T)rtu_HoldDataTicks) {
        /* Transition: '<S13>:5' */
        localDW->is_c2_TempMeasure = TempMeasure_IN_End_State;

        /* Entry 'End_State': '<S13>:4' */
        localB->output = 0.0;
      } else {
        if (rtu_if_transition == 1) {
          /* Transition: '<S13>:12' */
          localDW->is_c2_TempMeasure = TempMeasure_IN_Begin_State;
          localDW->temporalCounter_i1 = 0U;

          /* Entry 'Begin_State': '<S13>:2' */
          localB->output = 1.0;
        }
      }
      break;

     case TempMeasure_IN_Begin_State0:
      /* During 'Begin_State0': '<S13>:15' */
      if (rtu_if_transition == 1) {
        /* Transition: '<S13>:16' */
        localDW->is_c2_TempMeasure = TempMeasure_IN_Begin_State;
        localDW->temporalCounter_i1 = 0U;

        /* Entry 'Begin_State': '<S13>:2' */
        localB->output = 1.0;
      }
      break;

     default:
      /* During 'End_State': '<S13>:4' */
      if (rtu_if_transition == 1) {
        /* Transition: '<S13>:13' */
        localDW->is_c2_TempMeasure = TempMeasure_IN_Begin_State;
        localDW->temporalCounter_i1 = 0U;

        /* Entry 'Begin_State': '<S13>:2' */
        localB->output = 1.0;
      }
      break;
    }
  }
}

/* Model step function for TID0 */
void TempMeasure_step0(void)           /* Sample time: [0.0025s, 0.0s] */
{
  real_T height;
  int_T idxDelay;
  boolean_T rtb_LogicalOperator1;
  boolean_T rtb_RelationalOperator1;
  boolean_T rtb_LogicalOperator1_f;
  boolean_T rtb_LogicalOperator1_mn;
  boolean_T rtb_LogicalOperator1_o;
  real_T rtb_prev_good_height;

  {                                    /* Sample time: [0.0025s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* S-Function (IMU_Sfcn_mex): '<S2>/IMU Read' */
  MDL_IMU_step( &TempMeasure_B.IMURead_o1, &TempMeasure_B.IMURead_o2);

  /* Logic: '<S31>/Logical Operator1' incorporates:
   *  Constant: '<S33>/Constant'
   *  RelationalOperator: '<S33>/Compare'
   */
  rtb_LogicalOperator1 = !(TempMeasure_B.IMURead_o2 >
    TempMeasure_P.Constant_Value_c);

  /* Logic: '<S36>/Logical Operator' incorporates:
   *  Constant: '<S36>/Constant'
   *  Constant: '<S36>/Constant1'
   *  RelationalOperator: '<S36>/Relational Operator'
   *  RelationalOperator: '<S36>/Relational Operator1'
   *  UnitDelay: '<S36>/Unit Delay'
   */
  TempMeasure_B.Transition_Detect = ((TempMeasure_P.Constant1_Value ==
    rtb_LogicalOperator1) && (TempMeasure_DW.UnitDelay_DSTATE ==
    TempMeasure_P.Constant_Value));

  /* Constant: '<S31>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples = TempMeasure_P.HoldForMSamples_Value;

  /* Chart: '<S34>/Chart' */
  TempMeasure_Chart(TempMeasure_B.Transition_Detect,
                    TempMeasure_B.HoldForMSamples, &TempMeasure_B.sf_Chart,
                    &TempMeasure_DW.sf_Chart);

  /* Switch: '<S31>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' incorporates:
   *  Constant: '<S34>/Constant2'
   *  Delay: '<S31>/Delay'
   *  Logic: '<S31>/Invert Logic'
   *  Logic: '<S34>/Logical Operator1'
   */
  if (!((TempMeasure_P.Constant2_Value != 0.0) && (TempMeasure_B.sf_Chart.output
        != 0.0))) {
    TempMeasure_B.IfTruewehavegooddataIffalsewe_l =
      TempMeasure_B.IMURead_o1.temperature_gyro;
  } else {
    TempMeasure_B.IfTruewehavegooddataIffalsewe_l =
      TempMeasure_DW.Delay_DSTATE_a[0];
  }

  /* End of Switch: '<S31>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' */

  /* Gain: '<Root>/Gain1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   *  Sum: '<Root>/Sum4'
   */
  TempMeasure_B.Gain1 = (real_T)TempMeasure_P.Gain1_Gain * 1.1920928955078125E-7
    * (real_T)(int16_T)((int16_T)TempMeasure_B.IfTruewehavegooddataIffalsewe_l +
                        TempMeasure_P.Constant1_Value_c);

  /* Logic: '<S25>/Logical Operator1' incorporates:
   *  Constant: '<S27>/Constant'
   *  RelationalOperator: '<S27>/Compare'
   */
  rtb_LogicalOperator1_f = !(TempMeasure_B.IMURead_o2 >
    TempMeasure_P.Constant_Value_o);

  /* Logic: '<S30>/Logical Operator' incorporates:
   *  Constant: '<S30>/Constant'
   *  Constant: '<S30>/Constant1'
   *  RelationalOperator: '<S30>/Relational Operator'
   *  RelationalOperator: '<S30>/Relational Operator1'
   *  UnitDelay: '<S30>/Unit Delay'
   */
  TempMeasure_B.Transition_Detect_h = ((TempMeasure_P.Constant1_Value_k ==
    rtb_LogicalOperator1_f) && (TempMeasure_DW.UnitDelay_DSTATE_b ==
    TempMeasure_P.Constant_Value_j));

  /* Constant: '<S25>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples_l = TempMeasure_P.HoldForMSamples_Value_f;

  /* Chart: '<S28>/Chart' */
  TempMeasure_Chart(TempMeasure_B.Transition_Detect_h,
                    TempMeasure_B.HoldForMSamples_l, &TempMeasure_B.sf_Chart_a,
                    &TempMeasure_DW.sf_Chart_a);

  /* Switch: '<S25>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' incorporates:
   *  Constant: '<S28>/Constant2'
   *  Delay: '<S25>/Delay'
   *  Logic: '<S25>/Invert Logic'
   *  Logic: '<S28>/Logical Operator1'
   */
  if (!((TempMeasure_P.Constant2_Value_c != 0.0) &&
        (TempMeasure_B.sf_Chart_a.output != 0.0))) {
    TempMeasure_B.IfTruewehavegooddataIffalsewe_h[0] =
      TempMeasure_B.IMURead_o1.vx;
    TempMeasure_B.IfTruewehavegooddataIffalsewe_h[1] =
      TempMeasure_B.IMURead_o1.vy;
    TempMeasure_B.IfTruewehavegooddataIffalsewe_h[2] =
      TempMeasure_B.IMURead_o1.vz;
  } else {
    TempMeasure_B.IfTruewehavegooddataIffalsewe_h[0] =
      TempMeasure_DW.Delay_DSTATE_c[0];
    TempMeasure_B.IfTruewehavegooddataIffalsewe_h[1] =
      TempMeasure_DW.Delay_DSTATE_c[1];
    TempMeasure_B.IfTruewehavegooddataIffalsewe_h[2] =
      TempMeasure_DW.Delay_DSTATE_c[2];
  }

  /* End of Switch: '<S25>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' */

  /* Logic: '<S19>/Logical Operator1' incorporates:
   *  Constant: '<S21>/Constant'
   *  RelationalOperator: '<S21>/Compare'
   */
  rtb_LogicalOperator1_mn = !(TempMeasure_B.IMURead_o2 >
    TempMeasure_P.Constant_Value_pc);

  /* Logic: '<S24>/Logical Operator' incorporates:
   *  Constant: '<S24>/Constant'
   *  Constant: '<S24>/Constant1'
   *  RelationalOperator: '<S24>/Relational Operator'
   *  RelationalOperator: '<S24>/Relational Operator1'
   *  UnitDelay: '<S24>/Unit Delay'
   */
  TempMeasure_B.Transition_Detect_m = ((TempMeasure_P.Constant1_Value_g ==
    rtb_LogicalOperator1_mn) && (TempMeasure_DW.UnitDelay_DSTATE_m ==
    TempMeasure_P.Constant_Value_e));

  /* Constant: '<S19>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples_j = TempMeasure_P.HoldForMSamples_Value_fw;

  /* Chart: '<S22>/Chart' */
  TempMeasure_Chart(TempMeasure_B.Transition_Detect_m,
                    TempMeasure_B.HoldForMSamples_j, &TempMeasure_B.sf_Chart_c,
                    &TempMeasure_DW.sf_Chart_c);

  /* Switch: '<S19>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' incorporates:
   *  Constant: '<S22>/Constant2'
   *  Delay: '<S19>/Delay'
   *  Logic: '<S19>/Invert Logic'
   *  Logic: '<S22>/Logical Operator1'
   */
  if (!((TempMeasure_P.Constant2_Value_n != 0.0) &&
        (TempMeasure_B.sf_Chart_c.output != 0.0))) {
    TempMeasure_B.IfTruewehavegooddataIffalsewe_a[0] =
      TempMeasure_B.IMURead_o1.mx;
    TempMeasure_B.IfTruewehavegooddataIffalsewe_a[1] =
      TempMeasure_B.IMURead_o1.my;
    TempMeasure_B.IfTruewehavegooddataIffalsewe_a[2] =
      TempMeasure_B.IMURead_o1.mz;
  } else {
    TempMeasure_B.IfTruewehavegooddataIffalsewe_a[0] =
      TempMeasure_DW.Delay_DSTATE_k[0];
    TempMeasure_B.IfTruewehavegooddataIffalsewe_a[1] =
      TempMeasure_DW.Delay_DSTATE_k[1];
    TempMeasure_B.IfTruewehavegooddataIffalsewe_a[2] =
      TempMeasure_DW.Delay_DSTATE_k[2];
  }

  /* End of Switch: '<S19>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' */

  /* Logic: '<S10>/Logical Operator1' incorporates:
   *  Constant: '<S11>/Constant'
   *  RelationalOperator: '<S11>/Compare'
   */
  rtb_RelationalOperator1 = !(TempMeasure_B.IMURead_o2 >
    TempMeasure_P.Constant_Value_a);

  /* Logic: '<S14>/Logical Operator' incorporates:
   *  Constant: '<S14>/Constant'
   *  Constant: '<S14>/Constant1'
   *  RelationalOperator: '<S14>/Relational Operator'
   *  RelationalOperator: '<S14>/Relational Operator1'
   *  UnitDelay: '<S14>/Unit Delay'
   */
  TempMeasure_B.Transition_Detect_m2 = ((TempMeasure_P.Constant1_Value_i ==
    rtb_RelationalOperator1) && (TempMeasure_DW.UnitDelay_DSTATE_e ==
    TempMeasure_P.Constant_Value_p));

  /* Constant: '<S10>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples_p = TempMeasure_P.HoldForMSamples_Value_h;

  /* Chart: '<S12>/Chart' */
  TempMeasure_Chart(TempMeasure_B.Transition_Detect_m2,
                    TempMeasure_B.HoldForMSamples_p, &TempMeasure_B.sf_Chart_j,
                    &TempMeasure_DW.sf_Chart_j);

  /* MATLAB Function: '<S8>/Height Calculation' incorporates:
   *  DataTypeConversion: '<S8>/Data Type Conversion1'
   *  Delay: '<S8>/Delay1'
   */
  /* MATLAB Function 'CheckSum Pre-Processing/Ultrasound Processing/Height Calculation': '<S38>:1' */
  if (TempMeasure_B.IMURead_o1.ultrasound < 10000) {
    /* '<S38>:1:6' */
    /* '<S38>:1:8' */
    height = ((real_T)TempMeasure_B.IMURead_o1.ultrasound - 880.0) / 26.553;

    /* '<S38>:1:9' */
    rtb_prev_good_height = height;
  } else {
    /*      height = u; */
    /*      prev_good_height = height; */
    /* '<S38>:1:14' */
    height = TempMeasure_DW.Delay1_DSTATE;

    /* '<S38>:1:15' */
    rtb_prev_good_height = TempMeasure_DW.Delay1_DSTATE;
  }

  /* '<S38>:1:18' */
  TempMeasure_B.y = height;

  /* End of MATLAB Function: '<S8>/Height Calculation' */

  /* Logic: '<S37>/Logical Operator1' incorporates:
   *  Constant: '<S39>/Constant'
   *  RelationalOperator: '<S39>/Compare'
   */
  rtb_LogicalOperator1_o = !(TempMeasure_B.IMURead_o2 >
    TempMeasure_P.Constant_Value_h);

  /* Logic: '<S42>/Logical Operator' incorporates:
   *  Constant: '<S42>/Constant'
   *  Constant: '<S42>/Constant1'
   *  RelationalOperator: '<S42>/Relational Operator'
   *  RelationalOperator: '<S42>/Relational Operator1'
   *  UnitDelay: '<S42>/Unit Delay'
   */
  TempMeasure_B.Transition_Detect_b = ((TempMeasure_P.Constant1_Value_p ==
    rtb_LogicalOperator1_o) && (TempMeasure_DW.UnitDelay_DSTATE_d ==
    TempMeasure_P.Constant_Value_k));

  /* Constant: '<S37>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples_f = TempMeasure_P.HoldForMSamples_Value_p;

  /* Chart: '<S40>/Chart' */
  TempMeasure_Chart(TempMeasure_B.Transition_Detect_b,
                    TempMeasure_B.HoldForMSamples_f, &TempMeasure_B.sf_Chart_p,
                    &TempMeasure_DW.sf_Chart_p);

  /* Switch: '<S37>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' incorporates:
   *  Constant: '<S40>/Constant2'
   *  Delay: '<S37>/Delay'
   *  Logic: '<S37>/Invert Logic'
   *  Logic: '<S40>/Logical Operator1'
   */
  if (!((TempMeasure_P.Constant2_Value_j != 0.0) &&
        (TempMeasure_B.sf_Chart_p.output != 0.0))) {
    TempMeasure_B.IfTruewehavegooddataIffalseweha = TempMeasure_B.y;
  } else {
    TempMeasure_B.IfTruewehavegooddataIffalseweha = TempMeasure_DW.Delay_DSTATE
      [0];
  }

  /* End of Switch: '<S37>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' */

  /* Update for UnitDelay: '<S36>/Unit Delay' */
  TempMeasure_DW.UnitDelay_DSTATE = rtb_LogicalOperator1;

  /* Update for Delay: '<S31>/Delay' */
  TempMeasure_DW.Delay_DSTATE_a[0] = TempMeasure_DW.Delay_DSTATE_a[1];
  TempMeasure_DW.Delay_DSTATE_a[1] = TempMeasure_DW.Delay_DSTATE_a[2];
  TempMeasure_DW.Delay_DSTATE_a[2] =
    TempMeasure_B.IfTruewehavegooddataIffalsewe_l;

  /* Update for UnitDelay: '<S30>/Unit Delay' */
  TempMeasure_DW.UnitDelay_DSTATE_b = rtb_LogicalOperator1_f;

  /* Update for Delay: '<S25>/Delay' */
  for (idxDelay = 0; idxDelay < 2; idxDelay++) {
    TempMeasure_DW.Delay_DSTATE_c[idxDelay * 3] = TempMeasure_DW.Delay_DSTATE_c
      [(idxDelay + 1) * 3];
    TempMeasure_DW.Delay_DSTATE_c[idxDelay * 3 + 1] =
      TempMeasure_DW.Delay_DSTATE_c[(idxDelay + 1) * 3 + 1];
    TempMeasure_DW.Delay_DSTATE_c[idxDelay * 3 + 2] =
      TempMeasure_DW.Delay_DSTATE_c[(idxDelay + 1) * 3 + 2];
  }

  TempMeasure_DW.Delay_DSTATE_c[6] =
    TempMeasure_B.IfTruewehavegooddataIffalsewe_h[0];
  TempMeasure_DW.Delay_DSTATE_c[7] =
    TempMeasure_B.IfTruewehavegooddataIffalsewe_h[1];
  TempMeasure_DW.Delay_DSTATE_c[8] =
    TempMeasure_B.IfTruewehavegooddataIffalsewe_h[2];

  /* End of Update for Delay: '<S25>/Delay' */

  /* Update for UnitDelay: '<S24>/Unit Delay' */
  TempMeasure_DW.UnitDelay_DSTATE_m = rtb_LogicalOperator1_mn;

  /* Update for Delay: '<S19>/Delay' */
  for (idxDelay = 0; idxDelay < 2; idxDelay++) {
    TempMeasure_DW.Delay_DSTATE_k[idxDelay * 3] = TempMeasure_DW.Delay_DSTATE_k
      [(idxDelay + 1) * 3];
    TempMeasure_DW.Delay_DSTATE_k[idxDelay * 3 + 1] =
      TempMeasure_DW.Delay_DSTATE_k[(idxDelay + 1) * 3 + 1];
    TempMeasure_DW.Delay_DSTATE_k[idxDelay * 3 + 2] =
      TempMeasure_DW.Delay_DSTATE_k[(idxDelay + 1) * 3 + 2];
  }

  TempMeasure_DW.Delay_DSTATE_k[6] =
    TempMeasure_B.IfTruewehavegooddataIffalsewe_a[0];
  TempMeasure_DW.Delay_DSTATE_k[7] =
    TempMeasure_B.IfTruewehavegooddataIffalsewe_a[1];
  TempMeasure_DW.Delay_DSTATE_k[8] =
    TempMeasure_B.IfTruewehavegooddataIffalsewe_a[2];

  /* End of Update for Delay: '<S19>/Delay' */

  /* Update for UnitDelay: '<S14>/Unit Delay' */
  TempMeasure_DW.UnitDelay_DSTATE_e = rtb_RelationalOperator1;

  /* Update for Delay: '<S8>/Delay1' */
  TempMeasure_DW.Delay1_DSTATE = rtb_prev_good_height;

  /* Update for UnitDelay: '<S42>/Unit Delay' */
  TempMeasure_DW.UnitDelay_DSTATE_d = rtb_LogicalOperator1_o;

  /* Update for Delay: '<S37>/Delay' */
  TempMeasure_DW.Delay_DSTATE[0] = TempMeasure_DW.Delay_DSTATE[1];
  TempMeasure_DW.Delay_DSTATE[1] = TempMeasure_DW.Delay_DSTATE[2];
  TempMeasure_DW.Delay_DSTATE[2] = TempMeasure_B.IfTruewehavegooddataIffalseweha;

  /* External mode */
  rtExtModeUploadCheckTrigger(3);
  rtExtModeUpload(0, TempMeasure_M->Timing.taskTime0);

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0025s, 0.0s] */
    if ((rtmGetTFinal(TempMeasure_M)!=-1) &&
        !((rtmGetTFinal(TempMeasure_M)-TempMeasure_M->Timing.taskTime0) >
          TempMeasure_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(TempMeasure_M, "Simulation finished");
    }

    if (rtmGetStopRequested(TempMeasure_M)) {
      rtmSetErrorStatus(TempMeasure_M, "Simulation finished");
    }
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  TempMeasure_M->Timing.taskTime0 =
    (++TempMeasure_M->Timing.clockTick0) * TempMeasure_M->Timing.stepSize0;
}

/* Model step function for TID1 */
void TempMeasure_step1(void)           /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real32_T rtb_BatteryVoltageMeasurement;

  /* S-Function (Battery_Sfcn_mex): '<Root>/Battery Voltage Measurement' */
  BatteryMeasure_step( &rtb_BatteryVoltageMeasurement);

  /* Gain: '<Root>/Deci-Volts to Volts' */
  TempMeasure_B.DeciVoltstoVolts = TempMeasure_P.DeciVoltstoVolts_Gain *
    rtb_BatteryVoltageMeasurement;
  rtExtModeUpload(1, ((TempMeasure_M->Timing.clockTick1) * 0.01));

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.01, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  TempMeasure_M->Timing.clockTick1++;
}

/* Model step function for TID2 */
void TempMeasure_step2(void)           /* Sample time: [0.1s, 0.0s] */
{
  /* DigitalClock: '<Root>/Digital Clock1' */
  TempMeasure_B.DigitalClock1 = ((TempMeasure_M->Timing.clockTick2) * 0.1);
  rtExtModeUpload(2, ((TempMeasure_M->Timing.clockTick2) * 0.1));

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.1, which is the step size
   * of the task. Size of "clockTick2" ensures timer will not overflow during the
   * application lifespan selected.
   */
  TempMeasure_M->Timing.clockTick2++;
}

/* Model initialize function */
void TempMeasure_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)TempMeasure_M, 0,
                sizeof(RT_MODEL_TempMeasure_T));
  rtmSetTFinal(TempMeasure_M, 400000.0);
  TempMeasure_M->Timing.stepSize0 = 0.0025;

  /* External mode info */
  TempMeasure_M->Sizes.checksums[0] = (212839982U);
  TempMeasure_M->Sizes.checksums[1] = (3493245051U);
  TempMeasure_M->Sizes.checksums[2] = (1619579751U);
  TempMeasure_M->Sizes.checksums[3] = (3961658145U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    TempMeasure_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(TempMeasure_M->extModeInfo,
      &TempMeasure_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(TempMeasure_M->extModeInfo,
                        TempMeasure_M->Sizes.checksums);
    rteiSetTPtr(TempMeasure_M->extModeInfo, rtmGetTPtr(TempMeasure_M));
  }

  /* block I/O */
  (void) memset(((void *) &TempMeasure_B), 0,
                sizeof(B_TempMeasure_T));

  /* states (dwork) */
  (void) memset((void *)&TempMeasure_DW, 0,
                sizeof(DW_TempMeasure_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    TempMeasure_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Start for Constant: '<S31>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples = TempMeasure_P.HoldForMSamples_Value;

  /* Start for Constant: '<S25>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples_l = TempMeasure_P.HoldForMSamples_Value_f;

  /* Start for Constant: '<S19>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples_j = TempMeasure_P.HoldForMSamples_Value_fw;

  /* Start for Constant: '<S10>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples_p = TempMeasure_P.HoldForMSamples_Value_h;

  /* Start for Constant: '<S37>/Hold For M Samples' */
  TempMeasure_B.HoldForMSamples_f = TempMeasure_P.HoldForMSamples_Value_p;

  {
    int32_T i;

    /* S-Function (IMU_Sfcn_mex): <S2>/IMU Read */
    MDL_IMU_start();

    /* InitializeConditions for UnitDelay: '<S36>/Unit Delay' */
    TempMeasure_DW.UnitDelay_DSTATE = TempMeasure_P.UnitDelay_InitialCondition;

    /* InitializeConditions for Chart: '<S34>/Chart' */
    TempMeasure_Chart_Init(&TempMeasure_DW.sf_Chart);

    /* InitializeConditions for Delay: '<S31>/Delay' */
    TempMeasure_DW.Delay_DSTATE_a[0] = TempMeasure_P.Delay_InitialCondition_e;
    TempMeasure_DW.Delay_DSTATE_a[1] = TempMeasure_P.Delay_InitialCondition_e;
    TempMeasure_DW.Delay_DSTATE_a[2] = TempMeasure_P.Delay_InitialCondition_e;

    /* InitializeConditions for UnitDelay: '<S30>/Unit Delay' */
    TempMeasure_DW.UnitDelay_DSTATE_b =
      TempMeasure_P.UnitDelay_InitialCondition_f;

    /* InitializeConditions for Chart: '<S28>/Chart' */
    TempMeasure_Chart_Init(&TempMeasure_DW.sf_Chart_a);

    /* InitializeConditions for Delay: '<S25>/Delay' */
    for (i = 0; i < 9; i++) {
      TempMeasure_DW.Delay_DSTATE_c[i] = TempMeasure_P.Delay_InitialCondition_c;
    }

    /* End of InitializeConditions for Delay: '<S25>/Delay' */

    /* InitializeConditions for UnitDelay: '<S24>/Unit Delay' */
    TempMeasure_DW.UnitDelay_DSTATE_m =
      TempMeasure_P.UnitDelay_InitialCondition_fz;

    /* InitializeConditions for Chart: '<S22>/Chart' */
    TempMeasure_Chart_Init(&TempMeasure_DW.sf_Chart_c);

    /* InitializeConditions for Delay: '<S19>/Delay' */
    for (i = 0; i < 9; i++) {
      TempMeasure_DW.Delay_DSTATE_k[i] = TempMeasure_P.Delay_InitialCondition_i;
    }

    /* End of InitializeConditions for Delay: '<S19>/Delay' */

    /* InitializeConditions for UnitDelay: '<S14>/Unit Delay' */
    TempMeasure_DW.UnitDelay_DSTATE_e =
      TempMeasure_P.UnitDelay_InitialCondition_j;

    /* InitializeConditions for Chart: '<S12>/Chart' */
    TempMeasure_Chart_Init(&TempMeasure_DW.sf_Chart_j);

    /* InitializeConditions for Delay: '<S8>/Delay1' */
    TempMeasure_DW.Delay1_DSTATE = TempMeasure_P.Delay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S42>/Unit Delay' */
    TempMeasure_DW.UnitDelay_DSTATE_d =
      TempMeasure_P.UnitDelay_InitialCondition_h;

    /* InitializeConditions for Chart: '<S40>/Chart' */
    TempMeasure_Chart_Init(&TempMeasure_DW.sf_Chart_p);

    /* InitializeConditions for Delay: '<S37>/Delay' */
    TempMeasure_DW.Delay_DSTATE[0] = TempMeasure_P.Delay_InitialCondition;
    TempMeasure_DW.Delay_DSTATE[1] = TempMeasure_P.Delay_InitialCondition;
    TempMeasure_DW.Delay_DSTATE[2] = TempMeasure_P.Delay_InitialCondition;

    /* S-Function (Battery_Sfcn_mex): <Root>/Battery Voltage Measurement */
    BatteryMeasure_start();
  }
}

/* Model terminate function */
void TempMeasure_terminate(void)
{
  /* S-Function (IMU_Sfcn_mex): <S2>/IMU Read */
  MDL_IMU_term();

  /* S-Function (Battery_Sfcn_mex): <Root>/Battery Voltage Measurement */
  BatteryMeasure_term();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
