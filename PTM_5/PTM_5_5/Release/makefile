################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
PTM_5_5.lss \

FLASH_IMAGE += \
PTM_5_5.hex \

EEPROM_IMAGE += \
PTM_5_5.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: PTM_5_5.elf secondary-outputs

# Tool invocations
PTM_5_5.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,PTM_5_5.map -mmcu=atmega32 -o "PTM_5_5.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

PTM_5_5.lss: PTM_5_5.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S PTM_5_5.elf  >"PTM_5_5.lss"
	@echo 'Finished building: $@'
	@echo ' '

PTM_5_5.hex: PTM_5_5.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex PTM_5_5.elf  "PTM_5_5.hex"
	@echo 'Finished building: $@'
	@echo ' '

PTM_5_5.eep: PTM_5_5.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex PTM_5_5.elf  "PTM_5_5.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: PTM_5_5.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 PTM_5_5.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) PTM_5_5.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
