/*******************************************************************************
* File Name: CMG_UARTINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CMG_UART.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (CMG_UART_RX_INTERRUPT_ENABLED && (CMG_UART_RX_ENABLED || CMG_UART_HD_ENABLED))
    /*******************************************************************************
    * Function Name: CMG_UART_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  CMG_UART_rxBuffer - RAM buffer pointer for save received data.
    *  CMG_UART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  CMG_UART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  CMG_UART_rxBufferOverflow - software overflow flag. Set to one
    *     when CMG_UART_rxBufferWrite index overtakes
    *     CMG_UART_rxBufferRead index.
    *  CMG_UART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when CMG_UART_rxBufferWrite is equal to
    *    CMG_UART_rxBufferRead
    *  CMG_UART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  CMG_UART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(CMG_UART_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef CMG_UART_RXISR_ENTRY_CALLBACK
        CMG_UART_RXISR_EntryCallback();
    #endif /* CMG_UART_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START CMG_UART_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = CMG_UART_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in CMG_UART_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (CMG_UART_RX_STS_BREAK | 
                            CMG_UART_RX_STS_PAR_ERROR |
                            CMG_UART_RX_STS_STOP_ERROR | 
                            CMG_UART_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                CMG_UART_errorStatus |= readStatus & ( CMG_UART_RX_STS_BREAK | 
                                                            CMG_UART_RX_STS_PAR_ERROR | 
                                                            CMG_UART_RX_STS_STOP_ERROR | 
                                                            CMG_UART_RX_STS_OVERRUN);
                /* `#START CMG_UART_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef CMG_UART_RXISR_ERROR_CALLBACK
                CMG_UART_RXISR_ERROR_Callback();
            #endif /* CMG_UART_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & CMG_UART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = CMG_UART_RXDATA_REG;
            #if (CMG_UART_RXHW_ADDRESS_ENABLED)
                if(CMG_UART_rxAddressMode == (uint8)CMG_UART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & CMG_UART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & CMG_UART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            CMG_UART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            CMG_UART_rxAddressDetected = 0u;
                        }
                    }
                    if(CMG_UART_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        CMG_UART_rxBuffer[CMG_UART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    CMG_UART_rxBuffer[CMG_UART_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                CMG_UART_rxBuffer[CMG_UART_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (CMG_UART_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(CMG_UART_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        CMG_UART_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    CMG_UART_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(CMG_UART_rxBufferWrite >= CMG_UART_RX_BUFFER_SIZE)
                    {
                        CMG_UART_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(CMG_UART_rxBufferWrite == CMG_UART_rxBufferRead)
                    {
                        CMG_UART_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (CMG_UART_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            CMG_UART_RXSTATUS_MASK_REG  &= (uint8)~CMG_UART_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(CMG_UART_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (CMG_UART_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & CMG_UART_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START CMG_UART_RXISR_END` */

        /* `#END` */

    #ifdef CMG_UART_RXISR_EXIT_CALLBACK
        CMG_UART_RXISR_ExitCallback();
    #endif /* CMG_UART_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (CMG_UART_RX_INTERRUPT_ENABLED && (CMG_UART_RX_ENABLED || CMG_UART_HD_ENABLED)) */


#if (CMG_UART_TX_INTERRUPT_ENABLED && CMG_UART_TX_ENABLED)
    /*******************************************************************************
    * Function Name: CMG_UART_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  CMG_UART_txBuffer - RAM buffer pointer for transmit data from.
    *  CMG_UART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  CMG_UART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(CMG_UART_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef CMG_UART_TXISR_ENTRY_CALLBACK
        CMG_UART_TXISR_EntryCallback();
    #endif /* CMG_UART_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START CMG_UART_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((CMG_UART_txBufferRead != CMG_UART_txBufferWrite) &&
             ((CMG_UART_TXSTATUS_REG & CMG_UART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(CMG_UART_txBufferRead >= CMG_UART_TX_BUFFER_SIZE)
            {
                CMG_UART_txBufferRead = 0u;
            }

            CMG_UART_TXDATA_REG = CMG_UART_txBuffer[CMG_UART_txBufferRead];

            /* Set next pointer */
            CMG_UART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START CMG_UART_TXISR_END` */

        /* `#END` */

    #ifdef CMG_UART_TXISR_EXIT_CALLBACK
        CMG_UART_TXISR_ExitCallback();
    #endif /* CMG_UART_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (CMG_UART_TX_INTERRUPT_ENABLED && CMG_UART_TX_ENABLED) */


/* [] END OF FILE */
