/**
  ******************************************************************************
  * @file    usbpd_pwr_if.c
  * @author  MCD Application Team
  * @brief   This file contains power interface control functions.
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

#define __USBPD_PWR_IF_C

/* Includes ------------------------------------------------------------------*/
#include "usbpd_pwr_if.h"
#include "usbpd_hw_if.h"
#include "usbpd_pwr_if.h"
#include "usbpd_dpm_user.h"
#include "usbpd_dpm_core.h"
#include "usbpd_dpm_conf.h"
#include "usbpd_pdo_defs.h"

/* Private typedef -----------------------------------------------------------*/
#define POWER_IF_TRACE(_PORT_,_MSG_,_SIZE_)
/* Private define ------------------------------------------------------------*/

#if ((PORT0_NB_SOURCEPDO) > USBPD_MAX_NB_PDO)
#error "Nb of Source PDO/APDO is exceeding stack capabilities"
#endif
#if ((PORT0_NB_SINKPDO) > USBPD_MAX_NB_PDO)
#error "Nb of Sink PDO/APDO is exceeding stack capabilities"
#endif

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
  * @brief  USBPD Port PDO Storage array declaration
  */

/**** PDO ****/
USBPD_PWR_Port_PDO_Storage_TypeDef PWR_Port_PDO_Storage[USBPD_PORT_COUNT];

/* Private function prototypes -----------------------------------------------*/
/* Functions to initialize Source PDOs */
uint32_t _PWR_SRCFixedPDO(float  _C_, float _V_,
                          USBPD_CORE_PDO_PeakCurr_TypeDef _PK_,
                          USBPD_CORE_PDO_DRDataSupport_TypeDef DRDSupport,
                          USBPD_CORE_PDO_USBCommCapable_TypeDef UsbCommCapable,
                          USBPD_CORE_PDO_ExtPowered_TypeDef ExtPower,
                          USBPD_CORE_PDO_USBSuspendSupport_TypeDef UsbSuspendSupport,
                          USBPD_CORE_PDO_DRPowerSupport_TypeDef DRPSupport);

uint32_t _PWR_SRCVariablePDO(float _MAXV_, float _MINV_, float _C_);

uint32_t _PWR_SRCBatteryPDO(float _MAXV_,float _MINV_,float _PWR_);
/* Functions to initialize Sink PDOs */

uint32_t _PWR_SNKFixedPDO(float  _C_, float _V_,
                          USBPD_CORE_PDO_DRDataSupport_TypeDef DRDSupport,
                          USBPD_CORE_PDO_USBCommCapable_TypeDef UsbCommCapable,
                          USBPD_CORE_PDO_ExtPowered_TypeDef ExtPower,
                          USBPD_CORE_PDO_HigherCapability_TypeDef HigherCapab,
                          USBPD_CORE_PDO_DRPowerSupport_TypeDef DRPSupport);

uint32_t _PWR_SNKVariablePDO(float  _MAXV_,float _MINV_,float _C_);

uint32_t _PWR_SNKBatteryPDO(float _MAXV_,float _MINV_,float _PWR_);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize structures and variables related to power board profiles
  *         used by Sink and Source, for all available ports.
  * @retval USBPD status
*/
/* GNU Compiler */
#if defined(__GNUC__)
/* ARM Compiler */
#elif defined(__CC_ARM)
/* IAR Compiler */
#elif defined(__ICCARM__)
#pragma optimize=none
#endif
USBPD_StatusTypeDef USBPD_PWR_IF_Init(void)
{

  /* Set links to PDO values and number for Port 0 (defined in PDO arrays in H file).
   */

#if (PORT0_NB_SINKPDO > 0)
  PWR_Port_PDO_Storage[USBPD_PORT_0].SinkPDO.ListOfPDO = (uint32_t *)PORT0_PDO_ListSNK;
  PWR_Port_PDO_Storage[USBPD_PORT_0].SinkPDO.NumberOfPDO = PORT0_NB_SINKPDO;
#endif

  return USBPD_OK;
}



/**
  * @brief  Resets the Power Board
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_PowerResetGlobal(void)
{
  int i = 0;

  /* Resets all the ports */
  for(i = 0; i < USBPD_PORT_COUNT; i++)
  {
    USBPD_PWR_IF_PowerReset(i);
  }
  return USBPD_OK;
}

/**
  * @brief  Resets the Power on a specified port
  * @param  PortNum Port number
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_PowerReset(uint8_t PortNum)
{
  /* check for valid port */
  if (!USBPD_PORT_IsValid(PortNum))
  {
    return USBPD_ERROR;
  }

  /* Put the usbpd port into ready to start the application */
  return USBPD_PWR_IF_InitPower(PortNum);
}

/**
  * @brief  Checks if the power on a specified port is ready
  * @param  PortNum Port number
  * @param  Vsafe   Vsafe status based on @ref USBPD_VSAFE_StatusTypeDef
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_SupplyReady(uint8_t PortNum, USBPD_VSAFE_StatusTypeDef Vsafe)
{
  USBPD_StatusTypeDef status = USBPD_ERROR;

  /* check for valid port */
  if (!USBPD_PORT_IsValid(PortNum))
  {
    return USBPD_ERROR;
  }

  if (USBPD_VSAFE_0V == Vsafe)
  {
    /* Vsafe0V */
    status = (HW_IF_PWR_GetVoltage(PortNum) < CAD_threshold_VBus? USBPD_OK: USBPD_ERROR);
  }
  else
  {
    /* Vsafe5V */
    status = (HW_IF_PWR_GetVoltage(PortNum) > CAD_threshold_VBus? USBPD_OK: USBPD_ERROR);
  }
  return status;
}

/**
  * @brief  Enables VBUS power on a specified port
  * @param  PortNum Port number
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_VBUSEnable(uint8_t PortNum)
{
  USBPD_StatusTypeDef _status = USBPD_ERROR;
  
  /* check for valid port */
  if (USBPD_PORT_IsValid(PortNum))
  {
    POWER_IF_TRACE(PortNum, "EN_VBUS", 7);
    /* Set the new state */
    _status = (USBPD_StatusTypeDef)HW_IF_PWR_Enable(PortNum, USBPD_ENABLE, DPM_Params[PortNum].VconnCCIs, DPM_Params[PortNum].VconnStatus, USBPD_PORTPOWERROLE_SRC);
  }
  return _status;
}

/**
  * @brief  Disbale VBUS/VCONN the power on a specified port
  * @param  PortNum Port number
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_VBUSDisable(uint8_t PortNum)
{
  USBPD_StatusTypeDef _status = USBPD_ERROR;
  
  /* check for valid port */
  if (USBPD_PORT_IsValid(PortNum))
  {
    POWER_IF_TRACE(PortNum, "DIS VBUS", 8);
    /* Set the new state */
    _status = (USBPD_StatusTypeDef)HW_IF_PWR_Enable(PortNum, USBPD_DISABLE, DPM_Params[PortNum].VconnCCIs, DPM_Params[PortNum].VconnStatus, USBPD_PORTPOWERROLE_SRC);
  }
  return _status;
}

/**
  * @brief  Disable the SNK to stop current consumption 
  * @param  PortNum Port number
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_SNKDisable(uint8_t PortNum)
{
  USBPD_StatusTypeDef _status = USBPD_ERROR;
  
  /* check for valid port */
  if (USBPD_PORT_IsValid(PortNum))
  {
    /* Set the new state */
    _status = (USBPD_StatusTypeDef)HW_IF_PWR_Enable(PortNum, USBPD_DISABLE, DPM_Params[PortNum].VconnCCIs, DPM_Params[PortNum].VconnStatus, USBPD_PORTPOWERROLE_SNK);
  }
  return _status;
}

/**
  * @brief  Initialize power on a specified port
  * @param  PortNum Port number
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PWR_IF_InitPower(uint8_t PortNum)
{
  return USBPD_OK;
}

/**
  * @brief  Checks if the power on a specified port is enabled
  * @param  PortNum Port number
  * @retval USBPD_ENABLE or USBPD_DISABLE
  */
USBPD_FunctionalState USBPD_PWR_IF_VBUSIsEnabled(uint8_t PortNum)
{
  /* Get the Status of the port */
  return USBPD_PORT_IsValid(PortNum) ? (USBPD_FunctionalState)HW_IF_PWR_VBUSIsEnabled(PortNum) : USBPD_DISABLE;
}

/**
  * @brief  Reads the voltage and the current on a specified port
  * @param  PortNum Port number
  * @param  pVoltage: The Voltage in mV
  * @param  pCurrent: The Current in mA
  * @retval USBPD_ERROR or USBPD_OK
*/
USBPD_StatusTypeDef USBPD_PWR_IF_ReadVA(uint8_t PortNum, uint16_t *pVoltage, uint16_t *pCurrent)
{
  /* check for valid port */
  if (!USBPD_PORT_IsValid(PortNum))
  {
    return USBPD_ERROR;
  }

  /* USBPD_OK if at least one pointer is not null, otherwise USBPD_ERROR */
  USBPD_StatusTypeDef ret = USBPD_ERROR;

  /* Get values from HW_IF */
  if (pVoltage != NULL)
  {
    *pVoltage = HW_IF_PWR_GetVoltage(PortNum);
    ret = USBPD_OK;
  }
  if (pCurrent != NULL)
  {
    *pCurrent = HW_IF_PWR_GetCurrent(PortNum);
    ret = USBPD_OK;
  }

  return ret;
}

/**
  * @brief  Create SRC Fixed PDO object
  * @param  _C_: Current in A
  * @param  _V_: voltage in V
  * @param  _PK_: The peak of current
  * @param  DRDSupport: Data Role Swap support indication
  * @param  UsbCommCapable: USB communications capability indication
  * @param  ExtPower: Port externally powered indication
  * @param  UsbSuspendSupport: USB Suspend support indication
  * @param  DRPSupport: Dual Role Power support indication
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SRCFixedPDO(float  _C_, float _V_,
                          USBPD_CORE_PDO_PeakCurr_TypeDef _PK_,
                          USBPD_CORE_PDO_DRDataSupport_TypeDef DRDSupport,
                          USBPD_CORE_PDO_USBCommCapable_TypeDef UsbCommCapable,
                          USBPD_CORE_PDO_ExtPowered_TypeDef ExtPower,
                          USBPD_CORE_PDO_USBSuspendSupport_TypeDef UsbSuspendSupport,
                          USBPD_CORE_PDO_DRPowerSupport_TypeDef DRPSupport)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCFixedPDO.MaxCurrentIn10mAunits       = PWR_A_10MA(_C_);
  pdo.SRCFixedPDO.VoltageIn50mVunits          = PWR_V_50MV(_V_);
  pdo.SRCFixedPDO.PeakCurrent                 = _PK_;
  pdo.SRCFixedPDO.DataRoleSwap                = DRDSupport;
  pdo.SRCFixedPDO.USBCommunicationsCapable    = UsbCommCapable;
  pdo.SRCFixedPDO.ExternallyPowered           = ExtPower;
  pdo.SRCFixedPDO.USBSuspendSupported         = UsbSuspendSupport;
  pdo.SRCFixedPDO.DualRolePower               = DRPSupport;
  pdo.SRCFixedPDO.FixedSupply                 = USBPD_CORE_PDO_TYPE_FIXED;
  return pdo.d32;
}

/**
  * @brief  Create SRC Variable PDO object
  * @param  _MAXV_ Max voltage in V
  * @param  _MINV_ Min voltage in V
  * @param  _C_: Max current in A
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SRCVariablePDO(float _MAXV_, float _MINV_, float _C_)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCVariablePDO.MaxCurrentIn10mAunits = PWR_A_10MA(_C_);
  pdo.SRCVariablePDO.MaxVoltageIn50mVunits = PWR_V_50MV(_MAXV_);
  pdo.SRCVariablePDO.MinVoltageIn50mVunits = PWR_V_50MV(_MINV_);
  pdo.SRCVariablePDO.VariableSupply        = USBPD_CORE_PDO_TYPE_VARIABLE;
  return pdo.d32;
}

/**
  * @brief  Create SRC Battery PDO object
  * @param  _MAXV_ Max voltage in V
  * @param  _MINV_ Min voltage in V
  * @param  _PWR_ Max allowable power in W
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SRCBatteryPDO(float _MAXV_,float _MINV_,float _PWR_)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCBatteryPDO.MaxAllowablePowerIn250mWunits = PWR_W(_PWR_);
  pdo.SRCBatteryPDO.MinVoltageIn50mVunits         = PWR_V_50MV(_MINV_);
  pdo.SRCBatteryPDO.MaxVoltageIn50mVunits         = PWR_V_50MV(_MAXV_);
  pdo.SRCBatteryPDO.Battery                       = USBPD_CORE_PDO_TYPE_BATTERY;
  return pdo.d32;
}

/**
  * @brief  Create SNK Fixed PDO object
  * @param  _C_ Current in A
  * @param  _V_ voltage in V
  * @param  DRDSupport: Data Role Swap support indication
  * @param  UsbCommCapable: USB communications capability indication
  * @param  ExtPower: Port externally powered indication
  * @param  HigherCapab: Sink needs more than vSafe5V to provide full functionality indication
  * @param  DRPSupport: Dual Role Power support indication
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SNKFixedPDO(float  _C_, float _V_,
                          USBPD_CORE_PDO_DRDataSupport_TypeDef DRDSupport,
                          USBPD_CORE_PDO_USBCommCapable_TypeDef UsbCommCapable,
                          USBPD_CORE_PDO_ExtPowered_TypeDef ExtPower,
                          USBPD_CORE_PDO_HigherCapability_TypeDef HigherCapab,
                          USBPD_CORE_PDO_DRPowerSupport_TypeDef DRPSupport)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SNKFixedPDO.OperationalCurrentIn10mAunits = PWR_A_10MA(_C_);
  pdo.SNKFixedPDO.VoltageIn50mVunits            = PWR_V_50MV(_V_);
  pdo.SNKFixedPDO.DataRoleSwap                  = DRDSupport;
  pdo.SNKFixedPDO.USBCommunicationsCapable      = UsbCommCapable;
  pdo.SNKFixedPDO.ExternallyPowered             = ExtPower;
  pdo.SNKFixedPDO.HigherCapability              = HigherCapab;
  pdo.SNKFixedPDO.DualRolePower                 = DRPSupport;
  pdo.SNKFixedPDO.FixedSupply                   = USBPD_CORE_PDO_TYPE_FIXED;

  return pdo.d32;
}

/**
  * @brief  Create SNK Variable PDO object
  * @param  _MAXV_ Max voltage in V
  * @param  _MINV_ Min voltage in V
  * @param  _C_: Max current in A
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SNKVariablePDO(float  _MAXV_,float _MINV_,float _C_)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCVariablePDO.MaxCurrentIn10mAunits = PWR_A_10MA(_C_);
  pdo.SRCVariablePDO.MaxVoltageIn50mVunits = PWR_V_50MV(_MAXV_);
  pdo.SRCVariablePDO.MinVoltageIn50mVunits = PWR_V_50MV(_MINV_);
  pdo.SRCVariablePDO.VariableSupply        = USBPD_CORE_PDO_TYPE_VARIABLE;
  return pdo.d32;
}

/**
  * @brief  Create SNK Battery PDO object
  * @param  _MAXV_ Max voltage in V
  * @param  _MINV_ Min voltage in V
  * @param  _PWR_ Max allowable power in W
  * @retval PDO object value (expressed on u32)
  */
uint32_t _PWR_SNKBatteryPDO(float _MAXV_,float _MINV_,float _PWR_)
{
  USBPD_PDO_TypeDef pdo;

  pdo.d32 = 0;
  pdo.SRCBatteryPDO.MaxAllowablePowerIn250mWunits = PWR_W(_PWR_);
  pdo.SRCBatteryPDO.MinVoltageIn50mVunits         = PWR_V_50MV(_MINV_);
  pdo.SRCBatteryPDO.MaxVoltageIn50mVunits         = PWR_V_50MV(_MAXV_);
  pdo.SRCBatteryPDO.Battery                       = USBPD_CORE_PDO_TYPE_BATTERY;
  return pdo.d32;
}



/**
  * @brief  Allow PDO data reading from PWR_IF storage.
  * @param  PortNum Port number
  * @param  DataId Type of data to be read from PWR_IF
  *         This parameter can be one of the following values:
  *           @arg @ref USBPD_CORE_DATATYPE_SRC_PDO Source PDO reading requested
  *           @arg @ref USBPD_CORE_DATATYPE_SNK_PDO Sink PDO reading requested
  * @param  Ptr Pointer on address where PDO values should be written (u32 pointer)
  * @param  Size Pointer on nb of u32 written by PWR_IF (nb of PDOs)
  * @retval None
  */
void USBPD_PWR_IF_GetPortPDOs(uint8_t PortNum, USBPD_CORE_DataInfoType_TypeDef DataId, uint32_t *Ptr, uint32_t *Size)
{
  uint32_t   nbpdo, index, nb_valid_pdo = 0;
  uint32_t   *ptpdoarray = NULL;

  /* Check if valid port */
  if (USBPD_PORT_IsValid(PortNum))
  {
    /* According to type of PDO to be read, set pointer on values and nb of elements */
    switch (DataId)
    {
    case USBPD_CORE_DATATYPE_SNK_PDO:
      nbpdo       = PWR_Port_PDO_Storage[PortNum].SinkPDO.NumberOfPDO;
      ptpdoarray  = PWR_Port_PDO_Storage[PortNum].SinkPDO.ListOfPDO;
      break;
    default:
      nbpdo = 0;
      break;
    }

    /* Copy PDO data in output buffer */
    for (index = 0; index < nbpdo; index++)
    {
      {
        USPBPD_WRITE32((uint32_t *)(Ptr + nb_valid_pdo), *ptpdoarray);
        nb_valid_pdo++;
      }
      ptpdoarray++;
    }
    /* Set nb of read PDO (nb of u32 elements); */
    *Size = nb_valid_pdo;
  }
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
