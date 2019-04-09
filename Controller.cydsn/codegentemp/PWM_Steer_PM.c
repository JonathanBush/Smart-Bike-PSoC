/*******************************************************************************
* File Name: PWM_Steer_PM.c
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

#include "PWM_Steer.h"

static PWM_Steer_backupStruct PWM_Steer_backup;


/*******************************************************************************
* Function Name: PWM_Steer_SaveConfig
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
*  PWM_Steer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Steer_SaveConfig(void) 
{

    #if(!PWM_Steer_UsingFixedFunction)
        #if(!PWM_Steer_PWMModeIsCenterAligned)
            PWM_Steer_backup.PWMPeriod = PWM_Steer_ReadPeriod();
        #endif /* (!PWM_Steer_PWMModeIsCenterAligned) */
        PWM_Steer_backup.PWMUdb = PWM_Steer_ReadCounter();
        #if (PWM_Steer_UseStatus)
            PWM_Steer_backup.InterruptMaskValue = PWM_Steer_STATUS_MASK;
        #endif /* (PWM_Steer_UseStatus) */

        #if(PWM_Steer_DeadBandMode == PWM_Steer__B_PWM__DBM_256_CLOCKS || \
            PWM_Steer_DeadBandMode == PWM_Steer__B_PWM__DBM_2_4_CLOCKS)
            PWM_Steer_backup.PWMdeadBandValue = PWM_Steer_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Steer_KillModeMinTime)
             PWM_Steer_backup.PWMKillCounterPeriod = PWM_Steer_ReadKillTime();
        #endif /* (PWM_Steer_KillModeMinTime) */

        #if(PWM_Steer_UseControl)
            PWM_Steer_backup.PWMControlRegister = PWM_Steer_ReadControlRegister();
        #endif /* (PWM_Steer_UseControl) */
    #endif  /* (!PWM_Steer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Steer_RestoreConfig
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
*  PWM_Steer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Steer_RestoreConfig(void) 
{
        #if(!PWM_Steer_UsingFixedFunction)
            #if(!PWM_Steer_PWMModeIsCenterAligned)
                PWM_Steer_WritePeriod(PWM_Steer_backup.PWMPeriod);
            #endif /* (!PWM_Steer_PWMModeIsCenterAligned) */

            PWM_Steer_WriteCounter(PWM_Steer_backup.PWMUdb);

            #if (PWM_Steer_UseStatus)
                PWM_Steer_STATUS_MASK = PWM_Steer_backup.InterruptMaskValue;
            #endif /* (PWM_Steer_UseStatus) */

            #if(PWM_Steer_DeadBandMode == PWM_Steer__B_PWM__DBM_256_CLOCKS || \
                PWM_Steer_DeadBandMode == PWM_Steer__B_PWM__DBM_2_4_CLOCKS)
                PWM_Steer_WriteDeadTime(PWM_Steer_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Steer_KillModeMinTime)
                PWM_Steer_WriteKillTime(PWM_Steer_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Steer_KillModeMinTime) */

            #if(PWM_Steer_UseControl)
                PWM_Steer_WriteControlRegister(PWM_Steer_backup.PWMControlRegister);
            #endif /* (PWM_Steer_UseControl) */
        #endif  /* (!PWM_Steer_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Steer_Sleep
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
*  PWM_Steer_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Steer_Sleep(void) 
{
    #if(PWM_Steer_UseControl)
        if(PWM_Steer_CTRL_ENABLE == (PWM_Steer_CONTROL & PWM_Steer_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Steer_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Steer_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Steer_UseControl) */

    /* Stop component */
    PWM_Steer_Stop();

    /* Save registers configuration */
    PWM_Steer_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Steer_Wakeup
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
*  PWM_Steer_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Steer_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Steer_RestoreConfig();

    if(PWM_Steer_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Steer_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
