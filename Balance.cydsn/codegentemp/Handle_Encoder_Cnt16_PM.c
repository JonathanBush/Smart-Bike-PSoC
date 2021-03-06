/*******************************************************************************
* File Name: Handle_Encoder_Cnt16_PM.c  
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

#include "Handle_Encoder_Cnt16.h"

static Handle_Encoder_Cnt16_backupStruct Handle_Encoder_Cnt16_backup;


/*******************************************************************************
* Function Name: Handle_Encoder_Cnt16_SaveConfig
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
*  Handle_Encoder_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Handle_Encoder_Cnt16_SaveConfig(void) 
{
    #if (!Handle_Encoder_Cnt16_UsingFixedFunction)

        Handle_Encoder_Cnt16_backup.CounterUdb = Handle_Encoder_Cnt16_ReadCounter();

        #if(!Handle_Encoder_Cnt16_ControlRegRemoved)
            Handle_Encoder_Cnt16_backup.CounterControlRegister = Handle_Encoder_Cnt16_ReadControlRegister();
        #endif /* (!Handle_Encoder_Cnt16_ControlRegRemoved) */

    #endif /* (!Handle_Encoder_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Handle_Encoder_Cnt16_RestoreConfig
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
*  Handle_Encoder_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Handle_Encoder_Cnt16_RestoreConfig(void) 
{      
    #if (!Handle_Encoder_Cnt16_UsingFixedFunction)

       Handle_Encoder_Cnt16_WriteCounter(Handle_Encoder_Cnt16_backup.CounterUdb);

        #if(!Handle_Encoder_Cnt16_ControlRegRemoved)
            Handle_Encoder_Cnt16_WriteControlRegister(Handle_Encoder_Cnt16_backup.CounterControlRegister);
        #endif /* (!Handle_Encoder_Cnt16_ControlRegRemoved) */

    #endif /* (!Handle_Encoder_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Handle_Encoder_Cnt16_Sleep
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
*  Handle_Encoder_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Handle_Encoder_Cnt16_Sleep(void) 
{
    #if(!Handle_Encoder_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Handle_Encoder_Cnt16_CTRL_ENABLE == (Handle_Encoder_Cnt16_CONTROL & Handle_Encoder_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Handle_Encoder_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Handle_Encoder_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        Handle_Encoder_Cnt16_backup.CounterEnableState = 1u;
        if(Handle_Encoder_Cnt16_backup.CounterEnableState != 0u)
        {
            Handle_Encoder_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!Handle_Encoder_Cnt16_ControlRegRemoved) */
    
    Handle_Encoder_Cnt16_Stop();
    Handle_Encoder_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: Handle_Encoder_Cnt16_Wakeup
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
*  Handle_Encoder_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Handle_Encoder_Cnt16_Wakeup(void) 
{
    Handle_Encoder_Cnt16_RestoreConfig();
    #if(!Handle_Encoder_Cnt16_ControlRegRemoved)
        if(Handle_Encoder_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Handle_Encoder_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Handle_Encoder_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
