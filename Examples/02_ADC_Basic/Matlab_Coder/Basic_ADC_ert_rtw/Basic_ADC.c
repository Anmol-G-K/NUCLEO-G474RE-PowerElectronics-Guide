/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Basic_ADC.c
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

#include "Basic_ADC.h"
#include "Basic_ADC_types.h"
#include "rtwtypes.h"
#include "stm_adc_ll.h"
#include <stddef.h>
#include "Basic_ADC_private.h"

/* Block states (default storage) */
DW_Basic_ADC_T Basic_ADC_DW;

/* Real-time model */
static RT_MODEL_Basic_ADC_T Basic_ADC_M_;
RT_MODEL_Basic_ADC_T *const Basic_ADC_M = &Basic_ADC_M_;

/* Forward declaration for local functions */
static void Basic_ADC_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj);
static void Basic_ADC_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj)
{
  ADC_Type_T adcStructLoc;
  obj->isSetupComplete = false;

  /* Start for MATLABSystem: '<S3>/Analog to Digital Converter' */
  obj->isInitialized = 1;
  adcStructLoc.InternalBufferPtr = (void *)(NULL);

  /* Start for MATLABSystem: '<S3>/Analog to Digital Converter' */
  adcStructLoc.InjectedNoOfConversion = 0U;
  adcStructLoc.peripheralPtr = ADC1;
  adcStructLoc.dmaPeripheralPtr = NULL;
  adcStructLoc.dmastream = 0;
  adcStructLoc.DataTransferMode = ADC_DR_TRANSFER;
  adcStructLoc.DmaTransferMode = ADC_DMA_TRANSFER_LIMITED;
  adcStructLoc.InternalBufferSize = 1U;
  adcStructLoc.RegularNoOfConversion = 1U;
  obj->ADCHandle = ADC_Handle_Init(&adcStructLoc, ADC_NORMAL_MODE, 1,
    ADC_TRIGGER_AND_READ, LL_ADC_REG_SEQ_SCAN_DISABLE);
  enableADCAutomaticCalibrationOffset(obj->ADCHandle, 2);
  enableADC(obj->ADCHandle);
  startADCConversionForExternalTrigger(obj->ADCHandle, 1);
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

/* Model step function */
void Basic_ADC_step(void)
{
  uint16_T data;

  /* MATLABSystem: '<S3>/Analog to Digital Converter' */
  if (Basic_ADC_DW.obj.TunablePropsChanged) {
    Basic_ADC_DW.obj.TunablePropsChanged = false;
  }

  regularReadADCNormal(Basic_ADC_DW.obj.ADCHandle, ADC_TRIGGER_AND_READ, &data);

  /* End of MATLABSystem: '<S3>/Analog to Digital Converter' */
}

/* Model initialize function */
void Basic_ADC_initialize(void)
{
  /* Start for MATLABSystem: '<S3>/Analog to Digital Converter' */
  Basic_ADC_DW.obj.isInitialized = 0;
  Basic_ADC_DW.obj.matlabCodegenIsDeleted = false;
  Basic_ADC_SystemCore_setup(&Basic_ADC_DW.obj);
}

/* Model terminate function */
void Basic_ADC_terminate(void)
{
  /* Terminate for MATLABSystem: '<S3>/Analog to Digital Converter' */
  if (!Basic_ADC_DW.obj.matlabCodegenIsDeleted) {
    Basic_ADC_DW.obj.matlabCodegenIsDeleted = true;
    if ((Basic_ADC_DW.obj.isInitialized == 1) &&
        Basic_ADC_DW.obj.isSetupComplete) {
      ADC_Handle_Deinit(Basic_ADC_DW.obj.ADCHandle, ADC_NORMAL_MODE, 1);
    }
  }

  /* End of Terminate for MATLABSystem: '<S3>/Analog to Digital Converter' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
