/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Basic_Led_Blink.c
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

#include "Basic_Led_Blink.h"
#include "rtwtypes.h"

/* Block states (default storage) */
DW_Basic_Led_Blink_T Basic_Led_Blink_DW;

/* Real-time model */
static RT_MODEL_Basic_Led_Blink_T Basic_Led_Blink_M_;
RT_MODEL_Basic_Led_Blink_T *const Basic_Led_Blink_M = &Basic_Led_Blink_M_;

/* Model step function */
void Basic_Led_Blink_step(void)
{
  GPIO_TypeDef * portNameLoc;
  uint32_T shiftVal;
  int32_T rtb_DiscretePulseGenerator;
  uint32_T pinMask;
  uint32_T pinWriteLoc;

  /* DiscretePulseGenerator: '<Root>/Discrete Pulse Generator' */
  rtb_DiscretePulseGenerator = ((Basic_Led_Blink_DW.clockTickCounter < 1) &&
    (Basic_Led_Blink_DW.clockTickCounter >= 0));
  if (Basic_Led_Blink_DW.clockTickCounter >= 1) {
    Basic_Led_Blink_DW.clockTickCounter = 0;
  } else {
    Basic_Led_Blink_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Discrete Pulse Generator' */

  /* MATLABSystem: '<S3>/Digital Port Write' */
  portNameLoc = GPIOA;
  shiftVal = MW_GPIO_BIT_SHIFT;
  if (rtb_DiscretePulseGenerator != 0) {
    pinWriteLoc = 32U;
  } else {
    pinWriteLoc = 0U;
  }

  pinWriteLoc = mw_shift(pinWriteLoc, shiftVal);
  pinMask = mw_shift(32U, shiftVal);
  LL_GPIO_SetOutputPin(portNameLoc, pinWriteLoc);
  LL_GPIO_ResetOutputPin(portNameLoc, ~pinWriteLoc & pinMask);

  /* End of MATLABSystem: '<S3>/Digital Port Write' */
}

/* Model initialize function */
void Basic_Led_Blink_initialize(void)
{
  /* Start for MATLABSystem: '<S3>/Digital Port Write' */
  Basic_Led_Blink_DW.obj.matlabCodegenIsDeleted = false;
  Basic_Led_Blink_DW.obj.isInitialized = 1;
  Basic_Led_Blink_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void Basic_Led_Blink_terminate(void)
{
  /* Terminate for MATLABSystem: '<S3>/Digital Port Write' */
  if (!Basic_Led_Blink_DW.obj.matlabCodegenIsDeleted) {
    Basic_Led_Blink_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S3>/Digital Port Write' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
