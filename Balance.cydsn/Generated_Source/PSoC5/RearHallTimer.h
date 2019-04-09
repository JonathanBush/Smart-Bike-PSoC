/*******************************************************************************
* File Name: RearHallTimer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_RearHallTimer_H)
#define CY_TIMER_RearHallTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 RearHallTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define RearHallTimer_Resolution                 32u
#define RearHallTimer_UsingFixedFunction         0u
#define RearHallTimer_UsingHWCaptureCounter      0u
#define RearHallTimer_SoftwareCaptureMode        0u
#define RearHallTimer_SoftwareTriggerMode        0u
#define RearHallTimer_UsingHWEnable              0u
#define RearHallTimer_EnableTriggerMode          0u
#define RearHallTimer_InterruptOnCaptureCount    0u
#define RearHallTimer_RunModeUsed                0u
#define RearHallTimer_ControlRegRemoved          0u

#if defined(RearHallTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define RearHallTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (RearHallTimer_UsingFixedFunction)
    #define RearHallTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define RearHallTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End RearHallTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!RearHallTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (RearHallTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!RearHallTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}RearHallTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    RearHallTimer_Start(void) ;
void    RearHallTimer_Stop(void) ;

void    RearHallTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   RearHallTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define RearHallTimer_GetInterruptSource() RearHallTimer_ReadStatusRegister()

#if(!RearHallTimer_UDB_CONTROL_REG_REMOVED)
    uint8   RearHallTimer_ReadControlRegister(void) ;
    void    RearHallTimer_WriteControlRegister(uint8 control) ;
#endif /* (!RearHallTimer_UDB_CONTROL_REG_REMOVED) */

uint32  RearHallTimer_ReadPeriod(void) ;
void    RearHallTimer_WritePeriod(uint32 period) ;
uint32  RearHallTimer_ReadCounter(void) ;
void    RearHallTimer_WriteCounter(uint32 counter) ;
uint32  RearHallTimer_ReadCapture(void) ;
void    RearHallTimer_SoftwareCapture(void) ;

#if(!RearHallTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (RearHallTimer_SoftwareCaptureMode)
        void    RearHallTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!RearHallTimer_UsingFixedFunction) */

    #if (RearHallTimer_SoftwareTriggerMode)
        void    RearHallTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (RearHallTimer_SoftwareTriggerMode) */

    #if (RearHallTimer_EnableTriggerMode)
        void    RearHallTimer_EnableTrigger(void) ;
        void    RearHallTimer_DisableTrigger(void) ;
    #endif /* (RearHallTimer_EnableTriggerMode) */


    #if(RearHallTimer_InterruptOnCaptureCount)
        void    RearHallTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (RearHallTimer_InterruptOnCaptureCount) */

    #if (RearHallTimer_UsingHWCaptureCounter)
        void    RearHallTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   RearHallTimer_ReadCaptureCount(void) ;
    #endif /* (RearHallTimer_UsingHWCaptureCounter) */

    void RearHallTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void RearHallTimer_Init(void)          ;
void RearHallTimer_Enable(void)        ;
void RearHallTimer_SaveConfig(void)    ;
void RearHallTimer_RestoreConfig(void) ;
void RearHallTimer_Sleep(void)         ;
void RearHallTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define RearHallTimer__B_TIMER__CM_NONE 0
#define RearHallTimer__B_TIMER__CM_RISINGEDGE 1
#define RearHallTimer__B_TIMER__CM_FALLINGEDGE 2
#define RearHallTimer__B_TIMER__CM_EITHEREDGE 3
#define RearHallTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define RearHallTimer__B_TIMER__TM_NONE 0x00u
#define RearHallTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define RearHallTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define RearHallTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define RearHallTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define RearHallTimer_INIT_PERIOD             4294967295u
#define RearHallTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << RearHallTimer_CTRL_CAP_MODE_SHIFT))
#define RearHallTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << RearHallTimer_CTRL_TRIG_MODE_SHIFT))
#if (RearHallTimer_UsingFixedFunction)
    #define RearHallTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << RearHallTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << RearHallTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define RearHallTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << RearHallTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << RearHallTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << RearHallTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (RearHallTimer_UsingFixedFunction) */
#define RearHallTimer_INIT_CAPTURE_COUNT      (2u)
#define RearHallTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << RearHallTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (RearHallTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define RearHallTimer_STATUS         (*(reg8 *) RearHallTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define RearHallTimer_STATUS_MASK    (*(reg8 *) RearHallTimer_TimerHW__SR0 )
    #define RearHallTimer_CONTROL        (*(reg8 *) RearHallTimer_TimerHW__CFG0)
    #define RearHallTimer_CONTROL2       (*(reg8 *) RearHallTimer_TimerHW__CFG1)
    #define RearHallTimer_CONTROL2_PTR   ( (reg8 *) RearHallTimer_TimerHW__CFG1)
    #define RearHallTimer_RT1            (*(reg8 *) RearHallTimer_TimerHW__RT1)
    #define RearHallTimer_RT1_PTR        ( (reg8 *) RearHallTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define RearHallTimer_CONTROL3       (*(reg8 *) RearHallTimer_TimerHW__CFG2)
        #define RearHallTimer_CONTROL3_PTR   ( (reg8 *) RearHallTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define RearHallTimer_GLOBAL_ENABLE  (*(reg8 *) RearHallTimer_TimerHW__PM_ACT_CFG)
    #define RearHallTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) RearHallTimer_TimerHW__PM_STBY_CFG)

    #define RearHallTimer_CAPTURE_LSB         (* (reg16 *) RearHallTimer_TimerHW__CAP0 )
    #define RearHallTimer_CAPTURE_LSB_PTR       ((reg16 *) RearHallTimer_TimerHW__CAP0 )
    #define RearHallTimer_PERIOD_LSB          (* (reg16 *) RearHallTimer_TimerHW__PER0 )
    #define RearHallTimer_PERIOD_LSB_PTR        ((reg16 *) RearHallTimer_TimerHW__PER0 )
    #define RearHallTimer_COUNTER_LSB         (* (reg16 *) RearHallTimer_TimerHW__CNT_CMP0 )
    #define RearHallTimer_COUNTER_LSB_PTR       ((reg16 *) RearHallTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define RearHallTimer_BLOCK_EN_MASK                     RearHallTimer_TimerHW__PM_ACT_MSK
    #define RearHallTimer_BLOCK_STBY_EN_MASK                RearHallTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define RearHallTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define RearHallTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define RearHallTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define RearHallTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define RearHallTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define RearHallTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << RearHallTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define RearHallTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define RearHallTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << RearHallTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define RearHallTimer_CTRL_MODE_SHIFT                 0x01u
        #define RearHallTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << RearHallTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define RearHallTimer_CTRL_RCOD_SHIFT        0x02u
        #define RearHallTimer_CTRL_ENBL_SHIFT        0x00u
        #define RearHallTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define RearHallTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << RearHallTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define RearHallTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << RearHallTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define RearHallTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << RearHallTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define RearHallTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << RearHallTimer_CTRL_RCOD_SHIFT))
        #define RearHallTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << RearHallTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define RearHallTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define RearHallTimer_RT1_MASK                        ((uint8)((uint8)0x03u << RearHallTimer_RT1_SHIFT))
    #define RearHallTimer_SYNC                            ((uint8)((uint8)0x03u << RearHallTimer_RT1_SHIFT))
    #define RearHallTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define RearHallTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << RearHallTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define RearHallTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << RearHallTimer_SYNCDSI_SHIFT))

    #define RearHallTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << RearHallTimer_CTRL_MODE_SHIFT))
    #define RearHallTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << RearHallTimer_CTRL_MODE_SHIFT))
    #define RearHallTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << RearHallTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define RearHallTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define RearHallTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define RearHallTimer_STATUS_TC_INT_MASK_SHIFT        (RearHallTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define RearHallTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (RearHallTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define RearHallTimer_STATUS_TC                       ((uint8)((uint8)0x01u << RearHallTimer_STATUS_TC_SHIFT))
    #define RearHallTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << RearHallTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define RearHallTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << RearHallTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define RearHallTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << RearHallTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define RearHallTimer_STATUS              (* (reg8 *) RearHallTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define RearHallTimer_STATUS_MASK         (* (reg8 *) RearHallTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define RearHallTimer_STATUS_AUX_CTRL     (* (reg8 *) RearHallTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define RearHallTimer_CONTROL             (* (reg8 *) RearHallTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(RearHallTimer_Resolution <= 8u) /* 8-bit Timer */
        #define RearHallTimer_CAPTURE_LSB         (* (reg8 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define RearHallTimer_CAPTURE_LSB_PTR       ((reg8 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define RearHallTimer_PERIOD_LSB          (* (reg8 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define RearHallTimer_PERIOD_LSB_PTR        ((reg8 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define RearHallTimer_COUNTER_LSB         (* (reg8 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define RearHallTimer_COUNTER_LSB_PTR       ((reg8 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(RearHallTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define RearHallTimer_CAPTURE_LSB         (* (reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define RearHallTimer_CAPTURE_LSB_PTR       ((reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define RearHallTimer_PERIOD_LSB          (* (reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define RearHallTimer_PERIOD_LSB_PTR        ((reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define RearHallTimer_COUNTER_LSB         (* (reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define RearHallTimer_COUNTER_LSB_PTR       ((reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define RearHallTimer_CAPTURE_LSB         (* (reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define RearHallTimer_CAPTURE_LSB_PTR       ((reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define RearHallTimer_PERIOD_LSB          (* (reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define RearHallTimer_PERIOD_LSB_PTR        ((reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define RearHallTimer_COUNTER_LSB         (* (reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define RearHallTimer_COUNTER_LSB_PTR       ((reg16 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(RearHallTimer_Resolution <= 24u)/* 24-bit Timer */
        #define RearHallTimer_CAPTURE_LSB         (* (reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define RearHallTimer_CAPTURE_LSB_PTR       ((reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define RearHallTimer_PERIOD_LSB          (* (reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define RearHallTimer_PERIOD_LSB_PTR        ((reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define RearHallTimer_COUNTER_LSB         (* (reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define RearHallTimer_COUNTER_LSB_PTR       ((reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define RearHallTimer_CAPTURE_LSB         (* (reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define RearHallTimer_CAPTURE_LSB_PTR       ((reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define RearHallTimer_PERIOD_LSB          (* (reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define RearHallTimer_PERIOD_LSB_PTR        ((reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define RearHallTimer_COUNTER_LSB         (* (reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define RearHallTimer_COUNTER_LSB_PTR       ((reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define RearHallTimer_CAPTURE_LSB         (* (reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define RearHallTimer_CAPTURE_LSB_PTR       ((reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define RearHallTimer_PERIOD_LSB          (* (reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define RearHallTimer_PERIOD_LSB_PTR        ((reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define RearHallTimer_COUNTER_LSB         (* (reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define RearHallTimer_COUNTER_LSB_PTR       ((reg32 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define RearHallTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) RearHallTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (RearHallTimer_UsingHWCaptureCounter)
        #define RearHallTimer_CAP_COUNT              (*(reg8 *) RearHallTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define RearHallTimer_CAP_COUNT_PTR          ( (reg8 *) RearHallTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define RearHallTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) RearHallTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define RearHallTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) RearHallTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (RearHallTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define RearHallTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define RearHallTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define RearHallTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define RearHallTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define RearHallTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define RearHallTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << RearHallTimer_CTRL_INTCNT_SHIFT))
    #define RearHallTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << RearHallTimer_CTRL_TRIG_MODE_SHIFT))
    #define RearHallTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << RearHallTimer_CTRL_TRIG_EN_SHIFT))
    #define RearHallTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << RearHallTimer_CTRL_CAP_MODE_SHIFT))
    #define RearHallTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << RearHallTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define RearHallTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define RearHallTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define RearHallTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define RearHallTimer_STATUS_TC_INT_MASK_SHIFT       RearHallTimer_STATUS_TC_SHIFT
    #define RearHallTimer_STATUS_CAPTURE_INT_MASK_SHIFT  RearHallTimer_STATUS_CAPTURE_SHIFT
    #define RearHallTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define RearHallTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define RearHallTimer_STATUS_FIFOFULL_INT_MASK_SHIFT RearHallTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define RearHallTimer_STATUS_TC                      ((uint8)((uint8)0x01u << RearHallTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define RearHallTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << RearHallTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define RearHallTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << RearHallTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define RearHallTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << RearHallTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define RearHallTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << RearHallTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define RearHallTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << RearHallTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define RearHallTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << RearHallTimer_STATUS_FIFOFULL_SHIFT))

    #define RearHallTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define RearHallTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define RearHallTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define RearHallTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define RearHallTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define RearHallTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_RearHallTimer_H */


/* [] END OF FILE */
