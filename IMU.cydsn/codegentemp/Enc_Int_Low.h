/*******************************************************************************
* File Name: Enc_Int_Low.h
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
#if !defined(CY_ISR_Enc_Int_Low_H)
#define CY_ISR_Enc_Int_Low_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Enc_Int_Low_Start(void);
void Enc_Int_Low_StartEx(cyisraddress address);
void Enc_Int_Low_Stop(void);

CY_ISR_PROTO(Enc_Int_Low_Interrupt);

void Enc_Int_Low_SetVector(cyisraddress address);
cyisraddress Enc_Int_Low_GetVector(void);

void Enc_Int_Low_SetPriority(uint8 priority);
uint8 Enc_Int_Low_GetPriority(void);

void Enc_Int_Low_Enable(void);
uint8 Enc_Int_Low_GetState(void);
void Enc_Int_Low_Disable(void);

void Enc_Int_Low_SetPending(void);
void Enc_Int_Low_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Enc_Int_Low ISR. */
#define Enc_Int_Low_INTC_VECTOR            ((reg32 *) Enc_Int_Low__INTC_VECT)

/* Address of the Enc_Int_Low ISR priority. */
#define Enc_Int_Low_INTC_PRIOR             ((reg8 *) Enc_Int_Low__INTC_PRIOR_REG)

/* Priority of the Enc_Int_Low interrupt. */
#define Enc_Int_Low_INTC_PRIOR_NUMBER      Enc_Int_Low__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Enc_Int_Low interrupt. */
#define Enc_Int_Low_INTC_SET_EN            ((reg32 *) Enc_Int_Low__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Enc_Int_Low interrupt. */
#define Enc_Int_Low_INTC_CLR_EN            ((reg32 *) Enc_Int_Low__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Enc_Int_Low interrupt state to pending. */
#define Enc_Int_Low_INTC_SET_PD            ((reg32 *) Enc_Int_Low__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Enc_Int_Low interrupt. */
#define Enc_Int_Low_INTC_CLR_PD            ((reg32 *) Enc_Int_Low__INTC_CLR_PD_REG)


#endif /* CY_ISR_Enc_Int_Low_H */


/* [] END OF FILE */
