################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Core/src/usbpd_dpm_core.c \
C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Core/src/usbpd_trace.c 

OBJS += \
./Middlewares/ST/STM32_USBPD_Library/Core/usbpd_dpm_core.o \
./Middlewares/ST/STM32_USBPD_Library/Core/usbpd_trace.o 

C_DEPS += \
./Middlewares/ST/STM32_USBPD_Library/Core/usbpd_dpm_core.d \
./Middlewares/ST/STM32_USBPD_Library/Core/usbpd_trace.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USBPD_Library/Core/usbpd_dpm_core.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Core/src/usbpd_dpm_core.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -DUSE_HAL_DRIVER -DUSE_STM32F0XX_NUCLEO -D_RTOS -DUSBPD_LED_SERVER '-DUSBPD_PORT_COUNT=1' -D_SRC -DMB1303 -DUSE_FULL_LL_DRIVER -DUSBPD_STUSB1602 -DCONF_NORMAL -DUSBPDCORE_LIB_PD3_CONFIG_1 -D_TRACE_NA -D_ERROR_RECOVERY -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../../../../../../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F0xx-Nucleo -I../../../../../../../../Drivers/BSP/P-NUCLEO-USB002 -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/STUSB1602 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/inc -I../../../../../../../../Utilities/LED_SERVER -Os -ffunction-sections -Wall -Wno-strict-aliasing -Wno-unused-variable -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USBPD_Library/Core/usbpd_dpm_core.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USBPD_Library/Core/usbpd_trace.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Core/src/usbpd_trace.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -DUSE_HAL_DRIVER -DUSE_STM32F0XX_NUCLEO -D_RTOS -DUSBPD_LED_SERVER '-DUSBPD_PORT_COUNT=1' -D_SRC -DMB1303 -DUSE_FULL_LL_DRIVER -DUSBPD_STUSB1602 -DCONF_NORMAL -DUSBPDCORE_LIB_PD3_CONFIG_1 -D_TRACE_NA -D_ERROR_RECOVERY -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../../../../../../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F0xx-Nucleo -I../../../../../../../../Drivers/BSP/P-NUCLEO-USB002 -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/STUSB1602 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/inc -I../../../../../../../../Utilities/LED_SERVER -Os -ffunction-sections -Wall -Wno-strict-aliasing -Wno-unused-variable -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USBPD_Library/Core/usbpd_trace.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

