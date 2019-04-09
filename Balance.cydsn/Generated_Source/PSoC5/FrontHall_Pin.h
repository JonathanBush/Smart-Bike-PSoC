/*******************************************************************************
* File Name: FrontHall_Pin.h  
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

#if !defined(CY_PINS_FrontHall_Pin_H) /* Pins FrontHall_Pin_H */
#define CY_PINS_FrontHall_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FrontHall_Pin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FrontHall_Pin__PORT == 15 && ((FrontHall_Pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FrontHall_Pin_Write(uint8 value);
void    FrontHall_Pin_SetDriveMode(uint8 mode);
uint8   FrontHall_Pin_ReadDataReg(void);
uint8   FrontHall_Pin_Read(void);
void    FrontHall_Pin_SetInterruptMode(uint16 position, uint16 mode);
uint8   FrontHall_Pin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FrontHall_Pin_SetDriveMode() function.
     *  @{
     */
        #define FrontHall_Pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FrontHall_Pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FrontHall_Pin_DM_RES_UP          PIN_DM_RES_UP
        #define FrontHall_Pin_DM_RES_DWN         PIN_DM_RES_DWN
        #define FrontHall_Pin_DM_OD_LO           PIN_DM_OD_LO
        #define FrontHall_Pin_DM_OD_HI           PIN_DM_OD_HI
        #define FrontHall_Pin_DM_STRONG          PIN_DM_STRONG
        #define FrontHall_Pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FrontHall_Pin_MASK               FrontHall_Pin__MASK
#define FrontHall_Pin_SHIFT              FrontHall_Pin__SHIFT
#define FrontHall_Pin_WIDTH              1u

/* Interrupt constants */
#if defined(FrontHall_Pin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FrontHall_Pin_SetInterruptMode() function.
     *  @{
     */
        #define FrontHall_Pin_INTR_NONE      (uint16)(0x0000u)
        #define FrontHall_Pin_INTR_RISING    (uint16)(0x0001u)
        #define FrontHall_Pin_INTR_FALLING   (uint16)(0x0002u)
        #define FrontHall_Pin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FrontHall_Pin_INTR_MASK      (0x01u) 
#endif /* (FrontHall_Pin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FrontHall_Pin_PS                     (* (reg8 *) FrontHall_Pin__PS)
/* Data Register */
#define FrontHall_Pin_DR                     (* (reg8 *) FrontHall_Pin__DR)
/* Port Number */
#define FrontHall_Pin_PRT_NUM                (* (reg8 *) FrontHall_Pin__PRT) 
/* Connect to Analog Globals */                                                  
#define FrontHall_Pin_AG                     (* (reg8 *) FrontHall_Pin__AG)                       
/* Analog MUX bux enable */
#define FrontHall_Pin_AMUX                   (* (reg8 *) FrontHall_Pin__AMUX) 
/* Bidirectional Enable */                                                        
#define FrontHall_Pin_BIE                    (* (reg8 *) FrontHall_Pin__BIE)
/* Bit-mask for Aliased Register Access */
#define FrontHall_Pin_BIT_MASK               (* (reg8 *) FrontHall_Pin__BIT_MASK)
/* Bypass Enable */
#define FrontHall_Pin_BYP                    (* (reg8 *) FrontHall_Pin__BYP)
/* Port wide control signals */                                                   
#define FrontHall_Pin_CTL                    (* (reg8 *) FrontHall_Pin__CTL)
/* Drive Modes */
#define FrontHall_Pin_DM0                    (* (reg8 *) FrontHall_Pin__DM0) 
#define FrontHall_Pin_DM1                    (* (reg8 *) FrontHall_Pin__DM1)
#define FrontHall_Pin_DM2                    (* (reg8 *) FrontHall_Pin__DM2) 
/* Input Buffer Disable Override */
#define FrontHall_Pin_INP_DIS                (* (reg8 *) FrontHall_Pin__INP_DIS)
/* LCD Common or Segment Drive */
#define FrontHall_Pin_LCD_COM_SEG            (* (reg8 *) FrontHall_Pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define FrontHall_Pin_LCD_EN                 (* (reg8 *) FrontHall_Pin__LCD_EN)
/* Slew Rate Control */
#define FrontHall_Pin_SLW                    (* (reg8 *) FrontHall_Pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FrontHall_Pin_PRTDSI__CAPS_SEL       (* (reg8 *) FrontHall_Pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FrontHall_Pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FrontHall_Pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FrontHall_Pin_PRTDSI__OE_SEL0        (* (reg8 *) FrontHall_Pin__PRTDSI__OE_SEL0) 
#define FrontHall_Pin_PRTDSI__OE_SEL1        (* (reg8 *) FrontHall_Pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FrontHall_Pin_PRTDSI__OUT_SEL0       (* (reg8 *) FrontHall_Pin__PRTDSI__OUT_SEL0) 
#define FrontHall_Pin_PRTDSI__OUT_SEL1       (* (reg8 *) FrontHall_Pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FrontHall_Pin_PRTDSI__SYNC_OUT       (* (reg8 *) FrontHall_Pin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FrontHall_Pin__SIO_CFG)
    #define FrontHall_Pin_SIO_HYST_EN        (* (reg8 *) FrontHall_Pin__SIO_HYST_EN)
    #define FrontHall_Pin_SIO_REG_HIFREQ     (* (reg8 *) FrontHall_Pin__SIO_REG_HIFREQ)
    #define FrontHall_Pin_SIO_CFG            (* (reg8 *) FrontHall_Pin__SIO_CFG)
    #define FrontHall_Pin_SIO_DIFF           (* (reg8 *) FrontHall_Pin__SIO_DIFF)
#endif /* (FrontHall_Pin__SIO_CFG) */

/* Interrupt Registers */
#if defined(FrontHall_Pin__INTSTAT)
    #define FrontHall_Pin_INTSTAT            (* (reg8 *) FrontHall_Pin__INTSTAT)
    #define FrontHall_Pin_SNAP               (* (reg8 *) FrontHall_Pin__SNAP)
    
	#define FrontHall_Pin_0_INTTYPE_REG 		(* (reg8 *) FrontHall_Pin__0__INTTYPE)
#endif /* (FrontHall_Pin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FrontHall_Pin_H */


/* [] END OF FILE */
