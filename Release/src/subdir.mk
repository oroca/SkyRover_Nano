################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/buzzer.c \
../src/cli.c \
../src/config.c \
../src/drv_adc.c \
../src/drv_adxl345.c \
../src/drv_bma280.c \
../src/drv_bmp085.c \
../src/drv_gpio.c \
../src/drv_hcsr04.c \
../src/drv_hmc5883l.c \
../src/drv_i2c.c \
../src/drv_i2c_soft.c \
../src/drv_l3g4200d.c \
../src/drv_ledring.c \
../src/drv_mma845x.c \
../src/drv_mpu3050.c \
../src/drv_mpu6050.c \
../src/drv_ms5611.c \
../src/drv_pwm.c \
../src/drv_serial.c \
../src/drv_softserial.c \
../src/drv_spi.c \
../src/drv_system.c \
../src/drv_timer.c \
../src/drv_uart.c \
../src/drv_vcom.c \
../src/drv_vcom_q.c \
../src/gps.c \
../src/hexairbot.c \
../src/imu.c \
../src/main.c \
../src/mixer.c \
../src/mw.c \
../src/printf.c \
../src/sbus.c \
../src/sensors.c \
../src/serial.c \
../src/spektrum.c \
../src/sumd.c \
../src/telemetry.c \
../src/utils.c 

OBJS += \
./src/buzzer.o \
./src/cli.o \
./src/config.o \
./src/drv_adc.o \
./src/drv_adxl345.o \
./src/drv_bma280.o \
./src/drv_bmp085.o \
./src/drv_gpio.o \
./src/drv_hcsr04.o \
./src/drv_hmc5883l.o \
./src/drv_i2c.o \
./src/drv_i2c_soft.o \
./src/drv_l3g4200d.o \
./src/drv_ledring.o \
./src/drv_mma845x.o \
./src/drv_mpu3050.o \
./src/drv_mpu6050.o \
./src/drv_ms5611.o \
./src/drv_pwm.o \
./src/drv_serial.o \
./src/drv_softserial.o \
./src/drv_spi.o \
./src/drv_system.o \
./src/drv_timer.o \
./src/drv_uart.o \
./src/drv_vcom.o \
./src/drv_vcom_q.o \
./src/gps.o \
./src/hexairbot.o \
./src/imu.o \
./src/main.o \
./src/mixer.o \
./src/mw.o \
./src/printf.o \
./src/sbus.o \
./src/sensors.o \
./src/serial.o \
./src/spektrum.o \
./src/sumd.o \
./src/telemetry.o \
./src/utils.o 

C_DEPS += \
./src/buzzer.d \
./src/cli.d \
./src/config.d \
./src/drv_adc.d \
./src/drv_adxl345.d \
./src/drv_bma280.d \
./src/drv_bmp085.d \
./src/drv_gpio.d \
./src/drv_hcsr04.d \
./src/drv_hmc5883l.d \
./src/drv_i2c.d \
./src/drv_i2c_soft.d \
./src/drv_l3g4200d.d \
./src/drv_ledring.d \
./src/drv_mma845x.d \
./src/drv_mpu3050.d \
./src/drv_mpu6050.d \
./src/drv_ms5611.d \
./src/drv_pwm.d \
./src/drv_serial.d \
./src/drv_softserial.d \
./src/drv_spi.d \
./src/drv_system.d \
./src/drv_timer.d \
./src/drv_uart.d \
./src/drv_vcom.d \
./src/drv_vcom_q.d \
./src/gps.d \
./src/hexairbot.d \
./src/imu.d \
./src/main.d \
./src/mixer.d \
./src/mw.d \
./src/printf.d \
./src/sbus.d \
./src/sensors.d \
./src/serial.d \
./src/spektrum.d \
./src/sumd.d \
./src/telemetry.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DBOOT=1 -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\src" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\STM32F10x_StdPeriph_Driver\inc" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\CMSIS\Include" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\CMSIS\Device\ST\STM32F10x" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\CMSIS_RTOS" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\include" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\FreeRTOS\Source\portable\GCC\ARM_CM3" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\STM32_USB-FS-Device_Driver\inc" -I"D:\SmartRover-DevFrame-x86-64\workspace\eclipse\SkyRover_Rev1\lib\USB_Port" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


