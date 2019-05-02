/*******************************************************************************
* File Name: EncTimer_PM.c
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

#include "EncTimer.h"

static EncTimer_backupStruct EncTimer_backup;


/*******************************************************************************
* Function Name: EncTimer_SaveConfig
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
*  EncTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EncTimer_SaveConfig(void) 
{
    #if (!EncTimer_UsingFixedFunction)
        EncTimer_backup.TimerUdb = EncTimer_ReadCounter();
        EncTimer_backup.InterruptMaskValue = EncTimer_STATUS_MASK;
        #if (EncTimer_UsingHWCaptureCounter)
            EncTimer_backup.TimerCaptureCounter = EncTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!EncTimer_UDB_CONTROL_REG_REMOVED)
            EncTimer_backup.TimerControlRegister = EncTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: EncTimer_RestoreConfig
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
*  EncTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EncTimer_RestoreConfig(void) 
{   
    #if (!EncTimer_UsingFixedFunction)

        EncTimer_WriteCounter(EncTimer_backup.TimerUdb);
        EncTimer_STATUS_MASK =EncTimer_backup.InterruptMaskValue;
        #if (EncTimer_UsingHWCaptureCounter)
            EncTimer_SetCaptureCount(EncTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!EncTimer_UDB_CONTROL_REG_REMOVED)
            EncTimer_WriteControlRegister(EncTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: EncTimer_Sleep
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
*  EncTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void EncTimer_Sleep(void) 
{
    #if(!EncTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(EncTimer_CTRL_ENABLE == (EncTimer_CONTROL & EncTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            EncTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            EncTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    EncTimer_Stop();
    EncTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: EncTimer_Wakeup
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
*  EncTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EncTimer_Wakeup(void) 
{
    EncTimer_RestoreConfig();
    #if(!EncTimer_UDB_CONTROL_REG_REMOVED)
        if(EncTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                EncTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
