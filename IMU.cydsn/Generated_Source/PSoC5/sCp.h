/*******************************************************************************
* File Name: sCp.h  
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

#if !defined(CY_PINS_sCp_H) /* Pins sCp_H */
#define CY_PINS_sCp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sCp_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sCp__PORT == 15 && ((sCp__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sCp_Write(uint8 value);
void    sCp_SetDriveMode(uint8 mode);
uint8   sCp_ReadDataReg(void);
uint8   sCp_Read(void);
void    sCp_SetInterruptMode(uint16 position, uint16 mode);
uint8   sCp_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sCp_SetDriveMode() function.
     *  @{
     */
        #define sCp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sCp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sCp_DM_RES_UP          PIN_DM_RES_UP
        #define sCp_DM_RES_DWN         PIN_DM_RES_DWN
        #define sCp_DM_OD_LO           PIN_DM_OD_LO
        #define sCp_DM_OD_HI           PIN_DM_OD_HI
        #define sCp_DM_STRONG          PIN_DM_STRONG
        #define sCp_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sCp_MASK               sCp__MASK
#define sCp_SHIFT              sCp__SHIFT
#define sCp_WIDTH              1u

/* Interrupt constants */
#if defined(sCp__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sCp_SetInterruptMode() function.
     *  @{
     */
        #define sCp_INTR_NONE      (uint16)(0x0000u)
        #define sCp_INTR_RISING    (uint16)(0x0001u)
        #define sCp_INTR_FALLING   (uint16)(0x0002u)
        #define sCp_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sCp_INTR_MASK      (0x01u) 
#endif /* (sCp__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sCp_PS                     (* (reg8 *) sCp__PS)
/* Data Register */
#define sCp_DR                     (* (reg8 *) sCp__DR)
/* Port Number */
#define sCp_PRT_NUM                (* (reg8 *) sCp__PRT) 
/* Connect to Analog Globals */                                                  
#define sCp_AG                     (* (reg8 *) sCp__AG)                       
/* Analog MUX bux enable */
#define sCp_AMUX                   (* (reg8 *) sCp__AMUX) 
/* Bidirectional Enable */                                                        
#define sCp_BIE                    (* (reg8 *) sCp__BIE)
/* Bit-mask for Aliased Register Access */
#define sCp_BIT_MASK               (* (reg8 *) sCp__BIT_MASK)
/* Bypass Enable */
#define sCp_BYP                    (* (reg8 *) sCp__BYP)
/* Port wide control signals */                                                   
#define sCp_CTL                    (* (reg8 *) sCp__CTL)
/* Drive Modes */
#define sCp_DM0                    (* (reg8 *) sCp__DM0) 
#define sCp_DM1                    (* (reg8 *) sCp__DM1)
#define sCp_DM2                    (* (reg8 *) sCp__DM2) 
/* Input Buffer Disable Override */
#define sCp_INP_DIS                (* (reg8 *) sCp__INP_DIS)
/* LCD Common or Segment Drive */
#define sCp_LCD_COM_SEG            (* (reg8 *) sCp__LCD_COM_SEG)
/* Enable Segment LCD */
#define sCp_LCD_EN                 (* (reg8 *) sCp__LCD_EN)
/* Slew Rate Control */
#define sCp_SLW                    (* (reg8 *) sCp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sCp_PRTDSI__CAPS_SEL       (* (reg8 *) sCp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sCp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sCp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sCp_PRTDSI__OE_SEL0        (* (reg8 *) sCp__PRTDSI__OE_SEL0) 
#define sCp_PRTDSI__OE_SEL1        (* (reg8 *) sCp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sCp_PRTDSI__OUT_SEL0       (* (reg8 *) sCp__PRTDSI__OUT_SEL0) 
#define sCp_PRTDSI__OUT_SEL1       (* (reg8 *) sCp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sCp_PRTDSI__SYNC_OUT       (* (reg8 *) sCp__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sCp__SIO_CFG)
    #define sCp_SIO_HYST_EN        (* (reg8 *) sCp__SIO_HYST_EN)
    #define sCp_SIO_REG_HIFREQ     (* (reg8 *) sCp__SIO_REG_HIFREQ)
    #define sCp_SIO_CFG            (* (reg8 *) sCp__SIO_CFG)
    #define sCp_SIO_DIFF           (* (reg8 *) sCp__SIO_DIFF)
#endif /* (sCp__SIO_CFG) */

/* Interrupt Registers */
#if defined(sCp__INTSTAT)
    #define sCp_INTSTAT            (* (reg8 *) sCp__INTSTAT)
    #define sCp_SNAP               (* (reg8 *) sCp__SNAP)
    
	#define sCp_0_INTTYPE_REG 		(* (reg8 *) sCp__0__INTTYPE)
#endif /* (sCp__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sCp_H */


/* [] END OF FILE */
