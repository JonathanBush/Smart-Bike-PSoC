/*******************************************************************************
* File Name: Timer_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Timer.h"

static Timer_backupStruct Timer_backup;


/*******************************************************************************
* Function Name: Timer_SaveConfig
********************************************************************************
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
*  Timer_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Timer_SaveConfig(void) 
{
    #if (!Timer_UsingFixedFunction)

        Timer_backup.CounterUdb = Timer_ReadCounter();

        #if(!Timer_ControlRegRemoved)
            Timer_backup.CounterControlRegister = Timer_ReadControlRegister();
        #endif /* (!Timer_ControlRegRemoved) */

    #endif /* (!Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Timer_RestoreConfig
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
*  Timer_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_RestoreConfig(void) 
{      
    #if (!Timer_UsingFixedFunction)

       Timer_WriteCounter(Timer_backup.CounterUdb);

        #if(!Timer_ControlRegRemoved)
            Timer_WriteControlRegister(Timer_backup.CounterControlRegister);
        #endif /* (!Timer_ControlRegRemoved) */

    #endif /* (!Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Timer_Sleep
********************************************************************************
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
*  Timer_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Sleep(void) 
{
    #if(!Timer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Timer_CTRL_ENABLE == (Timer_CONTROL & Timer_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Timer_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Timer_backup.CounterEnableState = 0u;
        }
    #else
        Timer_backup.CounterEnableState = 1u;
        if(Timer_backup.CounterEnableState != 0u)
        {
            Timer_backup.CounterEnableState = 0u;
        }
    #endif /* (!Timer_ControlRegRemoved) */
    
    Timer_Stop();
    Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Wakeup
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
*  Timer_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Wakeup(void) 
{
    Timer_RestoreConfig();
    #if(!Timer_ControlRegRemoved)
        if(Timer_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Timer_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Timer_ControlRegRemoved) */
    
}


/* [] END OF FILE */
