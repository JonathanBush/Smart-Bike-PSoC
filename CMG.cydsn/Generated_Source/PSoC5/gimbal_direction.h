/*******************************************************************************
* File Name: gimbal_direction.h  
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

#if !defined(CY_PINS_gimbal_direction_H) /* Pins gimbal_direction_H */
#define CY_PINS_gimbal_direction_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "gimbal_direction_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 gimbal_direction__PORT == 15 && ((gimbal_direction__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    gimbal_direction_Write(uint8 value);
void    gimbal_direction_SetDriveMode(uint8 mode);
uint8   gimbal_direction_ReadDataReg(void);
uint8   gimbal_direction_Read(void);
void    gimbal_direction_SetInterruptMode(uint16 position, uint16 mode);
uint8   gimbal_direction_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the gimbal_direction_SetDriveMode() function.
     *  @{
     */
        #define gimbal_direction_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define gimbal_direction_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define gimbal_direction_DM_RES_UP          PIN_DM_RES_UP
        #define gimbal_direction_DM_RES_DWN         PIN_DM_RES_DWN
        #define gimbal_direction_DM_OD_LO           PIN_DM_OD_LO
        #define gimbal_direction_DM_OD_HI           PIN_DM_OD_HI
        #define gimbal_direction_DM_STRONG          PIN_DM_STRONG
        #define gimbal_direction_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define gimbal_direction_MASK               gimbal_direction__MASK
#define gimbal_direction_SHIFT              gimbal_direction__SHIFT
#define gimbal_direction_WIDTH              1u

/* Interrupt constants */
#if defined(gimbal_direction__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in gimbal_direction_SetInterruptMode() function.
     *  @{
     */
        #define gimbal_direction_INTR_NONE      (uint16)(0x0000u)
        #define gimbal_direction_INTR_RISING    (uint16)(0x0001u)
        #define gimbal_direction_INTR_FALLING   (uint16)(0x0002u)
        #define gimbal_direction_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define gimbal_direction_INTR_MASK      (0x01u) 
#endif /* (gimbal_direction__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define gimbal_direction_PS                     (* (reg8 *) gimbal_direction__PS)
/* Data Register */
#define gimbal_direction_DR                     (* (reg8 *) gimbal_direction__DR)
/* Port Number */
#define gimbal_direction_PRT_NUM                (* (reg8 *) gimbal_direction__PRT) 
/* Connect to Analog Globals */                                                  
#define gimbal_direction_AG                     (* (reg8 *) gimbal_direction__AG)                       
/* Analog MUX bux enable */
#define gimbal_direction_AMUX                   (* (reg8 *) gimbal_direction__AMUX) 
/* Bidirectional Enable */                                                        
#define gimbal_direction_BIE                    (* (reg8 *) gimbal_direction__BIE)
/* Bit-mask for Aliased Register Access */
#define gimbal_direction_BIT_MASK               (* (reg8 *) gimbal_direction__BIT_MASK)
/* Bypass Enable */
#define gimbal_direction_BYP                    (* (reg8 *) gimbal_direction__BYP)
/* Port wide control signals */                                                   
#define gimbal_direction_CTL                    (* (reg8 *) gimbal_direction__CTL)
/* Drive Modes */
#define gimbal_direction_DM0                    (* (reg8 *) gimbal_direction__DM0) 
#define gimbal_direction_DM1                    (* (reg8 *) gimbal_direction__DM1)
#define gimbal_direction_DM2                    (* (reg8 *) gimbal_direction__DM2) 
/* Input Buffer Disable Override */
#define gimbal_direction_INP_DIS                (* (reg8 *) gimbal_direction__INP_DIS)
/* LCD Common or Segment Drive */
#define gimbal_direction_LCD_COM_SEG            (* (reg8 *) gimbal_direction__LCD_COM_SEG)
/* Enable Segment LCD */
#define gimbal_direction_LCD_EN                 (* (reg8 *) gimbal_direction__LCD_EN)
/* Slew Rate Control */
#define gimbal_direction_SLW                    (* (reg8 *) gimbal_direction__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define gimbal_direction_PRTDSI__CAPS_SEL       (* (reg8 *) gimbal_direction__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define gimbal_direction_PRTDSI__DBL_SYNC_IN    (* (reg8 *) gimbal_direction__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define gimbal_direction_PRTDSI__OE_SEL0        (* (reg8 *) gimbal_direction__PRTDSI__OE_SEL0) 
#define gimbal_direction_PRTDSI__OE_SEL1        (* (reg8 *) gimbal_direction__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define gimbal_direction_PRTDSI__OUT_SEL0       (* (reg8 *) gimbal_direction__PRTDSI__OUT_SEL0) 
#define gimbal_direction_PRTDSI__OUT_SEL1       (* (reg8 *) gimbal_direction__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define gimbal_direction_PRTDSI__SYNC_OUT       (* (reg8 *) gimbal_direction__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(gimbal_direction__SIO_CFG)
    #define gimbal_direction_SIO_HYST_EN        (* (reg8 *) gimbal_direction__SIO_HYST_EN)
    #define gimbal_direction_SIO_REG_HIFREQ     (* (reg8 *) gimbal_direction__SIO_REG_HIFREQ)
    #define gimbal_direction_SIO_CFG            (* (reg8 *) gimbal_direction__SIO_CFG)
    #define gimbal_direction_SIO_DIFF           (* (reg8 *) gimbal_direction__SIO_DIFF)
#endif /* (gimbal_direction__SIO_CFG) */

/* Interrupt Registers */
#if defined(gimbal_direction__INTSTAT)
    #define gimbal_direction_INTSTAT            (* (reg8 *) gimbal_direction__INTSTAT)
    #define gimbal_direction_SNAP               (* (reg8 *) gimbal_direction__SNAP)
    
	#define gimbal_direction_0_INTTYPE_REG 		(* (reg8 *) gimbal_direction__0__INTTYPE)
#endif /* (gimbal_direction__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_gimbal_direction_H */


/* [] END OF FILE */
