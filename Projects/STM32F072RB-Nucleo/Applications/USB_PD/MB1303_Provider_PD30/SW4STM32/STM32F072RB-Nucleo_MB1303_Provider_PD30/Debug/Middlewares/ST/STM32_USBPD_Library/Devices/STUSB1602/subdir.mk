################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_cad_hw_if.c \
C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_hw_if_it.c \
C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_phy.c \
C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_phy_hw_if.c \
C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_pwr_hw_if.c \
C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_stusb16xx_hw_if.c \
C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_timersserver.c 

OBJS += \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_cad_hw_if.o \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_hw_if_it.o \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_phy.o \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_phy_hw_if.o \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_pwr_hw_if.o \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_stusb16xx_hw_if.o \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_timersserver.o 

C_DEPS += \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_cad_hw_if.d \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_hw_if_it.d \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_phy.d \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_phy_hw_if.d \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_pwr_hw_if.d \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_stusb16xx_hw_if.d \
./Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_timersserver.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_cad_hw_if.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_cad_hw_if.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -DUSE_HAL_DRIVER -DUSE_STM32F0XX_NUCLEO -D_RTOS -DUSBPD_LED_SERVER '-DUSBPD_PORT_COUNT=1' -D_SRC -DMB1303 -DUSE_FULL_LL_DRIVER -DUSBPD_STUSB1602 -DCONF_NORMAL -DUSBPDCORE_LIB_PD3_CONFIG_1 -D_TRACE_NA -D_ERROR_RECOVERY -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../../../../../../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F0xx-Nucleo -I../../../../../../../../Drivers/BSP/P-NUCLEO-USB002 -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/STUSB1602 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/inc -I../../../../../../../../Utilities/LED_SERVER -Os -ffunction-sections -Wall -Wno-strict-aliasing -Wno-unused-variable -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_cad_hw_if.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_hw_if_it.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_hw_if_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -DUSE_HAL_DRIVER -DUSE_STM32F0XX_NUCLEO -D_RTOS -DUSBPD_LED_SERVER '-DUSBPD_PORT_COUNT=1' -D_SRC -DMB1303 -DUSE_FULL_LL_DRIVER -DUSBPD_STUSB1602 -DCONF_NORMAL -DUSBPDCORE_LIB_PD3_CONFIG_1 -D_TRACE_NA -D_ERROR_RECOVERY -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../../../../../../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F0xx-Nucleo -I../../../../../../../../Drivers/BSP/P-NUCLEO-USB002 -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/STUSB1602 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/inc -I../../../../../../../../Utilities/LED_SERVER -Os -ffunction-sections -Wall -Wno-strict-aliasing -Wno-unused-variable -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_hw_if_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_phy.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_phy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -DUSE_HAL_DRIVER -DUSE_STM32F0XX_NUCLEO -D_RTOS -DUSBPD_LED_SERVER '-DUSBPD_PORT_COUNT=1' -D_SRC -DMB1303 -DUSE_FULL_LL_DRIVER -DUSBPD_STUSB1602 -DCONF_NORMAL -DUSBPDCORE_LIB_PD3_CONFIG_1 -D_TRACE_NA -D_ERROR_RECOVERY -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../../../../../../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F0xx-Nucleo -I../../../../../../../../Drivers/BSP/P-NUCLEO-USB002 -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/STUSB1602 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/inc -I../../../../../../../../Utilities/LED_SERVER -Os -ffunction-sections -Wall -Wno-strict-aliasing -Wno-unused-variable -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_phy.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_phy_hw_if.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_phy_hw_if.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -DUSE_HAL_DRIVER -DUSE_STM32F0XX_NUCLEO -D_RTOS -DUSBPD_LED_SERVER '-DUSBPD_PORT_COUNT=1' -D_SRC -DMB1303 -DUSE_FULL_LL_DRIVER -DUSBPD_STUSB1602 -DCONF_NORMAL -DUSBPDCORE_LIB_PD3_CONFIG_1 -D_TRACE_NA -D_ERROR_RECOVERY -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../../../../../../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F0xx-Nucleo -I../../../../../../../../Drivers/BSP/P-NUCLEO-USB002 -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/STUSB1602 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/inc -I../../../../../../../../Utilities/LED_SERVER -Os -ffunction-sections -Wall -Wno-strict-aliasing -Wno-unused-variable -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_phy_hw_if.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_pwr_hw_if.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_pwr_hw_if.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -DUSE_HAL_DRIVER -DUSE_STM32F0XX_NUCLEO -D_RTOS -DUSBPD_LED_SERVER '-DUSBPD_PORT_COUNT=1' -D_SRC -DMB1303 -DUSE_FULL_LL_DRIVER -DUSBPD_STUSB1602 -DCONF_NORMAL -DUSBPDCORE_LIB_PD3_CONFIG_1 -D_TRACE_NA -D_ERROR_RECOVERY -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../../../../../../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F0xx-Nucleo -I../../../../../../../../Drivers/BSP/P-NUCLEO-USB002 -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/STUSB1602 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/inc -I../../../../../../../../Utilities/LED_SERVER -Os -ffunction-sections -Wall -Wno-strict-aliasing -Wno-unused-variable -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_pwr_hw_if.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_stusb16xx_hw_if.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_stusb16xx_hw_if.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -DUSE_HAL_DRIVER -DUSE_STM32F0XX_NUCLEO -D_RTOS -DUSBPD_LED_SERVER '-DUSBPD_PORT_COUNT=1' -D_SRC -DMB1303 -DUSE_FULL_LL_DRIVER -DUSBPD_STUSB1602 -DCONF_NORMAL -DUSBPDCORE_LIB_PD3_CONFIG_1 -D_TRACE_NA -D_ERROR_RECOVERY -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../../../../../../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F0xx-Nucleo -I../../../../../../../../Drivers/BSP/P-NUCLEO-USB002 -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/STUSB1602 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/inc -I../../../../../../../../Utilities/LED_SERVER -Os -ffunction-sections -Wall -Wno-strict-aliasing -Wno-unused-variable -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_stusb16xx_hw_if.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_timersserver.o: C:/Users/Andrew/Documents/Repo/STUSB1602/Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/src/usbpd_timersserver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F072xB -DUSE_HAL_DRIVER -DUSE_STM32F0XX_NUCLEO -D_RTOS -DUSBPD_LED_SERVER '-DUSBPD_PORT_COUNT=1' -D_SRC -DMB1303 -DUSE_FULL_LL_DRIVER -DUSBPD_STUSB1602 -DCONF_NORMAL -DUSBPDCORE_LIB_PD3_CONFIG_1 -D_TRACE_NA -D_ERROR_RECOVERY -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../../../../../../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F0xx-Nucleo -I../../../../../../../../Drivers/BSP/P-NUCLEO-USB002 -I../../../../../../../../Drivers/CMSIS/Include -I../../../../../../../../Drivers/BSP/Components/STUSB1602 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../../../../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Core/inc -I../../../../../../../../Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/inc -I../../../../../../../../Utilities/LED_SERVER -Os -ffunction-sections -Wall -Wno-strict-aliasing -Wno-unused-variable -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USBPD_Library/Devices/STUSB1602/usbpd_timersserver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
