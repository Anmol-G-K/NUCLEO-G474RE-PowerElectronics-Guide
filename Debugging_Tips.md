# Debugging Guide

## Common Issues and Solutions

### Compilation Errors

**Error: "undefined reference to `HAL_*`"**
- Ensure STM32CubeMX configuration is complete
- Check that HAL drivers are included in project
- Verify project build path is correct

**Error: "conflicting types for function"**
- Check for duplicate function declarations
- Ensure header guards are present in `.h` files
- Look for typos in function signatures

### Build Warnings

**Warning: "unused variable"**
```c
// Mark intentionally unused variables
(void)unused_var;  // This suppresses the warning
```

**Warning: "implicit function declaration"**
- Include the appropriate header file
- Check function prototype is declared before use

### Hardware Issues

**LED not blinking**
- Verify USB connection to board
- Check STM32CubeIDE recognizes the board
- Confirm correct pin configuration in CubeMX
- Try different USB port

**No serial output on UART**
- Verify UART pins are correctly configured (PA2, PA3 for USART2)
- Check baud rate matches serial terminal (typically 115200)
- Ensure UART is initialized before use
- Try different serial terminal software

**ADC readings incorrect**
- Verify analog input pins are configured
- Check ADC clock frequency
- Ensure sampling time is sufficient for your input impedance
- Take multiple samples and average

### Debugging with STM32CubeIDE

**Using Breakpoints**
1. Click on line number to set breakpoint
2. Right-click breakpoint for conditional settings
3. Run → Debug As → STM32 C/C++ Application
4. Use Debug perspective toolbar to step through code

**Viewing Variables**
- Open Variables window: Window → Show View → Variables
- Watch expressions: add custom expressions to track values
- Memory window: directly inspect memory addresses

**Using printf for Debugging**
```c
// Redirect printf to UART
#include <stdio.h>

int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}

// Now use printf normally
printf("ADC Value: %d\r\n", adc_value);
```

## MATLAB Embedded Coder Configuration

### Required CubeMX Settings

Since we strictly use low-level drivers with MATLAB Embedded Coder, ensure these settings are configured:

**Step 1: Driver Selection**
1. In STM32CubeMX, go to **Project Manager → Advanced Settings**
2. Set **Driver Selector** to **LL** (Low-Level drivers, not HAL)

**Step 2: Code Generation Options**
In the same **Advanced Settings** page:
- **Generated Functions Visibility**: Keep "static" checkbox **UNCHECKED**
- **Do not generate function call**: Keep this checkbox **UNCHECKED**

These settings ensure compatibility between STM32CubeMX-generated code and MATLAB Embedded Coder.

### Timer Configuration Issues

**Symptom:** Timer-based code not generating PWM or interrupts correctly, even after proper CubeMX configuration.

**Root Cause:** MATLAB Embedded Coder can encounter initialization issues with advanced timers when converting Simulink models to C code.

**Workaround:**
1. In STM32CubeMX, add a **second general-purpose timer** (e.g., TIM3) to your configuration
2. Configure TIM3 with basic settings:
   - Clock Source: Internal Clock
   - Prescaler: 1
   - Counter Period: 1000
   - Enable interrupt (if needed)
3. **Do not use TIM3 in your Simulink model** — it's only for initialization
4. Generate code and rebuild in STM32CubeIDE
5. Flash and test your board

This dummy timer ensures proper initialization sequence and resolves the timer synchronization issue.

### Code Generation Issues

**Simulink model compiles but behavior is incorrect**
- Verify all block parameters match hardware (frequencies, gains, sample rates)
- Check data types match between Simulink and C code
- Enable code generation report to inspect generated code
- Confirm Advanced Settings match requirements (LL driver, unchecked boxes)

**Missing function definitions**
- Ensure MATLAB Embedded Coder is licensed
- Check build process log for errors
- Regenerate code from clean Simulink model
- Verify driver selection is set to LL

## Performance Issues

**Code runs slow or misses real-time deadlines**
- Profile code using timing printouts
- Check ADC sample rate isn't too high
- Reduce unnecessary computations in interrupt handlers
- Use DMA for ADC and UART when possible

**High CPU usage**
- Avoid busy-wait loops; use interrupts instead
- Reduce printf calls in fast loops (impacts performance)
- Check for infinite loops or missing break conditions

## Hardware-Level Debugging

**Using Oscilloscope**
- Check PWM signal frequency and duty cycle
- Verify timing relationships between signals
- Look for glitches or noise

**Current Measurement**
- Use logic analyzer for digital signals
- Insert series resistor for current sensing
- Monitor supply voltage under load

## Tips and Best Practices

✅ **Do:**
- Test each example individually before combining
- Start with simple configurations and add complexity
- Use version control and commit working versions
- Document custom configurations
- Test on actual hardware, not just simulation

❌ **Don't:**
- Change code without rebuilding
- Ignore compiler warnings
- Use blocking delays in time-critical code
- Skip testing with actual power electronics circuits

## Getting Help

If issues persist:
1. Check [GitHub Issues](../../issues) for similar problems
2. Review example projects for reference implementations
3. Consult [STM32G474RE Datasheet](https://www.st.com/resource/en/datasheet/stm32g474re.pdf)
4. Create a new issue with detailed error description

---

**Last Updated:** February 2026