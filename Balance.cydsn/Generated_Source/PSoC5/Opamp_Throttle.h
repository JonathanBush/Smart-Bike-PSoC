/*******************************************************************************
* File Name: Opamp_Throttle.h  
* Version 1.90
*
* Description:
*  This file contains the function prototypes and constants used in
*  the OpAmp (Analog Buffer) Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_Opamp_Throttle_H) 
#define CY_OPAMP_Opamp_Throttle_H 

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component OpAmp_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
}   Opamp_Throttle_BACKUP_STRUCT;

/* Variable describes initial state of the component */
extern uint8 Opamp_Throttle_initVar;


/**************************************
*        Function Prototypes 
**************************************/

void Opamp_Throttle_Start(void)               ;
void Opamp_Throttle_Stop(void)                ;
void Opamp_Throttle_SetPower(uint8 power)     ;
void Opamp_Throttle_Sleep(void)               ;
void Opamp_Throttle_Wakeup(void)              ;
void Opamp_Throttle_SaveConfig(void)          ;
void Opamp_Throttle_RestoreConfig(void)       ;
void Opamp_Throttle_Init(void)                ;
void Opamp_Throttle_Enable(void)              ;


/**************************************
*           API Constants
**************************************/

/* Power constants for SetPower() function */
#define Opamp_Throttle_LPOCPOWER              (0x00u)
#define Opamp_Throttle_LOWPOWER               (0x01u)
#define Opamp_Throttle_MEDPOWER               (0x02u)
#define Opamp_Throttle_HIGHPOWER              (0x03u)


/**************************************
*           Parameter Defaults        
**************************************/
#define Opamp_Throttle_DEFAULT_POWER          (3u)
#define Opamp_Throttle_DEFAULT_MODE           (1u)


/**************************************
*             Registers
**************************************/

#define Opamp_Throttle_CR_REG                 (* (reg8 *) Opamp_Throttle_ABuf__CR)
#define Opamp_Throttle_CR_PTR                 (  (reg8 *) Opamp_Throttle_ABuf__CR)

#define Opamp_Throttle_MX_REG                 (* (reg8 *) Opamp_Throttle_ABuf__MX)
#define Opamp_Throttle_MX_PTR                 (  (reg8 *) Opamp_Throttle_ABuf__MX)

#define Opamp_Throttle_SW_REG                 (* (reg8 *) Opamp_Throttle_ABuf__SW)
#define Opamp_Throttle_SW_PTR                 (  (reg8 *) Opamp_Throttle_ABuf__SW)

/* Active mode power manager register */
#define Opamp_Throttle_PM_ACT_CFG_REG         (* (reg8 *) Opamp_Throttle_ABuf__PM_ACT_CFG)
#define Opamp_Throttle_PM_ACT_CFG_PTR         (  (reg8 *) Opamp_Throttle_ABuf__PM_ACT_CFG)

/* Alternative mode power manager register */
#define Opamp_Throttle_PM_STBY_CFG_REG        (* (reg8 *) Opamp_Throttle_ABuf__PM_STBY_CFG)
#define Opamp_Throttle_PM_STBY_CFG_PTR        (  (reg8 *) Opamp_Throttle_ABuf__PM_STBY_CFG)

/* ANIF.PUMP.CR1 Pump Configuration Register 1 */
#define Opamp_Throttle_PUMP_CR1_REG           (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define Opamp_Throttle_PUMP_CR1_PTR           (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Trim register defines */
#define Opamp_Throttle_TR0_REG                (* (reg8 *) Opamp_Throttle_ABuf__TR0)
#define Opamp_Throttle_TR0_PTR                (  (reg8 *) Opamp_Throttle_ABuf__TR0)

#define Opamp_Throttle_TR1_REG                (* (reg8 *) Opamp_Throttle_ABuf__TR1)
#define Opamp_Throttle_TR1_PTR                (  (reg8 *) Opamp_Throttle_ABuf__TR1)


/**************************************
*       Register Constants
**************************************/

/* CX Analog Buffer Input Selection Register */

/* Power mode defines */

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */ 
#define Opamp_Throttle_ACT_PWR_EN             Opamp_Throttle_ABuf__PM_ACT_MSK 
/* PM_STBY_CFG (Alternative Active Power Mode CFG Register) mask */ 
#define Opamp_Throttle_STBY_PWR_EN            Opamp_Throttle_ABuf__PM_STBY_MSK 
/* Power mask */
#define Opamp_Throttle_PWR_MASK               (0x03u)

/* MX Analog Buffer Input Selection Register */

/* Bit Field  MX_VN */
#define Opamp_Throttle_MX_VN_MASK             (0x30u)
#define Opamp_Throttle_MX_VN_NC               (0x00u)
#define Opamp_Throttle_MX_VN_AG4              (0x10u)
#define Opamp_Throttle_MX_VN_AG6              (0x20u)

/* Bit Field  MX_VP */
#define Opamp_Throttle_MX_VP_MASK             (0x0Fu)
#define Opamp_Throttle_MX_VP_NC               (0x00u)
#define Opamp_Throttle_MX_VP_VREF             (0x09u)
#define Opamp_Throttle_MX_VP_AG4              (0x01u)
#define Opamp_Throttle_MX_VP_AG5              (0x02u)
#define Opamp_Throttle_MX_VP_AG6              (0x03u)
#define Opamp_Throttle_MX_VP_AG7              (0x04u)
#define Opamp_Throttle_MX_VP_ABUS0            (0x05u)
#define Opamp_Throttle_MX_VP_ABUS1            (0x06u)
#define Opamp_Throttle_MX_VP_ABUS2            (0x07u)
#define Opamp_Throttle_MX_VP_ABUS3            (0x08u)

/* SW Analog Buffer Routing Switch Reg */

/* Bit Field  SW */
#define Opamp_Throttle_SW_MASK                (0x07u) 
#define Opamp_Throttle_SW_SWINP               (0x04u)  /* Enable positive input */
#define Opamp_Throttle_SW_SWINN               (0x02u)  /* Enable negative input */

/* Pump configuration register masks */
#define Opamp_Throttle_PUMP_CR1_CLKSEL        (0x40u)
#define Opamp_Throttle_PUMP_CR1_FORCE         (0x20u)
#define Opamp_Throttle_PUMP_CR1_AUTO          (0x10u)

#endif /* CY_OPAMP_Opamp_Throttle_H */


/* [] END OF FILE */
