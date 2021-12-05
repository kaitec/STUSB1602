/**
  @page USB-C Power Delivery MB1303_DRP_RTOS application for STUSB1602 (P-NUCLEO-USB002 kit)
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    MB1303_DRP_RTOS/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USB-C Power Delivery MB1303_DRP_RTOS application.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim
  
@par Application Description
Use of the USB Power Delivery (USB-PD) Dual-Role Power (DRP) application running on STM32F072+STUSB1602 devices.
Project configuration is based on USB Power Delivery Specification revision 2.0, with support of DRP application on Port 0.

At startup:
 - Status LED (Blue LED D106) is on.
 - Role LEDs (Blue LEDs D100) blink three times meaning that the board is acting the DRP role.
 - CC LEDs (Orange LEDs D102) are off.
 - VBUS LEDs (Green LEDs D101) are off.

Because of the P-NUCLEO-USB002 acts the DRP role, the user can connect to port 0 receptacle an application 
which plays the consumer role as well as the provider role.
When a consumer is connected:
 - Role LED will blink one time to show that the device swiches to Provider.
 - CC LED will blink once if connected on CC1, twice if connected on CC2.
 - The STM32 MCU behaves as a Provider (Source mode), it exchanges Power profiles with 
   the connected device and waits for Power Request message from the attached consumer.
   While the communication is carried on, VBUS LED will blink.
   If the requested power can be met, the communication will end with an Accept message followed 
   by a PS_RDY message.
   Once the Explicit Contract is achieved, VBUS LED is on to indicate that the power contract was established.
When a provider is connected:
 - Role LED will blink twice to show that the device swiches to Consumer.
 - CC LED will blink once if connected on CC1, twice if connected on CC2.
 - The STM32 MCU behaves as a Consumer (Sink mode),it waits for Power Capabilities message 
   from the attached provider. When a Source Capabilities message is received, the STM32 
   starts the evaluation of the received capabilities and check if one of the received power 
   objects can meet its power requirement. 
   While the communication is carried on, VBUS LED will blink.
   The STM32 shall send the Request message to request the new power level from the offered 
   Source Capabilities.
   Once the Explicit Contract is achieved (PS_Ready message received), VBUS LED VBUS LED is on to 
   indicate that the power contract was established.

The Power Role Swap is also supported in this application. Power Role Swap could be triggered on Port 0 by pressing the user button.
According to connected device:
 - When connected to an USB-C provider only device (source mode), the power role swap between the two boards is not possible,
   DRP board will act automatically as a sink.
 - When connected to an USB-C consumer only device (sink mode), the power role swap between the two boards is not possible,
   DRP board will act automatically as a source.
 - When connected to an USB-C with DRP, the power role swap is supported. if Port 0, it could be triggered each time user button is pressed.

The DRP role can be managed with two different supply options according to the fact that the board is supplied by
the on-board STM32F072RB-Nucleo RevC voltage regulator by mean of a USB Type-A to Mini-B cable plugged to the CN1 connector and then to a PC
as well as it is supplied by mean of the VBUS delivered by the Provider attached or The P-NUCLEO-USB002 is connected to an external
power board by the connector CN4.

if the DRP is supplied by the on-board STM32F072RB-Nucleo RevC voltage regulator, by mean of a USB Type-A to Mini-B cable
plugged to the CN1 connector and then to a PC:
  - On STM32F072RB-Nucleo RevC board, verify that the jumper JP1 is open, jumper JP5 (PWR) is closed on U5V 
  (fitting the pins 1-2), and jumper JP6 (IDD) is closed.

On the expansion board:
  - jumpers JP400 is closed.
  - jumpers JP000 is closed on pin 1-2.


@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct operation.

@par Directory contents

  - MB1303_DRP_RTOS/Src/main.c                      Main program
  - MB1303_DRP_RTOS/Src/system_stm32f0xx.c          STM32F0xx system clock configuration file
  - MB1303_DRP_RTOS/Src/stm32f0xx_hal_msp.c         HAL MSP file
  - MB1303_DRP_RTOS/Src/stm32f0xx_it.c              Interrupt handlers
  - MB1303_DRP_RTOS/Src/usbpd_dpm_user.c            DPM layer implementation
  - MB1303_DRP_RTOS/Src/usbpd_pwr_if.c              General power interface configuration
  - MB1303_DRP_RTOS/Inc/main.h                      Main program header file
  - MB1303_DRP_RTOS/Inc/stm32f0xx_it.h              Interrupt handlers header file
  - MB1303_DRP_RTOS/Inc/stm32f0xx_hal_conf.h        HAL configuration file
  - MB1303_DRP_RTOS/Inc/usbpd_dpm_conf.h            USB-C Power Delivery application Configuration file
  - MB1303_DRP_RTOS/Inc/usbpd_dpm_user.h            DPM Layer header file
  - MB1303_DRP_RTOS/Inc/FreeRTOSConfig.h            FreeRTOS module configuration file
  - MB1303_DRP_RTOS/Inc/usbpd_dpm_user.h            DPM Layer header file
  - MB1303_DRP_RTOS/Inc/usbpd_pdo_defs.h            PDO definition central header file
  - MB1303_DRP_RTOS/Inc/usbpd_pdo_defs_Drp_1Port.h  1 Port DRP PDO definition file


@par Hardware and Software environment

  - This application runs on STM32F072 devices.
  
  - This example has been tested with P-NUCLEO-USB002 kit made by STMicroelectronics STM32F072RB-Nucleo RevC
    board and the expansion board RevB connected on top of CN7 and CN10 connectors. 
    The provided example can be easily tailored to any other supported device and development board.

  - Connect the P-NUCLEO-USB002 kit to the a USB-C Power Delivery consumer, provider or DRP attaching the
    USB typeC cable to the receptacle CN0/CN1 on the expansion board.
    To test this application, another P-NUCLEO-USB002 kit running the Consumer_RTOS, Provider_RTOS or DRP_RTOS role can be used.

  - STM32F072RB-Nucleo RevC Set-up
      - SB48, SB49, SB62 and SB63 must be closed
      - SB13, SB14, SB15 and SB21 must be removed
      - R34 and R36 must be removed
      - JP5 Jumper must be connected to U5V.

@par How to use it ?

In order to make the program work, you must do the following:
  - Open the IDE toolchain 
  - Rebuild all files and load your image into target memory
  - Run the application
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 