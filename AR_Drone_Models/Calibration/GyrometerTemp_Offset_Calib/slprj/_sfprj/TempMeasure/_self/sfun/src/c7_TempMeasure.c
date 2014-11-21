/* Include files */

#include <stddef.h>
#include "blas.h"
#include "TempMeasure_sfun.h"
#include "c7_TempMeasure.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "TempMeasure_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c7_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c7_IN_Begin_State              ((uint8_T)1U)
#define c7_IN_Begin_State0             ((uint8_T)2U)
#define c7_IN_End_State                ((uint8_T)3U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c7_debug_family_names[2] = { "nargin", "nargout" };

static const char * c7_b_debug_family_names[2] = { "nargin", "nargout" };

static const char * c7_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c7_d_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c7_e_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c7_f_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c7_g_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c7_h_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c7_i_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c7_j_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c7_k_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static boolean_T c7_dataWrittenToVector[1];

/* Function Declarations */
static void initialize_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance);
static void initialize_params_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance);
static void enable_c7_TempMeasure(SFc7_TempMeasureInstanceStruct *chartInstance);
static void disable_c7_TempMeasure(SFc7_TempMeasureInstanceStruct *chartInstance);
static void c7_update_debugger_state_c7_TempMeasure
  (SFc7_TempMeasureInstanceStruct *chartInstance);
static void ext_mode_exec_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c7_TempMeasure
  (SFc7_TempMeasureInstanceStruct *chartInstance);
static void set_sim_state_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_st);
static void c7_set_sim_state_side_effects_c7_TempMeasure
  (SFc7_TempMeasureInstanceStruct *chartInstance);
static void finalize_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance);
static void sf_gateway_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance);
static void initSimStructsc7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber, uint32_T c7_instanceNumber);
static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData);
static real_T c7_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct *chartInstance,
  const mxArray *c7_nargout, const char_T *c7_identifier);
static real_T c7_b_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static boolean_T c7_c_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static int32_T c7_d_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static uint8_T c7_e_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_is_active_c7_TempMeasure, const char_T
  *c7_identifier);
static uint8_T c7_f_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static uint32_T c7_g_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_temporalCounter_i1, const char_T
  *c7_identifier);
static uint32_T c7_h_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static const mxArray *c7_i_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_b_setSimStateSideEffectsInfo, const char_T
  *c7_identifier);
static const mxArray *c7_j_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_updateDataWrittenToVector(SFc7_TempMeasureInstanceStruct
  *chartInstance, uint32_T c7_vectorIndex);
static void init_dsm_address_info(SFc7_TempMeasureInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance)
{
  int32_T *c7_sfEvent;
  uint8_T *c7_is_active_c7_TempMeasure;
  uint8_T *c7_is_c7_TempMeasure;
  uint32_T *c7_temporalCounter_i1;
  c7_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 4);
  c7_is_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c7_is_active_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c7_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c7_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c7_doSetSimStateSideEffects = 0U;
  chartInstance->c7_setSimStateSideEffectsInfo = NULL;
  *c7_temporalCounter_i1 = 0U;
  *c7_is_active_c7_TempMeasure = 0U;
  *c7_is_c7_TempMeasure = c7_IN_NO_ACTIVE_CHILD;
}

static void initialize_params_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c7_TempMeasure(SFc7_TempMeasureInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c7_TempMeasure(SFc7_TempMeasureInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c7_update_debugger_state_c7_TempMeasure
  (SFc7_TempMeasureInstanceStruct *chartInstance)
{
  uint32_T c7_prevAniVal;
  uint8_T *c7_is_active_c7_TempMeasure;
  uint8_T *c7_is_c7_TempMeasure;
  int32_T *c7_sfEvent;
  c7_is_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c7_is_active_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c7_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  c7_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*c7_is_active_c7_TempMeasure == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 5U, *c7_sfEvent);
  }

  if (*c7_is_c7_TempMeasure == c7_IN_Begin_State0) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *c7_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *c7_sfEvent);
  }

  if (*c7_is_c7_TempMeasure == c7_IN_Begin_State) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *c7_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c7_sfEvent);
  }

  if (*c7_is_c7_TempMeasure == c7_IN_End_State) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *c7_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *c7_sfEvent);
  }

  _SFD_SET_ANIMATION(c7_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance)
{
  c7_update_debugger_state_c7_TempMeasure(chartInstance);
}

static const mxArray *get_sim_state_c7_TempMeasure
  (SFc7_TempMeasureInstanceStruct *chartInstance)
{
  const mxArray *c7_st;
  const mxArray *c7_y = NULL;
  real_T c7_hoistedGlobal;
  real_T c7_u;
  const mxArray *c7_b_y = NULL;
  uint8_T c7_b_hoistedGlobal;
  uint8_T c7_b_u;
  const mxArray *c7_c_y = NULL;
  uint8_T c7_c_hoistedGlobal;
  uint8_T c7_c_u;
  const mxArray *c7_d_y = NULL;
  uint32_T c7_d_hoistedGlobal;
  uint32_T c7_d_u;
  const mxArray *c7_e_y = NULL;
  real_T *c7_output;
  uint8_T *c7_is_active_c7_TempMeasure;
  uint8_T *c7_is_c7_TempMeasure;
  uint32_T *c7_temporalCounter_i1;
  c7_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 4);
  c7_output = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c7_is_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c7_is_active_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c7_st = NULL;
  c7_st = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_createcellmatrix(4, 1), false);
  c7_hoistedGlobal = *c7_output;
  c7_u = c7_hoistedGlobal;
  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c7_y, 0, c7_b_y);
  c7_b_hoistedGlobal = *c7_is_active_c7_TempMeasure;
  c7_b_u = c7_b_hoistedGlobal;
  c7_c_y = NULL;
  sf_mex_assign(&c7_c_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c7_y, 1, c7_c_y);
  c7_c_hoistedGlobal = *c7_is_c7_TempMeasure;
  c7_c_u = c7_c_hoistedGlobal;
  c7_d_y = NULL;
  sf_mex_assign(&c7_d_y, sf_mex_create("y", &c7_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c7_y, 2, c7_d_y);
  c7_d_hoistedGlobal = *c7_temporalCounter_i1;
  c7_d_u = c7_d_hoistedGlobal;
  c7_e_y = NULL;
  sf_mex_assign(&c7_e_y, sf_mex_create("y", &c7_d_u, 7, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c7_y, 3, c7_e_y);
  sf_mex_assign(&c7_st, c7_y, false);
  return c7_st;
}

static void set_sim_state_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_st)
{
  const mxArray *c7_u;
  real_T *c7_output;
  uint8_T *c7_is_active_c7_TempMeasure;
  uint8_T *c7_is_c7_TempMeasure;
  uint32_T *c7_temporalCounter_i1;
  c7_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 4);
  c7_output = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c7_is_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c7_is_active_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c7_u = sf_mex_dup(c7_st);
  *c7_output = c7_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u,
    0)), "output");
  *c7_is_active_c7_TempMeasure = c7_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c7_u, 1)), "is_active_c7_TempMeasure");
  *c7_is_c7_TempMeasure = c7_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c7_u, 2)), "is_c7_TempMeasure");
  *c7_temporalCounter_i1 = c7_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c7_u, 3)), "temporalCounter_i1");
  sf_mex_assign(&chartInstance->c7_setSimStateSideEffectsInfo,
                c7_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c7_u, 4)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c7_u);
  chartInstance->c7_doSetSimStateSideEffects = 1U;
  c7_update_debugger_state_c7_TempMeasure(chartInstance);
  sf_mex_destroy(&c7_st);
}

static void c7_set_sim_state_side_effects_c7_TempMeasure
  (SFc7_TempMeasureInstanceStruct *chartInstance)
{
  uint32_T *c7_temporalCounter_i1;
  uint8_T *c7_is_c7_TempMeasure;
  c7_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 4);
  c7_is_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  if (chartInstance->c7_doSetSimStateSideEffects != 0) {
    if (*c7_is_c7_TempMeasure == c7_IN_Begin_State) {
      if (sf_mex_sub(chartInstance->c7_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 2) == 0.0) {
        *c7_temporalCounter_i1 = 0U;
      }
    }

    chartInstance->c7_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c7_setSimStateSideEffectsInfo);
}

static void sf_gateway_c7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance)
{
  uint32_T c7_debug_family_var_map[2];
  real_T c7_nargin = 0.0;
  real_T c7_nargout = 0.0;
  uint32_T c7_b_debug_family_var_map[3];
  real_T c7_b_nargin = 0.0;
  real_T c7_b_nargout = 1.0;
  boolean_T c7_out;
  int8_T c7_temp;
  real_T c7_c_nargin = 0.0;
  real_T c7_c_nargout = 0.0;
  real_T c7_d_nargin = 0.0;
  real_T c7_d_nargout = 1.0;
  boolean_T c7_b_out;
  real_T c7_e_nargin = 0.0;
  real_T c7_e_nargout = 0.0;
  real_T c7_f_nargin = 0.0;
  real_T c7_f_nargout = 1.0;
  boolean_T c7_c_out;
  real_T c7_g_nargin = 0.0;
  real_T c7_g_nargout = 0.0;
  real_T c7_h_nargin = 0.0;
  real_T c7_h_nargout = 1.0;
  boolean_T c7_d_out;
  real_T c7_i_nargin = 0.0;
  real_T c7_i_nargout = 0.0;
  real_T *c7_output;
  uint8_T *c7_is_c7_TempMeasure;
  uint8_T *c7_is_active_c7_TempMeasure;
  boolean_T *c7_if_transition;
  uint32_T *c7_temporalCounter_i1;
  real_T *c7_HoldDataTicks;
  int32_T *c7_sfEvent;
  c7_temporalCounter_i1 = (uint32_T *)ssGetDWork(chartInstance->S, 4);
  c7_HoldDataTicks = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c7_if_transition = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c7_output = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c7_is_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c7_is_active_c7_TempMeasure = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c7_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  c7_set_sim_state_side_effects_c7_TempMeasure(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 5U, *c7_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c7_output, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c7_if_transition, 1U);
  _SFD_DATA_RANGE_CHECK(*c7_HoldDataTicks, 2U);
  *c7_sfEvent = CALL_EVENT;
  if (*c7_temporalCounter_i1 < MAX_uint32_T) {
    (*c7_temporalCounter_i1)++;
  }

  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 5U, *c7_sfEvent);
  if (*c7_is_active_c7_TempMeasure == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 5U, *c7_sfEvent);
    *c7_is_active_c7_TempMeasure = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, *c7_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *c7_sfEvent);
    *c7_is_c7_TempMeasure = c7_IN_Begin_State0;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *c7_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c7_debug_family_names,
      c7_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargin, 0U, c7_sf_marshallOut,
      c7_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargout, 1U, c7_sf_marshallOut,
      c7_sf_marshallIn);
    *c7_output = 0.0;
    c7_updateDataWrittenToVector(chartInstance, 0U);
    _SFD_DATA_RANGE_CHECK(*c7_output, 0U);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    switch (*c7_is_c7_TempMeasure) {
     case c7_IN_Begin_State:
      CV_CHART_EVAL(5, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, *c7_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c7_e_debug_family_names,
        c7_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_nargin, 0U, c7_sf_marshallOut,
        c7_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_nargout, 1U, c7_sf_marshallOut,
        c7_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_out, 2U, c7_b_sf_marshallOut,
        c7_b_sf_marshallIn);
      c7_temp = (int8_T)(*c7_temporalCounter_i1 >= _SFD_TRANS_TEMPORAL_THRESHOLD
                         ((uint32_T)*c7_HoldDataTicks, 32U, 1U));
      c7_out = CV_EML_IF(1, 0, 0, c7_temp);
      _SFD_SYMBOL_SCOPE_POP();
      if (c7_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *c7_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c7_sfEvent);
        *c7_is_c7_TempMeasure = c7_IN_End_State;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *c7_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c7_c_debug_family_names,
          c7_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_c_nargin, 0U, c7_sf_marshallOut,
          c7_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_c_nargout, 1U,
          c7_sf_marshallOut, c7_sf_marshallIn);
        *c7_output = 0.0;
        c7_updateDataWrittenToVector(chartInstance, 0U);
        _SFD_DATA_RANGE_CHECK(*c7_output, 0U);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, *c7_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c7_g_debug_family_names,
          c7_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_d_nargin, 0U, c7_sf_marshallOut,
          c7_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_d_nargout, 1U,
          c7_sf_marshallOut, c7_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_b_out, 2U, c7_b_sf_marshallOut,
          c7_b_sf_marshallIn);
        c7_b_out = CV_EML_IF(2, 0, 0, (real_T)*c7_if_transition == 1.0);
        _SFD_SYMBOL_SCOPE_POP();
        if (c7_b_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, *c7_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c7_sfEvent);
          *c7_is_c7_TempMeasure = c7_IN_Begin_State;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *c7_sfEvent);
          *c7_temporalCounter_i1 = 0U;
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c7_b_debug_family_names,
            c7_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_e_nargin, 0U,
            c7_sf_marshallOut, c7_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_e_nargout, 1U,
            c7_sf_marshallOut, c7_sf_marshallIn);
          *c7_output = 1.0;
          c7_updateDataWrittenToVector(chartInstance, 0U);
          _SFD_DATA_RANGE_CHECK(*c7_output, 0U);
          _SFD_SYMBOL_SCOPE_POP();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, *c7_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *c7_sfEvent);
      break;

     case c7_IN_Begin_State0:
      CV_CHART_EVAL(5, 0, 2);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U, *c7_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c7_d_debug_family_names,
        c7_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_f_nargin, 0U, c7_sf_marshallOut,
        c7_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_f_nargout, 1U, c7_sf_marshallOut,
        c7_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_c_out, 2U, c7_b_sf_marshallOut,
        c7_b_sf_marshallIn);
      c7_c_out = CV_EML_IF(4, 0, 0, (real_T)*c7_if_transition == 1.0);
      _SFD_SYMBOL_SCOPE_POP();
      if (c7_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, *c7_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *c7_sfEvent);
        *c7_is_c7_TempMeasure = c7_IN_Begin_State;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *c7_sfEvent);
        *c7_temporalCounter_i1 = 0U;
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c7_b_debug_family_names,
          c7_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_g_nargin, 0U, c7_sf_marshallOut,
          c7_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_g_nargout, 1U,
          c7_sf_marshallOut, c7_sf_marshallIn);
        *c7_output = 1.0;
        c7_updateDataWrittenToVector(chartInstance, 0U);
        _SFD_DATA_RANGE_CHECK(*c7_output, 0U);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, *c7_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *c7_sfEvent);
      break;

     case c7_IN_End_State:
      CV_CHART_EVAL(5, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U, *c7_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c7_f_debug_family_names,
        c7_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_h_nargin, 0U, c7_sf_marshallOut,
        c7_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_h_nargout, 1U, c7_sf_marshallOut,
        c7_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_d_out, 2U, c7_b_sf_marshallOut,
        c7_b_sf_marshallIn);
      c7_d_out = CV_EML_IF(3, 0, 0, (real_T)*c7_if_transition == 1.0);
      _SFD_SYMBOL_SCOPE_POP();
      if (c7_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, *c7_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *c7_sfEvent);
        *c7_is_c7_TempMeasure = c7_IN_Begin_State;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *c7_sfEvent);
        *c7_temporalCounter_i1 = 0U;
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c7_b_debug_family_names,
          c7_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_i_nargin, 0U, c7_sf_marshallOut,
          c7_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_i_nargout, 1U,
          c7_sf_marshallOut, c7_sf_marshallIn);
        *c7_output = 1.0;
        c7_updateDataWrittenToVector(chartInstance, 0U);
        _SFD_DATA_RANGE_CHECK(*c7_output, 0U);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U, *c7_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *c7_sfEvent);
      break;

     default:
      CV_CHART_EVAL(5, 0, 0);
      *c7_is_c7_TempMeasure = c7_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c7_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, *c7_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_TempMeasureMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc7_TempMeasure(SFc7_TempMeasureInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber, uint32_T c7_instanceNumber)
{
  (void)c7_machineNumber;
  (void)c7_chartNumber;
  (void)c7_instanceNumber;
}

static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  real_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_TempMeasureInstanceStruct *chartInstance;
  chartInstance = (SFc7_TempMeasureInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(real_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static real_T c7_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct *chartInstance,
  const mxArray *c7_nargout, const char_T *c7_identifier)
{
  real_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_nargout), &c7_thisId);
  sf_mex_destroy(&c7_nargout);
  return c7_y;
}

static real_T c7_b_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  real_T c7_y;
  real_T c7_d0;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_d0, 1, 0, 0U, 0, 0U, 0);
  c7_y = c7_d0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_nargout;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y;
  SFc7_TempMeasureInstanceStruct *chartInstance;
  chartInstance = (SFc7_TempMeasureInstanceStruct *)chartInstanceVoid;
  c7_nargout = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_nargout), &c7_thisId);
  sf_mex_destroy(&c7_nargout);
  *(real_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  boolean_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_TempMeasureInstanceStruct *chartInstance;
  chartInstance = (SFc7_TempMeasureInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(boolean_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static boolean_T c7_c_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  boolean_T c7_y;
  boolean_T c7_b0;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_b0, 1, 11, 0U, 0, 0U, 0);
  c7_y = c7_b0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_sf_internal_predicateOutput;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  boolean_T c7_y;
  SFc7_TempMeasureInstanceStruct *chartInstance;
  chartInstance = (SFc7_TempMeasureInstanceStruct *)chartInstanceVoid;
  c7_sf_internal_predicateOutput = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_sf_internal_predicateOutput), &c7_thisId);
  sf_mex_destroy(&c7_sf_internal_predicateOutput);
  *(boolean_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

const mxArray *sf_c7_TempMeasure_get_eml_resolved_functions_info(void)
{
  const mxArray *c7_nameCaptureInfo = NULL;
  c7_nameCaptureInfo = NULL;
  sf_mex_assign(&c7_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c7_nameCaptureInfo;
}

static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_TempMeasureInstanceStruct *chartInstance;
  chartInstance = (SFc7_TempMeasureInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(int32_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static int32_T c7_d_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  int32_T c7_y;
  int32_T c7_i0;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_i0, 1, 6, 0U, 0, 0U, 0);
  c7_y = c7_i0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_sfEvent;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  int32_T c7_y;
  SFc7_TempMeasureInstanceStruct *chartInstance;
  chartInstance = (SFc7_TempMeasureInstanceStruct *)chartInstanceVoid;
  c7_sfEvent = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_sfEvent), &c7_thisId);
  sf_mex_destroy(&c7_sfEvent);
  *(int32_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static uint8_T c7_e_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_is_active_c7_TempMeasure, const char_T
  *c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_is_active_c7_TempMeasure), &c7_thisId);
  sf_mex_destroy(&c7_is_active_c7_TempMeasure);
  return c7_y;
}

static uint8_T c7_f_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  uint8_T c7_u0;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_u0, 1, 3, 0U, 0, 0U, 0);
  c7_y = c7_u0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static uint32_T c7_g_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_temporalCounter_i1, const char_T
  *c7_identifier)
{
  uint32_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_temporalCounter_i1),
    &c7_thisId);
  sf_mex_destroy(&c7_temporalCounter_i1);
  return c7_y;
}

static uint32_T c7_h_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint32_T c7_y;
  uint32_T c7_u1;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_u1, 1, 7, 0U, 0, 0U, 0);
  c7_y = c7_u1;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static const mxArray *c7_i_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_b_setSimStateSideEffectsInfo, const char_T
  *c7_identifier)
{
  const mxArray *c7_y = NULL;
  emlrtMsgIdentifier c7_thisId;
  c7_y = NULL;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  sf_mex_assign(&c7_y, c7_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_b_setSimStateSideEffectsInfo), &c7_thisId), false);
  sf_mex_destroy(&c7_b_setSimStateSideEffectsInfo);
  return c7_y;
}

static const mxArray *c7_j_emlrt_marshallIn(SFc7_TempMeasureInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  const mxArray *c7_y = NULL;
  (void)chartInstance;
  (void)c7_parentId;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_duplicatearraysafe(&c7_u), false);
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_updateDataWrittenToVector(SFc7_TempMeasureInstanceStruct
  *chartInstance, uint32_T c7_vectorIndex)
{
  (void)chartInstance;
  c7_dataWrittenToVector[(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK(0, (int32_T)
    c7_vectorIndex, 0, 0, 1, 0)] = true;
}

static void init_dsm_address_info(SFc7_TempMeasureInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c7_TempMeasure_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1835010897U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2703587007U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3263174034U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(53026661U);
}

mxArray *sf_c7_TempMeasure_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("bShKk9L4dy4nqMKmXVAmYB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c7_TempMeasure_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c7_TempMeasure_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c7_TempMeasure(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[11],T\"output\",},{M[8],M[0],T\"is_active_c7_TempMeasure\",},{M[9],M[0],T\"is_c7_TempMeasure\",},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"wu\",M[2],M[1]}}}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c7_TempMeasure_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc7_TempMeasureInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc7_TempMeasureInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _TempMeasureMachineNumber_,
           7,
           3,
           5,
           0,
           3,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_TempMeasureMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_TempMeasureMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _TempMeasureMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"output");
          _SFD_SET_DATA_PROPS(1,1,1,0,"if_transition");
          _SFD_SET_DATA_PROPS(2,1,1,0,"HoldDataTicks");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_CH_SUBSTATE_COUNT(3);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,2);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
        }

        _SFD_CV_INIT_CHART(3,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(4,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(4,0,0,1,17,1,17);
        _SFD_CV_INIT_EML(1,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(1,0,0,0,25,0,25);
        _SFD_CV_INIT_EML(3,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(3,0,0,1,17,1,17);
        _SFD_CV_INIT_EML(2,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(2,0,0,1,17,1,17);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)c7_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c7_output;
          boolean_T *c7_if_transition;
          real_T *c7_HoldDataTicks;
          c7_HoldDataTicks = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c7_if_transition = (boolean_T *)ssGetInputPortSignal(chartInstance->S,
            0);
          c7_output = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c7_output);
          _SFD_SET_DATA_VALUE_PTR(1U, c7_if_transition);
          _SFD_SET_DATA_VALUE_PTR(2U, c7_HoldDataTicks);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _TempMeasureMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "XOAqxGOQvAHXu1V3yUSJFD";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_TempMeasure_optimization_info();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 7, "dworkChecksum");
    if (mxRTWDWorkChecksum != NULL) {
      double *pr = mxGetPr(mxRTWDWorkChecksum);
      if ((uint32_T)pr[0] != sfunDWorkChecksum[0] ||
          (uint32_T)pr[1] != sfunDWorkChecksum[1] ||
          (uint32_T)pr[2] != sfunDWorkChecksum[2] ||
          (uint32_T)pr[3] != sfunDWorkChecksum[3]) {
        sf_mex_error_message("Code generation and simulation targets registered different sets of persistent variables for the block. "
                             "External or Rapid Accelerator mode simulation requires code generation and simulation targets to "
                             "register the same set of persistent variables for this block. "
                             "This discrepancy is typically caused by MATLAB functions that have different code paths for "
                             "simulation and code generation targets where these code paths define different sets of persistent variables. "
                             "Please identify these code paths in the offending block and rewrite the MATLAB code so that "
                             "the set of persistent variables is the same between simulation and code generation.");
      }
    }
  }
}

static void sf_opaque_initialize_c7_TempMeasure(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc7_TempMeasureInstanceStruct*) chartInstanceVar)
    ->S);
  chart_debug_initialization(((SFc7_TempMeasureInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c7_TempMeasure((SFc7_TempMeasureInstanceStruct*)
    chartInstanceVar);
  initialize_c7_TempMeasure((SFc7_TempMeasureInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c7_TempMeasure(void *chartInstanceVar)
{
  enable_c7_TempMeasure((SFc7_TempMeasureInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c7_TempMeasure(void *chartInstanceVar)
{
  disable_c7_TempMeasure((SFc7_TempMeasureInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c7_TempMeasure(void *chartInstanceVar)
{
  sf_gateway_c7_TempMeasure((SFc7_TempMeasureInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c7_TempMeasure(void *chartInstanceVar)
{
  ext_mode_exec_c7_TempMeasure((SFc7_TempMeasureInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c7_TempMeasure(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c7_TempMeasure
    ((SFc7_TempMeasureInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c7_TempMeasure();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c7_TempMeasure(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c7_TempMeasure();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c7_TempMeasure((SFc7_TempMeasureInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c7_TempMeasure(SimStruct* S)
{
  return sf_internal_get_sim_state_c7_TempMeasure(S);
}

static void sf_opaque_set_sim_state_c7_TempMeasure(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c7_TempMeasure(S, st);
}

static void sf_opaque_terminate_c7_TempMeasure(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc7_TempMeasureInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_TempMeasure_optimization_info();
    }

    finalize_c7_TempMeasure((SFc7_TempMeasureInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc7_TempMeasure((SFc7_TempMeasureInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c7_TempMeasure(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c7_TempMeasure((SFc7_TempMeasureInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

mxArray *sf_c7_TempMeasure_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S1x2'varName','path'{{T\"is_active_c7_TempMeasure\",T\"is_active_c7_TempMeasure\"},{T\"is_c7_TempMeasure\",T\"is_c7_TempMeasure\"}}"
  };

  mxArray *mxTpInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  return mxTpInfo;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x5'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size'{{T\"int32\",,,,,,,M[0],M[]},{T\"boolean\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint32\",,,,,,,M[0],M[]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 5, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 864264916U, 1550946654U, 3412988460U,
    1343337187U };

  return checksum;
}

static void mdlSetWorkWidths_c7_TempMeasure(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_TempMeasure_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,7);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,7,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,7,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,7);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,7,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,7,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,7);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3723968238U));
  ssSetChecksum1(S,(61968132U));
  ssSetChecksum2(S,(2886198746U));
  ssSetChecksum3(S,(2595947387U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c7_TempMeasure(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c7_TempMeasure(SimStruct *S)
{
  SFc7_TempMeasureInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc7_TempMeasureInstanceStruct *)utMalloc(sizeof
    (SFc7_TempMeasureInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc7_TempMeasureInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c7_TempMeasure;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c7_TempMeasure;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c7_TempMeasure;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c7_TempMeasure;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c7_TempMeasure;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c7_TempMeasure;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c7_TempMeasure;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c7_TempMeasure;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c7_TempMeasure;
  chartInstance->chartInfo.mdlStart = mdlStart_c7_TempMeasure;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c7_TempMeasure;
  chartInstance->chartInfo.extModeExec = sf_opaque_ext_mode_exec_c7_TempMeasure;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c7_TempMeasure_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c7_TempMeasure(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c7_TempMeasure(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c7_TempMeasure(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c7_TempMeasure_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
