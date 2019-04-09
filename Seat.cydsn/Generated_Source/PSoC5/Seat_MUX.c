/*******************************************************************************
* File Name: Seat_MUX.c
* Version 1.80
*
*  Description:
*    This file contains functions for the AMuxSeq.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "Seat_MUX.h"

uint8 Seat_MUX_initVar = 0u;


/*******************************************************************************
* Function Name: Seat_MUX_Start
********************************************************************************
* Summary:
*  Disconnect all channels. The next time Next is called, channel 0 will be
*  connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Seat_MUX_Start(void)
{
    Seat_MUX_DisconnectAll();
    Seat_MUX_initVar = 1u;
}


/*******************************************************************************
* Function Name: Seat_MUX_Init
********************************************************************************
* Summary:
*  Disconnect all channels. The next time Next is called, channel 0 will be
*  connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Seat_MUX_Init(void)
{
    Seat_MUX_DisconnectAll();
}


/*******************************************************************************
* Function Name: Seat_MUX_Stop
********************************************************************************
* Summary:
*  Disconnect all channels. The next time Next is called, channel 0 will be
*  connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Seat_MUX_Stop(void)
{
    Seat_MUX_DisconnectAll();
}

#if (Seat_MUX_MUXTYPE == Seat_MUX_MUX_DIFF)

/*******************************************************************************
* Function Name: Seat_MUX_Next
********************************************************************************
* Summary:
*  Disconnects the previous channel and connects the next one in the sequence.
*  When Next is called for the first time after Init, Start, Enable, Stop, or
*  DisconnectAll, it connects channel 0.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Seat_MUX_Next(void)
{
    Seat_MUX_CYAMUXSIDE_A_Next();
    Seat_MUX_CYAMUXSIDE_B_Next();
}


/*******************************************************************************
* Function Name: Seat_MUX_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels. The next time Next is called, channel
*  0 will be connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Seat_MUX_DisconnectAll(void)
{
    Seat_MUX_CYAMUXSIDE_A_DisconnectAll();
    Seat_MUX_CYAMUXSIDE_B_DisconnectAll();
}


/*******************************************************************************
* Function Name: Seat_MUX_GetChannel
********************************************************************************
* Summary:
*  The currently connected channel is retuned. If no channel is connected
*  returns -1.
*
* Parameters:
*  void
*
* Return:
*  The current channel or -1.
*
*******************************************************************************/
int8 Seat_MUX_GetChannel(void)
{
    return Seat_MUX_CYAMUXSIDE_A_curChannel;
}

#else

/*******************************************************************************
* Function Name: Seat_MUX_GetChannel
********************************************************************************
* Summary:
*  The currently connected channel is retuned. If no channel is connected
*  returns -1.
*
* Parameters:
*  void
*
* Return:
*  The current channel or -1.
*
*******************************************************************************/
int8 Seat_MUX_GetChannel(void)
{
    return Seat_MUX_curChannel;
}

#endif


/* [] END OF FILE */
