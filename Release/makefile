################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utils/subdir.mk
-include libraries/Scheduler/subdir.mk
-include libraries/SCoop/subdir.mk
-include libraries/Due-RTC/subdir.mk
-include comstack/subdir.mk
-include arduino/variant/subdir.mk
-include arduino/core/USB/subdir.mk
-include arduino/core/subdir.mk
-include arduino/Wire/utility/subdir.mk
-include arduino/Wire/subdir.mk
-include arduino/Time/subdir.mk
-include arduino/SPI/subdir.mk
-include arduino/SD/utility/subdir.mk
-include arduino/SD/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
D:/Daten/Projekte/Arduino/DarkSkyOne/Release/arduino.ar \

ELF += \
DarkSkyOne.elf \

EEP += \
DarkSkyOne.eep \

FLASH_IMAGE += \
Release/DarkSkyOne.bin \


# All Target
all: DarkSkyOne

# Tool invocations
DarkSkyOne: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-size" -A "D:/Daten/Projekte/Arduino/DarkSkyOne/Release/DarkSkyOne.elf"
	@echo 'Finished building target: $@'
	@echo ' '

D:/Daten/Projekte/Arduino/DarkSkyOne/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-ar" rcs "D:/Daten/Projekte/Arduino/DarkSkyOne/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

DarkSkyOne.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-g++" -Os -Wl,--gc-sections -mcpu=cortex-m3 "-T/C:/Applications/arduino-1.5.2/hardware/arduino/sam/variants/arduino_due_x/linker_scripts/gcc/flash.ld" "-Wl,-Map,D:/Daten/Projekte/Arduino/DarkSkyOne/Release/DarkSkyOne.map" -o "D:/Daten/Projekte/Arduino/DarkSkyOne/Release/DarkSkyOne.elf" "-LD:/Daten/Projekte/Arduino/DarkSkyOne/Release" -lm -lgcc -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--start-group "D:/Daten/Projekte/Arduino/DarkSkyOne/Release/arduino/syscalls_sam3.c.o"   $(LINK_OBJ) $(AR)  "/C:/Applications/arduino-1.5.2/hardware/arduino/sam/variants/arduino_due_x/libsam_sam3x8e_gcc_rel.a" "D:/Daten/Projekte/Arduino/DarkSkyOne/Release/arduino.ar" -Wl,--end-group
	@echo 'Finished building: $@'
	@echo ' '

DarkSkyOne.eep: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

Release/DarkSkyOne.bin: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"C:/Applications/arduino-1.5.2/hardware/tools/g++_arm_none_eabi/bin/arm-none-eabi-objcopy" -O binary "D:/Daten/Projekte/Arduino/DarkSkyOne/Release/DarkSkyOne.elf" "D:/Daten/Projekte/Arduino/DarkSkyOne/Release/DarkSkyOne.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELF)$(C++_DEPS)$(AR)$(C_DEPS)$(CC_DEPS)$(FLASH_IMAGE)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(EEP)$(CXX_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) DarkSkyOne
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
