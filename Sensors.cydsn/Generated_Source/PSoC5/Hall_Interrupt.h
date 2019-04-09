/*******************************************************************************
* File Name: Hall_Interrupt.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Hall_Interrupt_H)
#define CY_ISR_Hall_Interrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Hall_Interrupt_Start(void);
void Hall_Interrupt_StartEx(cyisraddress address);
void Hall_Interrupt_Stop(void);

CY_ISR_PROTO(Hall_Interrupt_Interrupt);

void Hall_Interrupt_SetVector(cyisraddress address);
cyisraddress Hall_Interrupt_GetVector(void);

void Hall_Interrupt_SetPriority(uint8 priority);
uint8 Hall_Interrupt_GetPriority(void);

void Hall_Interrupt_Enable(void);
uint8 Hall_Interrupt_GetState(void);
void Hall_Interrupt_Disable(void);

void Hall_Interrupt_SetPending(void);
void Hall_Interrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Hall_Interrupt ISR. */
#define Hall_Interrupt_INTC_VECTOR            ((reg32 *) Hall_Interrupt__INTC_VECT)

/* Address of the Hall_Interrupt ISR priority. */
#define Hall_Interrupt_INTC_PRIOR             ((reg8 *) Hall_Interrupt__INTC_PRIOR_REG)

/* Priority of the Hall_Interrupt interrupt. */
#define Hall_Interrupt_INTC_PRIOR_NUMBER      Hall_Interrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Hall_Interrupt interrupt. */
#define Hall_Interrupt_INTC_SET_EN            ((reg32 *) Hall_Interrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Hall_Interrupt interrupt. */
#define Hall_Interrupt_INTC_CLR_EN            ((reg32 *) Hall_Interrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Hall_Interrupt interrupt state to pending. */
#define Hall_Interrupt_INTC_SET_PD            ((reg32 *) Hall_Interrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Hall_Interrupt interrupt. */
#define Hall_Interrupt_INTC_CLR_PD            ((reg32 *) Hall_Interrupt__INTC_CLR_PD_REG)


#endif /* CY_ISR_Hall_Interrupt_H */


/* [] END OF FILE */
