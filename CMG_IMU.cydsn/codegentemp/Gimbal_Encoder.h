/*******************************************************************************
* File Name: Gimbal_Encoder.h  
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_QUADRATURE_DECODER_Gimbal_Encoder_H)
#define CY_QUADRATURE_DECODER_Gimbal_Encoder_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define Gimbal_Encoder_COUNTER_SIZE               (16u)
#define Gimbal_Encoder_COUNTER_SIZE_8_BIT         (8u)
#define Gimbal_Encoder_COUNTER_SIZE_16_BIT        (16u)
#define Gimbal_Encoder_COUNTER_SIZE_32_BIT        (32u)

#if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT)
    #include "Gimbal_Encoder_Cnt8.h"
#else 
    /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT) || 
    *  (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT) 
    */
    #include "Gimbal_Encoder_Cnt16.h"
#endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT */

extern uint8 Gimbal_Encoder_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Gimbal_Encoder_COUNTER_RESOLUTION         (4u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} Gimbal_Encoder_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  Gimbal_Encoder_Init(void) ;
void  Gimbal_Encoder_Start(void) ;
void  Gimbal_Encoder_Stop(void) ;
void  Gimbal_Encoder_Enable(void) ;
uint8 Gimbal_Encoder_GetEvents(void) ;
void  Gimbal_Encoder_SetInterruptMask(uint8 mask) ;
uint8 Gimbal_Encoder_GetInterruptMask(void) ;
int16 Gimbal_Encoder_GetCounter(void) ;
void  Gimbal_Encoder_SetCounter(int16 value)
;
void  Gimbal_Encoder_Sleep(void) ;
void  Gimbal_Encoder_Wakeup(void) ;
void  Gimbal_Encoder_SaveConfig(void) ;
void  Gimbal_Encoder_RestoreConfig(void) ;

#if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(Gimbal_Encoder_ISR);
#endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
    #define Gimbal_Encoder_ISR_NUMBER             ((uint8) Gimbal_Encoder_isr__INTC_NUMBER)
    #define Gimbal_Encoder_ISR_PRIORITY           ((uint8) Gimbal_Encoder_isr__INTC_PRIOR_NUM)
#endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Gimbal_Encoder_GLITCH_FILTERING           (1u)
#define Gimbal_Encoder_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT)
    #define Gimbal_Encoder_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT) ||
    *  (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
    */
    #define Gimbal_Encoder_COUNTER_INIT_VALUE    (0x8000u)
    #define Gimbal_Encoder_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define Gimbal_Encoder_STATUS_REG                 (* (reg8 *) Gimbal_Encoder_bQuadDec_Stsreg__STATUS_REG)
#define Gimbal_Encoder_STATUS_PTR                 (  (reg8 *) Gimbal_Encoder_bQuadDec_Stsreg__STATUS_REG)
#define Gimbal_Encoder_STATUS_MASK                (* (reg8 *) Gimbal_Encoder_bQuadDec_Stsreg__MASK_REG)
#define Gimbal_Encoder_STATUS_MASK_PTR            (  (reg8 *) Gimbal_Encoder_bQuadDec_Stsreg__MASK_REG)
#define Gimbal_Encoder_SR_AUX_CONTROL             (* (reg8 *) Gimbal_Encoder_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define Gimbal_Encoder_SR_AUX_CONTROL_PTR         (  (reg8 *) Gimbal_Encoder_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define Gimbal_Encoder_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define Gimbal_Encoder_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define Gimbal_Encoder_COUNTER_RESET_SHIFT        (0x02u)
#define Gimbal_Encoder_INVALID_IN_SHIFT           (0x03u)
#define Gimbal_Encoder_COUNTER_OVERFLOW           ((uint8) (0x01u << Gimbal_Encoder_COUNTER_OVERFLOW_SHIFT))
#define Gimbal_Encoder_COUNTER_UNDERFLOW          ((uint8) (0x01u << Gimbal_Encoder_COUNTER_UNDERFLOW_SHIFT))
#define Gimbal_Encoder_COUNTER_RESET              ((uint8) (0x01u << Gimbal_Encoder_COUNTER_RESET_SHIFT))
#define Gimbal_Encoder_INVALID_IN                 ((uint8) (0x01u << Gimbal_Encoder_INVALID_IN_SHIFT))

#define Gimbal_Encoder_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define Gimbal_Encoder_INTERRUPTS_ENABLE          ((uint8)(0x01u << Gimbal_Encoder_INTERRUPTS_ENABLE_SHIFT))
#define Gimbal_Encoder_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define Gimbal_Encoder_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_Gimbal_Encoder_H */


/* [] END OF FILE */
