#ifndef __c3_TempMeasure_h__
#define __c3_TempMeasure_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc3_TempMeasureInstanceStruct
#define typedef_SFc3_TempMeasureInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  uint8_T c3_doSetSimStateSideEffects;
  const mxArray *c3_setSimStateSideEffectsInfo;
} SFc3_TempMeasureInstanceStruct;

#endif                                 /*typedef_SFc3_TempMeasureInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_TempMeasure_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_TempMeasure_get_check_sum(mxArray *plhs[]);
extern void c3_TempMeasure_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
