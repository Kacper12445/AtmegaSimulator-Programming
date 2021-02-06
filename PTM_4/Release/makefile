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
PTM_4.lss \

FLASH_IMAGE += \
PTM_4.hex \

EEPROM_IMAGE += \
PTM_4.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: PTM_4.elf secondary-outputs

# Tool invocations
PTM_4.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,PTM_4.map -mmcu=atmega32 -o "PTM_4.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

PTM_4.lss: PTM_4.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S PTM_4.elf  >"PTM_4.lss"
	@echo 'Finished building: $@'
	@echo ' '

PTM_4.hex: PTM_4.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex PTM_4.elf  "PTM_4.hex"
	@echo 'Finished building: $@'
	@echo ' '

PTM_4.eep: PTM_4.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex PTM_4.elf  "PTM_4.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: PTM_4.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 PTM_4.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) PTM_4.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
