/*******************************************************************************
* File Name: Timer.h  
* Version 3.0
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
    
#if !defined(CY_COUNTER_Timer_H)
#define CY_COUNTER_Timer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Timer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed Timer_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef Timer_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* Timer_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define Timer_Resolution            16u
#define Timer_UsingFixedFunction    1u
#define Timer_ControlRegRemoved     0u
#define Timer_COMPARE_MODE_SOFTWARE 0u
#define Timer_CAPTURE_MODE_SOFTWARE 0u
#define Timer_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    uint16 CounterUdb;         /* Current Counter Value */

    #if (!Timer_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!Timer_ControlRegRemoved) */

}Timer_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    Timer_Start(void) ;
void    Timer_Stop(void) ;
void    Timer_SetInterruptMode(uint8 interruptsMask) ;
uint8   Timer_ReadStatusRegister(void) ;
#define Timer_GetInterruptSource() Timer_ReadStatusRegister()
#if(!Timer_ControlRegRemoved)
    uint8   Timer_ReadControlRegister(void) ;
    void    Timer_WriteControlRegister(uint8 control) \
        ;
#endif /* (!Timer_ControlRegRemoved) */
#if (!(Timer_UsingFixedFunction && (CY_PSOC5A)))
    void    Timer_WriteCounter(uint16 counter) \
            ; 
#endif /* (!(Timer_UsingFixedFunction && (CY_PSOC5A))) */
uint16  Timer_ReadCounter(void) ;
uint16  Timer_ReadCapture(void) ;
void    Timer_WritePeriod(uint16 period) \
    ;
uint16  Timer_ReadPeriod( void ) ;
#if (!Timer_UsingFixedFunction)
    void    Timer_WriteCompare(uint16 compare) \
        ;
    uint16  Timer_ReadCompare( void ) \
        ;
#endif /* (!Timer_UsingFixedFunction) */

#if (Timer_COMPARE_MODE_SOFTWARE)
    void    Timer_SetCompareMode(uint8 compareMode) ;
#endif /* (Timer_COMPARE_MODE_SOFTWARE) */
#if (Timer_CAPTURE_MODE_SOFTWARE)
    void    Timer_SetCaptureMode(uint8 captureMode) ;
#endif /* (Timer_CAPTURE_MODE_SOFTWARE) */
void Timer_ClearFIFO(void)     ;
void Timer_Init(void)          ;
void Timer_Enable(void)        ;
void Timer_SaveConfig(void)    ;
void Timer_RestoreConfig(void) ;
void Timer_Sleep(void)         ;
void Timer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define Timer__B_COUNTER__LESS_THAN 1
#define Timer__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define Timer__B_COUNTER__EQUAL 0
#define Timer__B_COUNTER__GREATER_THAN 3
#define Timer__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define Timer__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define Timer_CMP_MODE_LT 1u
#define Timer_CMP_MODE_LTE 2u
#define Timer_CMP_MODE_EQ 0u
#define Timer_CMP_MODE_GT 3u
#define Timer_CMP_MODE_GTE 4u
#define Timer_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define Timer__B_COUNTER__NONE 0
#define Timer__B_COUNTER__RISING_EDGE 1
#define Timer__B_COUNTER__FALLING_EDGE 2
#define Timer__B_COUNTER__EITHER_EDGE 3
#define Timer__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define Timer_CAP_MODE_NONE 0u
#define Timer_CAP_MODE_RISE 1u
#define Timer_CAP_MODE_FALL 2u
#define Timer_CAP_MODE_BOTH 3u
#define Timer_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define Timer_CAPTURE_MODE_CONF       0u
#define Timer_INIT_PERIOD_VALUE       65535u
#define Timer_INIT_COUNTER_VALUE      65535u
#if (Timer_UsingFixedFunction)
#define Timer_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << Timer_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define Timer_INIT_COMPARE_VALUE      128u
#define Timer_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << Timer_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << Timer_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << Timer_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << Timer_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << Timer_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define Timer_DEFAULT_COMPARE_MODE    1u

#if( 0 != Timer_CAPTURE_MODE_CONF)
    #define Timer_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << Timer_CTRL_CAPMODE0_SHIFT))
#else    
    #define Timer_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != Timer_CAPTURE_MODE_CONF) */

#endif /* (Timer_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (Timer_UsingFixedFunction)
    #define Timer_STATICCOUNT_LSB     (*(reg16 *) Timer_CounterHW__CAP0 )
    #define Timer_STATICCOUNT_LSB_PTR ( (reg16 *) Timer_CounterHW__CAP0 )
    #define Timer_PERIOD_LSB          (*(reg16 *) Timer_CounterHW__PER0 )
    #define Timer_PERIOD_LSB_PTR      ( (reg16 *) Timer_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define Timer_COMPARE_LSB         (*(reg16 *) Timer_CounterHW__CNT_CMP0 )
    #define Timer_COMPARE_LSB_PTR     ( (reg16 *) Timer_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define Timer_COUNTER_LSB         (*(reg16 *) Timer_CounterHW__CNT_CMP0 )
    #define Timer_COUNTER_LSB_PTR     ( (reg16 *) Timer_CounterHW__CNT_CMP0 )
    #define Timer_RT1                 (*(reg8 *) Timer_CounterHW__RT1)
    #define Timer_RT1_PTR             ( (reg8 *) Timer_CounterHW__RT1)
#else
    
    #if (Timer_Resolution <= 8u) /* 8-bit Counter */
    
        #define Timer_STATICCOUNT_LSB     (*(reg8 *) \
            Timer_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define Timer_STATICCOUNT_LSB_PTR ( (reg8 *) \
            Timer_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define Timer_PERIOD_LSB          (*(reg8 *) \
            Timer_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define Timer_PERIOD_LSB_PTR      ( (reg8 *) \
            Timer_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define Timer_COMPARE_LSB         (*(reg8 *) \
            Timer_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define Timer_COMPARE_LSB_PTR     ( (reg8 *) \
            Timer_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define Timer_COUNTER_LSB         (*(reg8 *) \
            Timer_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define Timer_COUNTER_LSB_PTR     ( (reg8 *)\
            Timer_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #elif(Timer_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define Timer_STATICCOUNT_LSB     (*(reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define Timer_STATICCOUNT_LSB_PTR ( (reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define Timer_PERIOD_LSB          (*(reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define Timer_PERIOD_LSB_PTR      ( (reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define Timer_COMPARE_LSB         (*(reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define Timer_COMPARE_LSB_PTR     ( (reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define Timer_COUNTER_LSB         (*(reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define Timer_COUNTER_LSB_PTR     ( (reg16 *)\
                Timer_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define Timer_STATICCOUNT_LSB     (*(reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define Timer_STATICCOUNT_LSB_PTR ( (reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define Timer_PERIOD_LSB          (*(reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define Timer_PERIOD_LSB_PTR      ( (reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define Timer_COMPARE_LSB         (*(reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define Timer_COMPARE_LSB_PTR     ( (reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define Timer_COUNTER_LSB         (*(reg16 *) \
                Timer_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )  
            #define Timer_COUNTER_LSB_PTR     ( (reg16 *)\
                Timer_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(Timer_Resolution <= 24u) /* 24-bit Counter */
        
        #define Timer_STATICCOUNT_LSB     (*(reg32 *) \
            Timer_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define Timer_STATICCOUNT_LSB_PTR ( (reg32 *) \
            Timer_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define Timer_PERIOD_LSB          (*(reg32 *) \
            Timer_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define Timer_PERIOD_LSB_PTR      ( (reg32 *) \
            Timer_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define Timer_COMPARE_LSB         (*(reg32 *) \
            Timer_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define Timer_COMPARE_LSB_PTR     ( (reg32 *) \
            Timer_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define Timer_COUNTER_LSB         (*(reg32 *) \
            Timer_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define Timer_COUNTER_LSB_PTR     ( (reg32 *)\
            Timer_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define Timer_STATICCOUNT_LSB     (*(reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define Timer_STATICCOUNT_LSB_PTR ( (reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define Timer_PERIOD_LSB          (*(reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define Timer_PERIOD_LSB_PTR      ( (reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define Timer_COMPARE_LSB         (*(reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define Timer_COMPARE_LSB_PTR     ( (reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define Timer_COUNTER_LSB         (*(reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define Timer_COUNTER_LSB_PTR     ( (reg32 *)\
                Timer_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define Timer_STATICCOUNT_LSB     (*(reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define Timer_STATICCOUNT_LSB_PTR ( (reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define Timer_PERIOD_LSB          (*(reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define Timer_PERIOD_LSB_PTR      ( (reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define Timer_COMPARE_LSB         (*(reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define Timer_COMPARE_LSB_PTR     ( (reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define Timer_COUNTER_LSB         (*(reg32 *) \
                Timer_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )  
            #define Timer_COUNTER_LSB_PTR     ( (reg32 *)\
                Timer_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define Timer_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                Timer_CounterUDB_sC16_counterdp_u0__A0_REG )
				
    #define Timer_AUX_CONTROLDP0 \
        (*(reg8 *) Timer_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #define Timer_AUX_CONTROLDP0_PTR \
        ( (reg8 *) Timer_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (Timer_Resolution == 16 || Timer_Resolution == 24 || Timer_Resolution == 32)
       #define Timer_AUX_CONTROLDP1 \
           (*(reg8 *) Timer_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
       #define Timer_AUX_CONTROLDP1_PTR \
           ( (reg8 *) Timer_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (Timer_Resolution == 16 || Timer_Resolution == 24 || Timer_Resolution == 32) */
    
    #if (Timer_Resolution == 24 || Timer_Resolution == 32)
       #define Timer_AUX_CONTROLDP2 \
           (*(reg8 *) Timer_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
       #define Timer_AUX_CONTROLDP2_PTR \
           ( (reg8 *) Timer_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (Timer_Resolution == 24 || Timer_Resolution == 32) */
    
    #if (Timer_Resolution == 32)
       #define Timer_AUX_CONTROLDP3 \
           (*(reg8 *) Timer_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
       #define Timer_AUX_CONTROLDP3_PTR \
           ( (reg8 *) Timer_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (Timer_Resolution == 32) */

#endif  /* (Timer_UsingFixedFunction) */

#if (Timer_UsingFixedFunction)
    #define Timer_STATUS         (*(reg8 *) Timer_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define Timer_STATUS_MASK             (*(reg8 *) Timer_CounterHW__SR0 )
    #define Timer_STATUS_MASK_PTR         ( (reg8 *) Timer_CounterHW__SR0 )
    #define Timer_CONTROL                 (*(reg8 *) Timer_CounterHW__CFG0)
    #define Timer_CONTROL_PTR             ( (reg8 *) Timer_CounterHW__CFG0)
    #define Timer_CONTROL2                (*(reg8 *) Timer_CounterHW__CFG1)
    #define Timer_CONTROL2_PTR            ( (reg8 *) Timer_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define Timer_CONTROL3       (*(reg8 *) Timer_CounterHW__CFG2)
        #define Timer_CONTROL3_PTR   ( (reg8 *) Timer_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define Timer_GLOBAL_ENABLE           (*(reg8 *) Timer_CounterHW__PM_ACT_CFG)
    #define Timer_GLOBAL_ENABLE_PTR       ( (reg8 *) Timer_CounterHW__PM_ACT_CFG)
    #define Timer_GLOBAL_STBY_ENABLE      (*(reg8 *) Timer_CounterHW__PM_STBY_CFG)
    #define Timer_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) Timer_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define Timer_BLOCK_EN_MASK          Timer_CounterHW__PM_ACT_MSK
    #define Timer_BLOCK_STBY_EN_MASK     Timer_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define Timer_CTRL_ENABLE_SHIFT      0x00u
    #define Timer_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define Timer_CTRL_ENABLE            ((uint8)((uint8)0x01u << Timer_CTRL_ENABLE_SHIFT))         
    #define Timer_ONESHOT                ((uint8)((uint8)0x01u << Timer_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define Timer_CTRL_MODE_SHIFT        0x01u    
        #define Timer_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << Timer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define Timer_CTRL_MODE_SHIFT        0x00u    
        #define Timer_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << Timer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define Timer_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define Timer_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << Timer_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define Timer_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define Timer_STATUS_ZERO_INT_EN_MASK_SHIFT      (Timer_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define Timer_STATUS_ZERO            ((uint8)((uint8)0x01u << Timer_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define Timer_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)Timer_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define Timer_RT1_SHIFT            0x04u
    #define Timer_RT1_MASK             ((uint8)((uint8)0x03u << Timer_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define Timer_SYNC                 ((uint8)((uint8)0x03u << Timer_RT1_SHIFT))
    #define Timer_SYNCDSI_SHIFT        0x00u
    #define Timer_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << Timer_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define Timer_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << Timer_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !Timer_UsingFixedFunction */
    #define Timer_STATUS               (* (reg8 *) Timer_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define Timer_STATUS_PTR           (  (reg8 *) Timer_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define Timer_STATUS_MASK          (* (reg8 *) Timer_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define Timer_STATUS_MASK_PTR      (  (reg8 *) Timer_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define Timer_STATUS_AUX_CTRL      (*(reg8 *) Timer_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define Timer_STATUS_AUX_CTRL_PTR  ( (reg8 *) Timer_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define Timer_CONTROL              (* (reg8 *) Timer_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define Timer_CONTROL_PTR          (  (reg8 *) Timer_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define Timer_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define Timer_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define Timer_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define Timer_CTRL_CMPMODE_MASK      0x07u 
    #define Timer_CTRL_CAPMODE_MASK      0x03u  
    #define Timer_CTRL_RESET             ((uint8)((uint8)0x01u << Timer_CTRL_RESET_SHIFT))  
    #define Timer_CTRL_ENABLE            ((uint8)((uint8)0x01u << Timer_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define Timer_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define Timer_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define Timer_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define Timer_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define Timer_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define Timer_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define Timer_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Timer_STATUS_CMP_INT_EN_MASK_SHIFT       Timer_STATUS_CMP_SHIFT       
    #define Timer_STATUS_ZERO_INT_EN_MASK_SHIFT      Timer_STATUS_ZERO_SHIFT      
    #define Timer_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  Timer_STATUS_OVERFLOW_SHIFT  
    #define Timer_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT Timer_STATUS_UNDERFLOW_SHIFT 
    #define Timer_STATUS_CAPTURE_INT_EN_MASK_SHIFT   Timer_STATUS_CAPTURE_SHIFT   
    #define Timer_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  Timer_STATUS_FIFOFULL_SHIFT  
    #define Timer_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  Timer_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define Timer_STATUS_CMP             ((uint8)((uint8)0x01u << Timer_STATUS_CMP_SHIFT))  
    #define Timer_STATUS_ZERO            ((uint8)((uint8)0x01u << Timer_STATUS_ZERO_SHIFT)) 
    #define Timer_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << Timer_STATUS_OVERFLOW_SHIFT)) 
    #define Timer_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << Timer_STATUS_UNDERFLOW_SHIFT)) 
    #define Timer_STATUS_CAPTURE         ((uint8)((uint8)0x01u << Timer_STATUS_CAPTURE_SHIFT)) 
    #define Timer_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << Timer_STATUS_FIFOFULL_SHIFT))
    #define Timer_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << Timer_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Timer_STATUS_CMP_INT_EN_MASK            Timer_STATUS_CMP                    
    #define Timer_STATUS_ZERO_INT_EN_MASK           Timer_STATUS_ZERO            
    #define Timer_STATUS_OVERFLOW_INT_EN_MASK       Timer_STATUS_OVERFLOW        
    #define Timer_STATUS_UNDERFLOW_INT_EN_MASK      Timer_STATUS_UNDERFLOW       
    #define Timer_STATUS_CAPTURE_INT_EN_MASK        Timer_STATUS_CAPTURE         
    #define Timer_STATUS_FIFOFULL_INT_EN_MASK       Timer_STATUS_FIFOFULL        
    #define Timer_STATUS_FIFONEMP_INT_EN_MASK       Timer_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define Timer_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define Timer_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define Timer_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define Timer_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define Timer_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define Timer_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* Timer_UsingFixedFunction */

#endif  /* CY_COUNTER_Timer_H */


/* [] END OF FILE */

