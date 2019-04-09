/*******************************************************************************
* File Name: EncTimer_High.h
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

#if !defined(CY_TIMER_EncTimer_High_H)
#define CY_TIMER_EncTimer_High_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 EncTimer_High_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define EncTimer_High_Resolution                 16u
#define EncTimer_High_UsingFixedFunction         0u
#define EncTimer_High_UsingHWCaptureCounter      0u
#define EncTimer_High_SoftwareCaptureMode        0u
#define EncTimer_High_SoftwareTriggerMode        0u
#define EncTimer_High_UsingHWEnable              0u
#define EncTimer_High_EnableTriggerMode          1u
#define EncTimer_High_InterruptOnCaptureCount    1u
#define EncTimer_High_RunModeUsed                0u
#define EncTimer_High_ControlRegRemoved          0u

#if defined(EncTimer_High_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define EncTimer_High_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (EncTimer_High_UsingFixedFunction)
    #define EncTimer_High_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define EncTimer_High_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End EncTimer_High_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!EncTimer_High_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (EncTimer_High_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!EncTimer_High_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}EncTimer_High_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    EncTimer_High_Start(void) ;
void    EncTimer_High_Stop(void) ;

void    EncTimer_High_SetInterruptMode(uint8 interruptMode) ;
uint8   EncTimer_High_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define EncTimer_High_GetInterruptSource() EncTimer_High_ReadStatusRegister()

#if(!EncTimer_High_UDB_CONTROL_REG_REMOVED)
    uint8   EncTimer_High_ReadControlRegister(void) ;
    void    EncTimer_High_WriteControlRegister(uint8 control) ;
#endif /* (!EncTimer_High_UDB_CONTROL_REG_REMOVED) */

uint16  EncTimer_High_ReadPeriod(void) ;
void    EncTimer_High_WritePeriod(uint16 period) ;
uint16  EncTimer_High_ReadCounter(void) ;
void    EncTimer_High_WriteCounter(uint16 counter) ;
uint16  EncTimer_High_ReadCapture(void) ;
void    EncTimer_High_SoftwareCapture(void) ;

#if(!EncTimer_High_UsingFixedFunction) /* UDB Prototypes */
    #if (EncTimer_High_SoftwareCaptureMode)
        void    EncTimer_High_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!EncTimer_High_UsingFixedFunction) */

    #if (EncTimer_High_SoftwareTriggerMode)
        void    EncTimer_High_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (EncTimer_High_SoftwareTriggerMode) */

    #if (EncTimer_High_EnableTriggerMode)
        void    EncTimer_High_EnableTrigger(void) ;
        void    EncTimer_High_DisableTrigger(void) ;
    #endif /* (EncTimer_High_EnableTriggerMode) */


    #if(EncTimer_High_InterruptOnCaptureCount)
        void    EncTimer_High_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (EncTimer_High_InterruptOnCaptureCount) */

    #if (EncTimer_High_UsingHWCaptureCounter)
        void    EncTimer_High_SetCaptureCount(uint8 captureCount) ;
        uint8   EncTimer_High_ReadCaptureCount(void) ;
    #endif /* (EncTimer_High_UsingHWCaptureCounter) */

    void EncTimer_High_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void EncTimer_High_Init(void)          ;
void EncTimer_High_Enable(void)        ;
void EncTimer_High_SaveConfig(void)    ;
void EncTimer_High_RestoreConfig(void) ;
void EncTimer_High_Sleep(void)         ;
void EncTimer_High_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define EncTimer_High__B_TIMER__CM_NONE 0
#define EncTimer_High__B_TIMER__CM_RISINGEDGE 1
#define EncTimer_High__B_TIMER__CM_FALLINGEDGE 2
#define EncTimer_High__B_TIMER__CM_EITHEREDGE 3
#define EncTimer_High__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define EncTimer_High__B_TIMER__TM_NONE 0x00u
#define EncTimer_High__B_TIMER__TM_RISINGEDGE 0x04u
#define EncTimer_High__B_TIMER__TM_FALLINGEDGE 0x08u
#define EncTimer_High__B_TIMER__TM_EITHEREDGE 0x0Cu
#define EncTimer_High__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define EncTimer_High_INIT_PERIOD             65535u
#define EncTimer_High_INIT_CAPTURE_MODE       ((uint8)((uint8)2u << EncTimer_High_CTRL_CAP_MODE_SHIFT))
#define EncTimer_High_INIT_TRIGGER_MODE       ((uint8)((uint8)1u << EncTimer_High_CTRL_TRIG_MODE_SHIFT))
#if (EncTimer_High_UsingFixedFunction)
    #define EncTimer_High_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << EncTimer_High_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)1 << EncTimer_High_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define EncTimer_High_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << EncTimer_High_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)1 << EncTimer_High_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << EncTimer_High_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (EncTimer_High_UsingFixedFunction) */
#define EncTimer_High_INIT_CAPTURE_COUNT      (2u)
#define EncTimer_High_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << EncTimer_High_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (EncTimer_High_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define EncTimer_High_STATUS         (*(reg8 *) EncTimer_High_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define EncTimer_High_STATUS_MASK    (*(reg8 *) EncTimer_High_TimerHW__SR0 )
    #define EncTimer_High_CONTROL        (*(reg8 *) EncTimer_High_TimerHW__CFG0)
    #define EncTimer_High_CONTROL2       (*(reg8 *) EncTimer_High_TimerHW__CFG1)
    #define EncTimer_High_CONTROL2_PTR   ( (reg8 *) EncTimer_High_TimerHW__CFG1)
    #define EncTimer_High_RT1            (*(reg8 *) EncTimer_High_TimerHW__RT1)
    #define EncTimer_High_RT1_PTR        ( (reg8 *) EncTimer_High_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define EncTimer_High_CONTROL3       (*(reg8 *) EncTimer_High_TimerHW__CFG2)
        #define EncTimer_High_CONTROL3_PTR   ( (reg8 *) EncTimer_High_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define EncTimer_High_GLOBAL_ENABLE  (*(reg8 *) EncTimer_High_TimerHW__PM_ACT_CFG)
    #define EncTimer_High_GLOBAL_STBY_ENABLE  (*(reg8 *) EncTimer_High_TimerHW__PM_STBY_CFG)

    #define EncTimer_High_CAPTURE_LSB         (* (reg16 *) EncTimer_High_TimerHW__CAP0 )
    #define EncTimer_High_CAPTURE_LSB_PTR       ((reg16 *) EncTimer_High_TimerHW__CAP0 )
    #define EncTimer_High_PERIOD_LSB          (* (reg16 *) EncTimer_High_TimerHW__PER0 )
    #define EncTimer_High_PERIOD_LSB_PTR        ((reg16 *) EncTimer_High_TimerHW__PER0 )
    #define EncTimer_High_COUNTER_LSB         (* (reg16 *) EncTimer_High_TimerHW__CNT_CMP0 )
    #define EncTimer_High_COUNTER_LSB_PTR       ((reg16 *) EncTimer_High_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define EncTimer_High_BLOCK_EN_MASK                     EncTimer_High_TimerHW__PM_ACT_MSK
    #define EncTimer_High_BLOCK_STBY_EN_MASK                EncTimer_High_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define EncTimer_High_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define EncTimer_High_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define EncTimer_High_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define EncTimer_High_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define EncTimer_High_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define EncTimer_High_CTRL_ENABLE                        ((uint8)((uint8)0x01u << EncTimer_High_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define EncTimer_High_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define EncTimer_High_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << EncTimer_High_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define EncTimer_High_CTRL_MODE_SHIFT                 0x01u
        #define EncTimer_High_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << EncTimer_High_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define EncTimer_High_CTRL_RCOD_SHIFT        0x02u
        #define EncTimer_High_CTRL_ENBL_SHIFT        0x00u
        #define EncTimer_High_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define EncTimer_High_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << EncTimer_High_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define EncTimer_High_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << EncTimer_High_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define EncTimer_High_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << EncTimer_High_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define EncTimer_High_CTRL_RCOD       ((uint8)((uint8)0x03u << EncTimer_High_CTRL_RCOD_SHIFT))
        #define EncTimer_High_CTRL_ENBL       ((uint8)((uint8)0x80u << EncTimer_High_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define EncTimer_High_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define EncTimer_High_RT1_MASK                        ((uint8)((uint8)0x03u << EncTimer_High_RT1_SHIFT))
    #define EncTimer_High_SYNC                            ((uint8)((uint8)0x03u << EncTimer_High_RT1_SHIFT))
    #define EncTimer_High_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define EncTimer_High_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << EncTimer_High_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define EncTimer_High_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << EncTimer_High_SYNCDSI_SHIFT))

    #define EncTimer_High_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << EncTimer_High_CTRL_MODE_SHIFT))
    #define EncTimer_High_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << EncTimer_High_CTRL_MODE_SHIFT))
    #define EncTimer_High_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << EncTimer_High_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define EncTimer_High_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define EncTimer_High_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define EncTimer_High_STATUS_TC_INT_MASK_SHIFT        (EncTimer_High_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define EncTimer_High_STATUS_CAPTURE_INT_MASK_SHIFT   (EncTimer_High_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define EncTimer_High_STATUS_TC                       ((uint8)((uint8)0x01u << EncTimer_High_STATUS_TC_SHIFT))
    #define EncTimer_High_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << EncTimer_High_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define EncTimer_High_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << EncTimer_High_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define EncTimer_High_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << EncTimer_High_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define EncTimer_High_STATUS              (* (reg8 *) EncTimer_High_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define EncTimer_High_STATUS_MASK         (* (reg8 *) EncTimer_High_TimerUDB_rstSts_stsreg__MASK_REG)
    #define EncTimer_High_STATUS_AUX_CTRL     (* (reg8 *) EncTimer_High_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define EncTimer_High_CONTROL             (* (reg8 *) EncTimer_High_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(EncTimer_High_Resolution <= 8u) /* 8-bit Timer */
        #define EncTimer_High_CAPTURE_LSB         (* (reg8 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define EncTimer_High_CAPTURE_LSB_PTR       ((reg8 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define EncTimer_High_PERIOD_LSB          (* (reg8 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define EncTimer_High_PERIOD_LSB_PTR        ((reg8 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define EncTimer_High_COUNTER_LSB         (* (reg8 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define EncTimer_High_COUNTER_LSB_PTR       ((reg8 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(EncTimer_High_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define EncTimer_High_CAPTURE_LSB         (* (reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define EncTimer_High_CAPTURE_LSB_PTR       ((reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define EncTimer_High_PERIOD_LSB          (* (reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define EncTimer_High_PERIOD_LSB_PTR        ((reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define EncTimer_High_COUNTER_LSB         (* (reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define EncTimer_High_COUNTER_LSB_PTR       ((reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define EncTimer_High_CAPTURE_LSB         (* (reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define EncTimer_High_CAPTURE_LSB_PTR       ((reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define EncTimer_High_PERIOD_LSB          (* (reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define EncTimer_High_PERIOD_LSB_PTR        ((reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define EncTimer_High_COUNTER_LSB         (* (reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define EncTimer_High_COUNTER_LSB_PTR       ((reg16 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(EncTimer_High_Resolution <= 24u)/* 24-bit Timer */
        #define EncTimer_High_CAPTURE_LSB         (* (reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define EncTimer_High_CAPTURE_LSB_PTR       ((reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define EncTimer_High_PERIOD_LSB          (* (reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define EncTimer_High_PERIOD_LSB_PTR        ((reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define EncTimer_High_COUNTER_LSB         (* (reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define EncTimer_High_COUNTER_LSB_PTR       ((reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define EncTimer_High_CAPTURE_LSB         (* (reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define EncTimer_High_CAPTURE_LSB_PTR       ((reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define EncTimer_High_PERIOD_LSB          (* (reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define EncTimer_High_PERIOD_LSB_PTR        ((reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define EncTimer_High_COUNTER_LSB         (* (reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define EncTimer_High_COUNTER_LSB_PTR       ((reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define EncTimer_High_CAPTURE_LSB         (* (reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define EncTimer_High_CAPTURE_LSB_PTR       ((reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define EncTimer_High_PERIOD_LSB          (* (reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define EncTimer_High_PERIOD_LSB_PTR        ((reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define EncTimer_High_COUNTER_LSB         (* (reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define EncTimer_High_COUNTER_LSB_PTR       ((reg32 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define EncTimer_High_COUNTER_LSB_PTR_8BIT       ((reg8 *) EncTimer_High_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (EncTimer_High_UsingHWCaptureCounter)
        #define EncTimer_High_CAP_COUNT              (*(reg8 *) EncTimer_High_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define EncTimer_High_CAP_COUNT_PTR          ( (reg8 *) EncTimer_High_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define EncTimer_High_CAPTURE_COUNT_CTRL     (*(reg8 *) EncTimer_High_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define EncTimer_High_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) EncTimer_High_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (EncTimer_High_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define EncTimer_High_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define EncTimer_High_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define EncTimer_High_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define EncTimer_High_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define EncTimer_High_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define EncTimer_High_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << EncTimer_High_CTRL_INTCNT_SHIFT))
    #define EncTimer_High_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << EncTimer_High_CTRL_TRIG_MODE_SHIFT))
    #define EncTimer_High_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << EncTimer_High_CTRL_TRIG_EN_SHIFT))
    #define EncTimer_High_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << EncTimer_High_CTRL_CAP_MODE_SHIFT))
    #define EncTimer_High_CTRL_ENABLE                    ((uint8)((uint8)0x01u << EncTimer_High_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define EncTimer_High_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define EncTimer_High_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define EncTimer_High_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define EncTimer_High_STATUS_TC_INT_MASK_SHIFT       EncTimer_High_STATUS_TC_SHIFT
    #define EncTimer_High_STATUS_CAPTURE_INT_MASK_SHIFT  EncTimer_High_STATUS_CAPTURE_SHIFT
    #define EncTimer_High_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define EncTimer_High_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define EncTimer_High_STATUS_FIFOFULL_INT_MASK_SHIFT EncTimer_High_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define EncTimer_High_STATUS_TC                      ((uint8)((uint8)0x01u << EncTimer_High_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define EncTimer_High_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << EncTimer_High_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define EncTimer_High_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << EncTimer_High_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define EncTimer_High_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << EncTimer_High_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define EncTimer_High_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << EncTimer_High_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define EncTimer_High_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << EncTimer_High_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define EncTimer_High_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << EncTimer_High_STATUS_FIFOFULL_SHIFT))

    #define EncTimer_High_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define EncTimer_High_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define EncTimer_High_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define EncTimer_High_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define EncTimer_High_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define EncTimer_High_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_EncTimer_High_H */


/* [] END OF FILE */
