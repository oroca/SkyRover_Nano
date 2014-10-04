###############################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <msmith@FreeBSD.ORG> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return
###############################################################################
#
# Makefile for building the baseflight firmware.
#
# Invoke this with 'make help' to see the list of supported targets.
# 

###############################################################################
# Things that the user might override on the commandline
#

# The target to build, must be one of NAZE, FY90Q OR OLIMEXINO
TARGET		?= SKYROVER

# Compile-time options
OPTIONS		?=

# Debugger optons, must be empty or GDB
DEBUG ?=

# BootLoader options.
BOOT ?= 1


# Serial port/Device for flashing
SERIAL_DEVICE	?= /dev/ttyUSB0

###############################################################################
# Things that need to be maintained as the source changes
#

VALID_TARGETS	 = NAZE FY90Q OLIMEXINO SKYROVER

# Working directories
ROOT		 = $(dir $(lastword $(MAKEFILE_LIST)))
LIB_DIR		 = $(ROOT)/lib
SRC_DIR		 = $(ROOT)/src
CMSIS_DIR	 = $(ROOT)/lib/CMSIS
STDPERIPH_DIR	 = $(ROOT)/lib/STM32F10x_StdPeriph_Driver
OBJECT_DIR	 = $(ROOT)/obj
BIN_DIR		 = $(ROOT)/obj
RTOS_DIR	 = $(ROOT)/lib/FreeRTOS
U8GLIB_DIR	 = $(ROOT)/lib/u8glib


# Source files common to all targets
COMMON_SRC	 = startup_stm32f10x_md_gcc.s \
		   buzzer.c \
		   cli.c \
		   config.c \
		   gps.c \
		   imu.c \
		   main.c \
		   mixer.c \
		   mw.c \
		   sensors.c \
		   serial.c \
		   sbus.c \
		   sumd.c \
		   spektrum.c \
		   telemetry.c \
		   drv_gpio.c \
		   drv_i2c.c \
		   drv_i2c_soft.c \
		   drv_system.c \
		   drv_serial.c \
		   drv_softserial.c \
		   drv_uart.c \
		   drv_vcom.c \
		   drv_vcom_q.c \
		   drv_u8g.c \
		   printf.c \
		   utils.c \
		   $(CMSIS_SRC) \
		   $(STDPERIPH_SRC) \
		   $(RTOS_1_SRC) \
		   $(RTOS_2_SRC) \
		   $(RTOS_3_SRC) \
		   $(USB_1_SRC)  \
		   $(USB_2_SRC)	 \
		   $(THREAD_SRC) \
		   $(U8GLIB_SRC) 


# Source files for the NAZE target
NAZE_SRC	 = drv_adc.c \
		   drv_adxl345.c \
		   drv_bma280.c \
		   drv_bmp085.c \
		   drv_ms5611.c \
		   drv_hcsr04.c \
		   drv_hmc5883l.c \
		   drv_ledring.c \
		   drv_mma845x.c \
		   drv_mpu3050.c \
		   drv_mpu6050.c \
		   drv_l3g4200d.c \
		   drv_pwm.c \
		   drv_spi.c \
		   drv_timer.c \
		   $(COMMON_SRC)

# Source files for the FY90Q target
FY90Q_SRC	 = drv_adc_fy90q.c \
		   drv_pwm_fy90q.c \
		   $(COMMON_SRC)

# Source files for the OLIMEXINO target
OLIMEXINO_SRC	 = drv_spi.c \
		   drv_adc.c \
		   drv_adxl345.c \
		   drv_mpu3050.c \
		   drv_mpu6050.c \
		   drv_l3g4200d.c \
		   drv_pwm.c \
		   drv_timer.c \
		   $(COMMON_SRC)

# Source files for the SKYROVER target
SKYROVER_SRC	 = drv_adc.c \
		   drv_adxl345.c \
		   drv_bma280.c \
		   drv_bmp085.c \
		   drv_ms5611.c \
		   drv_hcsr04.c \
		   drv_hmc5883l.c \
		   drv_ledring.c \
		   drv_mma845x.c \
		   drv_mpu3050.c \
		   drv_mpu6050.c \
		   drv_l3g4200d.c \
		   drv_pwm.c \
		   drv_spi.c \
		   drv_timer.c \
		   hexairbot.c \
		   $(COMMON_SRC)


RTOS_SRC		= cmsis_os.c \
		   port.c \
		   croutine.c \
		   list.c \
		   queue.c \
		   tasks.c \
		   timers.c 



		   
# In some cases, %.s regarded as intermediate file, which is actually not.
# This will prevent accidental deletion of startup code.
.PRECIOUS: %.s

# Search path for baseflight sources
#VPATH		:= $(SRC_DIR):$(SRC_DIR)/baseflight_startups
VPATH		:= $(SRC_DIR)

# Search path and source files for the CMSIS sources
VPATH		:= $(VPATH):$(CMSIS_DIR)/Device/ST/STM32F10x
#CMSIS_SRC	 = $(notdir $(wildcard $(CMSIS_DIR)/CM3/CoreSupport/*.c \
#			               $(CMSIS_DIR)/CM3/DeviceSupport/ST/STM32F10x/*.c))
CMSIS_SRC	 = $(notdir $(wildcard $(CMSIS_DIR)/Device/ST/STM32F10x/*.c))

# Search path and source files for the ST stdperiph library
VPATH		:= $(VPATH):$(STDPERIPH_DIR)/src
STDPERIPH_SRC	 = $(notdir $(wildcard $(STDPERIPH_DIR)/src/*.c))

# Search path and source files for FreeRTOS
VPATH		:= $(VPATH):$(RTOS_DIR)/Source
RTOS_1_SRC	 = $(notdir $(wildcard $(RTOS_DIR)/Source/*.c))
VPATH		:= $(VPATH):$(RTOS_DIR)/Source/CMSIS_RTOS
RTOS_2_SRC	 = $(notdir $(wildcard $(RTOS_DIR)/Source/CMSIS_RTOS/*.c))
VPATH		:= $(VPATH):$(RTOS_DIR)/Source/portable/GCC/ARM_CM3
RTOS_3_SRC	 = $(notdir $(wildcard $(RTOS_DIR)/Source/portable/GCC/ARM_CM3/*.c))


# Search path and source files for USB
VPATH		:= $(VPATH):$(LIB_DIR)/STM32_USB-FS-Device_Driver/src
USB_1_SRC	 = $(notdir $(wildcard $(LIB_DIR)/STM32_USB-FS-Device_Driver/src/*.c))
VPATH		:= $(VPATH):$(LIB_DIR)/USB_Port
USB_2_SRC	 = $(notdir $(wildcard $(LIB_DIR)/USB_Port/*.c))

# Search path and source files for thread
VPATH		:= $(VPATH):$(SRC_DIR)/thread
THREAD_SRC	 = $(notdir $(wildcard $(SRC_DIR)/thread/*.c))

# Search path and source files for u8glib
VPATH		:= $(VPATH):$(U8GLIB_DIR)/src
U8GLIB_SRC	 = $(notdir $(wildcard $(U8GLIB_DIR)/src/*.c))


###############################################################################
# Things that might need changing to use different tools
#

# Tool names
CC		 = arm-none-eabi-gcc
OBJCOPY	 = arm-none-eabi-objcopy
SIZE     = arm-none-eabi-size
#
# Tool options.
#
INCLUDE_DIRS	 = $(SRC_DIR) \
		   $(STDPERIPH_DIR)/inc \
		   $(CMSIS_DIR)/Include \
		   $(CMSIS_DIR)/Device/ST/STM32F10x \
		   $(RTOS_DIR)/Source/CMSIS_RTOS \
		   $(RTOS_DIR)/Source/include \
		   $(RTOS_DIR)/Source/portable/GCC/ARM_CM3 \
		   $(LIB_DIR)/STM32_USB-FS-Device_Driver/inc \
		   $(LIB_DIR)/USB_Port \
		   $(SRC_DIR)/thread \
		   $(U8GLIB_DIR)/src \





ARCH_FLAGS	 = -mthumb -mcpu=cortex-m3
BASE_CFLAGS	 = $(ARCH_FLAGS) \
		   $(addprefix -D,$(OPTIONS)) \
		   $(addprefix -I,$(INCLUDE_DIRS)) \
		   -Wall \
		   -ffunction-sections \
		   -fdata-sections \
		   -DSTM32F10X_MD \
		   -DUSE_STDPERIPH_DRIVER \
		   -D$(TARGET) \
		   -DUSE_BOOT=$(BOOT)

ASFLAGS		 = $(ARCH_FLAGS) \
		   -x assembler-with-cpp \
		   $(addprefix -I,$(INCLUDE_DIRS))

# XXX Map/crossref output?

ifeq ($(BOOT),1)
LD_SCRIPT	 = $(ROOT)/stm32_flash_boot.ld
else
LD_SCRIPT	 = $(ROOT)/stm32_flash.ld
endif

LDFLAGS		 = -lm \
		   $(ARCH_FLAGS) \
		   -static \
		   -Wl,-gc-sections,-Map,$(TARGET_MAP) \
		   -T$(LD_SCRIPT)

###############################################################################
# No user-serviceable parts below
###############################################################################

#
# Things we will build
#
ifeq ($(filter $(TARGET),$(VALID_TARGETS)),)
$(error Target '$(TARGET)' is not valid, must be one of $(VALID_TARGETS))
endif

ifeq ($(DEBUG),GDB)
CFLAGS = $(BASE_CFLAGS) \
	-ggdb \
	-O0
else
CFLAGS = $(BASE_CFLAGS) \
	-Os
endif


TARGET_HEX	 = $(BIN_DIR)/$(TARGET).hex
TARGET_BIN	 = $(BIN_DIR)/$(TARGET).bin
TARGET_ELF	 = $(BIN_DIR)/$(TARGET).elf
TARGET_OBJS	 = $(addsuffix .o,$(addprefix $(OBJECT_DIR)/$(TARGET)/,$(basename $($(TARGET)_SRC))))
TARGET_MAP   = $(OBJECT_DIR)/$(TARGET).map


all: create_dir $(TARGET_HEX)

create_dir:
	@echo "Create $(OBJECT_DIR)/$(TARGET)"
ifeq ($(ComSpec),)
	$(shell [ -d $(OBJECT_DIR)/$(TARGET) ] || mkdir -p $(OBJECT_DIR)/$(TARGET))
else
	@echo "@md $(OBJECT_DIR)\$(TARGET) >NUL 2>&1"
	@md obj\$(TARGET) >NUL 2>&1 || echo "" >NUL
endif


# List of buildable ELF files and their object dependencies.
# It would be nice to compute these lists, but that seems to be just beyond make.

$(TARGET_HEX): $(TARGET_ELF) $(TARGET_BIN)
	$(OBJCOPY) -O ihex --set-start 0x8000000 $< $@

$(TARGET_BIN): $(TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

$(TARGET_ELF):  $(TARGET_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile
$(OBJECT_DIR)/$(TARGET)/%.o: %.c
#	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(CFLAGS) $<

# Assemble
$(OBJECT_DIR)/$(TARGET)/%.o: %.s
#	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(ASFLAGS) $< 
$(OBJECT_DIR)/$(TARGET)/%.o): %.S
#	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(ASFLAGS) $< 


all: $(TARGET_ELF) $(TARGET_BIN)

clean:
	rm -f $(TARGET_HEX) $(TARGET_ELF) $(TARGET_OBJS) $(TARGET_MAP)

flash_$(TARGET): $(TARGET_HEX)
	stty -F $(SERIAL_DEVICE) raw speed 115200 -crtscts cs8 -parenb -cstopb -ixon
	echo -n 'R' >$(SERIAL_DEVICE)
	stm32flash -w $(TARGET_HEX) -v -g 0x0 -b 115200 $(SERIAL_DEVICE)

flash: flash_$(TARGET)


unbrick_$(TARGET): $(TARGET_HEX)
	stty -F $(SERIAL_DEVICE) raw speed 115200 -crtscts cs8 -parenb -cstopb -ixon
	stm32flash -w $(TARGET_HEX) -v -g 0x0 -b 115200 $(SERIAL_DEVICE)

unbrick: unbrick_$(TARGET)

ELFSIZE = $(SIZE) -A $(TARGET_ELF)

sizeinfo:
	$(ELFSIZE)

help:
	@echo ""
	@echo "Makefile for the baseflight firmware"
	@echo ""
	@echo "Usage:"
	@echo "        make [TARGET=<target>] [OPTIONS=\"<options>\"]"
	@echo ""
	@echo "Valid TARGET values are: $(VALID_TARGETS)"
	@echo ""
