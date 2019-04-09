/*******************************************************************************
* File Name: Handle_Encoder.h  
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

#if !defined(CY_QUADRATURE_DECODER_Handle_Encoder_H)
#define CY_QUADRATURE_DECODER_Handle_Encoder_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define Handle_Encoder_COUNTER_SIZE               (16u)
#define Handle_Encoder_COUNTER_SIZE_8_BIT         (8u)
#define Handle_Encoder_COUNTER_SIZE_16_BIT        (16u)
#define Handle_Encoder_COUNTER_SIZE_32_BIT        (32u)

#if (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT)
    #include "Handle_Encoder_Cnt8.h"
#else 
    /* (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_16_BIT) || 
    *  (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_32_BIT) 
    */
    #include "Handle_Encoder_Cnt16.h"
#endif /* Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT */

extern uint8 Handle_Encoder_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Handle_Encoder_COUNTER_RESOLUTION         (4u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} Handle_Encoder_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  Handle_Encoder_Init(void) ;
void  Handle_Encoder_Start(void) ;
void  Handle_Encoder_Stop(void) ;
void  Handle_Encoder_Enable(void) ;
uint8 Handle_Encoder_GetEvents(void) ;
void  Handle_Encoder_SetInterruptMask(uint8 mask) ;
uint8 Handle_Encoder_GetInterruptMask(void) ;
int16 Handle_Encoder_GetCounter(void) ;
void  Handle_Encoder_SetCounter(int16 value)
;
void  Handle_Encoder_Sleep(void) ;
void  Handle_Encoder_Wakeup(void) ;
void  Handle_Encoder_SaveConfig(void) ;
void  Handle_Encoder_RestoreConfig(void) ;

#if (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(Handle_Encoder_ISR);
#endif /* Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_32_BIT)
    #define Handle_Encoder_ISR_NUMBER             ((uint8) Handle_Encoder_isr__INTC_NUMBER)
    #define Handle_Encoder_ISR_PRIORITY           ((uint8) Handle_Encoder_isr__INTC_PRIOR_NUM)
#endif /* Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Handle_Encoder_GLITCH_FILTERING           (1u)
#define Handle_Encoder_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT)
    #define Handle_Encoder_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_16_BIT) ||
    *  (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_32_BIT)
    */
    #define Handle_Encoder_COUNTER_INIT_VALUE    (0x8000u)
    #define Handle_Encoder_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define Handle_Encoder_STATUS_REG                 (* (reg8 *) Handle_Encoder_bQuadDec_Stsreg__STATUS_REG)
#define Handle_Encoder_STATUS_PTR                 (  (reg8 *) Handle_Encoder_bQuadDec_Stsreg__STATUS_REG)
#define Handle_Encoder_STATUS_MASK                (* (reg8 *) Handle_Encoder_bQuadDec_Stsreg__MASK_REG)
#define Handle_Encoder_STATUS_MASK_PTR            (  (reg8 *) Handle_Encoder_bQuadDec_Stsreg__MASK_REG)
#define Handle_Encoder_SR_AUX_CONTROL             (* (reg8 *) Handle_Encoder_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define Handle_Encoder_SR_AUX_CONTROL_PTR         (  (reg8 *) Handle_Encoder_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define Handle_Encoder_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define Handle_Encoder_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define Handle_Encoder_COUNTER_RESET_SHIFT        (0x02u)
#define Handle_Encoder_INVALID_IN_SHIFT           (0x03u)
#define Handle_Encoder_COUNTER_OVERFLOW           ((uint8) (0x01u << Handle_Encoder_COUNTER_OVERFLOW_SHIFT))
#define Handle_Encoder_COUNTER_UNDERFLOW          ((uint8) (0x01u << Handle_Encoder_COUNTER_UNDERFLOW_SHIFT))
#define Handle_Encoder_COUNTER_RESET              ((uint8) (0x01u << Handle_Encoder_COUNTER_RESET_SHIFT))
#define Handle_Encoder_INVALID_IN                 ((uint8) (0x01u << Handle_Encoder_INVALID_IN_SHIFT))

#define Handle_Encoder_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define Handle_Encoder_INTERRUPTS_ENABLE          ((uint8)(0x01u << Handle_Encoder_INTERRUPTS_ENABLE_SHIFT))
#define Handle_Encoder_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define Handle_Encoder_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_Handle_Encoder_H */


/* [] END OF FILE */
