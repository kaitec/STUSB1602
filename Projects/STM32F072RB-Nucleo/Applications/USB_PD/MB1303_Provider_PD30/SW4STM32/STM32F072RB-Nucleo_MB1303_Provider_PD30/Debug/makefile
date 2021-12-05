################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/LED_SERVER/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/portable/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/subdir.mk
-include Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/subdir.mk
-include Middlewares/ST/STM32_USBPD_Library/Core/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/STM32F0xx-Nucleo/subdir.mk
-include Drivers/BSP/P-NUCLEO-USB002/subdir.mk
-include Drivers/BSP/Components/STUSB1602/subdir.mk
-include Application/User/subdir.mk
-include Application/SW4STM32/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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
EXECUTABLES += \
STM32F072RB-Nucleo_MB1303_Provider_PD30.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32F072RB-Nucleo_MB1303_Provider_PD30.list \

OBJCOPY_BIN += \
STM32F072RB-Nucleo_MB1303_Provider_PD30.bin \


# All Target
all: STM32F072RB-Nucleo_MB1303_Provider_PD30.elf secondary-outputs

# Tool invocations
STM32F072RB-Nucleo_MB1303_Provider_PD30.elf: $(OBJS) $(USER_OBJS) ../STM32F072RBTx_FLASH.ld
	arm-none-eabi-gcc -o "STM32F072RB-Nucleo_MB1303_Provider_PD30.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"../STM32F072RBTx_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32F072RB-Nucleo_MB1303_Provider_PD30.map" -Wl,--gc-sections -static -L../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/lib --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32F072RB-Nucleo_MB1303_Provider_PD30.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32F072RB-Nucleo_MB1303_Provider_PD30.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32F072RB-Nucleo_MB1303_Provider_PD30.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32F072RB-Nucleo_MB1303_Provider_PD30.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
