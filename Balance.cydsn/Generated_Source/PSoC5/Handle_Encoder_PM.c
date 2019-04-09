/*******************************************************************************
* File Name: Handle_Encoder_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
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

#include "Handle_Encoder.h"

static Handle_Encoder_BACKUP_STRUCT Handle_Encoder_backup = {0u};


/*******************************************************************************
* Function Name: Handle_Encoder_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Handle_Encoder_SaveConfig(void) 
{
    #if (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT)
        Handle_Encoder_Cnt8_SaveConfig();
    #else 
        /* (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_16_BIT) || 
         * (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_32_BIT)
         */
        Handle_Encoder_Cnt16_SaveConfig();
    #endif /* (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: Handle_Encoder_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Handle_Encoder_RestoreConfig(void) 
{
    #if (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT)
        Handle_Encoder_Cnt8_RestoreConfig();
    #else 
        /* (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_16_BIT) || 
         * (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_32_BIT) 
         */
        Handle_Encoder_Cnt16_RestoreConfig();
    #endif /* (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: Handle_Encoder_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Handle_Encoder_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Handle_Encoder_Sleep(void) 
{
    if (0u != (Handle_Encoder_SR_AUX_CONTROL & Handle_Encoder_INTERRUPTS_ENABLE))
    {
        Handle_Encoder_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        Handle_Encoder_backup.enableState = 0u;
    }

    Handle_Encoder_Stop();
    Handle_Encoder_SaveConfig();
}


/*******************************************************************************
* Function Name: Handle_Encoder_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Handle_Encoder_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void Handle_Encoder_Wakeup(void) 
{
    Handle_Encoder_RestoreConfig();

    if (Handle_Encoder_backup.enableState != 0u)
    {
        #if (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT)
            Handle_Encoder_Cnt8_Enable();
        #else 
            /* (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_16_BIT) || 
            *  (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_32_BIT) 
            */
            Handle_Encoder_Cnt16_Enable();
        #endif /* (Handle_Encoder_COUNTER_SIZE == Handle_Encoder_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        Handle_Encoder_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

