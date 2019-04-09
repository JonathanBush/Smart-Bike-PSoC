/*******************************************************************************
* File Name: BNO_Interupt.h  
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

#if !defined(CY_PINS_BNO_Interupt_H) /* Pins BNO_Interupt_H */
#define CY_PINS_BNO_Interupt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BNO_Interupt_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BNO_Interupt__PORT == 15 && ((BNO_Interupt__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BNO_Interupt_Write(uint8 value);
void    BNO_Interupt_SetDriveMode(uint8 mode);
uint8   BNO_Interupt_ReadDataReg(void);
uint8   BNO_Interupt_Read(void);
void    BNO_Interupt_SetInterruptMode(uint16 position, uint16 mode);
uint8   BNO_Interupt_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BNO_Interupt_SetDriveMode() function.
     *  @{
     */
        #define BNO_Interupt_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BNO_Interupt_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BNO_Interupt_DM_RES_UP          PIN_DM_RES_UP
        #define BNO_Interupt_DM_RES_DWN         PIN_DM_RES_DWN
        #define BNO_Interupt_DM_OD_LO           PIN_DM_OD_LO
        #define BNO_Interupt_DM_OD_HI           PIN_DM_OD_HI
        #define BNO_Interupt_DM_STRONG          PIN_DM_STRONG
        #define BNO_Interupt_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BNO_Interupt_MASK               BNO_Interupt__MASK
#define BNO_Interupt_SHIFT              BNO_Interupt__SHIFT
#define BNO_Interupt_WIDTH              1u

/* Interrupt constants */
#if defined(BNO_Interupt__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BNO_Interupt_SetInterruptMode() function.
     *  @{
     */
        #define BNO_Interupt_INTR_NONE      (uint16)(0x0000u)
        #define BNO_Interupt_INTR_RISING    (uint16)(0x0001u)
        #define BNO_Interupt_INTR_FALLING   (uint16)(0x0002u)
        #define BNO_Interupt_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BNO_Interupt_INTR_MASK      (0x01u) 
#endif /* (BNO_Interupt__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BNO_Interupt_PS                     (* (reg8 *) BNO_Interupt__PS)
/* Data Register */
#define BNO_Interupt_DR                     (* (reg8 *) BNO_Interupt__DR)
/* Port Number */
#define BNO_Interupt_PRT_NUM                (* (reg8 *) BNO_Interupt__PRT) 
/* Connect to Analog Globals */                                                  
#define BNO_Interupt_AG                     (* (reg8 *) BNO_Interupt__AG)                       
/* Analog MUX bux enable */
#define BNO_Interupt_AMUX                   (* (reg8 *) BNO_Interupt__AMUX) 
/* Bidirectional Enable */                                                        
#define BNO_Interupt_BIE                    (* (reg8 *) BNO_Interupt__BIE)
/* Bit-mask for Aliased Register Access */
#define BNO_Interupt_BIT_MASK               (* (reg8 *) BNO_Interupt__BIT_MASK)
/* Bypass Enable */
#define BNO_Interupt_BYP                    (* (reg8 *) BNO_Interupt__BYP)
/* Port wide control signals */                                                   
#define BNO_Interupt_CTL                    (* (reg8 *) BNO_Interupt__CTL)
/* Drive Modes */
#define BNO_Interupt_DM0                    (* (reg8 *) BNO_Interupt__DM0) 
#define BNO_Interupt_DM1                    (* (reg8 *) BNO_Interupt__DM1)
#define BNO_Interupt_DM2                    (* (reg8 *) BNO_Interupt__DM2) 
/* Input Buffer Disable Override */
#define BNO_Interupt_INP_DIS                (* (reg8 *) BNO_Interupt__INP_DIS)
/* LCD Common or Segment Drive */
#define BNO_Interupt_LCD_COM_SEG            (* (reg8 *) BNO_Interupt__LCD_COM_SEG)
/* Enable Segment LCD */
#define BNO_Interupt_LCD_EN                 (* (reg8 *) BNO_Interupt__LCD_EN)
/* Slew Rate Control */
#define BNO_Interupt_SLW                    (* (reg8 *) BNO_Interupt__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BNO_Interupt_PRTDSI__CAPS_SEL       (* (reg8 *) BNO_Interupt__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BNO_Interupt_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BNO_Interupt__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BNO_Interupt_PRTDSI__OE_SEL0        (* (reg8 *) BNO_Interupt__PRTDSI__OE_SEL0) 
#define BNO_Interupt_PRTDSI__OE_SEL1        (* (reg8 *) BNO_Interupt__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BNO_Interupt_PRTDSI__OUT_SEL0       (* (reg8 *) BNO_Interupt__PRTDSI__OUT_SEL0) 
#define BNO_Interupt_PRTDSI__OUT_SEL1       (* (reg8 *) BNO_Interupt__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BNO_Interupt_PRTDSI__SYNC_OUT       (* (reg8 *) BNO_Interupt__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BNO_Interupt__SIO_CFG)
    #define BNO_Interupt_SIO_HYST_EN        (* (reg8 *) BNO_Interupt__SIO_HYST_EN)
    #define BNO_Interupt_SIO_REG_HIFREQ     (* (reg8 *) BNO_Interupt__SIO_REG_HIFREQ)
    #define BNO_Interupt_SIO_CFG            (* (reg8 *) BNO_Interupt__SIO_CFG)
    #define BNO_Interupt_SIO_DIFF           (* (reg8 *) BNO_Interupt__SIO_DIFF)
#endif /* (BNO_Interupt__SIO_CFG) */

/* Interrupt Registers */
#if defined(BNO_Interupt__INTSTAT)
    #define BNO_Interupt_INTSTAT            (* (reg8 *) BNO_Interupt__INTSTAT)
    #define BNO_Interupt_SNAP               (* (reg8 *) BNO_Interupt__SNAP)
    
	#define BNO_Interupt_0_INTTYPE_REG 		(* (reg8 *) BNO_Interupt__0__INTTYPE)
#endif /* (BNO_Interupt__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BNO_Interupt_H */


/* [] END OF FILE */
