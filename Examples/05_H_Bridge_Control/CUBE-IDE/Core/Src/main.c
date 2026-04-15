/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : H-Bridge Motor Control — Complementary PWM with Dead-Time
  *
  * Architecture:
  *   - HRTIM Timer A: 40 kHz complementary PWM on TA1 / TA2
  *   - ADC1 Ch1    : Analogue duty-cycle reference (0–3.3 V → 0–1 duty)
  *   - PC13 (B1)   : Stop button  — triggers controlled ramp-down (State 2)
  *   - PB15        : Direction button — toggles direction A / B (State 0 / 1)
  *   - LD2 (PA5)   : Heartbeat / status LED
  *
  * Timing constants (f_HRCK = 170 MHz × 4 = 680 MHz):
  *   PER  = 680 MHz / 40 kHz = 17 000 ticks  (Timer A period)
  *   DT   = 1 µs × 680 MHz  =    680 ticks  (dead-time gap)
  *   CMP2 = PER − DT         = 16 320 ticks  (TA2 fixed reset for end-of-cycle DT)
  *
  * PWM event table:
  *   TA1 SET   ← Period event  (t = 0)          High-side ON
  *   TA1 RESET ← CMP1          (t = duty×PER)   High-side OFF
  *   TA2 SET   ← CMP3          (t = CMP1+680)   Low-side ON  (after 1 µs DT)
  *   TA2 RESET ← CMP2          (t = 16 320)     Low-side OFF (before next cycle)
  *
  * Control states:
  *   State 0  — Direction A : PWM drives TA1/TA2 (forward)
  *   State 1  — Direction B : PWM drives TA1/TA2 (reverse, complemented)
  *   State 2  — Stop        : Integrator ramps duty to 0, then outputs disabled
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
    STATE_DIR_A = 0,   /*!< Direction A — TA1 is the "driven" output */
    STATE_DIR_B = 1,   /*!< Direction B — TA2 is the "driven" output (phase reversed) */
    STATE_STOP  = 2    /*!< Controlled ramp-down to zero duty, then disable */
} MotorState_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* ── HRTIM timing constants ─────────────────────────────────────────────── */
#define HRTIM_PERIOD_TICKS      17000U   /*!< Timer A period  (680 MHz / 40 kHz) */
#define HRTIM_DT_TICKS            680U   /*!< Dead-time ticks (1 µs × 680 MHz)   */
#define HRTIM_CMP2_TICKS        16320U   /*!< Fixed TA2 reset = PER − DT          */

/* HRTIM enforces a minimum compare value of 3 ticks for correct operation.  */
#define HRTIM_CMP_MIN               3U

/* ── Duty-cycle limits (normalised 0.0 – 1.0) ───────────────────────────── */
#define DUTY_MIN                 0.0f
#define DUTY_MAX                 1.0f

/* ── Master ramp integrator ─────────────────────────────────────────────── */
/* Rate at which duty tracks the ADC reference per control loop iteration.   */
/* Tune RAMP_RATE to set acceleration / deceleration aggressiveness.         */
#define RAMP_RATE               0.001f   /*!< Δ duty per loop tick             */

/* ── ADC full-scale count for 12-bit resolution ─────────────────────────── */
#define ADC_FULL_SCALE          4095.0f

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/** Clamp a float value between lo and hi */
#define CLAMP_F(x, lo, hi)  ( (x) < (lo) ? (lo) : ( (x) > (hi) ? (hi) : (x) ) )
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

HRTIM_HandleTypeDef hhrtim1;

/* USER CODE BEGIN PV */
/* ── Motor state machine ────────────────────────────────────────────────── */
static volatile MotorState_t motorState     = STATE_DIR_A;
static volatile MotorState_t dirBeforeStop  = STATE_DIR_A;  /* restored on stop exit */
static volatile bool         stopPend       = false;
static volatile bool         dirTogglePend  = false;
/* ── Master ramp integrator output (0.0 – 1.0) ──────────────────────────── */
static float 				 masterDuty = 0.0f;
static float                 stopDuty       = 0.0f;  /* ramp-down integrator */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_HRTIM1_Init(void);

static void     Motor_DisableAll(void);
static void     Motor_SetDirA(float duty);
static void     Motor_SetDirB(float duty);
static float    ADC_ReadDutyReference(void);
static uint32_t Duty_ToTicks(float duty);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* ---------------------------------------------------------------------------
 * Duty_ToTicks
 * Converts normalised duty [0.0, 1.0] → HRTIM compare ticks.
 * Enforces hardware minimum of HRTIM_CMP_MIN (3 ticks).
 * --------------------------------------------------------------------------*/
static uint32_t Duty_ToTicks(float duty)
{
    uint32_t ticks = (uint32_t)(duty * (float)HRTIM_PERIOD_TICKS);
    if (ticks < HRTIM_CMP_MIN)      ticks = HRTIM_CMP_MIN;
    if (ticks > HRTIM_PERIOD_TICKS) ticks = HRTIM_PERIOD_TICKS;
    return ticks;
}

/* ---------------------------------------------------------------------------
 * Motor_Start
 * Arms the HRTIM Timer A counter with safe near-zero compare values.
 * Both outputs remain idle (LOW) until Motor_SetDirA / Motor_SetDirB is
 * called on the next loop tick.
 *
 * Safe to call more than once — re-arms the counter after Motor_DisableAll
 * without reconfiguring the output waveform event sources.
 * --------------------------------------------------------------------------*/
static void Motor_Start(void)
{
    HRTIM_CompareCfgTypeDef cmp = {0};

    /* CMP1 — TA1 turn-off (start at minimum, i.e. near-zero duty) */
    cmp.CompareValue = HRTIM_CMP_MIN;
    HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A,
                                    HRTIM_COMPAREUNIT_1, &cmp);

    /* CMP2 — fixed TA2 RESET (end-of-cycle dead-time) */
    cmp.CompareValue       = HRTIM_CMP2_TICKS;
    cmp.AutoDelayedMode    = HRTIM_AUTODELAYEDMODE_REGULAR;
    cmp.AutoDelayedTimeout = 0x0000;
    HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A,
                                    HRTIM_COMPAREUNIT_2, &cmp);

    /* CMP3 — TA2 SET point (start at minimum + dead-time) */
    cmp.CompareValue = HRTIM_CMP_MIN + HRTIM_DT_TICKS;
    HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A,
                                    HRTIM_COMPAREUNIT_3, &cmp);

    /* Start the counter; outputs are individually gated by direction fns */
    HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_A);
}

/* ---------------------------------------------------------------------------
 * Motor_DisableAll
 * Stops both HRTIM outputs and the Timer A counter.
 * Must only be called once masterDuty has reached 0.
 * --------------------------------------------------------------------------*/
static void Motor_DisableAll(void)
{
    HAL_HRTIM_WaveformOutputStop(&hhrtim1,
                                 HRTIM_OUTPUT_TA1 | HRTIM_OUTPUT_TA2);
    HAL_HRTIM_WaveformCountStop(&hhrtim1, HRTIM_TIMERID_TIMER_A);
}

/* ---------------------------------------------------------------------------
 * Motor_SetDirA  (PB15 = 0)
 * TA1 = PWM output,  TA2 = forced idle LOW.
 *
 *   TA1 SET   ← Period event (t = 0)
 *   TA1 RESET ← CMP1        (t = duty × PER)
 * --------------------------------------------------------------------------*/
static void Motor_SetDirA(float duty)
{
    duty = CLAMP_F(duty, DUTY_MIN, DUTY_MAX);

    HRTIM_CompareCfgTypeDef cmp = {0};
    cmp.CompareValue = Duty_ToTicks(duty);
    HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A,
                                    HRTIM_COMPAREUNIT_1, &cmp);

    /* Ensure TA2 is off before enabling TA1 */
    HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA2);
    HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA1);
}

/* ---------------------------------------------------------------------------
 * Motor_SetDirB  (direction latch = STATE_DIR_B)
 * TA2 = PWM complement output,  TA1 = forced idle LOW.
 *
 * Effective TA2 on-time = (CMP2 − CMP3) / PER
 *                       = (16320 − (CMP1 + 680)) / 17000
 *
 * As masterDuty increases, CMP1 increases, CMP3 increases, and the
 * TA2 pulse shrinks — this is the complement relationship.
 * At duty = 0: CMP3 = 683,  TA2 on-time ≈ (16320−683)/17000 ≈ 92 %
 * At duty = 1: CMP3 ≥ PER,  TA2 on-time → 0  (guard clamps CMP3)
 *
 * Dead-time is preserved on both edges:
 *   Rising  DT : CMP3 = CMP1 + 680  (1 µs after TA1 would have turned off)
 *   Falling DT : CMP2 = 16320       (1 µs before period boundary)
 * --------------------------------------------------------------------------*/
static void Motor_SetDirB(float duty)
{
    duty = CLAMP_F(duty, DUTY_MIN, DUTY_MAX);

    HRTIM_CompareCfgTypeDef cmp = {0};

    uint32_t cmp1Ticks = Duty_ToTicks(duty);
    uint32_t cmp3Ticks = cmp1Ticks + HRTIM_DT_TICKS;

    /* Guard: CMP3 must not reach or exceed the period */
    if (cmp3Ticks >= HRTIM_PERIOD_TICKS)
        cmp3Ticks = HRTIM_PERIOD_TICKS - 1U;

    /* CMP3 — TA2 turn-on point */
    cmp.CompareValue = cmp3Ticks;
    HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A,
                                    HRTIM_COMPAREUNIT_3, &cmp);

    /* CMP2 — TA2 turn-off point (fixed, never changes) */
    cmp.CompareValue       = HRTIM_CMP2_TICKS;
    cmp.AutoDelayedMode    = HRTIM_AUTODELAYEDMODE_REGULAR;
    cmp.AutoDelayedTimeout = 0x0000;
    HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A,
                                    HRTIM_COMPAREUNIT_2, &cmp);

    /* Ensure TA1 is off before enabling TA2 */
    HAL_HRTIM_WaveformOutputStop(&hhrtim1, HRTIM_OUTPUT_TA1);
    HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TA2);
}

/* ---------------------------------------------------------------------------
 * ADC_ReadDutyReference
 * Software-triggered single conversion on ADC1 CH1.
 * Returns normalised [0.0, 1.0].
 * --------------------------------------------------------------------------*/
static float ADC_ReadDutyReference(void)
{
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        uint32_t raw  = HAL_ADC_GetValue(&hadc1);
        float    duty = (float)raw / ADC_FULL_SCALE;
        HAL_ADC_Stop(&hadc1);
        return CLAMP_F(duty, DUTY_MIN, DUTY_MAX);
    }
    HAL_ADC_Stop(&hadc1);
    return 0.0f;
}

/* ---------------------------------------------------------------------------
 * HAL_GPIO_EXTI_Callback
 *
 * PC13 (B1_Pin) — configured RISING edge, GPIO_NOPULL (board has external
 *                 pull-down). Sets stopPend; main loop handles stop/resume
 *                 toggle. No debounce — mechanical bounce may fire twice but
 *                 the toggle-on-flag pattern absorbs a double-set cleanly.
 *
 * PB15          — configured RISING edge, GPIO_PULLUP. Sets dirTogglePend;
 *                 main loop flips direction latch. Ignored while STATE_STOP.
 *
 * Only boolean flags are written here — no HAL calls, no state writes,
 * keeping ISR execution under 10 clock cycles.
 * --------------------------------------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == B1_Pin)
    {
        stopPend = true;          /* PC13 — stop or resume */
    }

    if (GPIO_Pin == GPIO_PIN_15)
    {
        dirTogglePend = true;     /* PB15 — latch direction toggle */
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_HRTIM1_Init();
  /* USER CODE BEGIN 2 */

  /* Calibrate ADC before first conversion */
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);

  /* Start HRTIM outputs — both channels enabled; duty held at 0 until
     the integrator ramps up from the ADC reference.                     */
  Motor_Start();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* ── Control loop — 10 ms tick ─────────────────────────────────────────
     *
     *  Each iteration:
     *    1. Consume ISR flags (direction toggle, stop/resume)
     *    2. Read ADC pot → adcDuty  [0.0, 1.0]
     *    3. Running : masterDuty = adcDuty  (instant, no ramp)
     *       Stopping: stopDuty  -= RAMP_RATE per tick until 0
     *    4. Drive correct HRTIM output or cut power when ramp complete
     *
     *  STATE_STOP entered on first PC13 press  → ramp-down begins
     *  STATE_STOP exited  on second PC13 press → direction restored, re-armed
     * ───────────────────────────────────────────────────────────────────── */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  /* ── 1. Service direction toggle (ISR latched) ──────────────────── */
	        if (dirTogglePend && (motorState != STATE_STOP))
	        {
	            dirTogglePend = false;
	            motorState    = (motorState == STATE_DIR_A) ? STATE_DIR_B : STATE_DIR_A;
	            dirBeforeStop = motorState;
	        }

	        /* ── 2. Service stop / resume button ────────────────────────────── */
	        if (stopPend)
	        {
	            stopPend = false;
	            if (motorState == STATE_STOP)
	            {
	                /* Second press — exit stop, restore direction */
	                motorState = dirBeforeStop;
	                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	            }
	            else
	            {
	                /* First press — snapshot current duty and begin ramp-down */
	                dirBeforeStop = motorState;
	                stopDuty      = masterDuty;   /* start ramp from current level */
	                motorState    = STATE_STOP;
	            }
	        }

	        /* ── 3. Read ADC — direct assign for running states ─────────────── */
	        float adcDuty = ADC_ReadDutyReference();

	        /* ── 4. Apply duty to active output ─────────────────────────────── */
	        if (motorState == STATE_STOP)
	        {
	            /* Ramp stopDuty down to 0 at RAMP_RATE per 10 ms tick */
	            stopDuty -= RAMP_RATE;
	            if (stopDuty < 0.0f) stopDuty = 0.0f;

	            if (stopDuty <= 0.0f)
	            {
	                /* Ramp complete — cut outputs */
	                Motor_DisableAll();
	                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	            }
	            else
	            {
	            	/* Still ramping — drive the output that was active at stop time.
					 * motorState is STATE_STOP so we cannot use it to select the
					 * output; dirBeforeStop holds the pre-stop direction snapshot.  */
	                if (dirBeforeStop == STATE_DIR_A)
	                    Motor_SetDirA(stopDuty);
	                else
	                    Motor_SetDirB(stopDuty);
	            }
	        }
	        else if (motorState == STATE_DIR_A)
	        {
	            masterDuty = adcDuty;   /* instant ADC tracking */
	            HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	            if (HAL_HRTIM_WaveformGetOutputState(&hhrtim1,
	                    HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1)
	                != HRTIM_OUTPUTSTATE_RUN)
	            {
	                Motor_Start();
	            }
	            Motor_SetDirA(masterDuty);
	        }
	        else   /* STATE_DIR_B */
	        {
	            masterDuty = adcDuty;   /* instant ADC tracking */
	            HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	            if (HAL_HRTIM_WaveformGetOutputState(&hhrtim1,
	                    HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA2)
	                != HRTIM_OUTPUTSTATE_RUN)
	            {
	                Motor_Start();
	            }
	            Motor_SetDirB(masterDuty);
	        }

	        HAL_Delay(10);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.GainCompensation = 0;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief HRTIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_HRTIM1_Init(void)
{

  /* USER CODE BEGIN HRTIM1_Init 0 */

  /* USER CODE END HRTIM1_Init 0 */

  HRTIM_TimeBaseCfgTypeDef pTimeBaseCfg = {0};
  HRTIM_TimerCfgTypeDef pTimerCfg = {0};
  HRTIM_TimerCtlTypeDef pTimerCtl = {0};
  HRTIM_CompareCfgTypeDef pCompareCfg = {0};
  HRTIM_OutputCfgTypeDef pOutputCfg = {0};

  /* USER CODE BEGIN HRTIM1_Init 1 */

  /* USER CODE END HRTIM1_Init 1 */
  hhrtim1.Instance = HRTIM1;
  hhrtim1.Init.HRTIMInterruptResquests = HRTIM_IT_NONE;
  hhrtim1.Init.SyncOptions = HRTIM_SYNCOPTION_NONE;
  if (HAL_HRTIM_Init(&hhrtim1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_HRTIM_DLLCalibrationStart(&hhrtim1, HRTIM_CALIBRATIONRATE_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_HRTIM_PollForDLLCalibration(&hhrtim1, 10) != HAL_OK)
  {
    Error_Handler();
  }
  pTimeBaseCfg.Period = 0xFFDF;
  pTimeBaseCfg.RepetitionCounter = 0x00;
  pTimeBaseCfg.PrescalerRatio = HRTIM_PRESCALERRATIO_MUL32;
  pTimeBaseCfg.Mode = HRTIM_MODE_CONTINUOUS;
  if (HAL_HRTIM_TimeBaseConfig(&hhrtim1, HRTIM_TIMERINDEX_MASTER, &pTimeBaseCfg) != HAL_OK)
  {
    Error_Handler();
  }
  pTimerCfg.InterruptRequests = HRTIM_MASTER_IT_NONE;
  pTimerCfg.DMARequests = HRTIM_MASTER_DMA_NONE;
  pTimerCfg.DMASrcAddress = 0x0000;
  pTimerCfg.DMADstAddress = 0x0000;
  pTimerCfg.DMASize = 0x1;
  pTimerCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
  pTimerCfg.InterleavedMode = HRTIM_INTERLEAVED_MODE_DISABLED;
  pTimerCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
  pTimerCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
  pTimerCfg.DACSynchro = HRTIM_DACSYNC_NONE;
  pTimerCfg.PreloadEnable = HRTIM_PRELOAD_DISABLED;
  pTimerCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
  pTimerCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
  pTimerCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_DISABLED;
  pTimerCfg.ReSyncUpdate = HRTIM_TIMERESYNC_UPDATE_UNCONDITIONAL;
  if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_MASTER, &pTimerCfg) != HAL_OK)
  {
    Error_Handler();
  }
  pTimeBaseCfg.Period = 17000;
  pTimeBaseCfg.PrescalerRatio = HRTIM_PRESCALERRATIO_MUL4;
  if (HAL_HRTIM_TimeBaseConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, &pTimeBaseCfg) != HAL_OK)
  {
    Error_Handler();
  }
  pTimerCtl.UpDownMode = HRTIM_TIMERUPDOWNMODE_UP;
  pTimerCtl.TrigHalf = HRTIM_TIMERTRIGHALF_DISABLED;
  pTimerCtl.GreaterCMP3 = HRTIM_TIMERGTCMP3_EQUAL;
  pTimerCtl.GreaterCMP1 = HRTIM_TIMERGTCMP1_EQUAL;
  pTimerCtl.DualChannelDacEnable = HRTIM_TIMER_DCDE_DISABLED;
  if (HAL_HRTIM_WaveformTimerControl(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, &pTimerCtl) != HAL_OK)
  {
    Error_Handler();
  }
  pTimerCfg.InterruptRequests = HRTIM_TIM_IT_NONE;
  pTimerCfg.DMARequests = HRTIM_TIM_DMA_NONE;
  pTimerCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;
  pTimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
  pTimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
  pTimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
  pTimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
  pTimerCfg.DelayedProtectionMode = HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DISABLED;
  pTimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_TIMER_A;
  pTimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
  pTimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_ENABLED;
  if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, &pTimerCfg) != HAL_OK)
  {
    Error_Handler();
  }
  pCompareCfg.CompareValue = 0;
  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, &pCompareCfg) != HAL_OK)
  {
    Error_Handler();
  }
  pCompareCfg.CompareValue = 16320;
  pCompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
  pCompareCfg.AutoDelayedTimeout = 0x0000;

  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_2, &pCompareCfg) != HAL_OK)
  {
    Error_Handler();
  }
  pCompareCfg.CompareValue = 0;
  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_3, &pCompareCfg) != HAL_OK)
  {
    Error_Handler();
  }
  pOutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
  pOutputCfg.SetSource = HRTIM_OUTPUTSET_TIMPER;
  pOutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP1;
  pOutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
  pOutputCfg.IdleLevel = HRTIM_OUTPUTIDLELEVEL_INACTIVE;
  pOutputCfg.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_NONE;
  pOutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
  pOutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1, &pOutputCfg) != HAL_OK)
  {
    Error_Handler();
  }
  pOutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP3;
  pOutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP2;
  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA2, &pOutputCfg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN HRTIM1_Init 2 */

  /* USER CODE END HRTIM1_Init 2 */
  HAL_HRTIM_MspPostInit(&hhrtim1);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LPUART1_TX_Pin LPUART1_RX_Pin */
  GPIO_InitStruct.Pin = LPUART1_TX_Pin|LPUART1_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF12_LPUART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
