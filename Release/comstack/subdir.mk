################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../comstack/ComDataLink.cpp \
../comstack/ComNetwork.cpp \
../comstack/ComStack.cpp \
../comstack/ComTCP.cpp \
../comstack/ComUDP.cpp 

CPP_DEPS += \
./comstack/ComDataLink.cpp.d \
./comstack/ComNetwork.cpp.d \
./comstack/ComStack.cpp.d \
./comstack/ComTCP.cpp.d \
./comstack/ComUDP.cpp.d 

LINK_OBJ += \
./comstack/ComDataLink.cpp.o \
./comstack/ComNetwork.cpp.o \
./comstack/ComStack.cpp.o \
./comstack/ComTCP.cpp.o \
./comstack/ComUDP.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
comstack/ComDataLink.cpp.o: ../comstack/ComDataLink.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=152 -D__SAM3X8E__ -mthumb -DUSB_PID=0x003e -DUSB_VID=0x2341 -DUSBCON "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/libsam" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\cores\arduino" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\variants\arduino_due_x" -I"C:\Applications\arduino-1.5.2\libraries\SD" -I"C:\Applications\arduino-1.5.2\libraries\SD\utility" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\libraries\SPI" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\SCoop" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Wire" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Time" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Due-RTC" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\utils" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\comstack" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\QueueList" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Scheduler" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

comstack/ComNetwork.cpp.o: ../comstack/ComNetwork.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=152 -D__SAM3X8E__ -mthumb -DUSB_PID=0x003e -DUSB_VID=0x2341 -DUSBCON "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/libsam" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\cores\arduino" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\variants\arduino_due_x" -I"C:\Applications\arduino-1.5.2\libraries\SD" -I"C:\Applications\arduino-1.5.2\libraries\SD\utility" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\libraries\SPI" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\SCoop" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Wire" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Time" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Due-RTC" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\utils" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\comstack" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\QueueList" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Scheduler" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

comstack/ComStack.cpp.o: ../comstack/ComStack.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=152 -D__SAM3X8E__ -mthumb -DUSB_PID=0x003e -DUSB_VID=0x2341 -DUSBCON "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/libsam" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\cores\arduino" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\variants\arduino_due_x" -I"C:\Applications\arduino-1.5.2\libraries\SD" -I"C:\Applications\arduino-1.5.2\libraries\SD\utility" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\libraries\SPI" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\SCoop" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Wire" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Time" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Due-RTC" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\utils" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\comstack" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\QueueList" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Scheduler" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

comstack/ComTCP.cpp.o: ../comstack/ComTCP.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=152 -D__SAM3X8E__ -mthumb -DUSB_PID=0x003e -DUSB_VID=0x2341 -DUSBCON "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/libsam" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\cores\arduino" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\variants\arduino_due_x" -I"C:\Applications\arduino-1.5.2\libraries\SD" -I"C:\Applications\arduino-1.5.2\libraries\SD\utility" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\libraries\SPI" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\SCoop" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Wire" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Time" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Due-RTC" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\utils" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\comstack" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\QueueList" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Scheduler" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

comstack/ComUDP.cpp.o: ../comstack/ComUDP.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -c -g -Os -w -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -Dprintf=iprintf -mcpu=cortex-m3 -DF_CPU=84000000L -DARDUINO=152 -D__SAM3X8E__ -mthumb -DUSB_PID=0x003e -DUSB_VID=0x2341 -DUSBCON "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/libsam" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/CMSIS/Include/" "-IC:/Applications/arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/"   -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\cores\arduino" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\variants\arduino_due_x" -I"C:\Applications\arduino-1.5.2\libraries\SD" -I"C:\Applications\arduino-1.5.2\libraries\SD\utility" -I"C:\Applications\arduino-1.5.2\hardware\arduino\sam\libraries\SPI" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\SCoop" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Wire" -I"C:\Applications\arduino-1.5.2\hardware\teensy\all\libraries\Time" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Due-RTC" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\utils" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\comstack" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\QueueList" -I"D:\Daten\Projekte\Arduino\DarkSkyOne\libraries\Scheduler" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


