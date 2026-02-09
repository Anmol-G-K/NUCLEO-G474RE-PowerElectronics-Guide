# Contributing to NUCLEO-G474RE-PowerElectronics-Guide

Thank you for your interest in contributing to this project! We welcome contributions from the community, whether it's bug reports, documentation improvements, new examples, or code enhancements. This document provides guidelines and instructions to help you contribute effectively.

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
- [Getting Started](#getting-started)
- [Development Workflow](#development-workflow)
- [Coding Standards](#coding-standards)
- [Commit Guidelines](#commit-guidelines)
- [Pull Request Process](#pull-request-process)
- [Documentation Guidelines](#documentation-guidelines)
- [Testing Guidelines](#testing-guidelines)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Enhancements](#suggesting-enhancements)
- [License](#license)
- [Questions or Need Help?](#questions-or-need-help)

## 📜 Code of Conduct

### Our Pledge

We are committed to providing a welcoming and inclusive environment for all contributors. We pledge to:

- Be respectful and constructive in all interactions
- Welcome contributors of all experience levels
- Foster an inclusive and harassment-free community
- Focus on what is best for the community

### Expected Behavior

- Be kind and respectful to others
- Provide constructive feedback
- Accept criticism gracefully
- Focus on the code, not the person

### Unacceptable Behavior

- Harassment, discrimination, or abusive language
- Trolling, insulting, or derogatory comments
- Public or private attacks
- Publishing others' private information

## 🤝 How Can I Contribute?

### 1. **Report Bugs**
If you find a bug, please report it! See [Reporting Bugs](#reporting-bugs) for details.

### 2. **Suggest Enhancements**
Have an idea for a new example or improvement? See [Suggesting Enhancements](#suggesting-enhancements).

### 3. **Add New Examples**
Create new power electronics application examples or expand existing ones.

### 4. **Improve Documentation**
Help clarify existing documentation or add new guides and tutorials.

### 5. **Fix Known Issues**
Browse open issues and submit pull requests to fix them.

### 6. **Review Pull Requests**
Provide constructive feedback on other contributors' pull requests.

### 7. **Share Knowledge**
Help answer questions in Issues and Discussions.

## 🚀 Getting Started

### Prerequisites

Before contributing, ensure you have:

1. **Git** installed ([download](https://git-scm.com/download))
2. **STM32CubeIDE** installed ([download](https://www.st.com/en/development-tools/stm32cubeide.html))
3. A **GitHub account** ([create one](https://github.com/signup))
4. A **NUCLEO-G474RE board** (for testing hardware-related contributions)
5. (Optional) **MATLAB** with Embedded Coder for MATLAB-related contributions

### Setting Up Your Development Environment

1. **Fork the repository**
   ```bash
   Click the "Fork" button at the top right of the GitHub page
   ```

2. **Clone your fork**
   ```bash
   git clone https://github.com/YOUR-USERNAME/NUCLEO-G474RE-PowerElectronics-Guide.git
   cd NUCLEO-G474RE-PowerElectronics-Guide
   ```

3. **Add upstream remote** (to sync with the main repository)
   ```bash
   git remote add upstream https://github.com/Anmol-G-K/NUCLEO-G474RE-PowerElectronics-Guide.git
   ```

4. **Verify remotes**
   ```bash
   git remote -v
   # Should show both 'origin' (your fork) and 'upstream' (original repo)
   ```

## 🔄 Development Workflow

### Creating a Feature Branch

1. **Sync with upstream**
   ```bash
   git fetch upstream
   git checkout main
   git merge upstream/main
   ```

2. **Create a new branch**
   ```bash
   git checkout -b feature/your-feature-name
   # or for bug fixes:
   git checkout -b bugfix/issue-description
   ```

   **Branch naming conventions:**
   - Features: `feature/descriptive-name`
   - Bug fixes: `bugfix/issue-description`
   - Documentation: `docs/description`
   - Examples: `example/example-name`

3. **Make your changes**
   - Write clean, well-commented code
   - Test thoroughly on actual hardware
   - Follow the coding standards (see below)

4. **Commit your changes**
   - See [Commit Guidelines](#commit-guidelines)

5. **Push to your fork**
   ```bash
   git push origin feature/your-feature-name
   ```

6. **Create a Pull Request**
   - See [Pull Request Process](#pull-request-process)

## 📝 Coding Standards

### C Code Style

We follow a consistent C coding style to ensure readability and maintainability.

#### Naming Conventions

```c
// Functions: snake_case
void pwm_initialize(void);
uint16_t adc_read_value(uint8_t channel);

// Variables: snake_case
uint32_t pwm_frequency = 20000;
volatile uint16_t adc_buffer[16];

// Constants: UPPER_SNAKE_CASE
#define PWM_MAX_FREQUENCY 100000
#define ADC_RESOLUTION 4096

// Struct members: snake_case
typedef struct {
    uint16_t frequency;
    uint8_t duty_cycle;
    uint8_t dead_time;
} PWM_Config_t;

// Typedef suffix: _t
typedef struct PWM_Config PWM_Config_t;
```

#### Code Formatting

```c
// Use 4-space indentation (not tabs)
if (condition) {
    // code block
} else {
    // code block
}

// Function declarations with clear parameter names
uint16_t adc_read_channel(uint8_t channel_num, uint8_t samples);

// Comments for complex operations
// Initialize PWM with 20kHz frequency and 50% duty cycle
pwm_init(20000, 50);

// Space before braces
for (int i = 0; i < count; i++) {
    // code
}

// One statement per line
int a = 5;
int b = 10;
// NOT: int a = 5; int b = 10;
```

#### Header File Template

```c
/**
 * @file pwm_driver.h
 * @brief PWM driver for STM32G474RE
 * @details Provides PWM generation with configurable frequency and duty cycle
 * @version 1.0
 * @date 2026-02-09
 * @author Your Name
 */

#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g4xx_hal.h"

/**
 * @brief Initialize PWM timer
 * @param frequency Desired PWM frequency in Hz
 * @param duty_cycle Duty cycle percentage (0-100)
 * @return Status code (0 = success, non-zero = error)
 */
int pwm_initialize(uint32_t frequency, uint8_t duty_cycle);

#ifdef __cplusplus
}
#endif

#endif // PWM_DRIVER_H
```

#### Source File Template

```c
/**
 * @file pwm_driver.c
 * @brief PWM driver implementation
 * @author Your Name
 */

#include "pwm_driver.h"

// Private definitions
#define PWM_MIN_FREQUENCY 1000
#define PWM_MAX_FREQUENCY 100000

// Private variables
static TIM_HandleTypeDef htim;
static uint32_t current_frequency = 0;

/**
 * @brief Initialize PWM timer
 * @param frequency Desired PWM frequency in Hz
 * @param duty_cycle Duty cycle percentage (0-100)
 * @return Status code (0 = success, -1 = error)
 */
int pwm_initialize(uint32_t frequency, uint8_t duty_cycle) {
    if (frequency < PWM_MIN_FREQUENCY || frequency > PWM_MAX_FREQUENCY) {
        return -1;  // Invalid frequency
    }
    
    // Implementation here
    current_frequency = frequency;
    
    return 0;  // Success
}
```

### Comments and Documentation

```c
// Single line comment for brief explanations
int result = calculate_value();  // Variable explanation

/**
 * @brief Multi-line comment for functions
 * @param param1 Description of parameter 1
 * @param param2 Description of parameter 2
 * @return Description of return value
 * 
 * Additional details about the function behavior,
 * edge cases, or important notes.
 */

// TODO: Mark incomplete work
// FIXME: Mark bugs or issues to be fixed
// NOTE: Important information or warnings
// HACK: Temporary solutions
```

### Best Practices

1. **Keep functions small and focused**
   - Each function should do one thing well
   - Aim for functions under 50 lines

2. **Avoid magic numbers**
   ```c
   // BAD
   if (adc_value > 2048) { ... }
   
   // GOOD
   #define ADC_MID_RANGE 2048
   if (adc_value > ADC_MID_RANGE) { ... }
   ```

3. **Use meaningful variable names**
   ```c
   // BAD
   uint16_t x = 0;
   
   // GOOD
   uint16_t pwm_duty_cycle = 0;
   ```

4. **Handle errors properly**
   ```c
   int result = pwm_initialize(20000, 50);
   if (result != 0) {
       // Handle error
       return -1;
   }
   ```

5. **Use const and static appropriately**
   ```c
   static uint32_t pwm_frequency = 20000;  // Private variable
   const uint8_t MAX_CHANNELS = 4;         // Constant
   ```

## 💬 Commit Guidelines

### Commit Message Format

Use clear, descriptive commit messages following this format:

```
<type>(<scope>): <subject>

<body>

<footer>
```

### Type

- **feat**: A new feature
- **fix**: A bug fix
- **docs**: Documentation only changes
- **style**: Changes that don't affect code meaning (formatting, missing semicolons, etc.)
- **refactor**: Code change that neither fixes a bug nor adds a feature
- **perf**: Code change that improves performance
- **test**: Adding missing tests or correcting existing tests
- **chore**: Changes to build process, dependencies, or tools

### Scope

The scope specifies what part of the codebase is affected:
- `pwm`: PWM-related changes
- `adc`: ADC-related changes
- `example`: Example project changes
- `docs`: Documentation changes
- `config`: Configuration changes

### Subject

- Use imperative mood ("add feature" not "added feature")
- Don't capitalize first letter
- No period (.) at the end
- Limit to 50 characters

### Body

- Optional but recommended for non-trivial changes
- Explain **what** and **why**, not how
- Wrap at 72 characters
- Separate from subject by blank line

### Footer

- Reference issues: `Closes #123` or `Fixes #456`
- Breaking changes: `BREAKING CHANGE: description`

### Examples

```
feat(pwm): add configurable dead-time support

Add dead-time configuration to PWM driver to prevent
shoot-through in half-bridge configurations. Allows
setting dead-time from 0 to 1000ns.

Closes #45

---

fix(adc): correct sampling time calculation

The ADC sampling time calculation was off by a factor
of 2. This caused incorrect analog readings at high
frequencies.

Fixes #78

---

docs: update PWM configuration guide with dead-time example

---

refactor(example): simplify motor control example code

Reduce code duplication by extracting common PWM
initialization into a helper function.
```

## 🔀 Pull Request Process

### Before Submitting

1. **Ensure your code follows standards**
   - Run through the [Coding Standards](#coding-standards) checklist
   - Check for compiler warnings
   <!-- -  clean build with `-Wall -Wextra` -->

2. **Test thoroughly**
   - Build without errors or warnings
   - Test on actual NUCLEO-G474RE hardware
   - Verify all examples still work

3. **Update documentation**
   - Update relevant documentation files
   - Add comments to complex code sections
   - Update README if needed

4. **Sync with upstream**
   ```bash
   git fetch upstream
   git rebase upstream/main
   ```

5. **Push to your fork**
   ```bash
   git push origin feature/your-feature-name
   ```

### Creating the Pull Request

1. **Go to the original repository** on GitHub
2. **Click "New Pull Request"**
3. **Select your fork and branch** as the source
4. **Fill in the PR template** with:

```markdown
## Description
Brief description of what this PR does.

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Example addition

## Related Issues
Closes #123

## Changes Made
- Change 1
- Change 2
- Change 3

## Testing
Describe how you tested this:
- [ ] Built successfully on STM32CubeIDE
- [ ] Tested on NUCLEO-G474RE hardware
- [ ] No compiler warnings
- [ ] All examples still work

## Screenshots or Demo
If applicable, add screenshots or videos demonstrating the changes.

## Checklist
- [ ] My code follows the coding standards
- [ ] I have commented my code, especially complex sections
- [ ] I have updated relevant documentation
- [ ] My changes don't break existing functionality
- [ ] I have tested this on actual hardware
```

### Review Process

- We'll review your PR promptly
- Expect requests for changes or clarifications
- Be open to feedback and willing to iterate
- Once approved, we'll merge your PR

## 📖 Documentation Guidelines

### For New Examples

When contributing a new example, create a `README.md` in the example directory:

```markdown
# 08_Your_Example_Name

## Overview
Brief description of what this example demonstrates.

## Hardware Setup
- List required components
- Diagram or schematic (if applicable)
- Pin connections

## Software Setup
- Prerequisites
- Configuration steps

## How It Works
Detailed explanation of the code and functionality.

## Key Features
- Feature 1
- Feature 2

## Expected Output
What should happen when you run this example.

## Troubleshooting
Common issues and solutions.

## Further Reading
Links to datasheets, application notes, or tutorials.
```

### For Documentation Files

- Use clear, concise language
- Include code examples where helpful
- Add diagrams or flowcharts for complex concepts
- Link to relevant resources

## ✅ Testing Guidelines

### Compilation Testing

```bash
# Build should complete with no errors
# Warnings should be minimal and documented

# Check for common issues:
# - Integer overflow
# - Uninitialized variables
# - Buffer overflows
# - Memory leaks (in embedded context)
```

### Hardware Testing

1. **Basic Functionality**
   - Program the board successfully
   - Verify expected behavior

2. **Stability Testing**
   - Run for extended periods
   - Monitor for unexpected resets
   - Check for memory leaks

3. **Edge Cases**
   - Test with extreme input values
   - Test with boundary conditions
   - Test error conditions

4. **Performance**
   - Verify timing constraints are met
   - Monitor CPU usage if applicable
   - Check for timing violations

## 🐛 Reporting Bugs

### Before Reporting

- Check if the bug has already been reported
- Verify you're using the latest version
- Confirm the bug is reproducible

### Creating a Bug Report

Use the GitHub Issue form and include:

```markdown
## Description
Clear description of the bug.

## Steps to Reproduce
1. Step 1
2. Step 2
3. Step 3

## Expected Behavior
What should happen.

## Actual Behavior
What actually happens.

## Environment
- STM32CubeIDE Version: X.XX
- NUCLEO Board: G474RE
- OS: Windows/Linux/Mac
- MATLAB Version: (if applicable)

## Attachments
- Project file (if applicable)
- Screenshots
- Error logs

## Additional Context
Any other relevant information.
```

## 💡 Suggesting Enhancements

### Before Suggesting

- Check if the enhancement has been discussed
- Verify it aligns with the project scope

### Creating a Feature Request

Use the GitHub Issue form and include:

```markdown
## Feature Description
Clear description of the proposed feature.

## Motivation
Why would this be useful?

## Example Use Case
Concrete example of how this would be used.

## Possible Implementation
Optional: suggest how this could be implemented.

## Additional Context
Any other relevant information.
```

## 📄 License

By contributing, you agree that your contributions will be licensed under the same MIT License that covers the project. See the [LICENSE](./LICENSE) file for details.

## ❓ Questions or Need Help?

- **GitHub Issues**: Ask questions in GitHub Issues
- **GitHub Discussions**: Use Discussions for broader topics
- **Email**: Contact the maintainer at cb.en.u4eee23103@cb.students.amrita.edu

## 🙏 Thank You!

Thank you for taking the time to contribute! Your help is greatly appreciated and helps make this project better for everyone.

---

**Happy Contributing!** ⭐

If you found this contribution guide helpful, please consider giving the repository a star!