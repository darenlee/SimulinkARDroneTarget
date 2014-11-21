#ifndef __c7_TempMeasure_h__
#define __c7_TempMeasure_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc7_TempMeasureInstanceStruct
#define typedef_SFc7_TempMeasureInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  uint8_T c7_doSetSimStateSideEffects;
  const mxArray *c7_setSimStateSideEffectsInfo;
} SFc7_TempMeasureInstanceStruct;

#endif                                 /*typedef_SFc7_TempMeasureInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c7_TempMeasure_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c7_TempMeasure_get_check_sum(mxArray *plhs[]);
extern void c7_TempMeasure_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
