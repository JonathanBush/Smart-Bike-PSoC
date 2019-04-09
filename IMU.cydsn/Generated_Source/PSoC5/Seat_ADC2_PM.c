/*******************************************************************************
* File Name: Seat_ADC2_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Seat_ADC2.h"


/***************************************
* Local data allocation
***************************************/

static Seat_ADC2_BACKUP_STRUCT  Seat_ADC2_backup =
{
    Seat_ADC2_DISABLED
};


/*******************************************************************************
* Function Name: Seat_ADC2_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Seat_ADC2_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Seat_ADC2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Seat_ADC2_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Seat_ADC2_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The Seat_ADC2_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Seat_ADC2_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Seat_ADC2_Sleep(void)
{
    if((Seat_ADC2_PWRMGR_SAR_REG  & Seat_ADC2_ACT_PWR_SAR_EN) != 0u)
    {
        if((Seat_ADC2_SAR_CSR0_REG & Seat_ADC2_SAR_SOF_START_CONV) != 0u)
        {
            Seat_ADC2_backup.enableState = Seat_ADC2_ENABLED | Seat_ADC2_STARTED;
        }
        else
        {
            Seat_ADC2_backup.enableState = Seat_ADC2_ENABLED;
        }
        Seat_ADC2_Stop();
    }
    else
    {
        Seat_ADC2_backup.enableState = Seat_ADC2_DISABLED;
    }
}


/*******************************************************************************
* Function Name: Seat_ADC2_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  Seat_ADC2_Sleep() was called. If the component was enabled before the
*  Seat_ADC2_Sleep() function was called, the
*  Seat_ADC2_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Seat_ADC2_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Seat_ADC2_Wakeup(void)
{
    if(Seat_ADC2_backup.enableState != Seat_ADC2_DISABLED)
    {
        Seat_ADC2_Enable();
        #if(Seat_ADC2_DEFAULT_CONV_MODE != Seat_ADC2__HARDWARE_TRIGGER)
            if((Seat_ADC2_backup.enableState & Seat_ADC2_STARTED) != 0u)
            {
                Seat_ADC2_StartConvert();
            }
        #endif /* End Seat_ADC2_DEFAULT_CONV_MODE != Seat_ADC2__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
