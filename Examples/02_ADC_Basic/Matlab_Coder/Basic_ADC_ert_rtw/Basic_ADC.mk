###########################################################################
## Makefile generated for component 'Basic_ADC'. 
## 
## Makefile     : Basic_ADC.mk
## Generated on : Sat Feb 14 22:26:49 2026
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/Basic_ADC.elf
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file

PRODUCT_NAME              = Basic_ADC
MAKEFILE                  = Basic_ADC.mk
MATLAB_ROOT               = C:/PROGRA~1/MATLAB/R2025a
MATLAB_BIN                = C:/PROGRA~1/MATLAB/R2025a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = C:/Users/GNKRISHNAN/Documents/GitHub/NUCLEO-G474RE-PowerElectronics-Guide/Examples/02_ADC_Basic/Matlab_Coder
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = ISO_C
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0
RELATIVE_PATH_TO_ANCHOR   = ..
COMPILER_COMMAND_FILE     = Basic_ADC_comp.rsp
CMD_FILE                  = Basic_ADC.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU Tools for ARM Embedded Processors
# Supported Version(s):    
# ToolchainInfo Version:   2025a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# TARGET_LOAD_CMD_ARGS
# TARGET_LOAD_CMD
# MW_GNU_ARM_TOOLS_PATH
# FDATASECTIONS_FLG

#-----------
# MACROS
#-----------

LIBGCC                    = ${shell $(MW_GNU_ARM_TOOLS_PATH)/arm-none-eabi-gcc ${CFLAGS} -print-libgcc-file-name}
LIBC                      = ${shell $(MW_GNU_ARM_TOOLS_PATH)/arm-none-eabi-gcc ${CFLAGS} -print-file-name=libc.a}
LIBM                      = ${shell $(MW_GNU_ARM_TOOLS_PATH)/arm-none-eabi-gcc ${CFLAGS} -print-file-name=libm.a}
PRODUCT_NAME_WITHOUT_EXTN = $(basename $(PRODUCT))
PRODUCT_BIN               = $(PRODUCT_NAME_WITHOUT_EXTN).bin
PRODUCT_HEX               = $(PRODUCT_NAME_WITHOUT_EXTN).hex
CPFLAGS                   = -O binary
SHELL                     = %SystemRoot%/system32/cmd.exe

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lm

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: GNU ARM Assembler
AS_PATH = $(MW_GNU_ARM_TOOLS_PATH)
AS = "$(AS_PATH)/arm-none-eabi-gcc"

# C Compiler: GNU ARM C Compiler
CC_PATH = $(MW_GNU_ARM_TOOLS_PATH)
CC = "$(CC_PATH)/arm-none-eabi-gcc"

# Linker: GNU ARM Linker
LD_PATH = $(MW_GNU_ARM_TOOLS_PATH)
LD = "$(LD_PATH)/arm-none-eabi-g++"

# C++ Compiler: GNU ARM C++ Compiler
CPP_PATH = $(MW_GNU_ARM_TOOLS_PATH)
CPP = "$(CPP_PATH)/arm-none-eabi-g++"

# C++ Linker: GNU ARM C++ Linker
CPP_LD_PATH = $(MW_GNU_ARM_TOOLS_PATH)
CPP_LD = "$(CPP_LD_PATH)/arm-none-eabi-g++"

# Archiver: GNU ARM Archiver
AR_PATH = $(MW_GNU_ARM_TOOLS_PATH)
AR = "$(AR_PATH)/arm-none-eabi-ar"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Binary Converter: Binary Converter
OBJCOPYPATH = $(MW_GNU_ARM_TOOLS_PATH)
OBJCOPY = "$(OBJCOPYPATH)/arm-none-eabi-objcopy"

# Hex Converter: Hex Converter
OBJCOPYPATH = $(MW_GNU_ARM_TOOLS_PATH)
OBJCOPY = "$(OBJCOPYPATH)/arm-none-eabi-objcopy"

# Executable Size: Executable Size
EXESIZEPATH = $(MW_GNU_ARM_TOOLS_PATH)
EXESIZE = "$(EXESIZEPATH)/arm-none-eabi-size"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = -o
CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @del /f/q
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = ruvs
ASFLAGS              = -MMD -MP -MF"$(@:%.s.o=%.s.dep)" -MT"$@"  \
                       -Wall \
                       -x assembler-with-cpp \
                       $(ASFLAGS_ADDITIONAL) \
                       $(DEFINES) \
                       $(INCLUDES) \
                       -c
OBJCOPYFLAGS_BIN     = -O binary $(PRODUCT) $(PRODUCT_BIN)
CFLAGS               = $(FDATASECTIONS_FLG) \
                       -Wall \
                       -c \
                       -MMD -MP -MF"$(@:%.c.o=%.c.dep)" -MT"$@"  \
                       -O0
CPPFLAGS             = -std=gnu++14 \
                       -fno-rtti \
                       -fno-exceptions \
                       $(FDATASECTIONS_FLG) \
                       -Wall \
                       -c \
                       -MMD -MP -MF"$(@:%.cpp.o=%.cpp.dep)" -MT"$@"  \
                       -O0
CPP_LDFLAGS          = -Wl,--gc-sections \
                       -Wl,-Map="$(PRODUCT_NAME).map"
CPP_SHAREDLIB_LDFLAGS  =
DOWNLOAD_FLAGS       =
EXESIZE_FLAGS        = $(PRODUCT)
EXECUTE_FLAGS        =
OBJCOPYFLAGS_HEX     = -O ihex $(PRODUCT) $(PRODUCT_HEX)
LDFLAGS              = -Wl,--gc-sections \
                       -Wl,-Map="$(PRODUCT_NAME).map"
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    =



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/Basic_ADC.elf
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DUSE_FULL_LL_DRIVER -DSTM32G474xx -DUSE_HAL_DRIVER -DMW_TIMEBASESOURCE=TIM2 -DMW_GPIO_BIT_SHIFT=0 -DMW_CubeMXVersion_6.12.0
DEFINES_BUILD_ARGS = -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0
DEFINES_CUSTOM = 
DEFINES_OPTS = -DTID01EQ=0
DEFINES_SKIPFORSIL = -DXCP_CUSTOM_PLATFORM -D__FPU_PRESENT=1U -D__FPU_USED=1U -DSTACK_SIZE=512 -DRT
DEFINES_STANDARD = -DMODEL=Basic_ADC -DNUMST=1 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0
DEFINES_STM32DEVICEDRIVERBLOCKS = -DMW_ADC1_ENABLED=1 -DMW_ADC1_VAR=mw_adc1

DEFINES = $(DEFINES_) $(DEFINES_BUILD_ARGS) $(DEFINES_CUSTOM) $(DEFINES_OPTS) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD) $(DEFINES_STM32DEVICEDRIVERBLOCKS)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/Basic_ADC_ert_rtw/Basic_ADC.c C:/ProgramData/MATLAB/SupportPackages/R2025a/toolbox/shared/supportpackages/stm32/src/overrideHALDelay.c C:/ProgramData/MATLAB/SupportPackages/R2025a/toolbox/shared/supportpackages/stm32/src/platform_timer.c $(MATLAB_ROOT)/toolbox/target/shared/armcortexmbase/scheduler/src/SysTickScheduler.c $(MATLAB_ROOT)/toolbox/target/shared/armcortexmbase/scheduler/src/m3m4m4f_multitasking.c $(START_DIR)/basicadc/Core/Src/main.c $(START_DIR)/basicadc/Core/Src/stm32g4xx_it.c $(START_DIR)/basicadc/Core/Src/stm32g4xx_hal_msp.c $(START_DIR)/basicadc/Core/Src/stm32g4xx_hal_timebase_tim.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_utils.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_exti.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_gpio.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_adc.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_dma.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_pwr.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_lpuart.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_rcc.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c $(START_DIR)/basicadc/Core/Src/system_stm32g4xx.c $(START_DIR)/basicadc/STM32CubeIDE/Application/User/Core/syscalls.c $(START_DIR)/basicadc/STM32CubeIDE/Application/User/Core/sysmem.c $(START_DIR)/basicadc/STM32CubeIDE/Application/User/Startup/startup_stm32g474retx.s C:/ProgramData/MATLAB/SupportPackages/R2025a/toolbox/shared/supportpackages/stm32/src/stm_adc_ll.c

MAIN_SRC = $(START_DIR)/Basic_ADC_ert_rtw/ert_main.c

ALL_SRCS = $(SRCS) $(MAIN_SRC)

###########################################################################
## OBJECTS
###########################################################################

OBJS = Basic_ADC.c.o overrideHALDelay.c.o platform_timer.c.o SysTickScheduler.c.o m3m4m4f_multitasking.c.o main.c.o stm32g4xx_it.c.o stm32g4xx_hal_msp.c.o stm32g4xx_hal_timebase_tim.c.o stm32g4xx_ll_utils.c.o stm32g4xx_ll_exti.c.o stm32g4xx_ll_gpio.c.o stm32g4xx_ll_adc.c.o stm32g4xx_ll_dma.c.o stm32g4xx_ll_pwr.c.o stm32g4xx_hal.c.o stm32g4xx_hal_rcc.c.o stm32g4xx_hal_rcc_ex.c.o stm32g4xx_hal_flash.c.o stm32g4xx_hal_flash_ex.c.o stm32g4xx_hal_flash_ramfunc.c.o stm32g4xx_hal_gpio.c.o stm32g4xx_hal_exti.c.o stm32g4xx_hal_dma.c.o stm32g4xx_hal_dma_ex.c.o stm32g4xx_hal_pwr.c.o stm32g4xx_hal_pwr_ex.c.o stm32g4xx_hal_cortex.c.o stm32g4xx_ll_lpuart.c.o stm32g4xx_ll_rcc.c.o stm32g4xx_hal_tim.c.o stm32g4xx_hal_tim_ex.c.o system_stm32g4xx.c.o syscalls.c.o sysmem.c.o startup_stm32g474retx.s.o stm_adc_ll.c.o

MAIN_OBJ = ert_main.c.o

ALL_OBJS = $(OBJS) $(MAIN_OBJ)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = C:/ProgramData/MATLAB/SupportPackages/R2025a/3P.instrset/cmsis_dsp.instrset/Lib/GCC/arm_cortexm4ldfsp_math/libCMSISDSP.a C:/ProgramData/MATLAB/SupportPackages/R2025a/toolbox/shared/supportpackages/stm32/lib/GCC/libmw_pdmfilter_m4_spfp.lib

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffp-contract=off
CFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CFLAGS += $(CFLAGS_SKIPFORSIL) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffp-contract=off
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS += $(CPPFLAGS_SKIPFORSIL) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard --entry Reset_Handler --specs=nosys.specs  -T "C:\Users\GNKRISHNAN\Documents\GitHub\NUCLEO-G474RE-PowerElectronics-Guide\Examples\02_ADC_Basic\Matlab_Coder\basicadc\STM32CubeIDE\STM32G474RETX_FLASH.ld"

CPP_LDFLAGS += $(CPP_LDFLAGS_SKIPFORSIL)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard --entry Reset_Handler --specs=nosys.specs  -T "C:\Users\GNKRISHNAN\Documents\GitHub\NUCLEO-G474RE-PowerElectronics-Guide\Examples\02_ADC_Basic\Matlab_Coder\basicadc\STM32CubeIDE\STM32G474RETX_FLASH.ld"

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL)

#-----------
# Linker
#-----------

LDFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard --entry Reset_Handler --specs=nosys.specs  -T "C:\Users\GNKRISHNAN\Documents\GitHub\NUCLEO-G474RE-PowerElectronics-Guide\Examples\02_ADC_Basic\Matlab_Coder\basicadc\STM32CubeIDE\STM32G474RETX_FLASH.ld"

LDFLAGS += $(LDFLAGS_SKIPFORSIL)

#---------------------
# MEX C++ Compiler
#---------------------

MEX_CPP_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CPPFLAGS += $(MEX_CPP_Compiler_BASIC)

#-----------------
# MEX Compiler
#-----------------

MEX_Compiler_BASIC =  @$(COMPILER_COMMAND_FILE)

MEX_CFLAGS += $(MEX_Compiler_BASIC)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_SKIPFORSIL = -mcpu=cortex-m4 -mthumb -mlittle-endian -mthumb-interwork -mfpu=fpv4-sp-d16 -mfloat-abi=hard --entry Reset_Handler --specs=nosys.specs  -T "C:\Users\GNKRISHNAN\Documents\GitHub\NUCLEO-G474RE-PowerElectronics-Guide\Examples\02_ADC_Basic\Matlab_Coder\basicadc\STM32CubeIDE\STM32G474RETX_FLASH.ld"

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_SKIPFORSIL)

###########################################################################
## INLINED COMMANDS
###########################################################################


ALL_DEPS:=$(patsubst %.o,%.dep,$(ALL_OBJS))
all:

ifndef DISABLE_GCC_FUNCTION_DATA_SECTIONS
FDATASECTIONS_FLG := -ffunction-sections -fdata-sections
endif



-include codertarget_assembly_flags.mk
-include ../codertarget_assembly_flags.mk
-include ../../codertarget_assembly_flags.mk
-include mw_gnu_arm_tools_path.mk
-include ../mw_gnu_arm_tools_path.mk
-include ../../mw_gnu_arm_tools_path.mk
-include $(ALL_DEPS)


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild postbuild download execute


all : build postbuild
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


postbuild : $(PRODUCT)
	@echo "### Invoking postbuild tool "Binary Converter" ..."
	$(OBJCOPY) $(OBJCOPYFLAGS_BIN)
	@echo "### Done invoking postbuild tool."
	@echo "### Invoking postbuild tool "Hex Converter" ..."
	$(OBJCOPY) $(OBJCOPYFLAGS_HEX)
	@echo "### Done invoking postbuild tool."
	@echo "### Invoking postbuild tool "Executable Size" ..."
	$(EXESIZE) $(EXESIZE_FLAGS)
	@echo "### Done invoking postbuild tool."


download : postbuild


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS) $(MAIN_OBJ)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(LD) $(LDFLAGS) -o $(PRODUCT) @$(CMD_FILE) $(LIBS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.c.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : %.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.s.o : %.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : %.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : %.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : %.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.s.o : $(RELATIVE_PATH_TO_ANCHOR)/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(RELATIVE_PATH_TO_ANCHOR)/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/Basic_ADC_ert_rtw/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/Basic_ADC_ert_rtw/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/Basic_ADC_ert_rtw/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/Basic_ADC_ert_rtw/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/Basic_ADC_ert_rtw/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/Basic_ADC_ert_rtw/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/Basic_ADC_ert_rtw/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_ROOT)/rtw/c/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_ROOT)/rtw/c/src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/rtw/c/src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/rtw/c/src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/rtw/c/src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_ROOT)/simulink/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_ROOT)/simulink/src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/simulink/src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/simulink/src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/simulink/src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(MATLAB_ROOT)/toolbox/simulink/blocks/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_ROOT)/toolbox/simulink/blocks/src/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_ROOT)/toolbox/simulink/blocks/src/%.S
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/toolbox/simulink/blocks/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/toolbox/simulink/blocks/src/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/toolbox/simulink/blocks/src/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_ROOT)/toolbox/simulink/blocks/src/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


Basic_ADC.c.o : $(START_DIR)/Basic_ADC_ert_rtw/Basic_ADC.c
	$(CC) $(CFLAGS) -o "$@" "$<"


ert_main.c.o : $(START_DIR)/Basic_ADC_ert_rtw/ert_main.c
	$(CC) $(CFLAGS) -o "$@" "$<"


overrideHALDelay.c.o : C:/ProgramData/MATLAB/SupportPackages/R2025a/toolbox/shared/supportpackages/stm32/src/overrideHALDelay.c
	$(CC) $(CFLAGS) -o "$@" "$<"


platform_timer.c.o : C:/ProgramData/MATLAB/SupportPackages/R2025a/toolbox/shared/supportpackages/stm32/src/platform_timer.c
	$(CC) $(CFLAGS) -o "$@" "$<"


SysTickScheduler.c.o : $(MATLAB_ROOT)/toolbox/target/shared/armcortexmbase/scheduler/src/SysTickScheduler.c
	$(CC) $(CFLAGS) -o "$@" "$<"


m3m4m4f_multitasking.c.o : $(MATLAB_ROOT)/toolbox/target/shared/armcortexmbase/scheduler/src/m3m4m4f_multitasking.c
	$(CC) $(CFLAGS) -o "$@" "$<"


main.c.o : $(START_DIR)/basicadc/Core/Src/main.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_it.c.o : $(START_DIR)/basicadc/Core/Src/stm32g4xx_it.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_msp.c.o : $(START_DIR)/basicadc/Core/Src/stm32g4xx_hal_msp.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_timebase_tim.c.o : $(START_DIR)/basicadc/Core/Src/stm32g4xx_hal_timebase_tim.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_ll_utils.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_utils.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_ll_exti.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_exti.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_ll_gpio.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_gpio.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_ll_adc.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_adc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_ll_dma.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_dma.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_ll_pwr.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_pwr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_rcc.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_rcc_ex.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_flash.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_flash_ex.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_flash_ramfunc.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_gpio.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_exti.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_dma.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_dma_ex.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_pwr.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_pwr_ex.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_cortex.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_ll_lpuart.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_lpuart.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_ll_rcc.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_rcc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_tim.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stm32g4xx_hal_tim_ex.c.o : $(START_DIR)/basicadc/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c
	$(CC) $(CFLAGS) -o "$@" "$<"


system_stm32g4xx.c.o : $(START_DIR)/basicadc/Core/Src/system_stm32g4xx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


syscalls.c.o : $(START_DIR)/basicadc/STM32CubeIDE/Application/User/Core/syscalls.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sysmem.c.o : $(START_DIR)/basicadc/STM32CubeIDE/Application/User/Core/sysmem.c
	$(CC) $(CFLAGS) -o "$@" "$<"


startup_stm32g474retx.s.o : $(START_DIR)/basicadc/STM32CubeIDE/Application/User/Startup/startup_stm32g474retx.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


stm_adc_ll.c.o : C:/ProgramData/MATLAB/SupportPackages/R2025a/toolbox/shared/supportpackages/stm32/src/stm_adc_ll.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### ASFLAGS = $(ASFLAGS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### OBJCOPYFLAGS_BIN = $(OBJCOPYFLAGS_BIN)"
	@echo "### OBJCOPYFLAGS_HEX = $(OBJCOPYFLAGS_HEX)"
	@echo "### EXESIZE_FLAGS = $(EXESIZE_FLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(RM) *.c.dep
	$(RM) *.cpp.dep
	$(RM) *.s.dep
	$(ECHO) "### Deleted all derived files."


