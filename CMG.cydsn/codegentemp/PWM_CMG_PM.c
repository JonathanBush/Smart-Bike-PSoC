/*******************************************************************************
* File Name: PWM_CMG_PM.c
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

#include "PWM_CMG.h"

static PWM_CMG_backupStruct PWM_CMG_backup;


/*******************************************************************************
* Function Name: PWM_CMG_SaveConfig
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
*  PWM_CMG_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_CMG_SaveConfig(void) 
{

    #if(!PWM_CMG_UsingFixedFunction)
        #if(!PWM_CMG_PWMModeIsCenterAligned)
            PWM_CMG_backup.PWMPeriod = PWM_CMG_ReadPeriod();
        #endif /* (!PWM_CMG_PWMModeIsCenterAligned) */
        PWM_CMG_backup.PWMUdb = PWM_CMG_ReadCounter();
        #if (PWM_CMG_UseStatus)
            PWM_CMG_backup.InterruptMaskValue = PWM_CMG_STATUS_MASK;
        #endif /* (PWM_CMG_UseStatus) */

        #if(PWM_CMG_DeadBandMode == PWM_CMG__B_PWM__DBM_256_CLOCKS || \
            PWM_CMG_DeadBandMode == PWM_CMG__B_PWM__DBM_2_4_CLOCKS)
            PWM_CMG_backup.PWMdeadBandValue = PWM_CMG_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_CMG_KillModeMinTime)
             PWM_CMG_backup.PWMKillCounterPeriod = PWM_CMG_ReadKillTime();
        #endif /* (PWM_CMG_KillModeMinTime) */

        #if(PWM_CMG_UseControl)
            PWM_CMG_backup.PWMControlRegister = PWM_CMG_ReadControlRegister();
        #endif /* (PWM_CMG_UseControl) */
    #endif  /* (!PWM_CMG_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_CMG_RestoreConfig
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
*  PWM_CMG_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_CMG_RestoreConfig(void) 
{
        #if(!PWM_CMG_UsingFixedFunction)
            #if(!PWM_CMG_PWMModeIsCenterAligned)
                PWM_CMG_WritePeriod(PWM_CMG_backup.PWMPeriod);
            #endif /* (!PWM_CMG_PWMModeIsCenterAligned) */

            PWM_CMG_WriteCounter(PWM_CMG_backup.PWMUdb);

            #if (PWM_CMG_UseStatus)
                PWM_CMG_STATUS_MASK = PWM_CMG_backup.InterruptMaskValue;
            #endif /* (PWM_CMG_UseStatus) */

            #if(PWM_CMG_DeadBandMode == PWM_CMG__B_PWM__DBM_256_CLOCKS || \
                PWM_CMG_DeadBandMode == PWM_CMG__B_PWM__DBM_2_4_CLOCKS)
                PWM_CMG_WriteDeadTime(PWM_CMG_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_CMG_KillModeMinTime)
                PWM_CMG_WriteKillTime(PWM_CMG_backup.PWMKillCounterPeriod);
            #endif /* (PWM_CMG_KillModeMinTime) */

            #if(PWM_CMG_UseControl)
                PWM_CMG_WriteControlRegister(PWM_CMG_backup.PWMControlRegister);
            #endif /* (PWM_CMG_UseControl) */
        #endif  /* (!PWM_CMG_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_CMG_Sleep
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
*  PWM_CMG_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_CMG_Sleep(void) 
{
    #if(PWM_CMG_UseControl)
        if(PWM_CMG_CTRL_ENABLE == (PWM_CMG_CONTROL & PWM_CMG_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_CMG_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_CMG_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_CMG_UseControl) */

    /* Stop component */
    PWM_CMG_Stop();

    /* Save registers configuration */
    PWM_CMG_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_CMG_Wakeup
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
*  PWM_CMG_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_CMG_Wakeup(void) 
{
     /* Restore registers values */
    PWM_CMG_RestoreConfig();

    if(PWM_CMG_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_CMG_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
