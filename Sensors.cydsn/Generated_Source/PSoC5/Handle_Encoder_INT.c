/*******************************************************************************
* File Name: Handle_Encoder_INT.c
* Version 3.0
*
* Description:
*  This file contains the Interrupt Service Routine (ISR) for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Handle_Encoder.h"
#include "Handle_Encoder_PVT.h"
#include "cyapicallbacks.h"

volatile int32 Handle_Encoder_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void Handle_Encoder_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for Quadrature Decoder Component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Handle_Encoder_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  Handle_Encoder_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( Handle_Encoder_ISR )
{
   uint8 Handle_Encoder_swStatus;

   Handle_Encoder_swStatus = Handle_Encoder_STATUS_REG;

    #ifdef Handle_Encoder_ISR_ENTRY_CALLBACK
        Handle_Encoder_ISR_EntryCallback();
    #endif /* Handle_Encoder_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START Handle_Encoder_ISR_START` */

    /* `#END` */

    if (0u != (Handle_Encoder_swStatus & Handle_Encoder_COUNTER_OVERFLOW))
    {
        Handle_Encoder_count32SoftPart += (int32) Handle_Encoder_COUNTER_MAX_VALUE;
    }
    else if (0u != (Handle_Encoder_swStatus & Handle_Encoder_COUNTER_UNDERFLOW))
    {
        Handle_Encoder_count32SoftPart -= (int32) Handle_Encoder_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (Handle_Encoder_swStatus & Handle_Encoder_COUNTER_RESET))
    {
        Handle_Encoder_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START Handle_Encoder_ISR_END` */

    /* `#END` */

    #ifdef Handle_Encoder_ISR_EXIT_CALLBACK
        Handle_Encoder_ISR_ExitCallback();
    #endif /* Handle_Encoder_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
