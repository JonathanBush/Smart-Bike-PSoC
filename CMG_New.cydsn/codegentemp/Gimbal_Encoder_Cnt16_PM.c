/*******************************************************************************
* File Name: Gimbal_Encoder_Cnt16_PM.c  
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

#include "Gimbal_Encoder_Cnt16.h"

static Gimbal_Encoder_Cnt16_backupStruct Gimbal_Encoder_Cnt16_backup;


/*******************************************************************************
* Function Name: Gimbal_Encoder_Cnt16_SaveConfig
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
*  Gimbal_Encoder_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Gimbal_Encoder_Cnt16_SaveConfig(void) 
{
    #if (!Gimbal_Encoder_Cnt16_UsingFixedFunction)

        Gimbal_Encoder_Cnt16_backup.CounterUdb = Gimbal_Encoder_Cnt16_ReadCounter();

        #if(!Gimbal_Encoder_Cnt16_ControlRegRemoved)
            Gimbal_Encoder_Cnt16_backup.CounterControlRegister = Gimbal_Encoder_Cnt16_ReadControlRegister();
        #endif /* (!Gimbal_Encoder_Cnt16_ControlRegRemoved) */

    #endif /* (!Gimbal_Encoder_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_Cnt16_RestoreConfig
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
*  Gimbal_Encoder_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Gimbal_Encoder_Cnt16_RestoreConfig(void) 
{      
    #if (!Gimbal_Encoder_Cnt16_UsingFixedFunction)

       Gimbal_Encoder_Cnt16_WriteCounter(Gimbal_Encoder_Cnt16_backup.CounterUdb);

        #if(!Gimbal_Encoder_Cnt16_ControlRegRemoved)
            Gimbal_Encoder_Cnt16_WriteControlRegister(Gimbal_Encoder_Cnt16_backup.CounterControlRegister);
        #endif /* (!Gimbal_Encoder_Cnt16_ControlRegRemoved) */

    #endif /* (!Gimbal_Encoder_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_Cnt16_Sleep
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
*  Gimbal_Encoder_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Gimbal_Encoder_Cnt16_Sleep(void) 
{
    #if(!Gimbal_Encoder_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Gimbal_Encoder_Cnt16_CTRL_ENABLE == (Gimbal_Encoder_Cnt16_CONTROL & Gimbal_Encoder_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Gimbal_Encoder_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Gimbal_Encoder_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        Gimbal_Encoder_Cnt16_backup.CounterEnableState = 1u;
        if(Gimbal_Encoder_Cnt16_backup.CounterEnableState != 0u)
        {
            Gimbal_Encoder_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!Gimbal_Encoder_Cnt16_ControlRegRemoved) */
    
    Gimbal_Encoder_Cnt16_Stop();
    Gimbal_Encoder_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: Gimbal_Encoder_Cnt16_Wakeup
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
*  Gimbal_Encoder_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Gimbal_Encoder_Cnt16_Wakeup(void) 
{
    Gimbal_Encoder_Cnt16_RestoreConfig();
    #if(!Gimbal_Encoder_Cnt16_ControlRegRemoved)
        if(Gimbal_Encoder_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Gimbal_Encoder_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Gimbal_Encoder_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
