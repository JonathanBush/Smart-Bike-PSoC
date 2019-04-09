/*******************************************************************************
* File Name: sBp.h  
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

#if !defined(CY_PINS_sBp_H) /* Pins sBp_H */
#define CY_PINS_sBp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sBp_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sBp__PORT == 15 && ((sBp__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sBp_Write(uint8 value);
void    sBp_SetDriveMode(uint8 mode);
uint8   sBp_ReadDataReg(void);
uint8   sBp_Read(void);
void    sBp_SetInterruptMode(uint16 position, uint16 mode);
uint8   sBp_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sBp_SetDriveMode() function.
     *  @{
     */
        #define sBp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sBp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sBp_DM_RES_UP          PIN_DM_RES_UP
        #define sBp_DM_RES_DWN         PIN_DM_RES_DWN
        #define sBp_DM_OD_LO           PIN_DM_OD_LO
        #define sBp_DM_OD_HI           PIN_DM_OD_HI
        #define sBp_DM_STRONG          PIN_DM_STRONG
        #define sBp_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sBp_MASK               sBp__MASK
#define sBp_SHIFT              sBp__SHIFT
#define sBp_WIDTH              1u

/* Interrupt constants */
#if defined(sBp__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sBp_SetInterruptMode() function.
     *  @{
     */
        #define sBp_INTR_NONE      (uint16)(0x0000u)
        #define sBp_INTR_RISING    (uint16)(0x0001u)
        #define sBp_INTR_FALLING   (uint16)(0x0002u)
        #define sBp_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sBp_INTR_MASK      (0x01u) 
#endif /* (sBp__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sBp_PS                     (* (reg8 *) sBp__PS)
/* Data Register */
#define sBp_DR                     (* (reg8 *) sBp__DR)
/* Port Number */
#define sBp_PRT_NUM                (* (reg8 *) sBp__PRT) 
/* Connect to Analog Globals */                                                  
#define sBp_AG                     (* (reg8 *) sBp__AG)                       
/* Analog MUX bux enable */
#define sBp_AMUX                   (* (reg8 *) sBp__AMUX) 
/* Bidirectional Enable */                                                        
#define sBp_BIE                    (* (reg8 *) sBp__BIE)
/* Bit-mask for Aliased Register Access */
#define sBp_BIT_MASK               (* (reg8 *) sBp__BIT_MASK)
/* Bypass Enable */
#define sBp_BYP                    (* (reg8 *) sBp__BYP)
/* Port wide control signals */                                                   
#define sBp_CTL                    (* (reg8 *) sBp__CTL)
/* Drive Modes */
#define sBp_DM0                    (* (reg8 *) sBp__DM0) 
#define sBp_DM1                    (* (reg8 *) sBp__DM1)
#define sBp_DM2                    (* (reg8 *) sBp__DM2) 
/* Input Buffer Disable Override */
#define sBp_INP_DIS                (* (reg8 *) sBp__INP_DIS)
/* LCD Common or Segment Drive */
#define sBp_LCD_COM_SEG            (* (reg8 *) sBp__LCD_COM_SEG)
/* Enable Segment LCD */
#define sBp_LCD_EN                 (* (reg8 *) sBp__LCD_EN)
/* Slew Rate Control */
#define sBp_SLW                    (* (reg8 *) sBp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sBp_PRTDSI__CAPS_SEL       (* (reg8 *) sBp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sBp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sBp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sBp_PRTDSI__OE_SEL0        (* (reg8 *) sBp__PRTDSI__OE_SEL0) 
#define sBp_PRTDSI__OE_SEL1        (* (reg8 *) sBp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sBp_PRTDSI__OUT_SEL0       (* (reg8 *) sBp__PRTDSI__OUT_SEL0) 
#define sBp_PRTDSI__OUT_SEL1       (* (reg8 *) sBp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sBp_PRTDSI__SYNC_OUT       (* (reg8 *) sBp__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sBp__SIO_CFG)
    #define sBp_SIO_HYST_EN        (* (reg8 *) sBp__SIO_HYST_EN)
    #define sBp_SIO_REG_HIFREQ     (* (reg8 *) sBp__SIO_REG_HIFREQ)
    #define sBp_SIO_CFG            (* (reg8 *) sBp__SIO_CFG)
    #define sBp_SIO_DIFF           (* (reg8 *) sBp__SIO_DIFF)
#endif /* (sBp__SIO_CFG) */

/* Interrupt Registers */
#if defined(sBp__INTSTAT)
    #define sBp_INTSTAT            (* (reg8 *) sBp__INTSTAT)
    #define sBp_SNAP               (* (reg8 *) sBp__SNAP)
    
	#define sBp_0_INTTYPE_REG 		(* (reg8 *) sBp__0__INTTYPE)
#endif /* (sBp__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sBp_H */


/* [] END OF FILE */
