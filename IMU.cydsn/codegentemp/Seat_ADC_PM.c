/*******************************************************************************
* File Name: Seat_ADC_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Seat_ADC.h"
#include "Seat_ADC_SAR.h"
#if(Seat_ADC_CLOCK_SOURCE == Seat_ADC_CLOCK_INTERNAL)
    #include "Seat_ADC_IntClock.h"
#endif   /* Seat_ADC_CLOCK_SOURCE == Seat_ADC_CLOCK_INTERNAL */


/*******************************************************************************
* Function Name: Seat_ADC_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Seat_ADC_Sleep(void)
{
    Seat_ADC_SAR_Stop();
    Seat_ADC_SAR_Sleep();
    Seat_ADC_Disable();

    #if(Seat_ADC_CLOCK_SOURCE == Seat_ADC_CLOCK_INTERNAL)
        Seat_ADC_IntClock_Stop();
    #endif   /* Seat_ADC_CLOCK_SOURCE == Seat_ADC_CLOCK_INTERNAL */
}


/*******************************************************************************
* Function Name: Seat_ADC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers. This should
*  be called just after awaking from sleep mode
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Seat_ADC_Wakeup(void)
{
    Seat_ADC_SAR_Wakeup();
    Seat_ADC_SAR_Enable();

    #if(Seat_ADC_CLOCK_SOURCE == Seat_ADC_CLOCK_INTERNAL)
        Seat_ADC_IntClock_Start();
    #endif   /* Seat_ADC_CLOCK_SOURCE == Seat_ADC_CLOCK_INTERNAL */

    /* The block is ready to use 10 us after the SAR enable signal is set high. */
    CyDelayUs(10u);
    
    Seat_ADC_Enable();

    #if(Seat_ADC_SAMPLE_MODE == Seat_ADC_SAMPLE_MODE_FREE_RUNNING)
        Seat_ADC_SAR_StartConvert();
    #endif /* (Seat_ADC_SAMPLE_MODE == Seat_ADC_SAMPLE_MODE_FREE_RUNNING) */

    (void) CY_GET_REG8(Seat_ADC_STATUS_PTR);
}


/*******************************************************************************
* Function Name: Seat_ADC_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current configuration of ADC non-retention registers
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Seat_ADC_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Seat_ADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the configuration of ADC non-retention registers
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Seat_ADC_RestoreConfig(void)
{

}


/* [] END OF FILE */
