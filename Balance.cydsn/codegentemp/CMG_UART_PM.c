/*******************************************************************************
* File Name: CMG_UART_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CMG_UART.h"


/***************************************
* Local data allocation
***************************************/

static CMG_UART_BACKUP_STRUCT  CMG_UART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: CMG_UART_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the CMG_UART_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  CMG_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CMG_UART_SaveConfig(void)
{
    #if(CMG_UART_CONTROL_REG_REMOVED == 0u)
        CMG_UART_backup.cr = CMG_UART_CONTROL_REG;
    #endif /* End CMG_UART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: CMG_UART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  CMG_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling CMG_UART_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void CMG_UART_RestoreConfig(void)
{
    #if(CMG_UART_CONTROL_REG_REMOVED == 0u)
        CMG_UART_CONTROL_REG = CMG_UART_backup.cr;
    #endif /* End CMG_UART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: CMG_UART_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The CMG_UART_Sleep() API saves the current component state. Then it
*  calls the CMG_UART_Stop() function and calls 
*  CMG_UART_SaveConfig() to save the hardware configuration.
*  Call the CMG_UART_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  CMG_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CMG_UART_Sleep(void)
{
    #if(CMG_UART_RX_ENABLED || CMG_UART_HD_ENABLED)
        if((CMG_UART_RXSTATUS_ACTL_REG  & CMG_UART_INT_ENABLE) != 0u)
        {
            CMG_UART_backup.enableState = 1u;
        }
        else
        {
            CMG_UART_backup.enableState = 0u;
        }
    #else
        if((CMG_UART_TXSTATUS_ACTL_REG  & CMG_UART_INT_ENABLE) !=0u)
        {
            CMG_UART_backup.enableState = 1u;
        }
        else
        {
            CMG_UART_backup.enableState = 0u;
        }
    #endif /* End CMG_UART_RX_ENABLED || CMG_UART_HD_ENABLED*/

    CMG_UART_Stop();
    CMG_UART_SaveConfig();
}


/*******************************************************************************
* Function Name: CMG_UART_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  CMG_UART_Sleep() was called. The CMG_UART_Wakeup() function
*  calls the CMG_UART_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  CMG_UART_Sleep() function was called, the CMG_UART_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  CMG_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CMG_UART_Wakeup(void)
{
    CMG_UART_RestoreConfig();
    #if( (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) )
        CMG_UART_ClearRxBuffer();
    #endif /* End (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) */
    #if(CMG_UART_TX_ENABLED || CMG_UART_HD_ENABLED)
        CMG_UART_ClearTxBuffer();
    #endif /* End CMG_UART_TX_ENABLED || CMG_UART_HD_ENABLED */

    if(CMG_UART_backup.enableState != 0u)
    {
        CMG_UART_Enable();
    }
}


/* [] END OF FILE */
