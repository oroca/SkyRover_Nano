################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/FreeRTOS/Source/croutine.c \
../lib/FreeRTOS/Source/list.c \
../lib/FreeRTOS/Source/queue.c \
../lib/FreeRTOS/Source/tasks.c \
../lib/FreeRTOS/Source/timers.c 

OBJS += \
./lib/FreeRTOS/Source/croutine.o \
./lib/FreeRTOS/Source/list.o \
./lib/FreeRTOS/Source/queue.o \
./lib/FreeRTOS/Source/tasks.o \
./lib/FreeRTOS/Source/timers.o 

C_DEPS += \
./lib/FreeRTOS/Source/croutine.d \
./lib/FreeRTOS/Source/list.d \
./lib/FreeRTOS/Source/queue.d \
./lib/FreeRTOS/Source/tasks.d \
./lib/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
lib/FreeRTOS/Source/%.o: ../lib/FreeRTOS/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DBOOT=1 -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\src" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\STM32F10x_StdPeriph_Driver\inc" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\CMSIS\Include" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\CMSIS\Device\ST\STM32F10x" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\CMSIS_RTOS" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\include" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\portable\GCC\ARM_CM3" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\STM32_USB-FS-Device_Driver\inc" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\USB_Port" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


