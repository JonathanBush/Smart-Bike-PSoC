/*******************************************************************************
* File Name: RearHallTimer_PM.c
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

#include "RearHallTimer.h"

static RearHallTimer_backupStruct RearHallTimer_backup;


/*******************************************************************************
* Function Name: RearHallTimer_SaveConfig
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
*  RearHallTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void RearHallTimer_SaveConfig(void) 
{
    #if (!RearHallTimer_UsingFixedFunction)
        RearHallTimer_backup.TimerUdb = RearHallTimer_ReadCounter();
        RearHallTimer_backup.InterruptMaskValue = RearHallTimer_STATUS_MASK;
        #if (RearHallTimer_UsingHWCaptureCounter)
            RearHallTimer_backup.TimerCaptureCounter = RearHallTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!RearHallTimer_UDB_CONTROL_REG_REMOVED)
            RearHallTimer_backup.TimerControlRegister = RearHallTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: RearHallTimer_RestoreConfig
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
*  RearHallTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void RearHallTimer_RestoreConfig(void) 
{   
    #if (!RearHallTimer_UsingFixedFunction)

        RearHallTimer_WriteCounter(RearHallTimer_backup.TimerUdb);
        RearHallTimer_STATUS_MASK =RearHallTimer_backup.InterruptMaskValue;
        #if (RearHallTimer_UsingHWCaptureCounter)
            RearHallTimer_SetCaptureCount(RearHallTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!RearHallTimer_UDB_CONTROL_REG_REMOVED)
            RearHallTimer_WriteControlRegister(RearHallTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: RearHallTimer_Sleep
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
*  RearHallTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void RearHallTimer_Sleep(void) 
{
    #if(!RearHallTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(RearHallTimer_CTRL_ENABLE == (RearHallTimer_CONTROL & RearHallTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            RearHallTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            RearHallTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    RearHallTimer_Stop();
    RearHallTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: RearHallTimer_Wakeup
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
*  RearHallTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void RearHallTimer_Wakeup(void) 
{
    RearHallTimer_RestoreConfig();
    #if(!RearHallTimer_UDB_CONTROL_REG_REMOVED)
        if(RearHallTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                RearHallTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
