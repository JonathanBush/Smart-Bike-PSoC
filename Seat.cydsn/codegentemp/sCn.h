/*******************************************************************************
* File Name: sCn.h  
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

#if !defined(CY_PINS_sCn_H) /* Pins sCn_H */
#define CY_PINS_sCn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sCn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sCn__PORT == 15 && ((sCn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sCn_Write(uint8 value);
void    sCn_SetDriveMode(uint8 mode);
uint8   sCn_ReadDataReg(void);
uint8   sCn_Read(void);
void    sCn_SetInterruptMode(uint16 position, uint16 mode);
uint8   sCn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sCn_SetDriveMode() function.
     *  @{
     */
        #define sCn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sCn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sCn_DM_RES_UP          PIN_DM_RES_UP
        #define sCn_DM_RES_DWN         PIN_DM_RES_DWN
        #define sCn_DM_OD_LO           PIN_DM_OD_LO
        #define sCn_DM_OD_HI           PIN_DM_OD_HI
        #define sCn_DM_STRONG          PIN_DM_STRONG
        #define sCn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sCn_MASK               sCn__MASK
#define sCn_SHIFT              sCn__SHIFT
#define sCn_WIDTH              1u

/* Interrupt constants */
#if defined(sCn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sCn_SetInterruptMode() function.
     *  @{
     */
        #define sCn_INTR_NONE      (uint16)(0x0000u)
        #define sCn_INTR_RISING    (uint16)(0x0001u)
        #define sCn_INTR_FALLING   (uint16)(0x0002u)
        #define sCn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sCn_INTR_MASK      (0x01u) 
#endif /* (sCn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sCn_PS                     (* (reg8 *) sCn__PS)
/* Data Register */
#define sCn_DR                     (* (reg8 *) sCn__DR)
/* Port Number */
#define sCn_PRT_NUM                (* (reg8 *) sCn__PRT) 
/* Connect to Analog Globals */                                                  
#define sCn_AG                     (* (reg8 *) sCn__AG)                       
/* Analog MUX bux enable */
#define sCn_AMUX                   (* (reg8 *) sCn__AMUX) 
/* Bidirectional Enable */                                                        
#define sCn_BIE                    (* (reg8 *) sCn__BIE)
/* Bit-mask for Aliased Register Access */
#define sCn_BIT_MASK               (* (reg8 *) sCn__BIT_MASK)
/* Bypass Enable */
#define sCn_BYP                    (* (reg8 *) sCn__BYP)
/* Port wide control signals */                                                   
#define sCn_CTL                    (* (reg8 *) sCn__CTL)
/* Drive Modes */
#define sCn_DM0                    (* (reg8 *) sCn__DM0) 
#define sCn_DM1                    (* (reg8 *) sCn__DM1)
#define sCn_DM2                    (* (reg8 *) sCn__DM2) 
/* Input Buffer Disable Override */
#define sCn_INP_DIS                (* (reg8 *) sCn__INP_DIS)
/* LCD Common or Segment Drive */
#define sCn_LCD_COM_SEG            (* (reg8 *) sCn__LCD_COM_SEG)
/* Enable Segment LCD */
#define sCn_LCD_EN                 (* (reg8 *) sCn__LCD_EN)
/* Slew Rate Control */
#define sCn_SLW                    (* (reg8 *) sCn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sCn_PRTDSI__CAPS_SEL       (* (reg8 *) sCn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sCn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sCn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sCn_PRTDSI__OE_SEL0        (* (reg8 *) sCn__PRTDSI__OE_SEL0) 
#define sCn_PRTDSI__OE_SEL1        (* (reg8 *) sCn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sCn_PRTDSI__OUT_SEL0       (* (reg8 *) sCn__PRTDSI__OUT_SEL0) 
#define sCn_PRTDSI__OUT_SEL1       (* (reg8 *) sCn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sCn_PRTDSI__SYNC_OUT       (* (reg8 *) sCn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sCn__SIO_CFG)
    #define sCn_SIO_HYST_EN        (* (reg8 *) sCn__SIO_HYST_EN)
    #define sCn_SIO_REG_HIFREQ     (* (reg8 *) sCn__SIO_REG_HIFREQ)
    #define sCn_SIO_CFG            (* (reg8 *) sCn__SIO_CFG)
    #define sCn_SIO_DIFF           (* (reg8 *) sCn__SIO_DIFF)
#endif /* (sCn__SIO_CFG) */

/* Interrupt Registers */
#if defined(sCn__INTSTAT)
    #define sCn_INTSTAT            (* (reg8 *) sCn__INTSTAT)
    #define sCn_SNAP               (* (reg8 *) sCn__SNAP)
    
	#define sCn_0_INTTYPE_REG 		(* (reg8 *) sCn__0__INTTYPE)
#endif /* (sCn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sCn_H */


/* [] END OF FILE */
