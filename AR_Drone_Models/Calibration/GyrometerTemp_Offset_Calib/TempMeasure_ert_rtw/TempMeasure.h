/*
 * File: TempMeasure.h
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

#ifndef RTW_HEADER_TempMeasure_h_
#define RTW_HEADER_TempMeasure_h_
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef TempMeasure_COMMON_INCLUDES_
# define TempMeasure_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "IMU_Navdata.h"
#include "i2c-dev.h"
#endif                                 /* TempMeasure_COMMON_INCLUDES_ */

#include "TempMeasure_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals for system '<S12>/Chart' */
typedef struct {
  real_T output;                       /* '<S12>/Chart' */
} B_Chart_TempMeasure_T;

/* Block states (auto storage) for system '<S12>/Chart' */
typedef struct {
  int32_T sfEvent;                     /* '<S12>/Chart' */
  uint32_T temporalCounter_i1;         /* '<S12>/Chart' */
  uint8_T is_active_c2_TempMeasure;    /* '<S12>/Chart' */
  uint8_T is_c2_TempMeasure;           /* '<S12>/Chart' */
  boolean_T isStable;                  /* '<S12>/Chart' */
} DW_Chart_TempMeasure_T;

/* Block signals (auto storage) */
typedef struct {
  IMU_Packets IMURead_o1;              /* '<S2>/IMU Read' */
  real_T HoldForMSamples;              /* '<S31>/Hold For M Samples' */
  real_T Gain1;                        /* '<Root>/Gain1' */
  real_T HoldForMSamples_l;            /* '<S25>/Hold For M Samples' */
  real_T HoldForMSamples_j;            /* '<S19>/Hold For M Samples' */
  real_T HoldForMSamples_p;            /* '<S10>/Hold For M Samples' */
  real_T HoldForMSamples_f;            /* '<S37>/Hold For M Samples' */
  real_T IfTruewehavegooddataIffalseweha;/* '<S37>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' */
  real_T DigitalClock1;                /* '<Root>/Digital Clock1' */
  real_T y;                            /* '<S8>/Height Calculation' */
  real32_T DeciVoltstoVolts;           /* '<Root>/Deci-Volts to Volts' */
  int32_T IMURead_o2;                  /* '<S2>/IMU Read' */
  int16_T IfTruewehavegooddataIffalsewe_h[3];/* '<S25>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' */
  int16_T IfTruewehavegooddataIffalsewe_a[3];/* '<S19>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' */
  uint16_T IfTruewehavegooddataIffalsewe_l;/* '<S31>/If True, we have good data, If false, we have bad data,  With bad data, use previous good data from N samples ago and hold it on that value for M samples' */
  boolean_T Transition_Detect;         /* '<S36>/Logical Operator' */
  boolean_T Transition_Detect_h;       /* '<S30>/Logical Operator' */
  boolean_T Transition_Detect_m;       /* '<S24>/Logical Operator' */
  boolean_T Transition_Detect_m2;      /* '<S14>/Logical Operator' */
  boolean_T Transition_Detect_b;       /* '<S42>/Logical Operator' */
  B_Chart_TempMeasure_T sf_Chart_p;    /* '<S40>/Chart' */
  B_Chart_TempMeasure_T sf_Chart;      /* '<S34>/Chart' */
  B_Chart_TempMeasure_T sf_Chart_a;    /* '<S28>/Chart' */
  B_Chart_TempMeasure_T sf_Chart_c;    /* '<S22>/Chart' */
  B_Chart_TempMeasure_T sf_Chart_j;    /* '<S12>/Chart' */
} B_TempMeasure_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Delay1_DSTATE;                /* '<S8>/Delay1' */
  real_T Delay_DSTATE[3];              /* '<S37>/Delay' */
  struct {
    void *LoggedData;
  } Accel1_PWORK;                      /* '<Root>/Accel1' */

  struct {
    void *LoggedData;
  } Bodyrates_PWORK;                   /* '<Root>/Body rates' */

  struct {
    void *LoggedData;
  } Magdata_PWORK;                     /* '<Root>/Mag data' */

  struct {
    void *LoggedData;
  } CheckSumValue_PWORK;               /* '<S1>/CheckSum Value' */

  struct {
    void *LoggedData;
  } Height_CalulationI_PWORK;          /* '<S8>/Height_Calulation I' */

  struct {
    void *LoggedData;
  } BatteryVoltage_PWORK;              /* '<Root>/Battery Voltage' */

  int16_T Delay_DSTATE_c[9];           /* '<S25>/Delay' */
  int16_T Delay_DSTATE_k[9];           /* '<S19>/Delay' */
  uint16_T Delay_DSTATE_a[3];          /* '<S31>/Delay' */
  boolean_T UnitDelay_DSTATE;          /* '<S36>/Unit Delay' */
  boolean_T UnitDelay_DSTATE_b;        /* '<S30>/Unit Delay' */
  boolean_T UnitDelay_DSTATE_m;        /* '<S24>/Unit Delay' */
  boolean_T UnitDelay_DSTATE_e;        /* '<S14>/Unit Delay' */
  boolean_T UnitDelay_DSTATE_d;        /* '<S42>/Unit Delay' */
  DW_Chart_TempMeasure_T sf_Chart_p;   /* '<S40>/Chart' */
  DW_Chart_TempMeasure_T sf_Chart;     /* '<S34>/Chart' */
  DW_Chart_TempMeasure_T sf_Chart_a;   /* '<S28>/Chart' */
  DW_Chart_TempMeasure_T sf_Chart_c;   /* '<S22>/Chart' */
  DW_Chart_TempMeasure_T sf_Chart_j;   /* '<S12>/Chart' */
} DW_TempMeasure_T;

/* Parameters (auto storage) */
struct P_TempMeasure_T_ {
  real_T Constant2_Value;              /* Expression: 1
                                        * Referenced by: '<S34>/Constant2'
                                        */
  real_T Constant1_Value;              /* Expression: 1
                                        * Referenced by: '<S36>/Constant1'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S36>/Constant'
                                        */
  real_T HoldForMSamples_Value;        /* Expression: 5
                                        * Referenced by: '<S31>/Hold For M Samples'
                                        */
  real_T Constant2_Value_c;            /* Expression: 1
                                        * Referenced by: '<S28>/Constant2'
                                        */
  real_T Constant1_Value_k;            /* Expression: 1
                                        * Referenced by: '<S30>/Constant1'
                                        */
  real_T Constant_Value_j;             /* Expression: 0
                                        * Referenced by: '<S30>/Constant'
                                        */
  real_T HoldForMSamples_Value_f;      /* Expression: 5
                                        * Referenced by: '<S25>/Hold For M Samples'
                                        */
  real_T Constant2_Value_n;            /* Expression: 1
                                        * Referenced by: '<S22>/Constant2'
                                        */
  real_T Constant1_Value_g;            /* Expression: 1
                                        * Referenced by: '<S24>/Constant1'
                                        */
  real_T Constant_Value_e;             /* Expression: 0
                                        * Referenced by: '<S24>/Constant'
                                        */
  real_T HoldForMSamples_Value_fw;     /* Expression: 5
                                        * Referenced by: '<S19>/Hold For M Samples'
                                        */
  real_T Constant1_Value_i;            /* Expression: 1
                                        * Referenced by: '<S14>/Constant1'
                                        */
  real_T Constant_Value_p;             /* Expression: 0
                                        * Referenced by: '<S14>/Constant'
                                        */
  real_T HoldForMSamples_Value_h;      /* Expression: 5
                                        * Referenced by: '<S10>/Hold For M Samples'
                                        */
  real_T Delay1_InitialCondition;      /* Expression: 0
                                        * Referenced by: '<S8>/Delay1'
                                        */
  real_T Constant2_Value_j;            /* Expression: 1
                                        * Referenced by: '<S40>/Constant2'
                                        */
  real_T Constant1_Value_p;            /* Expression: 1
                                        * Referenced by: '<S42>/Constant1'
                                        */
  real_T Constant_Value_k;             /* Expression: 0
                                        * Referenced by: '<S42>/Constant'
                                        */
  real_T HoldForMSamples_Value_p;      /* Expression: 5
                                        * Referenced by: '<S37>/Hold For M Samples'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 0
                                        * Referenced by: '<S37>/Delay'
                                        */
  real32_T DeciVoltstoVolts_Gain;      /* Computed Parameter: DeciVoltstoVolts_Gain
                                        * Referenced by: '<Root>/Deci-Volts to Volts'
                                        */
  int32_T Constant_Value_c;            /* Computed Parameter: Constant_Value_c
                                        * Referenced by: '<S33>/Constant'
                                        */
  int32_T Constant_Value_o;            /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S27>/Constant'
                                        */
  int32_T Constant_Value_pc;           /* Computed Parameter: Constant_Value_pc
                                        * Referenced by: '<S21>/Constant'
                                        */
  int32_T Constant_Value_a;            /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S11>/Constant'
                                        */
  int32_T Constant_Value_h;            /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S39>/Constant'
                                        */
  uint32_T Delay_DelayLength;          /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<S31>/Delay'
                                        */
  uint32_T Delay_DelayLength_n;        /* Computed Parameter: Delay_DelayLength_n
                                        * Referenced by: '<S25>/Delay'
                                        */
  uint32_T Delay_DelayLength_a;        /* Computed Parameter: Delay_DelayLength_a
                                        * Referenced by: '<S19>/Delay'
                                        */
  uint32_T Delay1_DelayLength;         /* Computed Parameter: Delay1_DelayLength
                                        * Referenced by: '<S8>/Delay1'
                                        */
  uint32_T Delay_DelayLength_p;        /* Computed Parameter: Delay_DelayLength_p
                                        * Referenced by: '<S37>/Delay'
                                        */
  int16_T Constant1_Value_c;           /* Computed Parameter: Constant1_Value_c
                                        * Referenced by: '<Root>/Constant1'
                                        */
  int16_T Delay_InitialCondition_c;    /* Computed Parameter: Delay_InitialCondition_c
                                        * Referenced by: '<S25>/Delay'
                                        */
  int16_T Delay_InitialCondition_i;    /* Computed Parameter: Delay_InitialCondition_i
                                        * Referenced by: '<S19>/Delay'
                                        */
  uint16_T Delay_InitialCondition_e;   /* Computed Parameter: Delay_InitialCondition_e
                                        * Referenced by: '<S31>/Delay'
                                        */
  int16_T Gain1_Gain;                  /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<Root>/Gain1'
                                        */
  boolean_T UnitDelay_InitialCondition;/* Computed Parameter: UnitDelay_InitialCondition
                                        * Referenced by: '<S36>/Unit Delay'
                                        */
  boolean_T UnitDelay_InitialCondition_f;/* Computed Parameter: UnitDelay_InitialCondition_f
                                          * Referenced by: '<S30>/Unit Delay'
                                          */
  boolean_T UnitDelay_InitialCondition_fz;/* Computed Parameter: UnitDelay_InitialCondition_fz
                                           * Referenced by: '<S24>/Unit Delay'
                                           */
  boolean_T UnitDelay_InitialCondition_j;/* Computed Parameter: UnitDelay_InitialCondition_j
                                          * Referenced by: '<S14>/Unit Delay'
                                          */
  boolean_T UnitDelay_InitialCondition_h;/* Computed Parameter: UnitDelay_InitialCondition_h
                                          * Referenced by: '<S42>/Unit Delay'
                                          */
};

/* Real-time Model Data Structure */
struct tag_RTM_TempMeasure_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTick2;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_TempMeasure_T TempMeasure_P;

/* Block signals (auto storage) */
extern B_TempMeasure_T TempMeasure_B;

/* Block states (auto storage) */
extern DW_TempMeasure_T TempMeasure_DW;

/* External function called from main */
extern void TempMeasure_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void TempMeasure_SetEventsForThisBaseStep(boolean_T *eventFlags);
extern void TempMeasure_initialize(void);
extern void TempMeasure_step0(void);
extern void TempMeasure_step1(void);
extern void TempMeasure_step2(void);
extern void TempMeasure_terminate(void);

/* Real-time Model object */
extern RT_MODEL_TempMeasure_T *const TempMeasure_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'TempMeasure'
 * '<S1>'   : 'TempMeasure/CheckSum Pre-Processing'
 * '<S2>'   : 'TempMeasure/Inertial Measurement'
 * '<S3>'   : 'TempMeasure/CheckSum Pre-Processing/Accelerometer Processing'
 * '<S4>'   : 'TempMeasure/CheckSum Pre-Processing/Connect this to temp this can lead to interesting behavior'
 * '<S5>'   : 'TempMeasure/CheckSum Pre-Processing/Magnetometer'
 * '<S6>'   : 'TempMeasure/CheckSum Pre-Processing/RateGyro Processing'
 * '<S7>'   : 'TempMeasure/CheckSum Pre-Processing/Temp'
 * '<S8>'   : 'TempMeasure/CheckSum Pre-Processing/Ultrasound Processing'
 * '<S9>'   : 'TempMeasure/CheckSum Pre-Processing/Accelerometer Processing/Calculate Accel Data'
 * '<S10>'  : 'TempMeasure/CheckSum Pre-Processing/Accelerometer Processing/CheckSum Correction'
 * '<S11>'  : 'TempMeasure/CheckSum Pre-Processing/Accelerometer Processing/CheckSum Correction/Compare To Zero'
 * '<S12>'  : 'TempMeasure/CheckSum Pre-Processing/Accelerometer Processing/CheckSum Correction/Generate Sample Holding Pulse'
 * '<S13>'  : 'TempMeasure/CheckSum Pre-Processing/Accelerometer Processing/CheckSum Correction/Generate Sample Holding Pulse/Chart'
 * '<S14>'  : 'TempMeasure/CheckSum Pre-Processing/Accelerometer Processing/CheckSum Correction/Generate Sample Holding Pulse/Transition Logic Detection'
 * '<S15>'  : 'TempMeasure/CheckSum Pre-Processing/Connect this to temp this can lead to interesting behavior/CheckSum Correction'
 * '<S16>'  : 'TempMeasure/CheckSum Pre-Processing/Connect this to temp this can lead to interesting behavior/CheckSum Correction/Generate Sample Holding Pulse'
 * '<S17>'  : 'TempMeasure/CheckSum Pre-Processing/Connect this to temp this can lead to interesting behavior/CheckSum Correction/Generate Sample Holding Pulse/Chart'
 * '<S18>'  : 'TempMeasure/CheckSum Pre-Processing/Connect this to temp this can lead to interesting behavior/CheckSum Correction/Generate Sample Holding Pulse/Transition Logic Detection'
 * '<S19>'  : 'TempMeasure/CheckSum Pre-Processing/Magnetometer/CheckSum Correction'
 * '<S20>'  : 'TempMeasure/CheckSum Pre-Processing/Magnetometer/Process Raw Mag Data'
 * '<S21>'  : 'TempMeasure/CheckSum Pre-Processing/Magnetometer/CheckSum Correction/Compare To Zero'
 * '<S22>'  : 'TempMeasure/CheckSum Pre-Processing/Magnetometer/CheckSum Correction/Generate Sample Holding Pulse'
 * '<S23>'  : 'TempMeasure/CheckSum Pre-Processing/Magnetometer/CheckSum Correction/Generate Sample Holding Pulse/Chart'
 * '<S24>'  : 'TempMeasure/CheckSum Pre-Processing/Magnetometer/CheckSum Correction/Generate Sample Holding Pulse/Transition Logic Detection'
 * '<S25>'  : 'TempMeasure/CheckSum Pre-Processing/RateGyro Processing/CheckSum Correction'
 * '<S26>'  : 'TempMeasure/CheckSum Pre-Processing/RateGyro Processing/Process Data'
 * '<S27>'  : 'TempMeasure/CheckSum Pre-Processing/RateGyro Processing/CheckSum Correction/Compare To Zero'
 * '<S28>'  : 'TempMeasure/CheckSum Pre-Processing/RateGyro Processing/CheckSum Correction/Generate Sample Holding Pulse'
 * '<S29>'  : 'TempMeasure/CheckSum Pre-Processing/RateGyro Processing/CheckSum Correction/Generate Sample Holding Pulse/Chart'
 * '<S30>'  : 'TempMeasure/CheckSum Pre-Processing/RateGyro Processing/CheckSum Correction/Generate Sample Holding Pulse/Transition Logic Detection'
 * '<S31>'  : 'TempMeasure/CheckSum Pre-Processing/Temp/CheckSum Correction'
 * '<S32>'  : 'TempMeasure/CheckSum Pre-Processing/Temp/Process Raw Mag Data'
 * '<S33>'  : 'TempMeasure/CheckSum Pre-Processing/Temp/CheckSum Correction/Compare To Zero'
 * '<S34>'  : 'TempMeasure/CheckSum Pre-Processing/Temp/CheckSum Correction/Generate Sample Holding Pulse'
 * '<S35>'  : 'TempMeasure/CheckSum Pre-Processing/Temp/CheckSum Correction/Generate Sample Holding Pulse/Chart'
 * '<S36>'  : 'TempMeasure/CheckSum Pre-Processing/Temp/CheckSum Correction/Generate Sample Holding Pulse/Transition Logic Detection'
 * '<S37>'  : 'TempMeasure/CheckSum Pre-Processing/Ultrasound Processing/CheckSum Correction'
 * '<S38>'  : 'TempMeasure/CheckSum Pre-Processing/Ultrasound Processing/Height Calculation'
 * '<S39>'  : 'TempMeasure/CheckSum Pre-Processing/Ultrasound Processing/CheckSum Correction/Compare To Zero'
 * '<S40>'  : 'TempMeasure/CheckSum Pre-Processing/Ultrasound Processing/CheckSum Correction/Generate Sample Holding Pulse'
 * '<S41>'  : 'TempMeasure/CheckSum Pre-Processing/Ultrasound Processing/CheckSum Correction/Generate Sample Holding Pulse/Chart'
 * '<S42>'  : 'TempMeasure/CheckSum Pre-Processing/Ultrasound Processing/CheckSum Correction/Generate Sample Holding Pulse/Transition Logic Detection'
 */
#endif                                 /* RTW_HEADER_TempMeasure_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
