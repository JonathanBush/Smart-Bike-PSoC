/*******************************************************************************
* File Name: Rx_SBUS.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Rx_SBUS_H) /* Pins Rx_SBUS_H */
#define CY_PINS_Rx_SBUS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Rx_SBUS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Rx_SBUS__PORT == 15 && ((Rx_SBUS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Rx_SBUS_Write(uint8 value);
void    Rx_SBUS_SetDriveMode(uint8 mode);
uint8   Rx_SBUS_ReadDataReg(void);
uint8   Rx_SBUS_Read(void);
void    Rx_SBUS_SetInterruptMode(uint16 position, uint16 mode);
uint8   Rx_SBUS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Rx_SBUS_SetDriveMode() function.
     *  @{
     */
        #define Rx_SBUS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Rx_SBUS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Rx_SBUS_DM_RES_UP          PIN_DM_RES_UP
        #define Rx_SBUS_DM_RES_DWN         PIN_DM_RES_DWN
        #define Rx_SBUS_DM_OD_LO           PIN_DM_OD_LO
        #define Rx_SBUS_DM_OD_HI           PIN_DM_OD_HI
        #define Rx_SBUS_DM_STRONG          PIN_DM_STRONG
        #define Rx_SBUS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Rx_SBUS_MASK               Rx_SBUS__MASK
#define Rx_SBUS_SHIFT              Rx_SBUS__SHIFT
#define Rx_SBUS_WIDTH              1u

/* Interrupt constants */
#if defined(Rx_SBUS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Rx_SBUS_SetInterruptMode() function.
     *  @{
     */
        #define Rx_SBUS_INTR_NONE      (uint16)(0x0000u)
        #define Rx_SBUS_INTR_RISING    (uint16)(0x0001u)
        #define Rx_SBUS_INTR_FALLING   (uint16)(0x0002u)
        #define Rx_SBUS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Rx_SBUS_INTR_MASK      (0x01u) 
#endif /* (Rx_SBUS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rx_SBUS_PS                     (* (reg8 *) Rx_SBUS__PS)
/* Data Register */
#define Rx_SBUS_DR                     (* (reg8 *) Rx_SBUS__DR)
/* Port Number */
#define Rx_SBUS_PRT_NUM                (* (reg8 *) Rx_SBUS__PRT) 
/* Connect to Analog Globals */                                                  
#define Rx_SBUS_AG                     (* (reg8 *) Rx_SBUS__AG)                       
/* Analog MUX bux enable */
#define Rx_SBUS_AMUX                   (* (reg8 *) Rx_SBUS__AMUX) 
/* Bidirectional Enable */                                                        
#define Rx_SBUS_BIE                    (* (reg8 *) Rx_SBUS__BIE)
/* Bit-mask for Aliased Register Access */
#define Rx_SBUS_BIT_MASK               (* (reg8 *) Rx_SBUS__BIT_MASK)
/* Bypass Enable */
#define Rx_SBUS_BYP                    (* (reg8 *) Rx_SBUS__BYP)
/* Port wide control signals */                                                   
#define Rx_SBUS_CTL                    (* (reg8 *) Rx_SBUS__CTL)
/* Drive Modes */
#define Rx_SBUS_DM0                    (* (reg8 *) Rx_SBUS__DM0) 
#define Rx_SBUS_DM1                    (* (reg8 *) Rx_SBUS__DM1)
#define Rx_SBUS_DM2                    (* (reg8 *) Rx_SBUS__DM2) 
/* Input Buffer Disable Override */
#define Rx_SBUS_INP_DIS                (* (reg8 *) Rx_SBUS__INP_DIS)
/* LCD Common or Segment Drive */
#define Rx_SBUS_LCD_COM_SEG            (* (reg8 *) Rx_SBUS__LCD_COM_SEG)
/* Enable Segment LCD */
#define Rx_SBUS_LCD_EN                 (* (reg8 *) Rx_SBUS__LCD_EN)
/* Slew Rate Control */
#define Rx_SBUS_SLW                    (* (reg8 *) Rx_SBUS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Rx_SBUS_PRTDSI__CAPS_SEL       (* (reg8 *) Rx_SBUS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Rx_SBUS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Rx_SBUS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Rx_SBUS_PRTDSI__OE_SEL0        (* (reg8 *) Rx_SBUS__PRTDSI__OE_SEL0) 
#define Rx_SBUS_PRTDSI__OE_SEL1        (* (reg8 *) Rx_SBUS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Rx_SBUS_PRTDSI__OUT_SEL0       (* (reg8 *) Rx_SBUS__PRTDSI__OUT_SEL0) 
#define Rx_SBUS_PRTDSI__OUT_SEL1       (* (reg8 *) Rx_SBUS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Rx_SBUS_PRTDSI__SYNC_OUT       (* (reg8 *) Rx_SBUS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Rx_SBUS__SIO_CFG)
    #define Rx_SBUS_SIO_HYST_EN        (* (reg8 *) Rx_SBUS__SIO_HYST_EN)
    #define Rx_SBUS_SIO_REG_HIFREQ     (* (reg8 *) Rx_SBUS__SIO_REG_HIFREQ)
    #define Rx_SBUS_SIO_CFG            (* (reg8 *) Rx_SBUS__SIO_CFG)
    #define Rx_SBUS_SIO_DIFF           (* (reg8 *) Rx_SBUS__SIO_DIFF)
#endif /* (Rx_SBUS__SIO_CFG) */

/* Interrupt Registers */
#if defined(Rx_SBUS__INTSTAT)
    #define Rx_SBUS_INTSTAT            (* (reg8 *) Rx_SBUS__INTSTAT)
    #define Rx_SBUS_SNAP               (* (reg8 *) Rx_SBUS__SNAP)
    
	#define Rx_SBUS_0_INTTYPE_REG 		(* (reg8 *) Rx_SBUS__0__INTTYPE)
#endif /* (Rx_SBUS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Rx_SBUS_H */


/* [] END OF FILE */
