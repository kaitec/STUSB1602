/**
  ******************************************************************************
  * @file    usbpd_core.h
  * @author  MCD Application Team
  * @brief   This file contains the core stack API.
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
#ifndef __USBPD_CORE_H_
#define __USBPD_CORE_H_

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "usbpd_def.h"
#if defined(USBPDCORE_TCPM_SUPPORT)
#include "tcpc.h"
#endif /* USBPDCORE_TCPM_SUPPORT */

/** @addtogroup STM32_USBPD_LIBRARY
  * @{
  */

/** @addtogroup USBPD_CORE
  * @{
  */

/** @addtogroup USBPD_CORE_CAD
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup USBPD_CORE_CAD_Exported_Types USBPD CORE CAD Exported Types
  * @{
  */

/**
  * @brief funtion return value @ref USBPD_CORE_CAD
  * @{
  */
typedef enum
{
  USBPD_CAD_OK          ,         /*!< USBPD CAD Status OK                */
  USBPD_CAD_INVALID_PORT,         /*!< USBPD CAD Status INVALID PORT      */
  USBPD_CAD_ERROR,                /*!< USBPD CAD Status ERROR             */
  USBPD_CAD_MALLOCERROR           /*!< USBPD CAD Status ERROR MALLOC      */
}
USBPD_CAD_StatusTypeDef;
/**
  * @}
  */

/**
  * @brief activation value @ref USBPD_CORE_CAD
  * @{
  */
 typedef enum 
 {
   USBPD_CAD_DISABLE,         /*!< USBPD CAD activation status Disable   */
   USBPD_CAD_ENABLE           /*!< USBPD CAD activation status Enable   */
 } USBPD_CAD_activation;
/**
  * @}
  */

/**
  * @brief CallBacks exposed by the @ref USBPD_CORE_CAD
  */
typedef struct
{
  /**
  * @brief  CallBack reporting events on a specified port.
  * @param  PortNum The handle of the port
  * @param  State   CAD state
  * @param  Cc      The Communication Channel for the USBPD communication
  * @retval None
  */
  void (*USBPD_CAD_CallbackEvent)(uint8_t PortNum, USBPD_CAD_EVENT State, CCxPin_TypeDef Cc);
  /**
  * @brief  CallBack to wakeup the CAD.
  * @retval None
  */
  void (*USBPD_CAD_WakeUp)(void);
}USBPD_CAD_Callbacks;

/**
  * @}
  */

/** @defgroup USBPD_CORE_CAD_Exported_Functions_Grp1 USBPD CORE CAD Exported Functions
  * @{
  */
/**
  * @brief  Initialize the CAD module for a specified port.
  * @param  PortNum           Index of current used port
  * @param  CallbackFunctions CAD port callback function
  * @param  Settings          Pointer on @ref USBPD_SettingsTypeDef structure
  * @param  Params            Pointer on @ref USBPD_ParamsTypeDef structure
  * @retval USBPD_CAD status
  */
USBPD_CAD_StatusTypeDef USBPD_CAD_Init(uint8_t PortNum, USBPD_CAD_Callbacks *CallbackFunctions, USBPD_SettingsTypeDef *Settings, USBPD_ParamsTypeDef *Params);

/**
  * @brief  Main CAD task.
  * @retval Timing in ms
  */
uint32_t                USBPD_CAD_Process(void);

/**
  * @brief  Enable or Disable CAD port.
  * @param  PortNum Index of current used port
  * @param  State   The new state of the port
  * @retval None
  */
void                    USBPD_CAD_PortEnable(uint8_t PortNum, USBPD_CAD_activation State);

/**
  * @brief  Set as SNK.
  * @param  PortNum Index of current used port
  * @retval None
  */
void                    USBPD_CAD_AssertRd(uint8_t PortNum);

/**
  * @brief  Set as SRC.
  * @param  PortNum Index of current used port
  * @retval None
  */
void                    USBPD_CAD_AssertRp(uint8_t PortNum);

/**
  * @brief  Set type C state machine in error recovery state
  * @param  PortNum Index of current used port
  * @retval None
  */
void                    USBPD_CAD_EnterErrorRecovery(uint8_t PortNum);
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup USBPD_CORE_PE
  * @{
  */

#ifdef USBPDCORE_VDM
/** @addtogroup USBPD_CORE_VDM
  * @{
  */

/** @defgroup USBPD_CORE_VDM_Exported_Callback USBPD CORE VDM Exported Callback
  * @{
  */

/**
  * @brief CallBacks exposed by the @ref USBPD_CORE_PE
  * */
typedef struct
{
  /**
    * @brief  VDM Discovery identity callback (answer to Discover Identity message)
    * @param  PortNum   current port number
    * @param  pIdentity Pointer on USBPD_DiscoveryIdentity_TypeDef structure
    * @retval USBPD status : USBPD_ACK or USBPD_BUSY
    */
  USBPD_StatusTypeDef (*USBPD_VDM_DiscoverIdentity)(uint8_t PortNum, USBPD_DiscoveryIdentity_TypeDef *pIdentity);

  /**
    * @brief  VDM Discover SVID callback (retrieve SVID supported by device for answer to Discovery mode)
    * @param  PortNum     current port number
    * @param  p_SVID_Info Pointer on USBPD_SVIDInfo_TypeDef structure
    * @retval USBPD status  USBPD_BUSY or USBPD_ACK or USBPD_NAK
    */
  USBPD_StatusTypeDef (*USBPD_VDM_DiscoverSVIDs)(uint8_t PortNum, uint16_t **p_SVID_Data, uint8_t *nbSVID);

  /**
    * @brief  VDM Discover Mode callback (report all the modes supported by SVID)
    * @param  PortNum      current port number
    * @param  SVID         SVID ID
    * @param  p_ModeTab    Pointer on the mode value
    * @param  NumberOfMode Number of mode available
    * @retval USBPD status
    */
  USBPD_StatusTypeDef (*USBPD_VDM_DiscoverModes)(uint8_t PortNum, uint16_t SVID, uint32_t **p_ModeTab, uint8_t *NumberOfMode);

  /**
    * @brief  VDM Mode enter callback
    * @param  PortNum   current port number
    * @param  SVID      SVID ID
    * @param  ModeIndex Index of the mode to be entered
    * @retval USBPD status USBPD_ACK/USBPD_NAK
    */
  USBPD_StatusTypeDef (*USBPD_VDM_ModeEnter)(uint8_t PortNum, uint16_t SVID, uint32_t ModeIndex);

  /**
    * @brief  VDM Mode exit callback
    * @param  PortNum   current port number
    * @param  SVID      SVID ID
    * @param  ModeIndex Index of the mode to be exited
    * @retval USBPD status USBPD_ACK/USBPD_NAK
    */
  USBPD_StatusTypeDef (*USBPD_VDM_ModeExit)(uint8_t PortNum, uint16_t SVID, uint32_t ModeIndex);

  /**
    * @brief  Inform identity callback (Identity information received in Discovery identity answer)
    * @param  PortNum       current port number
    * @param  SOPType       SOP type 
    * @param  CommandStatus Command status based on @ref USBPD_VDM_CommandType_Typedef
    * @param  pIdentity     Pointer on the discovery identity information based on @ref USBPD_DiscoveryIdentity_TypeDef
    * @retval USBPD status 
    */
  void (*USBPD_VDM_InformIdentity)(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, USBPD_VDM_CommandType_Typedef CommandStatus, USBPD_DiscoveryIdentity_TypeDef *pIdentity);

  /**
    * @brief  Inform SVID callback
    * @param  PortNum       current port number
    * @param  SOPType       SOP type 
    * @param  CommandStatus Command status based on @ref USBPD_VDM_CommandType_Typedef
    * @param  pListSVID     Pointer of list of SVID based on @ref USBPD_SVIDInfo_TypeDef
    * @retval USBPD status
    */
  USBPD_StatusTypeDef (*USBPD_VDM_InformSVID)(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, USBPD_VDM_CommandType_Typedef CommandStatus, USBPD_SVIDInfo_TypeDef *pListSVID);

  /**
    * @brief  Inform Mode callback
    * @param  PortNum         current port number
    * @param  SOPType         SOP type 
    * @param  CommandStatus   Command status based on @ref USBPD_VDM_CommandType_Typedef
    * @param  pModesInfo      Pointer of Modes info based on @ref USBPD_ModeInfo_TypeDef
    * @retval USBPD status
    */
  USBPD_StatusTypeDef (*USBPD_VDM_InformMode)(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, USBPD_VDM_CommandType_Typedef CommandStatus, USBPD_ModeInfo_TypeDef *pModesInfo);

  /**
    * @brief  Inform Mode enter callback
    * @param  PortNum       current port number
    * @param  SOPType       SOP type 
    * @param  CommandStatus Command status based on @ref USBPD_VDM_CommandType_Typedef
    * @param  SVID          SVID ID
    * @param  ModeIndex     Index of the mode to be entered
    * @retval USBPD status
    */
  USBPD_StatusTypeDef (*USBPD_VDM_InformModeEnter)(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, USBPD_VDM_CommandType_Typedef CommandStatus, uint16_t SVID, uint32_t ModeIndex);

  /**
    * @brief  Inform Mode exit callback
    * @param  PortNum       current port number
    * @param  SOPType       SOP type 
    * @param  CommandStatus Command status based on @ref USBPD_VDM_CommandType_Typedef
    * @param  SVID          SVID ID
    * @param  ModeIndex     Index of the mode to be exited
    * @retval USBPD status
    */
  USBPD_StatusTypeDef (*USBPD_VDM_InformModeExit)(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, USBPD_VDM_CommandType_Typedef CommandStatus, uint16_t SVID, uint32_t ModeIndex);

  /**
    * @brief  Send VDM Attention message callback
    * @param  PortNum    current port number
    * @param  pNbData    Pointer of number of VDO to send
    * @param  pVDO       Pointer of VDO to send
    * @retval status
    */
  USBPD_StatusTypeDef (*USBPD_VDM_SendAttention)(uint8_t PortNum, uint8_t *pNbData, uint32_t *pVDO);

  /**
    * @brief  Receive VDM Attention callback
    * @param  PortNum   current port number
    * @param  NbData    Number of received VDO
    * @param  VDO       Received VDO
    * @retval status
    */
  void (*USBPD_VDM_ReceiveAttention)(uint8_t PortNum, uint8_t NbData, uint32_t VDO);

  /**
    * @brief  VDM Send Specific message callback
    * @param  PortNum    current port number
    * @param  VDMCommand VDM command based on @ref USBPD_VDM_Command_Typedef
    * @param  pNbData    Pointer of number of VDO to send
    * @param  pVDO       Pointer of VDO to send
    * @retval status
    */
  USBPD_StatusTypeDef (*USBPD_VDM_SendSpecific)(uint8_t PortNum, USBPD_VDM_Command_Typedef VDMCommand, uint8_t *pNbData, uint32_t *pVDO);

  /**
    * @brief  VDM Receive Specific message callback
    * @param  PortNum         Current port number
    * @param  VDMCommand      VDM command based on @ref USBPD_VDM_Command_Typedef
    * @param  pNbData     Pointer of number of received VDO and used for the answer
    * @param  pVDO        Pointer of received VDO and use for the answer
    * @retval status
    */
  USBPD_StatusTypeDef (*USBPD_VDM_ReceiveSpecific)(uint8_t PortNum, USBPD_VDM_Command_Typedef VDMCommand, uint8_t *pNbData, uint32_t *pVDO);

  /**
    * @brief  VDM Specific message callback to inform user of reception of VDM specific message
    * @param  PortNum    current port number
    * @param  VDMCommand VDM command based on @ref USBPD_VDM_Command_Typedef
    * @param  pNbData    Pointer of number of received VDO
    * @param  pVDO       Pointer of received VDO
    * @retval status
    */
  USBPD_StatusTypeDef (*USBPD_VDM_InformSpecific)(uint8_t PortNum, USBPD_VDM_Command_Typedef VDMCommand, uint8_t *pNbData, uint32_t *pVDO);
}USBPD_VDM_Callbacks;

/**
  * @}
  */

/**
  * @}
  */

#endif /* USBPDCORE_VDM */

/** @defgroup USBPD_CORE_PE_Exported_TypesDefinitions USBPD CORE PE Exported Types Definitions
  * @{
  */

/** @defgroup PE_CallBacks_structure_definition PE CallBacks structure definition
  * @brief  PE CallBacks exposed by the PE to the  DMP
  * @{
  */
typedef struct
{
  /**
    * @brief  Request the DPM to setup the new power level.
    * @param  PortNum Port number
    * @retval USBPD_ACCEPT, USBPD_REJECT, USBPD_WAIT
  */
  USBPD_StatusTypeDef (*USBPD_PE_RequestSetupNewPower)(uint8_t PortNum);

  /**
    * @brief  Inform the DPM to HardReset status.
    * @param  PortNum Port number
    * @param  Role of the board
    * @param  Status HR Status update
    * @retval None
  */
  void (*USBPD_PE_HardReset)(uint8_t PortNum, USBPD_PortPowerRole_TypeDef CurrentRole, USBPD_HR_Status_TypeDef Status);

  /**
    * @brief  Get evaluation of swap request from DPM.
    * @param  PortNum Port number
    * @retval USBPD_ACCEPT, USBPD_WAIT, USBPD_REJECT 
  */
  USBPD_StatusTypeDef (*USBPD_PE_EvaluatPRSwap)(uint8_t PortNum);

  /**
    * @brief  Callback to be used by PE to notify a generic event, clear for the specific DPM
    * @param  PortNum   Port number
    * @param  EventVal  @ref USBPD_NotifyEventValue_TypeDef
    * @retval none
    */
  void (*USBPD_PE_Notify)(uint8_t PortNum, USBPD_NotifyEventValue_TypeDef EventVal);

  /**
    * @brief  Request DPM to confirm if current contract is still valid.
    * @param  PortNum Port number
    * @retval USBPD_OK, USBPD_ERROR
    */
  USBPD_StatusTypeDef (*USBPD_PE_SRC_IsContractStillValid)(uint8_t PortNum);

  /**
    * @brief  Inform DPM that an extended message has been received.
    * @param  PortNum port number value
    * @param  MsgId extended message id
    * @param  ptrData : pointer on the data
    * @param  DataSize : size of the data  
    * @retval None
    */
  void (*USBPD_PE_ExtendedMessage)(uint8_t PortNum, USBPD_ExtendedMsg_TypeDef MsgId, uint8_t *ptrData, uint16_t DataSize);

  /**
    * @brief  Allow PE to retrieve information from DPM/PWR_IF.
    * @param  PortNum Port number
    * @param  DataId  Type of data to be read from DPM based on @ref USBPD_CORE_DataInfoType_TypeDef
    * @param  Ptr Pointer on address where DPM data should be written (u32 pointer)
    * @param  Size    Pointer on nb of bytes written by DPM
    * @retval None
    */
  void (*USBPD_PE_GetDataInfo)(uint8_t PortNum, USBPD_CORE_DataInfoType_TypeDef DataId , uint32_t *Ptr, uint32_t *Size);

  /**
    * @brief  Allow PE to update information in DPM/PWR_IF.
    * @param  PortNum Port number
    * @param  DataId  Type of data to be read from DPM based on @ref USBPD_CORE_DataInfoType_TypeDef
    * @param  Ptr Pointer on address where DPM data to be updated could be read (u32 pointer)
    * @param  Size    Nb of byte to be updated in DPM
    * @retval None
    */
  void (*USBPD_PE_SetDataInfo)(uint8_t PortNum, USBPD_CORE_DataInfoType_TypeDef DataId , uint32_t *Ptr, uint32_t Size);

  /**
    * @brief  Callback to be used by PE to evaluate a Request from Sink
    * @param  PortNum Port number
    * @param  PtrPowerObject  Pointer on the power data object
    * @retval USBPD_ACCEPT, USBPD_REJECT, USBPD_WAIT, USBPD_GOTOMIN
    */
  USBPD_StatusTypeDef (*USBPD_PE_SRC_EvaluateRequest)(uint8_t PortNum, USBPD_CORE_PDO_Type_TypeDef *PtrPowerObject);

  /**
    * @brief  Callback to be used by PE to evaluate a Source Capabilities from Source
    * @param  PortNum         Port number
    * @param  PtrRequestData  Pointer on selected request data object
    * @param  PtrPowerObject  Pointer on the power data object
    * @retval None
    */
  void (*USBPD_PE_SNK_EvaluateCapabilities)(uint8_t PortNum, uint32_t *RequestData, USBPD_CORE_PDO_Type_TypeDef *PtrPowerObject);

  /**
    * @brief  Callback to be used during power role swap
    * @param  PortNum Port number
    * @param  Role of the board
    * @param  Status HR Status update
    * @retval None
    */
  void (*USBPD_PE_PowerRoleSwap)(uint8_t PortNum, USBPD_PortPowerRole_TypeDef CurrentRole, USBPD_PRS_Status_TypeDef Status);

  /**
    * @brief  Callback to be used by PE to wakeup the state machine
    * @param  PortNum Port number
    * @retval None
    */
  void (*USBPD_PE_WakeupCallback)(uint8_t PortNum);

  /**
    * @brief  Callback to be used by PE to evaluate a Vconn swap
    * @param  PortNum Port number
    * @retval USBPD_ACCEPT, USBPD_REJECT, USBPD_WAIT
    */
  USBPD_StatusTypeDef (*USBPD_PE_EvaluateVconnSwap)(uint8_t PortNum);

  /**
    * @brief  Callback to be used by PE to manage VConn
    * @param  PortNum Port number
    * @param  State  Enable or Disable VConn on CC lines
    * @retval USBPD_ACCEPT, USBPD_REJECT
    */
  USBPD_StatusTypeDef (*USBPD_PE_VconnPwr)(uint8_t PortNum, USBPD_FunctionalState State);

  /**
    * @brief  Callback to be used by PE to manage VConn
    * @param  PortNum Port number
    * @retval None
    */
  void (*USBPD_PE_EnterErrorRecovery)(uint8_t PortNum);

  /**
    * @brief  Callback to be used by PE to know application status about DataRoleSwap
    * @param  PortNum Port number
    * @retval USBPD_REJECT, USBPD_ACCEPT
    */
  USBPD_StatusTypeDef (*USBPD_PE_DataRoleSwap)(uint8_t PortNum);

  /**
    * @brief  Callback to be used by PE to check is VBUS is ready or present
    * @param  PortNum Port number
    * @param  Vsafe   Vsafe status based on @ref USBPD_VSAFE_StatusTypeDef
    * @retval USBPD_DISABLE or USBPD_ENABLE
    */
  USBPD_FunctionalState (*USBPD_PE_IsPowerReady)(uint8_t PortNum, USBPD_VSAFE_StatusTypeDef Vsafe);

}USBPD_PE_Callbacks;

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup USBPD_CORE_PE_Exported_Functions USBPD CORE PE Exported Functions
  * @{
  */

/** @defgroup USBPD_CORE_PE_Exported_Functions_Group1 USBPD CORE PE Exported Functions to DPM CORE
  * @{
  */
/**
  * @brief  Initialize Policy Engine layer for a Port with a specified role
  * @param  PortNum     Index of current used port
  * @param  pSettings   Pointer on @ref USBPD_SettingsTypeDef structure
  * @param  pParams     Pointer on @ref USBPD_ParamsTypeDef structure
  * @param  PECallbacks Callback function to be passed to PRL layer
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PE_Init(uint8_t PortNum, USBPD_SettingsTypeDef *pSettings, USBPD_ParamsTypeDef *pParams, const USBPD_PE_Callbacks *PECallbacks);

/**
  * @brief  Check coherence between lib slected and the lib include inside the project
  * @param  LibId    Value fix defined with the switch lib.
  * @retval USBPD_TRUE or USBPD_FALSE
  */
uint32_t            USBPD_PE_CheckLIB(uint32_t LibId);

/**
  * @brief  Return the need of the stack in terms of dynamique allocation
  * @note   This value correspond to worst case 2 port os if application manage
  *         only one port divide the value by 2
  * @retval Memory size
  */
uint32_t            USBPD_PE_GetMemoryConsumption(void);

/**
  * @brief  Set the trace pointer
  * @param  Ptr function on trace
  * @retval None
  */
void                USBPD_PE_SetTrace(void *Ptr, uint8_t Debug);

#if defined(USBPDCORE_SRC) || defined(USBPDCORE_DRP)
/**
  * @brief  Policy Engine Source port main state machine
  * @param  PortNum Index of current used port
  * @retval Timing in ms
  */
uint32_t            USBPD_PE_StateMachine_SRC(uint8_t PortNum);
#endif /* USBPDCORE_SRC || USBPDCORE_DRP */

#if defined(USBPDCORE_SNK) || defined(USBPDCORE_DRP)
/**
  * @brief  Policy Engine Sink port main state machine
  * @param  PortNum Index of current used port
  * @retval Timing in ms
  */
uint32_t            USBPD_PE_StateMachine_SNK(uint8_t PortNum);
#endif /* USBPDCORE_SNK || USBPDCORE_DRP */

#ifdef USBPDCORE_DRP
/**
  * @brief  Policy Engine dual role port main state machine  
  * @param  PortNum Index of current used port
  * @retval Timing in ms
  */
uint32_t            USBPD_PE_StateMachine_DRP(uint8_t PortNum);
#endif /* USBPDCORE_DRP */

/**
  * @brief  Function called by DPM to set the cable status connected or disconnected.
  * @param  PortNum     Index of current used port
  * @param  IsConnected Cable connection status: 1 if connected and 0 is disconnected
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PE_IsCableConnected(uint8_t PortNum, uint8_t IsConnected);

/**
  * @brief  Increment PE Timers tick
  * @param  PortNum Index of current used port
  * @retval None
  */
void                USBPD_PE_TimerCounter(uint8_t PortNum);

/**
  * @}
  */

#ifdef USBPDCORE_VDM
/** @defgroup USBPD_CORE_PE_Exported_Functions_Group2 USBPD CORE PE Exported Functions to VDM USER
  * @{
  */
/**
  * @brief  Initialize VDM callback functions in PE
  * @param  PortNum       Index of current used port
  * @param  VDMCallbacks  Pointer on VDM callbacks based on @ref USBPD_VDM_Callbacks
  * @retval None
  */
void                USBPD_PE_InitVDM_Callback(uint8_t PortNum, USBPD_VDM_Callbacks *VDMCallbacks);
/**
  * @}
  */
#endif /* USBPDCORE_VDM */

/** @defgroup USBPD_CORE_PE_Exported_Functions_Group3 USBPD CORE PE Exported Functions to DPM USER
  * @{
  */

/**
  * @brief  Generic function to send a control message 
  * @param  PortNum   Index of current used port
  * @param  CtrlMsg   Control message id
  * @param  SOPType   SOP Type based on @ref USBPD_SOPType_TypeDef
  * @retval USBPD status  USBPD_BUSY, USBPD_ERROR, USBPD_FAIL
  */
USBPD_StatusTypeDef USBPD_PE_Request_CtrlMessage(uint8_t PortNum, USBPD_ControlMsg_TypeDef CtrlMsg, USBPD_SOPType_TypeDef SOPType);

/**
  * @brief  Generic function to send a data message 
  * @param  PortNum   Index of current used port
  * @param  DataMsg   Data message id based on @ref USBPD_DataMsg_TypeDef
  * @param  pData     Pointer of PDO to send
  * @param  Size      Size of the message to send (number of u32)
  * @retval USBPD status  USBPD_BUSY, USBPD_ERROR, USBPD_FAIL
  */
USBPD_StatusTypeDef USBPD_PE_Request_DataMessage(uint8_t PortNum, USBPD_DataMsg_TypeDef DataMsg, uint32_t *pData, uint32_t Size);

/**
  * @brief  Called by DPM to request PE to perform a Hard Reset.
  * @param  PortNum Index of current used port
  * @retval USBPD status USBPD_OK USBPD_BUSY USBPD_FAIL, USBPD_NOTSUPPORTED
  */
USBPD_StatusTypeDef USBPD_PE_Request_HardReset(uint8_t PortNum);

#if defined(USBPDCORE_SNK) || defined(USBPDCORE_DRP)
/**
  * @brief  Evaluate received Capabilities Message from Source port and prepare the request message  
  * @param  PortNum   Index of current used port
  * @param  Rdo       Requested data object 
  * @param  PWobject  Power Object
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PE_Send_Request(uint8_t PortNum, uint32_t Rdo, USBPD_CORE_PDO_Type_TypeDef PWobject);
#endif /* USBPDCORE_SNK || USBPDCORE_DRP */

#ifdef USBPDCORE_VDM
/**
  * @brief  Called by DPM to request the PE to perform a VDM identity request.
  * @note   On PD2.0, SVDM Identity cannot be sent by UFP.
  * @param  PortNum Index of current used port
  * @param  SOPType SOP Type (Only SOP or SOP')
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PE_SVDM_RequestIdentity(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType);

/**
  * @brief  Called by DPM to request the PE to perform a VDM SVID request.
  * @param  PortNum Index of current used port
  * @param  SOPType SOP Type (only valid for SOP or SOP')
  * @retval USBPD status : USBPD_BUSY, USBPD_OK, USBPD_FAIL
  */
USBPD_StatusTypeDef USBPD_PE_SVDM_RequestSVID(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType);

/**
  * @brief  Called by DPM to request the PE to perform a VDM Discovery mode message on one SVID.
  * @param  PortNum Index of current used port
  * @param  SOPType SOP Type
  * @param  SVID    SVID used for discovery mode message
  * @retval USBPD status : USBPD_BUSY, USBPD_OK, USBPD_FAIL
  */
USBPD_StatusTypeDef USBPD_PE_SVDM_RequestMode(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID);

/**
  * @brief  Called by DPM to request the PE to perform a VDM Discovery mode message on one SVID.
  * @param  PortNum   Index of current used port
  * @param  SOPType   SOP Type
  * @param  SVID      SVID used for discovery mode message
  * @param  ModeIndex Index of the mode to be entered
  * @retval USBPD status : USBPD_BUSY, USBPD_OK, USBPD_FAIL
  */
USBPD_StatusTypeDef USBPD_PE_SVDM_RequestModeEnter(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID, uint8_t ModeIndex);

/**
  * @brief  Called by DPM to request the PE to perform a VDM mode exit.
  * @param  PortNum   Index of current used port
  * @param  SOPType   SOP Type
  * @param  SVID      SVID used for discovery mode message
  * @param  ModeIndex Index of the mode to be exit
  * @retval USBPD status : USBPD_BUSY, USBPD_OK, USBPD_FAIL
  */
USBPD_StatusTypeDef USBPD_PE_SVDM_RequestModeExit(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID, uint8_t ModeIndex);

/**
  * @brief  Called by DPM to request the PE to perform a VDM Attention.
  * @param  PortNum Index of current used port
  * @param  SOPType Received message type based on @ref USBPD_SOPType_TypeDef
  * @param  SVID    Used SVID
  * @retval USBPD status : USBPD_BUSY, USBPD_OK, USBPD_FAIL
  */
USBPD_StatusTypeDef USBPD_PE_SVDM_RequestAttention(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, uint16_t SVID);

/**
  * @brief  Called by DPM to request the PE to send a specific SVDM message.
  * @param  PortNum Index of current used port
  * @param  SOPType Received message type based on @ref USBPD_SOPType_TypeDef
  * @param  Command VDM command based on @ref USBPD_VDM_Command_Typedef
  * @param  SVID    Used SVID
  * @retval USBPD status : USBPD_BUSY, USBPD_OK, USBPD_FAIL
  */
USBPD_StatusTypeDef USBPD_PE_SVDM_RequestSpecific(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, USBPD_VDM_Command_Typedef Command, uint16_t SVID);
#endif /* USBPDCORE_VDM */

#if defined(USBPD_REV30_SUPPORT)
/**
  * @brief  Send an chunked extended message and store data received inside a buffer
  * @param  PortNum      Port number value
  * @param  SOPType      Message type based on @ref USBPD_SOPType_TypeDef
  * @param  MessageType  Extended Msg type @ref USBPD_ExtendedMsg_TypeDef
  * @param  Ptrdata      Data pointer to PRL layer
  * @param  DataSize     Size of the data
  * @retval USBPD status
  */
USBPD_StatusTypeDef USBPD_PE_SendExtendedMessage(uint8_t PortNum, USBPD_SOPType_TypeDef SOPType, USBPD_ExtendedMsg_TypeDef MessageType, uint8_t *Ptrdata, uint16_t DataSize);

#if defined(USBPDCORE_FASTROLESWAP)
/**
  * @brief  Execute an FRS signalling.
  * @param  PortNum
  * @retval Timing in ms.
  */
void USBPD_PE_ExecFastRoleSwapSignalling(uint8_t PortNum);
#endif
#endif /* USBPD_REV30_SUPPORT */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup USBPD_CORE_PRL
  * @{
  */

/** @defgroup USBPD_CORE_PRL_Exported_Functions USBPD CORE PRL Exported Functions
  * @{
  */

/** @defgroup USBPD_CORE_PRL_Exported_Functions_Group1 USBPD CORE PRL Interface function for timer
  * @{
  */

/**
  * @brief  Decrement The PRL Timers values
  * @param  PortNum port number value
  * @retval None
  */
void USBPD_PRL_TimerCounter(uint8_t PortNum);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#if defined(USBPDCORE_TCPM_SUPPORT)
/** @addtogroup USBPD_CORE_TCPM
  * @{
  */

/** @defgroup USBPD_CORE_TCPM_Exported_Functions USBPD CORE TCPM Exported Functions
  * @{
  */

/** @defgroup USBPD_CORE_TCPM_Exported_Functions_Grp1 USBPD CORE TCPM Exported Functions to applications (DPM and PWR_IF)
  * @{
  */

/**
  * @brief  Initialize TCPC devices
  * @param  PortNum           Port number value
  * @param  TCPC_ToggleRole   Indication if TCPC should perform a role toggle or not
  * @param  Params            Pointer on PE parameters based on @ref USBPD_ParamsTypeDef
  * @param  CallbackFunctions Pointer on CAD callbacks
  * @param  TCPC_Driver       Pointer on TCPC drivers based on @ref TCPC_DrvTypeDef
  * @retval USBPD status
  */
USBPD_StatusTypeDef  USBPD_TCPM_HWInit(uint8_t PortNum, uint8_t TCPC_ToggleRole, USBPD_ParamsTypeDef *Params, USBPD_CAD_Callbacks *CallbackFunctions, TCPC_DrvTypeDef * TCPC_Driver);

/**
  * @brief  Set CC line for PD connection
  * @param  PortNum Port number value
  * @param  Pull Power role can be one of the following values:
  *         @arg @ref TYPEC_CC_RA
  *         @arg @ref TYPEC_CC_RP
  *         @arg @ref TYPEC_CC_RD
  *         @arg @ref TYPEC_CC_OPEN
  * @param  State Activation or deactivation of connection
  * @retval USBPD status
  */
USBPD_StatusTypeDef  USBPD_TCPM_set_cc(uint32_t PortNum, TCPC_CC_Pull_TypeDef Pull, USBPD_FunctionalState State);

/**
  * @brief  Enable or disable VCONN
  * @param  PortNum Port number value
  * @param  State   Activation or deactivation of VCONN
  * @retval USBPD status
  */
USBPD_StatusTypeDef  USBPD_TCPM_set_vconn(uint32_t PortNum, USBPD_FunctionalState State);

/**
  * @brief  Enable VBUS
  * @param  PortNum The port handle.
  * @retval USBPD status
  */
USBPD_StatusTypeDef  USBPD_TCPM_VBUS_Enable(uint32_t PortNum);

/**
  * @brief  Disable VBUS
  * @param  PortNum The port handle.
  * @retval USBPD status
  */
USBPD_StatusTypeDef  USBPD_TCPM_VBUS_Disable(uint32_t PortNum);

/**
  * @brief  Get VBUS voltage
  * @param  PortNum   The port handle.
  * @param  pVoltage  Pointer on the VBUS voltage
  * @retval VBUS value in mV
  */
uint16_t USBPD_TCPM_VBUS_GetVoltage(uint32_t PortNum);

/**
  * @brief  Retrieve the VBUS VSafe0 status for a specified port.
  * @param  PortNum The port handle.
  * @retval USBPD_StatusTypeDef
  */
USBPD_StatusTypeDef  USBPD_TCPM_VBUS_IsVsafe0V(uint32_t PortNum);

/**
  * @brief  Retrieve the VBUS Vsafe5V status for a specified port.
  * @param  PortNum The port handle.
  * @retval USBPD_StatusTypeDef
  */
USBPD_StatusTypeDef  USBPD_TCPM_VBUS_IsVsafe5V(uint32_t PortNum);

/**
  * @brief  Management of ALERT
  * @param  Event Event reported by application
  * @retval USBPD status
  */
USBPD_StatusTypeDef  USBPD_TCPM_alert(uint32_t Event);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* USBPDCORE_TCPM_SUPPORT */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USBPD_CORE_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
