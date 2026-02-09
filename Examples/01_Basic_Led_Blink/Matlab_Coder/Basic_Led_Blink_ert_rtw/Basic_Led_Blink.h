/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Basic_Led_Blink.h
 *
 * Code generated for Simulink model 'Basic_Led_Blink'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Mon Feb  9 19:46:46 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Basic_Led_Blink_h_
#define Basic_Led_Blink_h_
#ifndef Basic_Led_Blink_COMMON_INCLUDES_
#define Basic_Led_Blink_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#include "main.h"
#include "mw_stm32_utils.h"
#endif                                 /* Basic_Led_Blink_COMMON_INCLUDES_ */

#include "Basic_Led_Blink_types.h"
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
  stm32cube_blocks_DigitalPortW_T obj; /* '<S3>/Digital Port Write' */
  int32_T clockTickCounter;            /* '<Root>/Discrete Pulse Generator' */
} DW_Basic_Led_Blink_T;

/* Real-time Model Data Structure */
struct tag_RTM_Basic_Led_Blink_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_Basic_Led_Blink_T Basic_Led_Blink_DW;

/* Model entry point functions */
extern void Basic_Led_Blink_initialize(void);
extern void Basic_Led_Blink_step(void);
extern void Basic_Led_Blink_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Basic_Led_Blink_T *const Basic_Led_Blink_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

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
 * '<Root>' : 'Basic_Led_Blink'
 * '<S1>'   : 'Basic_Led_Blink/Digital Port Write'
 * '<S2>'   : 'Basic_Led_Blink/Digital Port Write/ECSoC'
 * '<S3>'   : 'Basic_Led_Blink/Digital Port Write/ECSoC/ECSimCodegen'
 */
#endif                                 /* Basic_Led_Blink_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
