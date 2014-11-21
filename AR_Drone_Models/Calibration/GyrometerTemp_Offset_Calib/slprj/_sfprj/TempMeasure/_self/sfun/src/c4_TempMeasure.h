#ifndef __c4_TempMeasure_h__
#define __c4_TempMeasure_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc4_TempMeasureInstanceStruct
#define typedef_SFc4_TempMeasureInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  uint8_T c4_doSetSimStateSideEffects;
  const mxArray *c4_setSimStateSideEffectsInfo;
} SFc4_TempMeasureInstanceStruct;

#endif                                 /*typedef_SFc4_TempMeasureInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_TempMeasure_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_TempMeasure_get_check_sum(mxArray *plhs[]);
extern void c4_TempMeasure_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
