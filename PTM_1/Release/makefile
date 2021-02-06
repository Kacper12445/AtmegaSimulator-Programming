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
Zadanie1.lss \

FLASH_IMAGE += \
Zadanie1.hex \

EEPROM_IMAGE += \
Zadanie1.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Zadanie1.elf secondary-outputs

# Tool invocations
Zadanie1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Zadanie1.map -mmcu=atmega32 -o "Zadanie1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Zadanie1.lss: Zadanie1.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Zadanie1.elf  >"Zadanie1.lss"
	@echo 'Finished building: $@'
	@echo ' '

Zadanie1.hex: Zadanie1.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Zadanie1.elf  "Zadanie1.hex"
	@echo 'Finished building: $@'
	@echo ' '

Zadanie1.eep: Zadanie1.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Zadanie1.elf  "Zadanie1.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Zadanie1.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Zadanie1.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Zadanie1.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
