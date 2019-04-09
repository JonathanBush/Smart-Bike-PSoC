/*******************************************************************************
* File Name: EncTimer_Low_PM.c
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

#include "EncTimer_Low.h"

static EncTimer_Low_backupStruct EncTimer_Low_backup;


/*******************************************************************************
* Function Name: EncTimer_Low_SaveConfig
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
*  EncTimer_Low_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EncTimer_Low_SaveConfig(void) 
{
    #if (!EncTimer_Low_UsingFixedFunction)
        EncTimer_Low_backup.TimerUdb = EncTimer_Low_ReadCounter();
        EncTimer_Low_backup.InterruptMaskValue = EncTimer_Low_STATUS_MASK;
        #if (EncTimer_Low_UsingHWCaptureCounter)
            EncTimer_Low_backup.TimerCaptureCounter = EncTimer_Low_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!EncTimer_Low_UDB_CONTROL_REG_REMOVED)
            EncTimer_Low_backup.TimerControlRegister = EncTimer_Low_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: EncTimer_Low_RestoreConfig
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
*  EncTimer_Low_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EncTimer_Low_RestoreConfig(void) 
{   
    #if (!EncTimer_Low_UsingFixedFunction)

        EncTimer_Low_WriteCounter(EncTimer_Low_backup.TimerUdb);
        EncTimer_Low_STATUS_MASK =EncTimer_Low_backup.InterruptMaskValue;
        #if (EncTimer_Low_UsingHWCaptureCounter)
            EncTimer_Low_SetCaptureCount(EncTimer_Low_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!EncTimer_Low_UDB_CONTROL_REG_REMOVED)
            EncTimer_Low_WriteControlRegister(EncTimer_Low_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: EncTimer_Low_Sleep
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
*  EncTimer_Low_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void EncTimer_Low_Sleep(void) 
{
    #if(!EncTimer_Low_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(EncTimer_Low_CTRL_ENABLE == (EncTimer_Low_CONTROL & EncTimer_Low_CTRL_ENABLE))
        {
            /* Timer is enabled */
            EncTimer_Low_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            EncTimer_Low_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    EncTimer_Low_Stop();
    EncTimer_Low_SaveConfig();
}


/*******************************************************************************
* Function Name: EncTimer_Low_Wakeup
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
*  EncTimer_Low_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EncTimer_Low_Wakeup(void) 
{
    EncTimer_Low_RestoreConfig();
    #if(!EncTimer_Low_UDB_CONTROL_REG_REMOVED)
        if(EncTimer_Low_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                EncTimer_Low_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
