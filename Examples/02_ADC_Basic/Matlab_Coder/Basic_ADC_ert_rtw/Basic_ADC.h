/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Basic_ADC.h
 *
 * Code generated for Simulink model 'Basic_ADC'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Sat Feb 14 22:25:48 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Basic_ADC_h_
#define Basic_ADC_h_
#ifndef Basic_ADC_COMMON_INCLUDES_
#define Basic_ADC_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif                                 /* Basic_ADC_COMMON_INCLUDES_ */

#include "Basic_ADC_types.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  stm32cube_blocks_AnalogInput__T obj; /* '<S3>/Analog to Digital Converter' */
} DW_Basic_ADC_T;

/* Real-time Model Data Structure */
struct tag_RTM_Basic_ADC_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_Basic_ADC_T Basic_ADC_DW;

/* Model entry point functions */
extern void Basic_ADC_initialize(void);
extern void Basic_ADC_step(void);
extern void Basic_ADC_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Basic_ADC_T *const Basic_ADC_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Gain' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 */

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
 * '<Root>' : 'Basic_ADC'
 * '<S1>'   : 'Basic_ADC/Analog to Digital Converter'
 * '<S2>'   : 'Basic_ADC/Analog to Digital Converter/ECSoC'
 * '<S3>'   : 'Basic_ADC/Analog to Digital Converter/ECSoC/ECSimCodegen'
 */
#endif                                 /* Basic_ADC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
