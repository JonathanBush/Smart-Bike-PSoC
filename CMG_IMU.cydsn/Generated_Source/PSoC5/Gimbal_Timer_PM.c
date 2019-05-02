/*******************************************************************************
* File Name: Gimbal_Timer_PM.c
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

#include "Gimbal_Timer.h"

static Gimbal_Timer_backupStruct Gimbal_Timer_backup;


/*******************************************************************************
* Function Name: Gimbal_Timer_SaveConfig
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
*  Gimbal_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Gimbal_Timer_SaveConfig(void) 
{
    #if (!Gimbal_Timer_UsingFixedFunction)
        Gimbal_Timer_backup.TimerUdb = Gimbal_Timer_ReadCounter();
        Gimbal_Timer_backup.InterruptMaskValue = Gimbal_Timer_STATUS_MASK;
        #if (Gimbal_Timer_UsingHWCaptureCounter)
            Gimbal_Timer_backup.TimerCaptureCounter = Gimbal_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Gimbal_Timer_UDB_CONTROL_REG_REMOVED)
            Gimbal_Timer_backup.TimerControlRegister = Gimbal_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Gimbal_Timer_RestoreConfig
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
*  Gimbal_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Gimbal_Timer_RestoreConfig(void) 
{   
    #if (!Gimbal_Timer_UsingFixedFunction)

        Gimbal_Timer_WriteCounter(Gimbal_Timer_backup.TimerUdb);
        Gimbal_Timer_STATUS_MASK =Gimbal_Timer_backup.InterruptMaskValue;
        #if (Gimbal_Timer_UsingHWCaptureCounter)
            Gimbal_Timer_SetCaptureCount(Gimbal_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Gimbal_Timer_UDB_CONTROL_REG_REMOVED)
            Gimbal_Timer_WriteControlRegister(Gimbal_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Gimbal_Timer_Sleep
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
*  Gimbal_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Gimbal_Timer_Sleep(void) 
{
    #if(!Gimbal_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Gimbal_Timer_CTRL_ENABLE == (Gimbal_Timer_CONTROL & Gimbal_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Gimbal_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Gimbal_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Gimbal_Timer_Stop();
    Gimbal_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Gimbal_Timer_Wakeup
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
*  Gimbal_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Gimbal_Timer_Wakeup(void) 
{
    Gimbal_Timer_RestoreConfig();
    #if(!Gimbal_Timer_UDB_CONTROL_REG_REMOVED)
        if(Gimbal_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Gimbal_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
