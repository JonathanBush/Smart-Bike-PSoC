/*******************************************************************************
* File Name: Throttle_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Throttle.h"

static Throttle_backupStruct Throttle_backup;


/*******************************************************************************
* Function Name: Throttle_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Throttle_SaveConfig(void) 
{
    if (!((Throttle_CR1 & Throttle_SRC_MASK) == Throttle_SRC_UDB))
    {
        Throttle_backup.data_value = Throttle_Data;
    }
}


/*******************************************************************************
* Function Name: Throttle_RestoreConfig
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
*******************************************************************************/
void Throttle_RestoreConfig(void) 
{
    if (!((Throttle_CR1 & Throttle_SRC_MASK) == Throttle_SRC_UDB))
    {
        if((Throttle_Strobe & Throttle_STRB_MASK) == Throttle_STRB_EN)
        {
            Throttle_Strobe &= (uint8)(~Throttle_STRB_MASK);
            Throttle_Data = Throttle_backup.data_value;
            Throttle_Strobe |= Throttle_STRB_EN;
        }
        else
        {
            Throttle_Data = Throttle_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Throttle_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  Throttle_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Throttle_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Throttle_ACT_PWR_EN == (Throttle_PWRMGR & Throttle_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Throttle_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Throttle_backup.enableState = 0u;
    }
    
    Throttle_Stop();
    Throttle_SaveConfig();
}


/*******************************************************************************
* Function Name: Throttle_Wakeup
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
*  Throttle_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Throttle_Wakeup(void) 
{
    Throttle_RestoreConfig();
    
    if(Throttle_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Throttle_Enable();

        /* Restore the data register */
        Throttle_SetValue(Throttle_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
