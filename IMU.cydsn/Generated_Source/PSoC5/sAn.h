/*******************************************************************************
* File Name: sAn.h  
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

#if !defined(CY_PINS_sAn_H) /* Pins sAn_H */
#define CY_PINS_sAn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sAn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sAn__PORT == 15 && ((sAn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sAn_Write(uint8 value);
void    sAn_SetDriveMode(uint8 mode);
uint8   sAn_ReadDataReg(void);
uint8   sAn_Read(void);
void    sAn_SetInterruptMode(uint16 position, uint16 mode);
uint8   sAn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sAn_SetDriveMode() function.
     *  @{
     */
        #define sAn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sAn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sAn_DM_RES_UP          PIN_DM_RES_UP
        #define sAn_DM_RES_DWN         PIN_DM_RES_DWN
        #define sAn_DM_OD_LO           PIN_DM_OD_LO
        #define sAn_DM_OD_HI           PIN_DM_OD_HI
        #define sAn_DM_STRONG          PIN_DM_STRONG
        #define sAn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sAn_MASK               sAn__MASK
#define sAn_SHIFT              sAn__SHIFT
#define sAn_WIDTH              1u

/* Interrupt constants */
#if defined(sAn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sAn_SetInterruptMode() function.
     *  @{
     */
        #define sAn_INTR_NONE      (uint16)(0x0000u)
        #define sAn_INTR_RISING    (uint16)(0x0001u)
        #define sAn_INTR_FALLING   (uint16)(0x0002u)
        #define sAn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sAn_INTR_MASK      (0x01u) 
#endif /* (sAn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sAn_PS                     (* (reg8 *) sAn__PS)
/* Data Register */
#define sAn_DR                     (* (reg8 *) sAn__DR)
/* Port Number */
#define sAn_PRT_NUM                (* (reg8 *) sAn__PRT) 
/* Connect to Analog Globals */                                                  
#define sAn_AG                     (* (reg8 *) sAn__AG)                       
/* Analog MUX bux enable */
#define sAn_AMUX                   (* (reg8 *) sAn__AMUX) 
/* Bidirectional Enable */                                                        
#define sAn_BIE                    (* (reg8 *) sAn__BIE)
/* Bit-mask for Aliased Register Access */
#define sAn_BIT_MASK               (* (reg8 *) sAn__BIT_MASK)
/* Bypass Enable */
#define sAn_BYP                    (* (reg8 *) sAn__BYP)
/* Port wide control signals */                                                   
#define sAn_CTL                    (* (reg8 *) sAn__CTL)
/* Drive Modes */
#define sAn_DM0                    (* (reg8 *) sAn__DM0) 
#define sAn_DM1                    (* (reg8 *) sAn__DM1)
#define sAn_DM2                    (* (reg8 *) sAn__DM2) 
/* Input Buffer Disable Override */
#define sAn_INP_DIS                (* (reg8 *) sAn__INP_DIS)
/* LCD Common or Segment Drive */
#define sAn_LCD_COM_SEG            (* (reg8 *) sAn__LCD_COM_SEG)
/* Enable Segment LCD */
#define sAn_LCD_EN                 (* (reg8 *) sAn__LCD_EN)
/* Slew Rate Control */
#define sAn_SLW                    (* (reg8 *) sAn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sAn_PRTDSI__CAPS_SEL       (* (reg8 *) sAn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sAn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sAn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sAn_PRTDSI__OE_SEL0        (* (reg8 *) sAn__PRTDSI__OE_SEL0) 
#define sAn_PRTDSI__OE_SEL1        (* (reg8 *) sAn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sAn_PRTDSI__OUT_SEL0       (* (reg8 *) sAn__PRTDSI__OUT_SEL0) 
#define sAn_PRTDSI__OUT_SEL1       (* (reg8 *) sAn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sAn_PRTDSI__SYNC_OUT       (* (reg8 *) sAn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sAn__SIO_CFG)
    #define sAn_SIO_HYST_EN        (* (reg8 *) sAn__SIO_HYST_EN)
    #define sAn_SIO_REG_HIFREQ     (* (reg8 *) sAn__SIO_REG_HIFREQ)
    #define sAn_SIO_CFG            (* (reg8 *) sAn__SIO_CFG)
    #define sAn_SIO_DIFF           (* (reg8 *) sAn__SIO_DIFF)
#endif /* (sAn__SIO_CFG) */

/* Interrupt Registers */
#if defined(sAn__INTSTAT)
    #define sAn_INTSTAT            (* (reg8 *) sAn__INTSTAT)
    #define sAn_SNAP               (* (reg8 *) sAn__SNAP)
    
	#define sAn_0_INTTYPE_REG 		(* (reg8 *) sAn__0__INTTYPE)
#endif /* (sAn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sAn_H */


/* [] END OF FILE */
