#ifndef __c2_TempMeasure_h__
#define __c2_TempMeasure_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_TempMeasureInstanceStruct
#define typedef_SFc2_TempMeasureInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  uint8_T c2_doSetSimStateSideEffects;
  const mxArray *c2_setSimStateSideEffectsInfo;
} SFc2_TempMeasureInstanceStruct;

#endif                                 /*typedef_SFc2_TempMeasureInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_TempMeasure_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_TempMeasure_get_check_sum(mxArray *plhs[]);
extern void c2_TempMeasure_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
