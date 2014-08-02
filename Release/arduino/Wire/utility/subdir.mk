################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Applications/arduino-1.5.2/hardware/teensy/all/libraries/Wire/utility/twi.c 

C_DEPS += \
./arduino/twi.c.d 

AR_OBJ += \
./arduino/twi.c.o 


# Each subdirectory must supply rules for building sources it contributes
arduino/twi.c.o: C:/Applications/arduino-1.5.2/hardware/teensy/all/libraries/Wire/utility/twi.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-gcc" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=152 -D__SAM3X8E__ -mthumb -DUSB_PID=0x003e -DUSB_VID=0x2341 -DUSBCON "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/libsam" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\cores\arduino" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\variants\arduino_due_x" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


