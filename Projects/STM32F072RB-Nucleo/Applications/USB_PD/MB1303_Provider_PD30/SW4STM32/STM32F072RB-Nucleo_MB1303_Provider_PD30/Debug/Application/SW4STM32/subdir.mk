################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/Andrew/Documents/Repo/STUSB1602/Projects/STM32F072RB-Nucleo/Applications/USB_PD/MB1303_Provider_PD30/SW4STM32/startup_stm32f072xb.s 

OBJS += \
./Application/SW4STM32/startup_stm32f072xb.o 

S_DEPS += \
./Application/SW4STM32/startup_stm32f072xb.d 


# Each subdirectory must supply rules for building sources it contributes
Application/SW4STM32/startup_stm32f072xb.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Projects/STM32F072RB-Nucleo/Applications/USB_PD/MB1303_Provider_PD30/SW4STM32/startup_stm32f072xb.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -c -I../../../Inc -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -x assembler-with-cpp -MMD -MP -MF"Application/SW4STM32/startup_stm32f072xb.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

