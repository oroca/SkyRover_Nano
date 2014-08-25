################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/STM32_USB-FS-Device_Driver/src/usb_core.c \
../lib/STM32_USB-FS-Device_Driver/src/usb_init.c \
../lib/STM32_USB-FS-Device_Driver/src/usb_int.c \
../lib/STM32_USB-FS-Device_Driver/src/usb_mem.c \
../lib/STM32_USB-FS-Device_Driver/src/usb_regs.c \
../lib/STM32_USB-FS-Device_Driver/src/usb_sil.c 

OBJS += \
./lib/STM32_USB-FS-Device_Driver/src/usb_core.o \
./lib/STM32_USB-FS-Device_Driver/src/usb_init.o \
./lib/STM32_USB-FS-Device_Driver/src/usb_int.o \
./lib/STM32_USB-FS-Device_Driver/src/usb_mem.o \
./lib/STM32_USB-FS-Device_Driver/src/usb_regs.o \
./lib/STM32_USB-FS-Device_Driver/src/usb_sil.o 

C_DEPS += \
./lib/STM32_USB-FS-Device_Driver/src/usb_core.d \
./lib/STM32_USB-FS-Device_Driver/src/usb_init.d \
./lib/STM32_USB-FS-Device_Driver/src/usb_int.d \
./lib/STM32_USB-FS-Device_Driver/src/usb_mem.d \
./lib/STM32_USB-FS-Device_Driver/src/usb_regs.d \
./lib/STM32_USB-FS-Device_Driver/src/usb_sil.d 


# Each subdirectory must supply rules for building sources it contributes
lib/STM32_USB-FS-Device_Driver/src/%.o: ../lib/STM32_USB-FS-Device_Driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DSTM32F10X_MD -DBOOT=1 -DSKYROVER -DUSE_STDPERIPH_DRIVER -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\src" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\STM32F10x_StdPeriph_Driver\inc" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\CMSIS\Include" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\CMSIS\Device\ST\STM32F10x" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\CMSIS_RTOS" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\include" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\portable\GCC\ARM_CM3" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\STM32_USB-FS-Device_Driver\inc" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\USB_Port" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


