################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include lib/USB_Port/subdir.mk
-include lib/STM32_USB-FS-Device_Driver/src/subdir.mk
-include lib/STM32F10x_StdPeriph_Driver/src/subdir.mk
-include lib/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include lib/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include lib/FreeRTOS/Source/subdir.mk
-include lib/CMSIS/Device/ST/STM32F10x/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
SkyRover_Rev1.bin \

SECONDARY_SIZE += \
SkyRover_Rev1.siz \


# All Target
all: SkyRover_Rev1.elf secondary-outputs

# Tool invocations
SkyRover_Rev1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\stm32_flash.ld" -Xlinker --gc-sections -Wl,-Map,"SkyRover_Rev1.map" -o "SkyRover_Rev1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SkyRover_Rev1.bin: SkyRover_Rev1.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "SkyRover_Rev1.elf"  "SkyRover_Rev1.bin"
	@echo 'Finished building: $@'
	@echo ' '

SkyRover_Rev1.siz: SkyRover_Rev1.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "SkyRover_Rev1.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(S_UPPER_DEPS) SkyRover_Rev1.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
