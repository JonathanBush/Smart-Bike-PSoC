/*******************************************************************************
* File Name: Gimbal_Encoder_PM.c
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

#include "Gimbal_Encoder.h"

static Gimbal_Encoder_BACKUP_STRUCT Gimbal_Encoder_backup = {0u};


/*******************************************************************************
* Function Name: Gimbal_Encoder_SaveConfig
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
void Gimbal_Encoder_SaveConfig(void) 
{
    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT)
        Gimbal_Encoder_Cnt8_SaveConfig();
    #else 
        /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT) || 
         * (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT)
         */
        Gimbal_Encoder_Cnt16_SaveConfig();
    #endif /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_RestoreConfig
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
void Gimbal_Encoder_RestoreConfig(void) 
{
    #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT)
        Gimbal_Encoder_Cnt8_RestoreConfig();
    #else 
        /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT) || 
         * (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT) 
         */
        Gimbal_Encoder_Cnt16_RestoreConfig();
    #endif /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_Sleep
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
*  Gimbal_Encoder_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Gimbal_Encoder_Sleep(void) 
{
    if (0u != (Gimbal_Encoder_SR_AUX_CONTROL & Gimbal_Encoder_INTERRUPTS_ENABLE))
    {
        Gimbal_Encoder_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        Gimbal_Encoder_backup.enableState = 0u;
    }

    Gimbal_Encoder_Stop();
    Gimbal_Encoder_SaveConfig();
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_Wakeup
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
*  Gimbal_Encoder_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void Gimbal_Encoder_Wakeup(void) 
{
    Gimbal_Encoder_RestoreConfig();

    if (Gimbal_Encoder_backup.enableState != 0u)
    {
        #if (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT)
            Gimbal_Encoder_Cnt8_Enable();
        #else 
            /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_16_BIT) || 
            *  (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_32_BIT) 
            */
            Gimbal_Encoder_Cnt16_Enable();
        #endif /* (Gimbal_Encoder_COUNTER_SIZE == Gimbal_Encoder_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        Gimbal_Encoder_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

