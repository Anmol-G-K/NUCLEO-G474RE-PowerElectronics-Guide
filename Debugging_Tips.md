# SPARK Debugging & Troubleshooting Guide

A comprehensive guide for troubleshooting firmware, Simulink code generation, and hardware-level issues on the STM32 NUCLEO-G474RE development board.

### 🔧 Toolchain Versions
![MCU](https://img.shields.io/badge/MCU-STM32G474RE-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
![IDE](https://img.shields.io/badge/IDE-STM32CubeIDE%20v1.19.0-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
![MATLAB](https://img.shields.io/badge/MATLAB-R2025a-0076A8?style=for-the-badge&logo=mathworks&logoColor=white)
![Embedded Coder](https://img.shields.io/badge/Embedded%20Coder-v25.1.0-4CAF50?style=for-the-badge&logo=mathworks&logoColor=white)
![STM32 Support Package](https://img.shields.io/badge/STM32%20Support%20Package-v25.1.0-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
![Last Updated](https://img.shields.io/github/last-commit/Anmol-G-K/NUCLEO-G474RE-PowerElectronics-Guide?path=Debugging_Tips.md&label=Last%20Updated&style=for-the-badge&color=4c6ef5)
---

## 📋 Table of Contents

- [Common Compilation & Build Issues](#common-compilation--build-issues)
- [Hardware & Peripheral Issues](#hardware--peripheral-issues)
- [Efficient Embedded Debugging Techniques](#efficient-embedded-debugging-techniques)
- [MATLAB Embedded Coder Troubleshooting](#matlab-embedded-coder-troubleshooting)
- [Hardware-Level Debugging & Instrumentation](#hardware-level-debugging--instrumentation)
- [FTDI Breakout Board Safety Guidelines](#ftdi-breakout-board-safety-guidelines)
- [Tips and Best Practices](#tips-and-best-practices)

---

## Common Compilation & Build Issues

### Compilation Errors

**Error: `undefined reference to HAL_*`**
- **Cause:** The respective HAL driver file is not included in the compilation build paths.
- **Solution:** 
  1. Open STM32CubeMX (`.ioc` file), ensure the peripheral is enabled.
  2. Check **Project Manager → Code Generator** and ensure the necessary HAL drivers are set to copy to the project.
  3. Verify the source folders are not excluded from the build in STM32CubeIDE (right-click folder $\rightarrow$ Properties $\rightarrow$ C/C++ Build $\rightarrow$ Settings).

**Error: `conflicting types for function`**
- **Cause:** Typo in declaration vs. definition, or duplicate function headers.
- **Solution:** 
  1. Verify the prototype in your `.h` file matches the signature in the `.c` file exactly.
  2. Ensure header files have proper preprocessor guards (`#ifndef HEADER_FILE_H` / `#define HEADER_FILE_H`).

### Build Warnings

**Warning: `unused variable`**
- **Solution:** If a variable is declared for future use or set in an ISR but read elsewhere dynamically, you can suppress this warning using a void cast:
  ```c
  (void)unusedVar; // Suppresses unused variable warning
  ```

**Warning: `implicit function declaration`**
- **Solution:** Include the correct header file containing the function prototype, or declare the function prototype at the top of your source file.

---

## Hardware & Peripheral Issues

### LED / Basic GPIO Failures
- Verify USB cable connection and ensure the board is powered (PWR LED on NUCLEO is solid green).
- Confirm the debugger connection (ST-Link) is detected under STM32CubeIDE.
- Check CubeMX pinout configuration: verify LD2 is routed to **PA5** and configured as `GPIO_Output`.

### Serial UART Transmission Failures
- Verify correct pin configuration in CubeMX (PA2 is USART2_TX, PA3 is USART2_RX on the NUCLEO board).
- Check that the baud rate of your terminal software matches the MCU code configuration (typically **115200 bps**, 8-N-1).
- Ensure `HAL_UART_Init` is called and returns success before attempting transmissions.

### ADC Accuracy & Sampling Issues
- **Impedance Mismatch:** If ADC readings drift or drop, ensure the ADC sampling time is configured to be high enough for the analog source impedance.
- **Calibration:** Always calibrate the ADC before starting conversions:
  ```c
  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
  ```
- **Noise Mitigation:** Take multiple consecutive samples and apply a simple software rolling-average filter.

---

## Efficient Embedded Debugging Techniques

In power electronics applications, halting the CPU with a standard breakpoint or printing data over slow blocking UART lines can be dangerous (e.g., stopping a control loop mid-cycle can keep a switch on and damage power stages). Use the following non-intrusive debugging techniques instead:

### 1. Live Expressions / Live Watch (Recommended)
Instead of pausing execution or using `printf` to display variables, watch variables update in real time over SWD (Serial Wire Debug) without halting the processor core:
1. Open the **Live Expressions** view in STM32CubeIDE (**Window → Show View → Live Expressions**).
2. Enter the name of your global or static variables (e.g. `masterDuty`, `motorState`).
3. Set the refresh rate to watch variables dynamically update while the MCU is running control loops at full speed.

### 2. STM32CubeMonitor (Graphical Logging)
For high-frequency monitoring of duty cycles, currents, and voltages, use **STM32CubeMonitor**:
- Reads MCU memory directly over the ST-Link SWD port.
- Graphs variables in real-time on a dashboard.
- Zero CPU execution overhead, ensuring real-time control deadlines are never missed.

### 3. ITM / SWO Trace (Hardware-Accelerated Debug Logs)
The Instruction Trace Macrocell (ITM) uses the ST-Link's Single Wire Output (SWO) pin to send logs at up to 10 Mbps with negligible CPU overhead compared to UART:
- Configure the SWO pin in CubeMX under **SYS $\rightarrow$ Debug $\rightarrow$ Trace Asynchronous Sw**.
- Redirect standard output to the ITM stimulus port.
- View output inside the STM32CubeIDE **SWV ITM Data Console**.

### 4. UART Printf Redirection (Fallback Only)
If standard `printf` is required, override the `_write` system call. Use this sparingly as blocking calls to `HAL_UART_Transmit` will cause timing delays in real-time code:
```c
#include <stdio.h>

int _write(int file, char *ptr, int len) {
    // Blocking transmit - warning: introduces significant execution delays
    HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}
```

---

## MATLAB Embedded Coder Troubleshooting

### Required CubeMX Settings
When configuring STM32CubeMX for code generation with MATLAB Embedded Coder, always follow these settings to maintain compatibility with Low-Level (LL) drivers:

1. **Driver Selection:** Navigate to **Project Manager → Advanced Settings** and set the peripheral drivers to **LL** (Low-Level) instead of HAL.
2. **Code Generation Options:** Ensure the **Generated Functions Visibility** checkbox for "static" and **Do not generate function call** are both **UNCHECKED**.

### Timer Configuration Issues

> [!WARNING]
> The dummy timer workaround detailed below is rare. Before attempting this, you must thoroughly verify your existing timer configurations, base clock frequencies, prescaler math, and register settings inside both STM32CubeMX and Simulink.

**Symptom:** Timer-based code generated by MATLAB Embedded Coder does not output PWM or trigger interrupts as configured.

**Root Cause:** Initialization ordering conflicts in generated code for advanced timers (e.g. HRTIM, TIM1, TIM8).

**Dummy Timer Workaround:**
1. In STM32CubeMX, add a secondary basic/general-purpose timer (e.g., **TIM3**) to the configuration.
2. Configure **TIM3** with simple defaults (Internal Clock source, Prescaler = 1, Period = 1000).
3. **Do not reference TIM3 in your Simulink model**; it serves purely to force the generated initialization sequence to structure correctly.
4. Regenerate code and rebuild the project.

---

## Hardware-Level Debugging & Instrumentation

> [!TIP]
> For a comprehensive list of recommended hardware tools, specifications, budget alternatives, and purchase links (including oscilloscopes, logic analyzers, serial adapters, and breadboard components), please see the [Recommended Test Equipment & Components](./README.md#%EF%B8%8F-recommended-test-equipment--components) section of the main README.

### Using an Oscilloscope
- **PWM Verification:** Check switching frequency and verify that the duty cycle matches your control variables.
- **Dead-Time Validation:** Always probe complementary PWM outputs (e.g. High-Side and Low-Side gates) simultaneously to verify dead-time insertion. Ensure there is absolutely no overlap to prevent shoot-through.
- **Glitch & Noise Detection:** Inspect gate drive signals for noise coupling, ringing, or voltage spikes caused by parasitics under high-current switching.

### Using a Logic Analyzer
- **Digital Protocol Analysis:** Capture and decode digital communication buses in real time (e.g., I2C, SPI, UART, or CAN) to verify packet transmission, address matching, and register read/write sequences.
- **Timing & State Analysis:** Monitor multiple digital channels concurrently to verify state machine transitions, interrupt execution latency, and GPIO synchronization (e.g. measuring the exact delay from when a GPIO flag toggles to when the PWM output changes).

---

## FTDI Breakout Board Safety Guidelines

When using external USB-to-UART (FTDI) breakout boards for debugging and logging in power electronics setups, you must follow these safety practices:

> [!CAUTION]
> **Ground Loop Hazard:** Connecting a non-isolated FTDI board directly from a high-power converter board to your PC's USB port can establish a ground loop. If the converter ground and your PC ground are at different potentials, excessive current can flow back through the USB port, destroying your NUCLEO board, your PC's motherboard, or presenting a shock hazard.

- **Use Isolated USB-to-UART Converters:** When debugging active high-voltage power converter boards, always use a magnetically or opto-isolated USB-to-UART breakout board to electrically decouple your PC from the high-power circuit.
- **Logic Level Matching:** Ensure the FTDI breakout voltage jumper is set to **3.3V**. The STM32G474RE operates on 3.3V logic; supplying 5V to non-5V-tolerant UART pins will permanently damage the microcontroller.
- **Power Connection Rule:** Connect only the **GND**, **TX**, and **RX** lines. Do **NOT** connect the VCC/5V/3V3 power pin of the FTDI breakout board to the NUCLEO board if the NUCLEO is already powered via its own USB port or an external power supply. Doing so causes power domain conflicts.
- **Connection Sequence:** Always power off the high-voltage power stage before plugging in or unplugging the FTDI breakout connections.

---

## Tips and Best Practices

- 📈 **Incremental Integration:** Verify peripheral configurations independently (e.g., check ADC and PWM individually) before integrating them into a closed-loop control system.
- ⚡ **Real-Time Deadlines:** Avoid placing complex mathematical computations or blocking delays inside High-Frequency Interrupt Service Routines (ISRs).
- 🛠️ **Hardware Verification:** Ensure simulation models run with realistic time-steps that match the actual hardware capability of the NUCLEO board's timers.

---
