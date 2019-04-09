/*******************************************************************************
* File Name: Steering_Direction.h  
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

#if !defined(CY_PINS_Steering_Direction_H) /* Pins Steering_Direction_H */
#define CY_PINS_Steering_Direction_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Steering_Direction_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Steering_Direction__PORT == 15 && ((Steering_Direction__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Steering_Direction_Write(uint8 value);
void    Steering_Direction_SetDriveMode(uint8 mode);
uint8   Steering_Direction_ReadDataReg(void);
uint8   Steering_Direction_Read(void);
void    Steering_Direction_SetInterruptMode(uint16 position, uint16 mode);
uint8   Steering_Direction_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Steering_Direction_SetDriveMode() function.
     *  @{
     */
        #define Steering_Direction_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Steering_Direction_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Steering_Direction_DM_RES_UP          PIN_DM_RES_UP
        #define Steering_Direction_DM_RES_DWN         PIN_DM_RES_DWN
        #define Steering_Direction_DM_OD_LO           PIN_DM_OD_LO
        #define Steering_Direction_DM_OD_HI           PIN_DM_OD_HI
        #define Steering_Direction_DM_STRONG          PIN_DM_STRONG
        #define Steering_Direction_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Steering_Direction_MASK               Steering_Direction__MASK
#define Steering_Direction_SHIFT              Steering_Direction__SHIFT
#define Steering_Direction_WIDTH              1u

/* Interrupt constants */
#if defined(Steering_Direction__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Steering_Direction_SetInterruptMode() function.
     *  @{
     */
        #define Steering_Direction_INTR_NONE      (uint16)(0x0000u)
        #define Steering_Direction_INTR_RISING    (uint16)(0x0001u)
        #define Steering_Direction_INTR_FALLING   (uint16)(0x0002u)
        #define Steering_Direction_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Steering_Direction_INTR_MASK      (0x01u) 
#endif /* (Steering_Direction__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Steering_Direction_PS                     (* (reg8 *) Steering_Direction__PS)
/* Data Register */
#define Steering_Direction_DR                     (* (reg8 *) Steering_Direction__DR)
/* Port Number */
#define Steering_Direction_PRT_NUM                (* (reg8 *) Steering_Direction__PRT) 
/* Connect to Analog Globals */                                                  
#define Steering_Direction_AG                     (* (reg8 *) Steering_Direction__AG)                       
/* Analog MUX bux enable */
#define Steering_Direction_AMUX                   (* (reg8 *) Steering_Direction__AMUX) 
/* Bidirectional Enable */                                                        
#define Steering_Direction_BIE                    (* (reg8 *) Steering_Direction__BIE)
/* Bit-mask for Aliased Register Access */
#define Steering_Direction_BIT_MASK               (* (reg8 *) Steering_Direction__BIT_MASK)
/* Bypass Enable */
#define Steering_Direction_BYP                    (* (reg8 *) Steering_Direction__BYP)
/* Port wide control signals */                                                   
#define Steering_Direction_CTL                    (* (reg8 *) Steering_Direction__CTL)
/* Drive Modes */
#define Steering_Direction_DM0                    (* (reg8 *) Steering_Direction__DM0) 
#define Steering_Direction_DM1                    (* (reg8 *) Steering_Direction__DM1)
#define Steering_Direction_DM2                    (* (reg8 *) Steering_Direction__DM2) 
/* Input Buffer Disable Override */
#define Steering_Direction_INP_DIS                (* (reg8 *) Steering_Direction__INP_DIS)
/* LCD Common or Segment Drive */
#define Steering_Direction_LCD_COM_SEG            (* (reg8 *) Steering_Direction__LCD_COM_SEG)
/* Enable Segment LCD */
#define Steering_Direction_LCD_EN                 (* (reg8 *) Steering_Direction__LCD_EN)
/* Slew Rate Control */
#define Steering_Direction_SLW                    (* (reg8 *) Steering_Direction__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Steering_Direction_PRTDSI__CAPS_SEL       (* (reg8 *) Steering_Direction__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Steering_Direction_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Steering_Direction__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Steering_Direction_PRTDSI__OE_SEL0        (* (reg8 *) Steering_Direction__PRTDSI__OE_SEL0) 
#define Steering_Direction_PRTDSI__OE_SEL1        (* (reg8 *) Steering_Direction__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Steering_Direction_PRTDSI__OUT_SEL0       (* (reg8 *) Steering_Direction__PRTDSI__OUT_SEL0) 
#define Steering_Direction_PRTDSI__OUT_SEL1       (* (reg8 *) Steering_Direction__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Steering_Direction_PRTDSI__SYNC_OUT       (* (reg8 *) Steering_Direction__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Steering_Direction__SIO_CFG)
    #define Steering_Direction_SIO_HYST_EN        (* (reg8 *) Steering_Direction__SIO_HYST_EN)
    #define Steering_Direction_SIO_REG_HIFREQ     (* (reg8 *) Steering_Direction__SIO_REG_HIFREQ)
    #define Steering_Direction_SIO_CFG            (* (reg8 *) Steering_Direction__SIO_CFG)
    #define Steering_Direction_SIO_DIFF           (* (reg8 *) Steering_Direction__SIO_DIFF)
#endif /* (Steering_Direction__SIO_CFG) */

/* Interrupt Registers */
#if defined(Steering_Direction__INTSTAT)
    #define Steering_Direction_INTSTAT            (* (reg8 *) Steering_Direction__INTSTAT)
    #define Steering_Direction_SNAP               (* (reg8 *) Steering_Direction__SNAP)
    
	#define Steering_Direction_0_INTTYPE_REG 		(* (reg8 *) Steering_Direction__0__INTTYPE)
#endif /* (Steering_Direction__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Steering_Direction_H */


/* [] END OF FILE */
