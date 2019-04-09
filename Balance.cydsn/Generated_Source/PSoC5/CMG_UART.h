/*******************************************************************************
* File Name: CMG_UART.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_CMG_UART_H)
#define CY_UART_CMG_UART_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define CMG_UART_RX_ENABLED                     (1u)
#define CMG_UART_TX_ENABLED                     (1u)
#define CMG_UART_HD_ENABLED                     (0u)
#define CMG_UART_RX_INTERRUPT_ENABLED           (0u)
#define CMG_UART_TX_INTERRUPT_ENABLED           (0u)
#define CMG_UART_INTERNAL_CLOCK_USED            (1u)
#define CMG_UART_RXHW_ADDRESS_ENABLED           (0u)
#define CMG_UART_OVER_SAMPLE_COUNT              (8u)
#define CMG_UART_PARITY_TYPE                    (0u)
#define CMG_UART_PARITY_TYPE_SW                 (0u)
#define CMG_UART_BREAK_DETECT                   (0u)
#define CMG_UART_BREAK_BITS_TX                  (13u)
#define CMG_UART_BREAK_BITS_RX                  (13u)
#define CMG_UART_TXCLKGEN_DP                    (1u)
#define CMG_UART_USE23POLLING                   (1u)
#define CMG_UART_FLOW_CONTROL                   (0u)
#define CMG_UART_CLK_FREQ                       (0u)
#define CMG_UART_TX_BUFFER_SIZE                 (4u)
#define CMG_UART_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(CMG_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define CMG_UART_CONTROL_REG_REMOVED            (0u)
#else
    #define CMG_UART_CONTROL_REG_REMOVED            (1u)
#endif /* End CMG_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct CMG_UART_backupStruct_
{
    uint8 enableState;

    #if(CMG_UART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End CMG_UART_CONTROL_REG_REMOVED */

} CMG_UART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void CMG_UART_Start(void) ;
void CMG_UART_Stop(void) ;
uint8 CMG_UART_ReadControlRegister(void) ;
void CMG_UART_WriteControlRegister(uint8 control) ;

void CMG_UART_Init(void) ;
void CMG_UART_Enable(void) ;
void CMG_UART_SaveConfig(void) ;
void CMG_UART_RestoreConfig(void) ;
void CMG_UART_Sleep(void) ;
void CMG_UART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) )

    #if (CMG_UART_RX_INTERRUPT_ENABLED)
        #define CMG_UART_EnableRxInt()  CyIntEnable (CMG_UART_RX_VECT_NUM)
        #define CMG_UART_DisableRxInt() CyIntDisable(CMG_UART_RX_VECT_NUM)
        CY_ISR_PROTO(CMG_UART_RXISR);
    #endif /* CMG_UART_RX_INTERRUPT_ENABLED */

    void CMG_UART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void CMG_UART_SetRxAddress1(uint8 address) ;
    void CMG_UART_SetRxAddress2(uint8 address) ;

    void  CMG_UART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 CMG_UART_ReadRxData(void) ;
    uint8 CMG_UART_ReadRxStatus(void) ;
    uint8 CMG_UART_GetChar(void) ;
    uint16 CMG_UART_GetByte(void) ;
    uint8 CMG_UART_GetRxBufferSize(void)
                                                            ;
    void CMG_UART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define CMG_UART_GetRxInterruptSource   CMG_UART_ReadRxStatus

#endif /* End (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) */

/* Only if TX is enabled */
#if(CMG_UART_TX_ENABLED || CMG_UART_HD_ENABLED)

    #if(CMG_UART_TX_INTERRUPT_ENABLED)
        #define CMG_UART_EnableTxInt()  CyIntEnable (CMG_UART_TX_VECT_NUM)
        #define CMG_UART_DisableTxInt() CyIntDisable(CMG_UART_TX_VECT_NUM)
        #define CMG_UART_SetPendingTxInt() CyIntSetPending(CMG_UART_TX_VECT_NUM)
        #define CMG_UART_ClearPendingTxInt() CyIntClearPending(CMG_UART_TX_VECT_NUM)
        CY_ISR_PROTO(CMG_UART_TXISR);
    #endif /* CMG_UART_TX_INTERRUPT_ENABLED */

    void CMG_UART_SetTxInterruptMode(uint8 intSrc) ;
    void CMG_UART_WriteTxData(uint8 txDataByte) ;
    uint8 CMG_UART_ReadTxStatus(void) ;
    void CMG_UART_PutChar(uint8 txDataByte) ;
    void CMG_UART_PutString(const char8 string[]) ;
    void CMG_UART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void CMG_UART_PutCRLF(uint8 txDataByte) ;
    void CMG_UART_ClearTxBuffer(void) ;
    void CMG_UART_SetTxAddressMode(uint8 addressMode) ;
    void CMG_UART_SendBreak(uint8 retMode) ;
    uint8 CMG_UART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define CMG_UART_PutStringConst         CMG_UART_PutString
    #define CMG_UART_PutArrayConst          CMG_UART_PutArray
    #define CMG_UART_GetTxInterruptSource   CMG_UART_ReadTxStatus

#endif /* End CMG_UART_TX_ENABLED || CMG_UART_HD_ENABLED */

#if(CMG_UART_HD_ENABLED)
    void CMG_UART_LoadRxConfig(void) ;
    void CMG_UART_LoadTxConfig(void) ;
#endif /* End CMG_UART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_CMG_UART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    CMG_UART_CyBtldrCommStart(void) CYSMALL ;
    void    CMG_UART_CyBtldrCommStop(void) CYSMALL ;
    void    CMG_UART_CyBtldrCommReset(void) CYSMALL ;
    cystatus CMG_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus CMG_UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_CMG_UART)
        #define CyBtldrCommStart    CMG_UART_CyBtldrCommStart
        #define CyBtldrCommStop     CMG_UART_CyBtldrCommStop
        #define CyBtldrCommReset    CMG_UART_CyBtldrCommReset
        #define CyBtldrCommWrite    CMG_UART_CyBtldrCommWrite
        #define CyBtldrCommRead     CMG_UART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_CMG_UART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define CMG_UART_BYTE2BYTE_TIME_OUT (25u)
    #define CMG_UART_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define CMG_UART_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define CMG_UART_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define CMG_UART_SET_SPACE      (0x00u)
#define CMG_UART_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (CMG_UART_TX_ENABLED) || (CMG_UART_HD_ENABLED) )
    #if(CMG_UART_TX_INTERRUPT_ENABLED)
        #define CMG_UART_TX_VECT_NUM            (uint8)CMG_UART_TXInternalInterrupt__INTC_NUMBER
        #define CMG_UART_TX_PRIOR_NUM           (uint8)CMG_UART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* CMG_UART_TX_INTERRUPT_ENABLED */

    #define CMG_UART_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define CMG_UART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define CMG_UART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(CMG_UART_TX_ENABLED)
        #define CMG_UART_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (CMG_UART_HD_ENABLED) */
        #define CMG_UART_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (CMG_UART_TX_ENABLED) */

    #define CMG_UART_TX_STS_COMPLETE            (uint8)(0x01u << CMG_UART_TX_STS_COMPLETE_SHIFT)
    #define CMG_UART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << CMG_UART_TX_STS_FIFO_EMPTY_SHIFT)
    #define CMG_UART_TX_STS_FIFO_FULL           (uint8)(0x01u << CMG_UART_TX_STS_FIFO_FULL_SHIFT)
    #define CMG_UART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << CMG_UART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (CMG_UART_TX_ENABLED) || (CMG_UART_HD_ENABLED)*/

#if( (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) )
    #if(CMG_UART_RX_INTERRUPT_ENABLED)
        #define CMG_UART_RX_VECT_NUM            (uint8)CMG_UART_RXInternalInterrupt__INTC_NUMBER
        #define CMG_UART_RX_PRIOR_NUM           (uint8)CMG_UART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* CMG_UART_RX_INTERRUPT_ENABLED */
    #define CMG_UART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define CMG_UART_RX_STS_BREAK_SHIFT             (0x01u)
    #define CMG_UART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define CMG_UART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define CMG_UART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define CMG_UART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define CMG_UART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define CMG_UART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define CMG_UART_RX_STS_MRKSPC           (uint8)(0x01u << CMG_UART_RX_STS_MRKSPC_SHIFT)
    #define CMG_UART_RX_STS_BREAK            (uint8)(0x01u << CMG_UART_RX_STS_BREAK_SHIFT)
    #define CMG_UART_RX_STS_PAR_ERROR        (uint8)(0x01u << CMG_UART_RX_STS_PAR_ERROR_SHIFT)
    #define CMG_UART_RX_STS_STOP_ERROR       (uint8)(0x01u << CMG_UART_RX_STS_STOP_ERROR_SHIFT)
    #define CMG_UART_RX_STS_OVERRUN          (uint8)(0x01u << CMG_UART_RX_STS_OVERRUN_SHIFT)
    #define CMG_UART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << CMG_UART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define CMG_UART_RX_STS_ADDR_MATCH       (uint8)(0x01u << CMG_UART_RX_STS_ADDR_MATCH_SHIFT)
    #define CMG_UART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << CMG_UART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define CMG_UART_RX_HW_MASK                     (0x7Fu)
#endif /* End (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) */

/* Control Register definitions */
#define CMG_UART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define CMG_UART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define CMG_UART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define CMG_UART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define CMG_UART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define CMG_UART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define CMG_UART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define CMG_UART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define CMG_UART_CTRL_HD_SEND               (uint8)(0x01u << CMG_UART_CTRL_HD_SEND_SHIFT)
#define CMG_UART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << CMG_UART_CTRL_HD_SEND_BREAK_SHIFT)
#define CMG_UART_CTRL_MARK                  (uint8)(0x01u << CMG_UART_CTRL_MARK_SHIFT)
#define CMG_UART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << CMG_UART_CTRL_PARITY_TYPE0_SHIFT)
#define CMG_UART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << CMG_UART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define CMG_UART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define CMG_UART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define CMG_UART_SEND_BREAK                         (0x00u)
#define CMG_UART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define CMG_UART_REINIT                             (0x02u)
#define CMG_UART_SEND_WAIT_REINIT                   (0x03u)

#define CMG_UART_OVER_SAMPLE_8                      (8u)
#define CMG_UART_OVER_SAMPLE_16                     (16u)

#define CMG_UART_BIT_CENTER                         (CMG_UART_OVER_SAMPLE_COUNT - 2u)

#define CMG_UART_FIFO_LENGTH                        (4u)
#define CMG_UART_NUMBER_OF_START_BIT                (1u)
#define CMG_UART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define CMG_UART_TXBITCTR_BREAKBITS8X   ((CMG_UART_BREAK_BITS_TX * CMG_UART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define CMG_UART_TXBITCTR_BREAKBITS ((CMG_UART_BREAK_BITS_TX * CMG_UART_OVER_SAMPLE_COUNT) - 1u)

#define CMG_UART_HALF_BIT_COUNT   \
                            (((CMG_UART_OVER_SAMPLE_COUNT / 2u) + (CMG_UART_USE23POLLING * 1u)) - 2u)
#if (CMG_UART_OVER_SAMPLE_COUNT == CMG_UART_OVER_SAMPLE_8)
    #define CMG_UART_HD_TXBITCTR_INIT   (((CMG_UART_BREAK_BITS_TX + \
                            CMG_UART_NUMBER_OF_START_BIT) * CMG_UART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define CMG_UART_RXBITCTR_INIT  ((((CMG_UART_BREAK_BITS_RX + CMG_UART_NUMBER_OF_START_BIT) \
                            * CMG_UART_OVER_SAMPLE_COUNT) + CMG_UART_HALF_BIT_COUNT) - 1u)

#else /* CMG_UART_OVER_SAMPLE_COUNT == CMG_UART_OVER_SAMPLE_16 */
    #define CMG_UART_HD_TXBITCTR_INIT   ((8u * CMG_UART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define CMG_UART_RXBITCTR_INIT      (((7u * CMG_UART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      CMG_UART_HALF_BIT_COUNT)
#endif /* End CMG_UART_OVER_SAMPLE_COUNT */

#define CMG_UART_HD_RXBITCTR_INIT                   CMG_UART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 CMG_UART_initVar;
#if (CMG_UART_TX_INTERRUPT_ENABLED && CMG_UART_TX_ENABLED)
    extern volatile uint8 CMG_UART_txBuffer[CMG_UART_TX_BUFFER_SIZE];
    extern volatile uint8 CMG_UART_txBufferRead;
    extern uint8 CMG_UART_txBufferWrite;
#endif /* (CMG_UART_TX_INTERRUPT_ENABLED && CMG_UART_TX_ENABLED) */
#if (CMG_UART_RX_INTERRUPT_ENABLED && (CMG_UART_RX_ENABLED || CMG_UART_HD_ENABLED))
    extern uint8 CMG_UART_errorStatus;
    extern volatile uint8 CMG_UART_rxBuffer[CMG_UART_RX_BUFFER_SIZE];
    extern volatile uint8 CMG_UART_rxBufferRead;
    extern volatile uint8 CMG_UART_rxBufferWrite;
    extern volatile uint8 CMG_UART_rxBufferLoopDetect;
    extern volatile uint8 CMG_UART_rxBufferOverflow;
    #if (CMG_UART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 CMG_UART_rxAddressMode;
        extern volatile uint8 CMG_UART_rxAddressDetected;
    #endif /* (CMG_UART_RXHW_ADDRESS_ENABLED) */
#endif /* (CMG_UART_RX_INTERRUPT_ENABLED && (CMG_UART_RX_ENABLED || CMG_UART_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define CMG_UART__B_UART__AM_SW_BYTE_BYTE 1
#define CMG_UART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define CMG_UART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define CMG_UART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define CMG_UART__B_UART__AM_NONE 0

#define CMG_UART__B_UART__NONE_REVB 0
#define CMG_UART__B_UART__EVEN_REVB 1
#define CMG_UART__B_UART__ODD_REVB 2
#define CMG_UART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define CMG_UART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define CMG_UART_NUMBER_OF_STOP_BITS    (1u)

#if (CMG_UART_RXHW_ADDRESS_ENABLED)
    #define CMG_UART_RX_ADDRESS_MODE    (0u)
    #define CMG_UART_RX_HW_ADDRESS1     (0u)
    #define CMG_UART_RX_HW_ADDRESS2     (0u)
#endif /* (CMG_UART_RXHW_ADDRESS_ENABLED) */

#define CMG_UART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << CMG_UART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << CMG_UART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << CMG_UART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << CMG_UART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << CMG_UART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << CMG_UART_RX_STS_BREAK_SHIFT) \
                                        | (0 << CMG_UART_RX_STS_OVERRUN_SHIFT))

#define CMG_UART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << CMG_UART_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << CMG_UART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << CMG_UART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << CMG_UART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef CMG_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define CMG_UART_CONTROL_REG \
                            (* (reg8 *) CMG_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define CMG_UART_CONTROL_PTR \
                            (  (reg8 *) CMG_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End CMG_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(CMG_UART_TX_ENABLED)
    #define CMG_UART_TXDATA_REG          (* (reg8 *) CMG_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define CMG_UART_TXDATA_PTR          (  (reg8 *) CMG_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define CMG_UART_TXDATA_AUX_CTL_REG  (* (reg8 *) CMG_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define CMG_UART_TXDATA_AUX_CTL_PTR  (  (reg8 *) CMG_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define CMG_UART_TXSTATUS_REG        (* (reg8 *) CMG_UART_BUART_sTX_TxSts__STATUS_REG)
    #define CMG_UART_TXSTATUS_PTR        (  (reg8 *) CMG_UART_BUART_sTX_TxSts__STATUS_REG)
    #define CMG_UART_TXSTATUS_MASK_REG   (* (reg8 *) CMG_UART_BUART_sTX_TxSts__MASK_REG)
    #define CMG_UART_TXSTATUS_MASK_PTR   (  (reg8 *) CMG_UART_BUART_sTX_TxSts__MASK_REG)
    #define CMG_UART_TXSTATUS_ACTL_REG   (* (reg8 *) CMG_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define CMG_UART_TXSTATUS_ACTL_PTR   (  (reg8 *) CMG_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(CMG_UART_TXCLKGEN_DP)
        #define CMG_UART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define CMG_UART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define CMG_UART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define CMG_UART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define CMG_UART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define CMG_UART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define CMG_UART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define CMG_UART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define CMG_UART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define CMG_UART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) CMG_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* CMG_UART_TXCLKGEN_DP */

#endif /* End CMG_UART_TX_ENABLED */

#if(CMG_UART_HD_ENABLED)

    #define CMG_UART_TXDATA_REG             (* (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define CMG_UART_TXDATA_PTR             (  (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define CMG_UART_TXDATA_AUX_CTL_REG     (* (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define CMG_UART_TXDATA_AUX_CTL_PTR     (  (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define CMG_UART_TXSTATUS_REG           (* (reg8 *) CMG_UART_BUART_sRX_RxSts__STATUS_REG )
    #define CMG_UART_TXSTATUS_PTR           (  (reg8 *) CMG_UART_BUART_sRX_RxSts__STATUS_REG )
    #define CMG_UART_TXSTATUS_MASK_REG      (* (reg8 *) CMG_UART_BUART_sRX_RxSts__MASK_REG )
    #define CMG_UART_TXSTATUS_MASK_PTR      (  (reg8 *) CMG_UART_BUART_sRX_RxSts__MASK_REG )
    #define CMG_UART_TXSTATUS_ACTL_REG      (* (reg8 *) CMG_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define CMG_UART_TXSTATUS_ACTL_PTR      (  (reg8 *) CMG_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End CMG_UART_HD_ENABLED */

#if( (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) )
    #define CMG_UART_RXDATA_REG             (* (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define CMG_UART_RXDATA_PTR             (  (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define CMG_UART_RXADDRESS1_REG         (* (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define CMG_UART_RXADDRESS1_PTR         (  (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define CMG_UART_RXADDRESS2_REG         (* (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define CMG_UART_RXADDRESS2_PTR         (  (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define CMG_UART_RXDATA_AUX_CTL_REG     (* (reg8 *) CMG_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define CMG_UART_RXBITCTR_PERIOD_REG    (* (reg8 *) CMG_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define CMG_UART_RXBITCTR_PERIOD_PTR    (  (reg8 *) CMG_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define CMG_UART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) CMG_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define CMG_UART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) CMG_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define CMG_UART_RXBITCTR_COUNTER_REG   (* (reg8 *) CMG_UART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define CMG_UART_RXBITCTR_COUNTER_PTR   (  (reg8 *) CMG_UART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define CMG_UART_RXSTATUS_REG           (* (reg8 *) CMG_UART_BUART_sRX_RxSts__STATUS_REG )
    #define CMG_UART_RXSTATUS_PTR           (  (reg8 *) CMG_UART_BUART_sRX_RxSts__STATUS_REG )
    #define CMG_UART_RXSTATUS_MASK_REG      (* (reg8 *) CMG_UART_BUART_sRX_RxSts__MASK_REG )
    #define CMG_UART_RXSTATUS_MASK_PTR      (  (reg8 *) CMG_UART_BUART_sRX_RxSts__MASK_REG )
    #define CMG_UART_RXSTATUS_ACTL_REG      (* (reg8 *) CMG_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define CMG_UART_RXSTATUS_ACTL_PTR      (  (reg8 *) CMG_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) */

#if(CMG_UART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define CMG_UART_INTCLOCK_CLKEN_REG     (* (reg8 *) CMG_UART_IntClock__PM_ACT_CFG)
    #define CMG_UART_INTCLOCK_CLKEN_PTR     (  (reg8 *) CMG_UART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define CMG_UART_INTCLOCK_CLKEN_MASK    CMG_UART_IntClock__PM_ACT_MSK
#endif /* End CMG_UART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(CMG_UART_TX_ENABLED)
    #define CMG_UART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End CMG_UART_TX_ENABLED */

#if(CMG_UART_HD_ENABLED)
    #define CMG_UART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End CMG_UART_HD_ENABLED */

#if( (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) )
    #define CMG_UART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define CMG_UART_WAIT_1_MS      CMG_UART_BL_CHK_DELAY_MS   

#define CMG_UART_TXBUFFERSIZE   CMG_UART_TX_BUFFER_SIZE
#define CMG_UART_RXBUFFERSIZE   CMG_UART_RX_BUFFER_SIZE

#if (CMG_UART_RXHW_ADDRESS_ENABLED)
    #define CMG_UART_RXADDRESSMODE  CMG_UART_RX_ADDRESS_MODE
    #define CMG_UART_RXHWADDRESS1   CMG_UART_RX_HW_ADDRESS1
    #define CMG_UART_RXHWADDRESS2   CMG_UART_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define CMG_UART_RXAddressMode  CMG_UART_RXADDRESSMODE
#endif /* (CMG_UART_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define CMG_UART_initvar                    CMG_UART_initVar

#define CMG_UART_RX_Enabled                 CMG_UART_RX_ENABLED
#define CMG_UART_TX_Enabled                 CMG_UART_TX_ENABLED
#define CMG_UART_HD_Enabled                 CMG_UART_HD_ENABLED
#define CMG_UART_RX_IntInterruptEnabled     CMG_UART_RX_INTERRUPT_ENABLED
#define CMG_UART_TX_IntInterruptEnabled     CMG_UART_TX_INTERRUPT_ENABLED
#define CMG_UART_InternalClockUsed          CMG_UART_INTERNAL_CLOCK_USED
#define CMG_UART_RXHW_Address_Enabled       CMG_UART_RXHW_ADDRESS_ENABLED
#define CMG_UART_OverSampleCount            CMG_UART_OVER_SAMPLE_COUNT
#define CMG_UART_ParityType                 CMG_UART_PARITY_TYPE

#if( CMG_UART_TX_ENABLED && (CMG_UART_TXBUFFERSIZE > CMG_UART_FIFO_LENGTH))
    #define CMG_UART_TXBUFFER               CMG_UART_txBuffer
    #define CMG_UART_TXBUFFERREAD           CMG_UART_txBufferRead
    #define CMG_UART_TXBUFFERWRITE          CMG_UART_txBufferWrite
#endif /* End CMG_UART_TX_ENABLED */
#if( ( CMG_UART_RX_ENABLED || CMG_UART_HD_ENABLED ) && \
     (CMG_UART_RXBUFFERSIZE > CMG_UART_FIFO_LENGTH) )
    #define CMG_UART_RXBUFFER               CMG_UART_rxBuffer
    #define CMG_UART_RXBUFFERREAD           CMG_UART_rxBufferRead
    #define CMG_UART_RXBUFFERWRITE          CMG_UART_rxBufferWrite
    #define CMG_UART_RXBUFFERLOOPDETECT     CMG_UART_rxBufferLoopDetect
    #define CMG_UART_RXBUFFER_OVERFLOW      CMG_UART_rxBufferOverflow
#endif /* End CMG_UART_RX_ENABLED */

#ifdef CMG_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define CMG_UART_CONTROL                CMG_UART_CONTROL_REG
#endif /* End CMG_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(CMG_UART_TX_ENABLED)
    #define CMG_UART_TXDATA                 CMG_UART_TXDATA_REG
    #define CMG_UART_TXSTATUS               CMG_UART_TXSTATUS_REG
    #define CMG_UART_TXSTATUS_MASK          CMG_UART_TXSTATUS_MASK_REG
    #define CMG_UART_TXSTATUS_ACTL          CMG_UART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(CMG_UART_TXCLKGEN_DP)
        #define CMG_UART_TXBITCLKGEN_CTR        CMG_UART_TXBITCLKGEN_CTR_REG
        #define CMG_UART_TXBITCLKTX_COMPLETE    CMG_UART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define CMG_UART_TXBITCTR_PERIOD        CMG_UART_TXBITCTR_PERIOD_REG
        #define CMG_UART_TXBITCTR_CONTROL       CMG_UART_TXBITCTR_CONTROL_REG
        #define CMG_UART_TXBITCTR_COUNTER       CMG_UART_TXBITCTR_COUNTER_REG
    #endif /* CMG_UART_TXCLKGEN_DP */
#endif /* End CMG_UART_TX_ENABLED */

#if(CMG_UART_HD_ENABLED)
    #define CMG_UART_TXDATA                 CMG_UART_TXDATA_REG
    #define CMG_UART_TXSTATUS               CMG_UART_TXSTATUS_REG
    #define CMG_UART_TXSTATUS_MASK          CMG_UART_TXSTATUS_MASK_REG
    #define CMG_UART_TXSTATUS_ACTL          CMG_UART_TXSTATUS_ACTL_REG
#endif /* End CMG_UART_HD_ENABLED */

#if( (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) )
    #define CMG_UART_RXDATA                 CMG_UART_RXDATA_REG
    #define CMG_UART_RXADDRESS1             CMG_UART_RXADDRESS1_REG
    #define CMG_UART_RXADDRESS2             CMG_UART_RXADDRESS2_REG
    #define CMG_UART_RXBITCTR_PERIOD        CMG_UART_RXBITCTR_PERIOD_REG
    #define CMG_UART_RXBITCTR_CONTROL       CMG_UART_RXBITCTR_CONTROL_REG
    #define CMG_UART_RXBITCTR_COUNTER       CMG_UART_RXBITCTR_COUNTER_REG
    #define CMG_UART_RXSTATUS               CMG_UART_RXSTATUS_REG
    #define CMG_UART_RXSTATUS_MASK          CMG_UART_RXSTATUS_MASK_REG
    #define CMG_UART_RXSTATUS_ACTL          CMG_UART_RXSTATUS_ACTL_REG
#endif /* End  (CMG_UART_RX_ENABLED) || (CMG_UART_HD_ENABLED) */

#if(CMG_UART_INTERNAL_CLOCK_USED)
    #define CMG_UART_INTCLOCK_CLKEN         CMG_UART_INTCLOCK_CLKEN_REG
#endif /* End CMG_UART_INTERNAL_CLOCK_USED */

#define CMG_UART_WAIT_FOR_COMLETE_REINIT    CMG_UART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_CMG_UART_H */


/* [] END OF FILE */
