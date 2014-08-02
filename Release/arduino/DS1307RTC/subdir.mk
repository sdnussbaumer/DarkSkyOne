################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Applications/arduino-1.5.2/hardware/teensy/all/libraries/DS1307RTC/DS1307RTC.cpp 

AR_OBJ += \
./arduino/DS1307RTC.cpp.o 

CPP_DEPS += \
./arduino/DS1307RTC.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
arduino/DS1307RTC.cpp.o: C:/Applications/arduino-1.5.2/hardware/teensy/all/libraries/DS1307RTC/DS1307RTC.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=152 -D__SAM3X8E__ -mthumb -DUSB_PID=0x003e -DUSB_VID=0x2341 -DUSBCON "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/libsam" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\cores\arduino" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\variants\arduino_due_x" -I"C:\Applications\arduino-1.5.2\libraries\SD" -I"C:\Applications\arduino-1.5.2\libraries\SD\utility" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\libraries\SPI" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\SCoop" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\DS1307RTC" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Wire" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Time" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


