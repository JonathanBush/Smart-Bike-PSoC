/*******************************************************************************
* File Name: sAp.h  
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

#if !defined(CY_PINS_sAp_H) /* Pins sAp_H */
#define CY_PINS_sAp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sAp_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sAp__PORT == 15 && ((sAp__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sAp_Write(uint8 value);
void    sAp_SetDriveMode(uint8 mode);
uint8   sAp_ReadDataReg(void);
uint8   sAp_Read(void);
void    sAp_SetInterruptMode(uint16 position, uint16 mode);
uint8   sAp_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sAp_SetDriveMode() function.
     *  @{
     */
        #define sAp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sAp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sAp_DM_RES_UP          PIN_DM_RES_UP
        #define sAp_DM_RES_DWN         PIN_DM_RES_DWN
        #define sAp_DM_OD_LO           PIN_DM_OD_LO
        #define sAp_DM_OD_HI           PIN_DM_OD_HI
        #define sAp_DM_STRONG          PIN_DM_STRONG
        #define sAp_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sAp_MASK               sAp__MASK
#define sAp_SHIFT              sAp__SHIFT
#define sAp_WIDTH              1u

/* Interrupt constants */
#if defined(sAp__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sAp_SetInterruptMode() function.
     *  @{
     */
        #define sAp_INTR_NONE      (uint16)(0x0000u)
        #define sAp_INTR_RISING    (uint16)(0x0001u)
        #define sAp_INTR_FALLING   (uint16)(0x0002u)
        #define sAp_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sAp_INTR_MASK      (0x01u) 
#endif /* (sAp__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sAp_PS                     (* (reg8 *) sAp__PS)
/* Data Register */
#define sAp_DR                     (* (reg8 *) sAp__DR)
/* Port Number */
#define sAp_PRT_NUM                (* (reg8 *) sAp__PRT) 
/* Connect to Analog Globals */                                                  
#define sAp_AG                     (* (reg8 *) sAp__AG)                       
/* Analog MUX bux enable */
#define sAp_AMUX                   (* (reg8 *) sAp__AMUX) 
/* Bidirectional Enable */                                                        
#define sAp_BIE                    (* (reg8 *) sAp__BIE)
/* Bit-mask for Aliased Register Access */
#define sAp_BIT_MASK               (* (reg8 *) sAp__BIT_MASK)
/* Bypass Enable */
#define sAp_BYP                    (* (reg8 *) sAp__BYP)
/* Port wide control signals */                                                   
#define sAp_CTL                    (* (reg8 *) sAp__CTL)
/* Drive Modes */
#define sAp_DM0                    (* (reg8 *) sAp__DM0) 
#define sAp_DM1                    (* (reg8 *) sAp__DM1)
#define sAp_DM2                    (* (reg8 *) sAp__DM2) 
/* Input Buffer Disable Override */
#define sAp_INP_DIS                (* (reg8 *) sAp__INP_DIS)
/* LCD Common or Segment Drive */
#define sAp_LCD_COM_SEG            (* (reg8 *) sAp__LCD_COM_SEG)
/* Enable Segment LCD */
#define sAp_LCD_EN                 (* (reg8 *) sAp__LCD_EN)
/* Slew Rate Control */
#define sAp_SLW                    (* (reg8 *) sAp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sAp_PRTDSI__CAPS_SEL       (* (reg8 *) sAp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sAp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sAp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sAp_PRTDSI__OE_SEL0        (* (reg8 *) sAp__PRTDSI__OE_SEL0) 
#define sAp_PRTDSI__OE_SEL1        (* (reg8 *) sAp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sAp_PRTDSI__OUT_SEL0       (* (reg8 *) sAp__PRTDSI__OUT_SEL0) 
#define sAp_PRTDSI__OUT_SEL1       (* (reg8 *) sAp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sAp_PRTDSI__SYNC_OUT       (* (reg8 *) sAp__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sAp__SIO_CFG)
    #define sAp_SIO_HYST_EN        (* (reg8 *) sAp__SIO_HYST_EN)
    #define sAp_SIO_REG_HIFREQ     (* (reg8 *) sAp__SIO_REG_HIFREQ)
    #define sAp_SIO_CFG            (* (reg8 *) sAp__SIO_CFG)
    #define sAp_SIO_DIFF           (* (reg8 *) sAp__SIO_DIFF)
#endif /* (sAp__SIO_CFG) */

/* Interrupt Registers */
#if defined(sAp__INTSTAT)
    #define sAp_INTSTAT            (* (reg8 *) sAp__INTSTAT)
    #define sAp_SNAP               (* (reg8 *) sAp__SNAP)
    
	#define sAp_0_INTTYPE_REG 		(* (reg8 *) sAp__0__INTTYPE)
#endif /* (sAp__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sAp_H */


/* [] END OF FILE */
