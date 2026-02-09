# NUCLEO-G474RE-PowerElectronics-Guide

![MCU](https://img.shields.io/badge/MCU-STM32G474RE-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
![IDE](https://img.shields.io/badge/IDE-STM32CubeIDE-2C7BE5?style=for-the-badge&logo=stmicroelectronics&logoColor=white)
![MATLAB](https://img.shields.io/badge/MATLAB-Embedded%20Coder-FF8200?style=for-the-badge&logo=mathworks&logoColor=white)
![Language](https://img.shields.io/badge/Language-C%20%7C%20Embedded%20C-A8B9CC?style=for-the-badge&logo=c&logoColor=black)
![License](https://img.shields.io/badge/License-MIT-4CAF50?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge)


A comprehensive guide to getting started with the **STM32 NUCLEO-G474RE** development board for power electronics applications. This repository provides tutorials, examples, and best practices for developing power electronics projects using **STM32CubeIDE** and **MATLAB Embedded Coder**.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Getting Started](#getting-started)
- [Project Structure](#project-structure)
- [Examples](#examples)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)
- [Support](#support)

## 🎯 Overview

This guide is designed for engineers and developers who want to learn how to build power electronics applications on the STM32 NUCLEO-G474RE board. Whether you're working with motor control, DC-DC converters, inverters, or other power electronics applications, you'll find practical examples and comprehensive tutorials.

The NUCLEO-G474RE is particularly suited for power electronics due to its:
- Advanced PWM capabilities (multiple timers with complementary outputs)
- High-resolution ADC for sensing and feedback
- Floating-point math co-processor (FPU)
- Sufficient computational power for real-time control algorithms

## ✨ Features

- **STM32CubeIDE Projects**: Complete, ready-to-use project templates
- **MATLAB Integration**: Selected examples with MATLAB Embedded Coder support
- **Power Electronics Focus**: PWM generation, ADC sampling, feedback control, protection mechanisms
- **Step-by-Step Tutorials**: Beginner-friendly guides with detailed explanations
- **Real-World Examples**: Practical implementations of common power electronics circuits
- **Best Practices**: Firmware development guidelines for power electronics applications
- **Documentation**: Comprehensive comments and external documentation

## 📦 Prerequisites

### Knowledge
- Basic understanding of embedded C programming
- Familiarity with STM32 microcontroller concepts
- Introductory power electronics knowledge (PWM, ADC, feedback control)
- (Optional) MATLAB/Simulink experience for MATLAB Embedded Coder examples

### Hardware
- STM32 NUCLEO-G474RE development board
- USB cable for programming and debugging
- ST-Link programmer (built-in on NUCLEO board)
<!-- - External power supply (optional, for high-power testing) -->

### Software
- STM32CubeIDE (version 1.10 or later)
- STM32CubeMX (typically included with CubeIDE)
- (Optional) MATLAB R2021b or later with Embedded Coder toolbox

## 🔧 Hardware Requirements

| Component | Specification |
|-----------|---------------|
| **Microcontroller** | STM32G474RE |
| **Flash Memory** | 512 KB |
| **RAM** | 160 KB |
| **Operating Voltage** | 2.0V - 3.6V |
| **ADC Resolution** | 12-bit |
| **Timer Channels** | Multiple advanced timers with complementary outputs |
| **Debug Interface** | ST-Link V2-1 (on-board) |

## 💻 Software Requirements

| Tool | Version | Purpose |
|------|---------|---------|
| **STM32CubeIDE** | 1.10+ | Development environment and debugging |
| **STM32CubeMX** | Included | Pin and peripheral configuration |
| **ARM GCC Compiler** | Included | C/C++ compilation |
| **MATLAB Embedded Coder** | R2021b+ | (Optional) Code generation from Simulink |

## 🚀 Getting Started

### Step 1: Clone the Repository

```bash
git clone https://github.com/Anmol-G-K/NUCLEO-G474RE-PowerElectronics-Guide.git
cd NUCLEO-G474RE-PowerElectronics-Guide
```

### Step 2: Install STM32CubeIDE

1. Download from [STMicroelectronics official website](https://www.st.com/en/development-tools/stm32cubeide.html)
2. Install following the official documentation
3. Ensure ST-Link drivers are installed

### Step 3: Open Your First Project

1. Launch STM32CubeIDE
2. Go to `File` → `Open Projects from File System`
3. Navigate to the `Examples/01_Basic_LED_Blink` folder
4. Select the project and click `Finish`

### Step 4: Build and Flash

1. Right-click on the project → `Build Project`
2. Connect the NUCLEO board via USB
3. Right-click on the project → `Run As` → `STM32 C/C++ Application`
4. Verify the LED blinks on the board

### Step 5: (Optional) MATLAB Setup

For examples using MATLAB Embedded Coder:

1. Install MATLAB with Embedded Coder toolbox
2. Configure MATLAB to use the ARM GCC compiler
3. Navigate to MATLAB examples in the specific folder
4. Follow the specific tutorial documentation

## 📁 Project Structure

```
NUCLEO-G474RE-PowerElectronics-Guide/
│
├── Examples/
│   ├── 01_Basic_LED_Blink/              # Simple GPIO introduction
│   ├── 02_ADC_Basic/                    # ADC sampling fundamentals
│   ├── 03_PWM_Generation/               # PWM basics and configuration
│   ├── 04_Timer_Basics/                 # Timer operation and ISR
│   ├── 05_H_Bridge_Control/             # H-Bridge PWM control
│   └── 06_Current_Sensing/              # ADC-based current measurement
│   └── 07_Phase_Shifted_PWM/            # Complex PWM Switching Technique 
│
├── README.md                             # This file
├── LICENSE                               # MIT License
└── CONTRIBUTING.md                       # Contribution guidelines

```
<!-- │   ├── 05_Motor_Control_Basic/          # Simple motor speed control -->

<!-- ├── Utilities/
│   ├── Common_Functions.c/h             # Reusable firmware functions
│   ├── Debug_UART.c/h                   # UART debugging utilities
│   └── Configuration.h                  # Global configuration parameters -->

<!-- ├── MATLAB_Examples/
│   ├── 01_PWM_Simulink/                 # PWM generation from Simulink
│   ├── 02_Motor_Speed_Control/          # Speed control with Embedded Coder
│   └── README_MATLAB.md                 # MATLAB-specific setup guide -->

<!-- │
├── Documentation/
│   ├── STM32G474RE_Overview.md          # Hardware specifications and features
│   ├── PWM_Configuration_Guide.md       # Detailed PWM setup guide
│   ├── ADC_Setup_Guide.md               # ADC configuration tutorial
│   ├── Debugging_Tips.md                # Debugging and troubleshooting
│   └── Power_Electronics_Basics.md      # Power electronics concepts -->

## 📚 Examples

### 1. Basic LED Blink
**Location**: `Examples/01_Basic_LED_Blink`

Get familiar with the development environment by blinking an LED. This example teaches GPIO configuration and basic project structure.

### 2. ADC Sampling
**Location**: `Examples/02_ADC_Basic`

Read analog values from a potentiometer or sensor. Essential for understanding feedback in power electronics applications.

### 3. PWM Generation
**Location**: `Examples/03_PWM_Generation`

Configure PWM signals for driving MOSFETs or IGBTs. Covers frequency, duty cycle, and dead-time configuration.

<!-- ### 4. Motor Speed Control
**Location**: `Examples/05_Motor_Control_Basic`

Practical example of a simple DC motor speed control using PWM and feedback. Demonstrates closed-loop control concepts.

### 5. MATLAB Embedded Coder PWM
**Location**: `MATLAB_Examples/01_PWM_Simulink`

Generate PWM control logic using MATLAB Simulink and deploy to hardware using Embedded Coder. -->

## 📖 Documentation

Comprehensive documentation is available in the `Documentation/` folder:

- **[STM32G474RE Overview](./Documentation/STM32G474RE_Overview.md)** - Hardware features and capabilities
- **[PWM Configuration Guide](./Documentation/PWM_Configuration_Guide.md)** - Advanced PWM setup
- **[ADC Setup Guide](./Documentation/ADC_Setup_Guide.md)** - Analog-to-digital conversion configuration
- **[Debugging Tips](./Documentation/Debugging_Tips.md)** - Troubleshooting and debugging techniques
- **[Power Electronics Basics](./Documentation/Power_Electronics_Basics.md)** - Fundamental concepts

## 🤝 Contributing

Contributions are welcome! Whether it's adding new examples, improving documentation, or reporting bugs:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/YourFeatureName`)
3. Commit your changes (`git commit -m 'Add your feature'`)
4. Push to the branch (`git push origin feature/YourFeatureName`)
5. Open a Pull Request

Please ensure your contributions:
- Follow the existing code style and structure
- Include meaningful comments in the code
- Add documentation for new examples
- Test thoroughly on actual hardware

See [CONTRIBUTING.md](./CONTRIBUTING.md) for more details.

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](./LICENSE) file for details.

This allows for both commercial and personal use with proper attribution.

## 🆘 Support

### Resources
- STM32:
  - [STMicroelectronics Official Documentation](https://www.st.com/en/microcontrollers/stm32g4-series.html)
  - [STM32 Nucleo-64 development board](https://www.st.com/en/evaluation-tools/nucleo-g474re.html)
  - [STM32G474RE](https://www.st.com/en/microcontrollers-microprocessors/stm32g474re.html)
  - [STM32CubeIDE User Manual](https://www.st.com/resource/en/user_manual/dm00629855-stm32cubeide-integrated-development-environment-user-manual-stmicroelectronics.pdf)
- Matlab:
  - [Embedded Coder](https://in.mathworks.com/products/embedded-coder.html)
  - [Embedded Coder Support Package for STMicroelectronics STM32 Processors](https://in.mathworks.com/matlabcentral/fileexchange/43093-embedded-coder-support-package-for-stmicroelectronics-stm32-processors)

### Getting Help
- **Issues**: Check existing [GitHub Issues](../../issues) or create a new one
- **Discussions**: Use GitHub Discussions for questions and knowledge sharing
<!-- - **Documentation**: Refer to the `Documentation/` folder first -->

### Troubleshooting
- **Compilation Errors**: Check [Debugging Tips](./Debugging_Tips.md)
- **Hardware Issues**: Verify connections and power supply
- **STM32CubeIDE Problems**: Update to the latest version

### Tutorials
- [Get Started with Embedded Coder](https://in.mathworks.com/help/ecoder/product-fundamentals.html)
- [Embedded Coder Documentation](https://in.mathworks.com/help/ecoder/index.html)
- [Getting Started with STMicroelectronics STM32 Processor Based Boards](https://in.mathworks.com/help/ecoder/stmicroelectronicsstm32f4discovery/ug/Getting-started-stm32cubemx.html)
- [STMicroelectronics STM32 Documentation](https://in.mathworks.com/help/ecoder/stm32-spkg.html)

### Reference Manuals:
- [STM32 G474RE User Manual](https://www.st.com/resource/en/user_manual/um2505-stm32g4-nucleo64-boards-mb1367-stmicroelectronics.pdf)
- [STM32G474xE Datasheet](https://www.st.com/resource/en/datasheet/stm32g474re.pdf)
- [STM32 G474RE Reference Manual](https://www.st.com/resource/en/reference_manual/rm0440-stm32g4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [Application note - HRTIM Cookbook](https://www.st.com/resource/en/application_note/an4539-hrtim-cookbook-stmicroelectronics.pdf)
- [ Description of STM32G4 HAL and low-layer drivers](https://www.st.com/resource/en/user_manual/um2570-description-of-stm32g4-hal-and-lowlayer-drivers--stmicroelectronics.pdf)

## 🗺️ Roadmap

Planned additions:
- [ ] Three-phase inverter control example
- [ ] Advanced PWM dead-time management
- [ ] Real-time data logging example
<!-- - [ ] Bootloader implementation -->
- [ ] More MATLAB Embedded Coder examples
- [ ] FreeRTOS integration example
- [ ] CAN bus communication tutorial

## 📝 Citation

If you use this guide in your projects or research, please cite:

```
NUCLEO-G474RE-PowerElectronics-Guide
https://github.com/Anmol-G-K/NUCLEO-G474RE-PowerElectronics-Guide
```

## 👨‍💻 Author

**Anmol Govindarajapuram Krishnan**
- GitHub: [@Anmol-G-K](https://github.com/Anmol-G-K)
- Email: cb.en.u4eee23103@cb.students.amrita.edu

## 🙏 Acknowledgments

- STMicroelectronics for excellent microcontrollers and tools
- The embedded systems and power electronics community
- Contributors and users who provide feedback

---

**Last Updated**: February 2026  
**Status**: Active Development

For the latest updates and announcements, watch this repository! ⭐