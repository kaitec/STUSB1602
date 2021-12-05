/**
  ******************************************************************************
  * @file    stm32f0xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   This file contains HW interface MSP functions.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics International N.V. 
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
#include "stm32f0xx_hal.h"
#include "usbpd_hw_if.h"

/** @addtogroup STM32F0xx_HAL_Examples
  * @{
  */

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the Global MSP.
  * @note   This function is called from HAL_Init() function to perform system
  *         level initialization (GPIOs, clock, DMA, interrupt).
  * @retval None
  */
void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  /* Enable the RCC peripheral clock associated to all the selected GPIOs */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
#if defined(GPIOD)
  __HAL_RCC_GPIOD_CLK_ENABLE();
#endif /* GPIOD */
#if defined(GPIOF)
  __HAL_RCC_GPIOF_CLK_ENABLE();
#endif /* GPIOD */
}
/**
  * @brief ADC MSP Initialization
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  /* Enable clock of ADCx peripheral */
  ADCx_CLK_ENABLE();
  PHY_HW_IF_ADCAnalogGPIO_Init();
  
  /* Enable clock of DMA associated to the peripheral */
  ADCx_DMA_CLK_ENABLE();
  PHY_HW_IF_ADCDMA_Init();
}

/**
  * @brief ADC MSP De-initialization
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  /* Reset peripherals */
  ADCx_FORCE_RESET();
  ADCx_RELEASE_RESET();
  
  /* De-initialize the GPIO pins of the selected ADC */
  PHY_HW_IF_ADCAnalogGPIO_DeInit();
  /* De-Initialize the DMA related to the ADC */
  PHY_HW_IF_ADCDMA_DeInit();
}

/**
  * @brief SPI MSP Initialization
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  uint8_t port_num = GET_PORT_FROM_SPI(hspi);
  
  /* Peripheral clock enable */
  SPI_CLK_ENABLE(port_num);
  
  GPIO_InitStruct.Pin = SPI_MISO_PIN(port_num);
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = SPI_MISO_ALTERNATE(port_num);
  HAL_GPIO_Init(SPI_MISO_PORT(port_num), &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SPI_MOSI_PIN(port_num);
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = SPI_MOSI_ALTERNATE(port_num);
  HAL_GPIO_Init(SPI_MOSI_PORT(port_num), &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SPI_CLK_PIN(port_num);
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = SPI_CLK_ALTERNATE(port_num);
  HAL_GPIO_Init(SPI_CLK_PORT(port_num), &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SPI_NSS_PIN(port_num);
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = SPI_NSS_ALTERNATE(port_num);
  HAL_GPIO_Init(SPI_NSS_PORT(port_num), &GPIO_InitStruct);

  /* TX DMA Initialization */
  STUSB16xx_HW_IF_TX_DMA_Init(port_num);

  /* RX DMA Initialization */
  STUSB16xx_HW_IF_RX_DMA_Init(port_num);  
}

/**
  * @brief SPI MSP De-initialization
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
  uint8_t port_num = GET_PORT_FROM_SPI(hspi);
  
  /* TX SPI clock pin De-initialization */
  HAL_GPIO_DeInit(SPI_CLK_PORT(port_num), SPI_CLK_PIN(port_num));
  
  /* Peripheral DMA DeInit*/
  HAL_DMA_DeInit(hspi->hdmatx);
}

/**
* @brief I2C MSP Initialization
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  uint8_t port_num = GET_PORT_FROM_I2C(hi2c);

  GPIO_InitStruct.Pin       = I2C_SCL_PIN(port_num)|I2C_SDA_PIN(port_num);
  GPIO_InitStruct.Mode      = I2C_MODE(port_num);
  GPIO_InitStruct.Pull      = I2C_PULL(port_num);
  GPIO_InitStruct.Speed     = I2C_SPEED(port_num);
  GPIO_InitStruct.Alternate = I2C_ALTERNATE(port_num);
  HAL_GPIO_Init(I2C_PORT(port_num), &GPIO_InitStruct);

  /* Peripheral clock enable */
  I2C_CLK_ENABLE(port_num);
}


/**
* @brief I2C MSP De-initialization
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  uint8_t port_num = GET_PORT_FROM_I2C(hi2c);
  
  /* Peripheral clock disable */
  I2C_CLK_DISABLE(port_num);

  HAL_GPIO_DeInit(I2C_PORT(port_num), I2C_SCL_PIN(port_num)|I2C_SDA_PIN(port_num));
}

/**
  * @brief CRC MSP Initialization
  * @param hcrc: CRC handle pointer
  * @retval None
  */
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc)
{
  /* CRC Peripheral clock enable */
  __HAL_RCC_CRC_CLK_ENABLE();
}

/**
  * @brief CRC MSP De-initialization
  * @param hcrc: CRC handle pointer
  * @retval None
  */
void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc)
{
  /* CRC Peripheral clock disable */
  __HAL_RCC_CRC_CLK_DISABLE();
}

/**
  * @brief TIM MSP Initialization
  * @param htim_base: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  uint8_t port_num = GET_PORT_FROM_TIM(htim_base);
  if(IS_RX_COUNTTIM(htim_base))  /* RX COUNT TIMER IDENTIFIED */
  {
    /* Peripheral clock enable */
    RX_COUNTTIM_CLK_ENABLE(port_num);

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(RX_COUNTTIM_IRQN(port_num), RX_COUNTTIMIRQ_PRIO(port_num), 0);
    HAL_NVIC_EnableIRQ(RX_COUNTTIM_IRQN(port_num));
  }
}

/**
  * @brief TIM MSP De-initialization
  * @param htim_base: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  uint8_t port_num = GET_PORT_FROM_TIM(htim_base);

  if ( IS_RX_COUNTTIM(htim_base) )  /* RX COUNT TIMER IDENTIFIED */
  {
    /* Peripheral clock enable */
     RX_COUNTTIM_CLK_DISABLE(port_num);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
