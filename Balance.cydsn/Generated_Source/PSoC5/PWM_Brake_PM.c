/*******************************************************************************
* File Name: PWM_Brake_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Brake.h"

static PWM_Brake_backupStruct PWM_Brake_backup;


/*******************************************************************************
* Function Name: PWM_Brake_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Brake_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Brake_SaveConfig(void) 
{

    #if(!PWM_Brake_UsingFixedFunction)
        #if(!PWM_Brake_PWMModeIsCenterAligned)
            PWM_Brake_backup.PWMPeriod = PWM_Brake_ReadPeriod();
        #endif /* (!PWM_Brake_PWMModeIsCenterAligned) */
        PWM_Brake_backup.PWMUdb = PWM_Brake_ReadCounter();
        #if (PWM_Brake_UseStatus)
            PWM_Brake_backup.InterruptMaskValue = PWM_Brake_STATUS_MASK;
        #endif /* (PWM_Brake_UseStatus) */

        #if(PWM_Brake_DeadBandMode == PWM_Brake__B_PWM__DBM_256_CLOCKS || \
            PWM_Brake_DeadBandMode == PWM_Brake__B_PWM__DBM_2_4_CLOCKS)
            PWM_Brake_backup.PWMdeadBandValue = PWM_Brake_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Brake_KillModeMinTime)
             PWM_Brake_backup.PWMKillCounterPeriod = PWM_Brake_ReadKillTime();
        #endif /* (PWM_Brake_KillModeMinTime) */

        #if(PWM_Brake_UseControl)
            PWM_Brake_backup.PWMControlRegister = PWM_Brake_ReadControlRegister();
        #endif /* (PWM_Brake_UseControl) */
    #endif  /* (!PWM_Brake_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Brake_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Brake_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Brake_RestoreConfig(void) 
{
        #if(!PWM_Brake_UsingFixedFunction)
            #if(!PWM_Brake_PWMModeIsCenterAligned)
                PWM_Brake_WritePeriod(PWM_Brake_backup.PWMPeriod);
            #endif /* (!PWM_Brake_PWMModeIsCenterAligned) */

            PWM_Brake_WriteCounter(PWM_Brake_backup.PWMUdb);

            #if (PWM_Brake_UseStatus)
                PWM_Brake_STATUS_MASK = PWM_Brake_backup.InterruptMaskValue;
            #endif /* (PWM_Brake_UseStatus) */

            #if(PWM_Brake_DeadBandMode == PWM_Brake__B_PWM__DBM_256_CLOCKS || \
                PWM_Brake_DeadBandMode == PWM_Brake__B_PWM__DBM_2_4_CLOCKS)
                PWM_Brake_WriteDeadTime(PWM_Brake_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Brake_KillModeMinTime)
                PWM_Brake_WriteKillTime(PWM_Brake_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Brake_KillModeMinTime) */

            #if(PWM_Brake_UseControl)
                PWM_Brake_WriteControlRegister(PWM_Brake_backup.PWMControlRegister);
            #endif /* (PWM_Brake_UseControl) */
        #endif  /* (!PWM_Brake_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Brake_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Brake_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Brake_Sleep(void) 
{
    #if(PWM_Brake_UseControl)
        if(PWM_Brake_CTRL_ENABLE == (PWM_Brake_CONTROL & PWM_Brake_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Brake_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Brake_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Brake_UseControl) */

    /* Stop component */
    PWM_Brake_Stop();

    /* Save registers configuration */
    PWM_Brake_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Brake_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Brake_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Brake_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Brake_RestoreConfig();

    if(PWM_Brake_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Brake_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
