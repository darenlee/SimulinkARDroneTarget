/* Include files */

#include "TempMeasure_sfun.h"
#include "TempMeasure_sfun_debug_macros.h"
#include "c1_TempMeasure.h"
#include "c2_TempMeasure.h"
#include "c3_TempMeasure.h"
#include "c4_TempMeasure.h"
#include "c5_TempMeasure.h"
#include "c7_TempMeasure.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _TempMeasureMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void TempMeasure_initializer(void)
{
}

void TempMeasure_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_TempMeasure_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_TempMeasure_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_TempMeasure_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==3) {
    c3_TempMeasure_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_TempMeasure_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_TempMeasure_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==7) {
    c7_TempMeasure_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_TempMeasure_process_testpoint_info_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char machineName[128];
  if (nrhs < 3 || !mxIsChar(prhs[0]) || !mxIsChar(prhs[1]))
    return 0;

  /* Possible call to get testpoint info. */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_testpoint_info"))
    return 0;
  mxGetString(prhs[1], machineName, sizeof(machineName)/sizeof(char));
  machineName[(sizeof(machineName)/sizeof(char)-1)] = '\0';
  if (!strcmp(machineName, "TempMeasure")) {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
    switch (chartFileNumber) {
     case 2:
      {
        extern mxArray *sf_c2_TempMeasure_get_testpoint_info(void);
        plhs[0] = sf_c2_TempMeasure_get_testpoint_info();
        break;
      }

     case 3:
      {
        extern mxArray *sf_c3_TempMeasure_get_testpoint_info(void);
        plhs[0] = sf_c3_TempMeasure_get_testpoint_info();
        break;
      }

     case 4:
      {
        extern mxArray *sf_c4_TempMeasure_get_testpoint_info(void);
        plhs[0] = sf_c4_TempMeasure_get_testpoint_info();
        break;
      }

     case 5:
      {
        extern mxArray *sf_c5_TempMeasure_get_testpoint_info(void);
        plhs[0] = sf_c5_TempMeasure_get_testpoint_info();
        break;
      }

     case 7:
      {
        extern mxArray *sf_c7_TempMeasure_get_testpoint_info(void);
        plhs[0] = sf_c7_TempMeasure_get_testpoint_info();
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }

    return 1;
  }

  return 0;

#else

  return 0;

#endif

}

unsigned int sf_TempMeasure_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4266605280U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2369921966U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(505871293U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(228502086U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2062674771U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(529154531U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3297852929U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(739030019U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_TempMeasure_get_check_sum(mxArray *plhs[]);
          sf_c1_TempMeasure_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_TempMeasure_get_check_sum(mxArray *plhs[]);
          sf_c2_TempMeasure_get_check_sum(plhs);
          break;
        }

       case 3:
        {
          extern void sf_c3_TempMeasure_get_check_sum(mxArray *plhs[]);
          sf_c3_TempMeasure_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_TempMeasure_get_check_sum(mxArray *plhs[]);
          sf_c4_TempMeasure_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_TempMeasure_get_check_sum(mxArray *plhs[]);
          sf_c5_TempMeasure_get_check_sum(plhs);
          break;
        }

       case 7:
        {
          extern void sf_c7_TempMeasure_get_check_sum(mxArray *plhs[]);
          sf_c7_TempMeasure_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3084158392U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2524169757U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2812955680U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(245732821U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3579837317U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2495234424U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3958470672U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4272806143U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_TempMeasure_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "NaTkOmYp2SK41NOQumL4xE") == 0) {
          extern mxArray *sf_c1_TempMeasure_get_autoinheritance_info(void);
          plhs[0] = sf_c1_TempMeasure_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "bShKk9L4dy4nqMKmXVAmYB") == 0) {
          extern mxArray *sf_c2_TempMeasure_get_autoinheritance_info(void);
          plhs[0] = sf_c2_TempMeasure_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 3:
      {
        if (strcmp(aiChksum, "bShKk9L4dy4nqMKmXVAmYB") == 0) {
          extern mxArray *sf_c3_TempMeasure_get_autoinheritance_info(void);
          plhs[0] = sf_c3_TempMeasure_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "bShKk9L4dy4nqMKmXVAmYB") == 0) {
          extern mxArray *sf_c4_TempMeasure_get_autoinheritance_info(void);
          plhs[0] = sf_c4_TempMeasure_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "bShKk9L4dy4nqMKmXVAmYB") == 0) {
          extern mxArray *sf_c5_TempMeasure_get_autoinheritance_info(void);
          plhs[0] = sf_c5_TempMeasure_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 7:
      {
        if (strcmp(aiChksum, "bShKk9L4dy4nqMKmXVAmYB") == 0) {
          extern mxArray *sf_c7_TempMeasure_get_autoinheritance_info(void);
          plhs[0] = sf_c7_TempMeasure_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_TempMeasure_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_TempMeasure_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_TempMeasure_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray *sf_c2_TempMeasure_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_TempMeasure_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 3:
      {
        extern const mxArray *sf_c3_TempMeasure_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c3_TempMeasure_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_TempMeasure_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_TempMeasure_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_TempMeasure_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_TempMeasure_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 7:
      {
        extern const mxArray *sf_c7_TempMeasure_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c7_TempMeasure_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_TempMeasure_third_party_uses_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "kRhN4hmHPoLvlawrR28tZ") == 0) {
          extern mxArray *sf_c1_TempMeasure_third_party_uses_info(void);
          plhs[0] = sf_c1_TempMeasure_third_party_uses_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c2_TempMeasure_third_party_uses_info(void);
          plhs[0] = sf_c2_TempMeasure_third_party_uses_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c3_TempMeasure_third_party_uses_info(void);
          plhs[0] = sf_c3_TempMeasure_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c4_TempMeasure_third_party_uses_info(void);
          plhs[0] = sf_c4_TempMeasure_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c5_TempMeasure_third_party_uses_info(void);
          plhs[0] = sf_c5_TempMeasure_third_party_uses_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c7_TempMeasure_third_party_uses_info(void);
          plhs[0] = sf_c7_TempMeasure_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_TempMeasure_updateBuildInfo_args_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(tpChksum, "kRhN4hmHPoLvlawrR28tZ") == 0) {
          extern mxArray *sf_c1_TempMeasure_updateBuildInfo_args_info(void);
          plhs[0] = sf_c1_TempMeasure_updateBuildInfo_args_info();
          break;
        }
      }

     case 2:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c2_TempMeasure_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_TempMeasure_updateBuildInfo_args_info();
          break;
        }
      }

     case 3:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c3_TempMeasure_updateBuildInfo_args_info(void);
          plhs[0] = sf_c3_TempMeasure_updateBuildInfo_args_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c4_TempMeasure_updateBuildInfo_args_info(void);
          plhs[0] = sf_c4_TempMeasure_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c5_TempMeasure_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_TempMeasure_updateBuildInfo_args_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "XOAqxGOQvAHXu1V3yUSJFD") == 0) {
          extern mxArray *sf_c7_TempMeasure_updateBuildInfo_args_info(void);
          plhs[0] = sf_c7_TempMeasure_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void TempMeasure_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _TempMeasureMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "TempMeasure","sfun",0,6,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_TempMeasureMachineNumber_,
    0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,_TempMeasureMachineNumber_,
    0);
}

void TempMeasure_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_TempMeasure_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("TempMeasure",
      "TempMeasure");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_TempMeasure_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
