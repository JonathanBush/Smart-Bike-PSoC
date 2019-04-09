/*******************************************************************************
* File Name: Speed_Timer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Speed_Timer.h"

static Speed_Timer_backupStruct Speed_Timer_backup;


/*******************************************************************************
* Function Name: Speed_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Speed_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Speed_Timer_SaveConfig(void) 
{
    #if (!Speed_Timer_UsingFixedFunction)
        Speed_Timer_backup.TimerUdb = Speed_Timer_ReadCounter();
        Speed_Timer_backup.InterruptMaskValue = Speed_Timer_STATUS_MASK;
        #if (Speed_Timer_UsingHWCaptureCounter)
            Speed_Timer_backup.TimerCaptureCounter = Speed_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Speed_Timer_UDB_CONTROL_REG_REMOVED)
            Speed_Timer_backup.TimerControlRegister = Speed_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Speed_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Speed_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Speed_Timer_RestoreConfig(void) 
{   
    #if (!Speed_Timer_UsingFixedFunction)

        Speed_Timer_WriteCounter(Speed_Timer_backup.TimerUdb);
        Speed_Timer_STATUS_MASK =Speed_Timer_backup.InterruptMaskValue;
        #if (Speed_Timer_UsingHWCaptureCounter)
            Speed_Timer_SetCaptureCount(Speed_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Speed_Timer_UDB_CONTROL_REG_REMOVED)
            Speed_Timer_WriteControlRegister(Speed_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Speed_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Speed_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Speed_Timer_Sleep(void) 
{
    #if(!Speed_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Speed_Timer_CTRL_ENABLE == (Speed_Timer_CONTROL & Speed_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Speed_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Speed_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Speed_Timer_Stop();
    Speed_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Speed_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Speed_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Speed_Timer_Wakeup(void) 
{
    Speed_Timer_RestoreConfig();
    #if(!Speed_Timer_UDB_CONTROL_REG_REMOVED)
        if(Speed_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Speed_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
