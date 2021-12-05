/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @brief   USBPD demo main file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
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
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_cortex.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_bb.h" 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define _HSE_ENABLE 1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USBD_HandleTypeDef hUsbDeviceBB[USBPD_PORT_COUNT];

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Billboard_Init(void);
static void CRS_SetUSBClockToHSI48(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  
  /* Set USB external clock to HSI48 */
  CRS_SetUSBClockToHSI48();

  /* Configure the system clock */
  SystemClock_Config();
  HAL_NVIC_SetPriority(SysTick_IRQn, TICK_INT_PRIORITY ,0U);
  LL_SYSTICK_EnableIT();

  /* Initialize BSP functionalities */
  USBPD_BSP_LED_Init();

  /* Global Init of USBPD HW */
  USBPD_HW_IF_GlobalHwInit();

  /* Initialize Billboard */
  Billboard_Init();

  /* Initialize the Device Policy Manager */
  if( USBPD_ERROR == USBPD_DPM_Init())
  {
    /* error the RTOS can't be started  */
    while(1);
  }
}

/**
  * @brief  Initialize billboard driver
  * @param  None
  * @retval None
  */
static void Billboard_Init(void)
{
  /* PLL used as USB clock source */
  LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_PLL);

#if (USBD_BOS_ENABLED == 1)
  USBD_BB_AlternateModeTypeDef AlternateMode;

  /* Add Display Port alternate mode */
  AlternateMode.VendorID = 0xFF01;
  AlternateMode.bAlternateMode = 0x01;
  AlternateMode.iAlternateModeString = 0x00;
  USBD_BB_AddAlternateMode(hUSBDBOSDesc, &AlternateMode);

  /* Setup Alternate mode with Index=0x00 as the prefered alternate mode */
  USBD_BB_SetupPreferedAltMode (hUSBDBOSDesc, 0x00);

  /* Setup the state of the alternate mode with index=0x00 */
  USBD_BB_SetupAltModeState (hUSBDBOSDesc, 0x00, CONFIGURATION_NOT_ATTEMPTED);
#endif

  /* Init Device Library,Add Supported Class and Start the library*/
  USBD_Init(&hUsbDeviceBB[USBPD_PORT_0], &BB_Desc, 0);
  USBD_RegisterClass(&hUsbDeviceBB[USBPD_PORT_0], &USBD_BB);

  /* Billboard is started if PD negociation done or legacy cable detected */
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI48)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 48000000
  *            PREDIV                         = 2
  *            PLLMUL                         = 2
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Set FLASH latency */ 
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  /* Enable HSI48 and wait for activation*/
  LL_RCC_HSI48_Enable(); 
  while(LL_RCC_HSI48_IsReady() != 1) 
  {
  };
  
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI48, LL_RCC_PLL_MUL_2, LL_RCC_PREDIV_DIV_2);
  
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };
  
  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };
  
  /* Set APB1 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  
  /* Set systick to 1ms in using frequency set to 48MHz */
  /* This frequency can be calculated through LL RCC macro */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ (HSI48_VALUE, LL_RCC_PLL_MUL_2, LL_RCC_PREDIV_DIV_2) */
  LL_Init1msTick(48000000);
  
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(48000000);
}

/**
  * @brief  Set USB clock to HSI48MHz
  * @retval None
  */
static void CRS_SetUSBClockToHSI48(void)
{ 
#if 0
  /* Enable HSI48 and wait for activation*/
  LL_RCC_HSI48_Enable(); 
  while(LL_RCC_HSI48_IsReady() != 1) 
  {
  };

#if 0
  /* HSI48 used as USB clock source */
  LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_HSI48);
  
  /*Configure the clock recovery system (CRS)**********************************/
  /*Enable CRS Clock*/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_CRS);
  
  /* HSI48 Synchronization with synchronization frequency (source set to USB SOF)  */
  /* Set the TRIM[5:0] to the default value : HSI48CalibrationValue = 0x20 
     Default Synchro Signal division factor (not divided) : RCC_CRS_SYNC_DIV1
     Synchro Signal source set to USB SOF 
     HSI48 is synchronized with USB SOF at 1KHz rate
  */
  LL_CRS_ConfigSynchronization(0x20 << CRS_CR_TRIM_Pos,   /* Tmp patch waiting for STM32F0_HAL #419318 */
                               LL_CRS_ERRORLIMIT_DEFAULT,
                               __LL_CRS_CALC_CALCULATE_RELOADVALUE(HSI48_VALUE, 1000),
                               LL_CRS_SYNC_DIV_1 | LL_CRS_SYNC_SOURCE_USB | LL_CRS_SYNC_POLARITY_FALLING
                              );
  
  /* Start automatic synchronization */ 
  /* Enable Automatic trimming & Frequency error counter */
  LL_CRS_EnableFreqErrorCounter();
  LL_CRS_EnableAutoTrimming();
#endif
  
  /* Set systick to 1ms in using frequency set to 48MHz */
  /* This frequency can be calculated through LL RCC macro */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ (HSI48_VALUE, LL_RCC_PLL_MUL_2, LL_RCC_PREDIV_DIV_2) */
  LL_Init1msTick(48000000);
  SysTick->CTRL|= SysTick_CTRL_TICKINT_Msk;
  HAL_NVIC_SetPriority(SysTick_IRQn, TICK_INT_PRIORITY ,0U);
  
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(48000000);
#endif
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
