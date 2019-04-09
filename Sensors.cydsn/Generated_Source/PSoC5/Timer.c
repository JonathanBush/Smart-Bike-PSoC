/*******************************************************************************
* File Name: Timer.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

#include "Timer.h"

uint8 Timer_initVar = 0u;


/*******************************************************************************
* Function Name: Timer_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_Init(void) 
{
        #if (!Timer_UsingFixedFunction && !Timer_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!Timer_UsingFixedFunction && !Timer_ControlRegRemoved) */
        
        #if(!Timer_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 Timer_interruptState;
        #endif /* (!Timer_UsingFixedFunction) */
        
        #if (Timer_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            Timer_CONTROL &= Timer_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                Timer_CONTROL2 &= ((uint8)(~Timer_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                Timer_CONTROL3 &= ((uint8)(~Timer_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (Timer_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                Timer_CONTROL |= Timer_ONESHOT;
            #endif /* (Timer_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            Timer_CONTROL2 |= Timer_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            Timer_RT1 &= ((uint8)(~Timer_RT1_MASK));
            Timer_RT1 |= Timer_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            Timer_RT1 &= ((uint8)(~Timer_SYNCDSI_MASK));
            Timer_RT1 |= Timer_SYNCDSI_EN;

        #else
            #if(!Timer_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = Timer_CONTROL & ((uint8)(~Timer_CTRL_CMPMODE_MASK));
            Timer_CONTROL = ctrl | Timer_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = Timer_CONTROL & ((uint8)(~Timer_CTRL_CAPMODE_MASK));
            
            #if( 0 != Timer_CAPTURE_MODE_CONF)
                Timer_CONTROL = ctrl | Timer_DEFAULT_CAPTURE_MODE;
            #else
                Timer_CONTROL = ctrl;
            #endif /* 0 != Timer_CAPTURE_MODE */ 
            
            #endif /* (!Timer_ControlRegRemoved) */
        #endif /* (Timer_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!Timer_UsingFixedFunction)
            Timer_ClearFIFO();
        #endif /* (!Timer_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        Timer_WritePeriod(Timer_INIT_PERIOD_VALUE);
        #if (!(Timer_UsingFixedFunction && (CY_PSOC5A)))
            Timer_WriteCounter(Timer_INIT_COUNTER_VALUE);
        #endif /* (!(Timer_UsingFixedFunction && (CY_PSOC5A))) */
        Timer_SetInterruptMode(Timer_INIT_INTERRUPTS_MASK);
        
        #if (!Timer_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)Timer_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            Timer_WriteCompare(Timer_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Timer_interruptState = CyEnterCriticalSection();
            
            Timer_STATUS_AUX_CTRL |= Timer_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(Timer_interruptState);
            
        #endif /* (!Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Timer_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void Timer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Timer_UsingFixedFunction)
        Timer_GLOBAL_ENABLE |= Timer_BLOCK_EN_MASK;
        Timer_GLOBAL_STBY_ENABLE |= Timer_BLOCK_STBY_EN_MASK;
    #endif /* (Timer_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!Timer_ControlRegRemoved || Timer_UsingFixedFunction)
        Timer_CONTROL |= Timer_CTRL_ENABLE;                
    #endif /* (!Timer_ControlRegRemoved || Timer_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: Timer_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  Timer_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Timer_Start(void) 
{
    if(Timer_initVar == 0u)
    {
        Timer_Init();
        
        Timer_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    Timer_Enable();        
}


/*******************************************************************************
* Function Name: Timer_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void Timer_Stop(void) 
{
    /* Disable Counter */
    #if(!Timer_ControlRegRemoved || Timer_UsingFixedFunction)
        Timer_CONTROL &= ((uint8)(~Timer_CTRL_ENABLE));        
    #endif /* (!Timer_ControlRegRemoved || Timer_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (Timer_UsingFixedFunction)
        Timer_GLOBAL_ENABLE &= ((uint8)(~Timer_BLOCK_EN_MASK));
        Timer_GLOBAL_STBY_ENABLE &= ((uint8)(~Timer_BLOCK_STBY_EN_MASK));
    #endif /* (Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Timer_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_SetInterruptMode(uint8 interruptsMask) 
{
    Timer_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: Timer_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   Timer_ReadStatusRegister(void) 
{
    return Timer_STATUS;
}


#if(!Timer_ControlRegRemoved)
/*******************************************************************************
* Function Name: Timer_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   Timer_ReadControlRegister(void) 
{
    return Timer_CONTROL;
}


/*******************************************************************************
* Function Name: Timer_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    Timer_WriteControlRegister(uint8 control) 
{
    Timer_CONTROL = control;
}

#endif  /* (!Timer_ControlRegRemoved) */


#if (!(Timer_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: Timer_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void Timer_WriteCounter(uint16 counter) \
                                   
{
    #if(Timer_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (Timer_GLOBAL_ENABLE & Timer_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        Timer_GLOBAL_ENABLE |= Timer_BLOCK_EN_MASK;
        CY_SET_REG16(Timer_COUNTER_LSB_PTR, (uint16)counter);
        Timer_GLOBAL_ENABLE &= ((uint8)(~Timer_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(Timer_COUNTER_LSB_PTR, counter);
    #endif /* (Timer_UsingFixedFunction) */
}
#endif /* (!(Timer_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: Timer_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 Timer_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(Timer_UsingFixedFunction)
		(void)CY_GET_REG16(Timer_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(Timer_COUNTER_LSB_PTR_8BIT);
	#endif/* (Timer_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(Timer_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Timer_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(Timer_STATICCOUNT_LSB_PTR));
    #endif /* (Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Timer_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 Timer_ReadCapture(void) 
{
    #if(Timer_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Timer_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(Timer_STATICCOUNT_LSB_PTR));
    #endif /* (Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Timer_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_WritePeriod(uint16 period) 
{
    #if(Timer_UsingFixedFunction)
        CY_SET_REG16(Timer_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(Timer_PERIOD_LSB_PTR, period);
    #endif /* (Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Timer_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 Timer_ReadPeriod(void) 
{
    #if(Timer_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Timer_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(Timer_PERIOD_LSB_PTR));
    #endif /* (Timer_UsingFixedFunction) */
}


#if (!Timer_UsingFixedFunction)
/*******************************************************************************
* Function Name: Timer_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void Timer_WriteCompare(uint16 compare) \
                                   
{
    #if(Timer_UsingFixedFunction)
        CY_SET_REG16(Timer_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(Timer_COMPARE_LSB_PTR, compare);
    #endif /* (Timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Timer_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 Timer_ReadCompare(void) 
{
    return (CY_GET_REG16(Timer_COMPARE_LSB_PTR));
}


#if (Timer_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Timer_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Timer_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    Timer_CONTROL &= ((uint8)(~Timer_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    Timer_CONTROL |= compareMode;
}
#endif  /* (Timer_COMPARE_MODE_SOFTWARE) */


#if (Timer_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Timer_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Timer_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    Timer_CONTROL &= ((uint8)(~Timer_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    Timer_CONTROL |= ((uint8)((uint8)captureMode << Timer_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (Timer_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: Timer_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void Timer_ClearFIFO(void) 
{

    while(0u != (Timer_ReadStatusRegister() & Timer_STATUS_FIFONEMP))
    {
        (void)Timer_ReadCapture();
    }

}
#endif  /* (!Timer_UsingFixedFunction) */


/* [] END OF FILE */

