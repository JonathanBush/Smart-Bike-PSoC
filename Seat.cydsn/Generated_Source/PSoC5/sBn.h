/*******************************************************************************
* File Name: sBn.h  
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

#if !defined(CY_PINS_sBn_H) /* Pins sBn_H */
#define CY_PINS_sBn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sBn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sBn__PORT == 15 && ((sBn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sBn_Write(uint8 value);
void    sBn_SetDriveMode(uint8 mode);
uint8   sBn_ReadDataReg(void);
uint8   sBn_Read(void);
void    sBn_SetInterruptMode(uint16 position, uint16 mode);
uint8   sBn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sBn_SetDriveMode() function.
     *  @{
     */
        #define sBn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sBn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sBn_DM_RES_UP          PIN_DM_RES_UP
        #define sBn_DM_RES_DWN         PIN_DM_RES_DWN
        #define sBn_DM_OD_LO           PIN_DM_OD_LO
        #define sBn_DM_OD_HI           PIN_DM_OD_HI
        #define sBn_DM_STRONG          PIN_DM_STRONG
        #define sBn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sBn_MASK               sBn__MASK
#define sBn_SHIFT              sBn__SHIFT
#define sBn_WIDTH              1u

/* Interrupt constants */
#if defined(sBn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sBn_SetInterruptMode() function.
     *  @{
     */
        #define sBn_INTR_NONE      (uint16)(0x0000u)
        #define sBn_INTR_RISING    (uint16)(0x0001u)
        #define sBn_INTR_FALLING   (uint16)(0x0002u)
        #define sBn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sBn_INTR_MASK      (0x01u) 
#endif /* (sBn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sBn_PS                     (* (reg8 *) sBn__PS)
/* Data Register */
#define sBn_DR                     (* (reg8 *) sBn__DR)
/* Port Number */
#define sBn_PRT_NUM                (* (reg8 *) sBn__PRT) 
/* Connect to Analog Globals */                                                  
#define sBn_AG                     (* (reg8 *) sBn__AG)                       
/* Analog MUX bux enable */
#define sBn_AMUX                   (* (reg8 *) sBn__AMUX) 
/* Bidirectional Enable */                                                        
#define sBn_BIE                    (* (reg8 *) sBn__BIE)
/* Bit-mask for Aliased Register Access */
#define sBn_BIT_MASK               (* (reg8 *) sBn__BIT_MASK)
/* Bypass Enable */
#define sBn_BYP                    (* (reg8 *) sBn__BYP)
/* Port wide control signals */                                                   
#define sBn_CTL                    (* (reg8 *) sBn__CTL)
/* Drive Modes */
#define sBn_DM0                    (* (reg8 *) sBn__DM0) 
#define sBn_DM1                    (* (reg8 *) sBn__DM1)
#define sBn_DM2                    (* (reg8 *) sBn__DM2) 
/* Input Buffer Disable Override */
#define sBn_INP_DIS                (* (reg8 *) sBn__INP_DIS)
/* LCD Common or Segment Drive */
#define sBn_LCD_COM_SEG            (* (reg8 *) sBn__LCD_COM_SEG)
/* Enable Segment LCD */
#define sBn_LCD_EN                 (* (reg8 *) sBn__LCD_EN)
/* Slew Rate Control */
#define sBn_SLW                    (* (reg8 *) sBn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sBn_PRTDSI__CAPS_SEL       (* (reg8 *) sBn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sBn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sBn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sBn_PRTDSI__OE_SEL0        (* (reg8 *) sBn__PRTDSI__OE_SEL0) 
#define sBn_PRTDSI__OE_SEL1        (* (reg8 *) sBn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sBn_PRTDSI__OUT_SEL0       (* (reg8 *) sBn__PRTDSI__OUT_SEL0) 
#define sBn_PRTDSI__OUT_SEL1       (* (reg8 *) sBn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sBn_PRTDSI__SYNC_OUT       (* (reg8 *) sBn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sBn__SIO_CFG)
    #define sBn_SIO_HYST_EN        (* (reg8 *) sBn__SIO_HYST_EN)
    #define sBn_SIO_REG_HIFREQ     (* (reg8 *) sBn__SIO_REG_HIFREQ)
    #define sBn_SIO_CFG            (* (reg8 *) sBn__SIO_CFG)
    #define sBn_SIO_DIFF           (* (reg8 *) sBn__SIO_DIFF)
#endif /* (sBn__SIO_CFG) */

/* Interrupt Registers */
#if defined(sBn__INTSTAT)
    #define sBn_INTSTAT            (* (reg8 *) sBn__INTSTAT)
    #define sBn_SNAP               (* (reg8 *) sBn__SNAP)
    
	#define sBn_0_INTTYPE_REG 		(* (reg8 *) sBn__0__INTTYPE)
#endif /* (sBn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sBn_H */


/* [] END OF FILE */
