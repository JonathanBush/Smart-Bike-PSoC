/*******************************************************************************
* File Name: Gimbal_Encoder.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
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

#include "Gimbal_Encoder.h"

#if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
    #include "Gimbal_Encoder_PVT.h"
#endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT */

uint8 Gimbal_Encoder_initVar = 0u;


/*******************************************************************************
* Function Name: Gimbal_Encoder_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Gimbal_Encoder_Init(void) 
{
    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(Gimbal_Encoder_ISR_NUMBER);
        /* Set the ISR to point to the Gimbal_Encoder_isr Interrupt. */
        (void) CyIntSetVector(Gimbal_Encoder_ISR_NUMBER, & Gimbal_Encoder_ISR);
        /* Set the priority. */
        CyIntSetPriority(Gimbal_Encoder_ISR_NUMBER, Gimbal_Encoder_ISR_PRIORITY);
    #endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Gimbal_Encoder_Enable(void) 
{
    uint8 enableInterrupts;

    Gimbal_Encoder_SetInterruptMask(Gimbal_Encoder_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) Gimbal_Encoder_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    Gimbal_Encoder_SR_AUX_CONTROL |= Gimbal_Encoder_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(Gimbal_Encoder_ISR_NUMBER);
    #endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Gimbal_Encoder_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Gimbal_Encoder_Start(void) 
{
    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT)
        Gimbal_Encoder_Cnt8_Start();
        Gimbal_Encoder_Cnt8_WriteCounter(Gimbal_Encoder_COUNTER_INIT_VALUE);
    #else
        /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT) || 
        *  (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT) 
        */
        Gimbal_Encoder_Cnt16_Start();
        Gimbal_Encoder_Cnt16_WriteCounter(Gimbal_Encoder_COUNTER_INIT_VALUE);
    #endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT */
    
    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)        
       Gimbal_Encoder_count32SoftPart = 0;
    #endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT */

    if (Gimbal_Encoder_initVar == 0u)
    {
        Gimbal_Encoder_Init();
        Gimbal_Encoder_initVar = 1u;
    }

    Gimbal_Encoder_Enable();
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Gimbal_Encoder_Stop(void) 
{
    uint8 enableInterrupts;

    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT)
        Gimbal_Encoder_Cnt8_Stop();
    #else 
        /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT) ||
        *  (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
        */
        Gimbal_Encoder_Cnt16_Stop();    /* counter disable */
    #endif /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    Gimbal_Encoder_SR_AUX_CONTROL &= (uint8) (~Gimbal_Encoder_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
        CyIntDisable(Gimbal_Encoder_ISR_NUMBER);    /* interrupt disable */
    #endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  Gimbal_Encoder_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int16 Gimbal_Encoder_GetCounter(void) 
{
    int16 count;
    uint16 tmpCnt;

    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(Gimbal_Encoder_ISR_NUMBER);

        tmpCnt = Gimbal_Encoder_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) Gimbal_Encoder_COUNTER_INIT_VALUE);
        count = Gimbal_Encoder_count32SoftPart + hwCount;

        CyIntEnable(Gimbal_Encoder_ISR_NUMBER);
    #else 
        /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT) || 
        *  (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT)
        */
        #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT)
            tmpCnt = Gimbal_Encoder_Cnt8_ReadCounter();
        #else /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT) */
            tmpCnt = Gimbal_Encoder_Cnt16_ReadCounter();
        #endif  /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT */

        count = (int16) ((int32) tmpCnt -
                (int32) Gimbal_Encoder_COUNTER_INIT_VALUE);

    #endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  Gimbal_Encoder_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Gimbal_Encoder_SetCounter(int16 value) 
{
    #if ((Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT) || \
         (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + Gimbal_Encoder_COUNTER_INIT_VALUE;
        }
        else
        {
            count = Gimbal_Encoder_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT)
            Gimbal_Encoder_Cnt8_WriteCounter(count);
        #else /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT) */
            Gimbal_Encoder_Cnt16_WriteCounter(count);
        #endif  /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT */
    #else /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT) */
        CyIntDisable(Gimbal_Encoder_ISR_NUMBER);

        Gimbal_Encoder_Cnt16_WriteCounter(Gimbal_Encoder_COUNTER_INIT_VALUE);
        Gimbal_Encoder_count32SoftPart = value;

        CyIntEnable(Gimbal_Encoder_ISR_NUMBER);
    #endif  /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT) ||
             * (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 Gimbal_Encoder_GetEvents(void) 
{
    return (Gimbal_Encoder_STATUS_REG & Gimbal_Encoder_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void Gimbal_Encoder_SetInterruptMask(uint8 mask) 
{
    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (Gimbal_Encoder_COUNTER_OVERFLOW | Gimbal_Encoder_COUNTER_UNDERFLOW |
                 Gimbal_Encoder_COUNTER_RESET);
    #endif /* Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT */

    Gimbal_Encoder_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 Gimbal_Encoder_GetInterruptMask(void) 
{
    return (Gimbal_Encoder_STATUS_MASK & Gimbal_Encoder_INIT_INT_MASK);
}


/* [] END OF FILE */
