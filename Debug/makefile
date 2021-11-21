################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
adf7030_test_hsi.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
adf7030_test_hsi.list \

OBJCOPY_HEX += \
adf7030_test_hsi.hex \

OBJCOPY_BIN += \
adf7030_test_hsi.bin \


# All Target
all: adf7030_test_hsi.elf secondary-outputs

# Tool invocations
adf7030_test_hsi.elf: $(OBJS) $(USER_OBJS)
	arm-none-eabi-gcc -o "adf7030_test_hsi.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 --specs=nosys.specs -Wl,-Map="adf7030_test_hsi.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

adf7030_test_hsi.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "adf7030_test_hsi.list"
	@echo 'Finished building: $@'
	@echo ' '

adf7030_test_hsi.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "adf7030_test_hsi.hex"
	@echo 'Finished building: $@'
	@echo ' '

adf7030_test_hsi.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "adf7030_test_hsi.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
