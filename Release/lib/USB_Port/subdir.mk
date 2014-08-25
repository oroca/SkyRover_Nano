################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/USB_Port/hw_config.c \
../lib/USB_Port/usb_desc.c \
../lib/USB_Port/usb_endp.c \
../lib/USB_Port/usb_istr.c \
../lib/USB_Port/usb_prop.c \
../lib/USB_Port/usb_pwr.c 

OBJS += \
./lib/USB_Port/hw_config.o \
./lib/USB_Port/usb_desc.o \
./lib/USB_Port/usb_endp.o \
./lib/USB_Port/usb_istr.o \
./lib/USB_Port/usb_prop.o \
./lib/USB_Port/usb_pwr.o 

C_DEPS += \
./lib/USB_Port/hw_config.d \
./lib/USB_Port/usb_desc.d \
./lib/USB_Port/usb_endp.d \
./lib/USB_Port/usb_istr.d \
./lib/USB_Port/usb_prop.d \
./lib/USB_Port/usb_pwr.d 


# Each subdirectory must supply rules for building sources it contributes
lib/USB_Port/%.o: ../lib/USB_Port/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DBOOT=1 -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\src" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\STM32F10x_StdPeriph_Driver\inc" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\CMSIS\Include" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\CMSIS\Device\ST\STM32F10x" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\CMSIS_RTOS" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\include" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\portable\GCC\ARM_CM3" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\STM32_USB-FS-Device_Driver\inc" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\USB_Port" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


