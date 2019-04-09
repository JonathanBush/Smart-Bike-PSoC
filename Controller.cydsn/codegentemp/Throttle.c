/*******************************************************************************
* File Name: Throttle.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Throttle.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 Throttle_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 Throttle_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static Throttle_backupStruct Throttle_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Throttle_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Throttle_Init(void) 
{
    Throttle_CR0 = (Throttle_MODE_V );

    /* Set default data source */
    #if(Throttle_DEFAULT_DATA_SRC != 0 )
        Throttle_CR1 = (Throttle_DEFAULT_CNTL | Throttle_DACBUS_ENABLE) ;
    #else
        Throttle_CR1 = (Throttle_DEFAULT_CNTL | Throttle_DACBUS_DISABLE) ;
    #endif /* (Throttle_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(Throttle_DEFAULT_STRB != 0)
        Throttle_Strobe |= Throttle_STRB_EN ;
    #endif/* (Throttle_DEFAULT_STRB != 0) */

    /* Set default range */
    Throttle_SetRange(Throttle_DEFAULT_RANGE); 

    /* Set default speed */
    Throttle_SetSpeed(Throttle_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: Throttle_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Throttle_Enable(void) 
{
    Throttle_PWRMGR |= Throttle_ACT_PWR_EN;
    Throttle_STBY_PWRMGR |= Throttle_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(Throttle_restoreVal == 1u) 
        {
             Throttle_CR0 = Throttle_backup.data_value;
             Throttle_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Throttle_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  Throttle_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Throttle_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(Throttle_initVar == 0u)
    { 
        Throttle_Init();
        Throttle_initVar = 1u;
    }

    /* Enable power to DAC */
    Throttle_Enable();

    /* Set default value */
    Throttle_SetValue(Throttle_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: Throttle_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Throttle_Stop(void) 
{
    /* Disble power to DAC */
    Throttle_PWRMGR &= (uint8)(~Throttle_ACT_PWR_EN);
    Throttle_STBY_PWRMGR &= (uint8)(~Throttle_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        Throttle_backup.data_value = Throttle_CR0;
        Throttle_CR0 = Throttle_CUR_MODE_OUT_OFF;
        Throttle_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Throttle_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Throttle_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    Throttle_CR0 &= (uint8)(~Throttle_HS_MASK);
    Throttle_CR0 |=  (speed & Throttle_HS_MASK);
}


/*******************************************************************************
* Function Name: Throttle_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Throttle_SetRange(uint8 range) 
{
    Throttle_CR0 &= (uint8)(~Throttle_RANGE_MASK);      /* Clear existing mode */
    Throttle_CR0 |= (range & Throttle_RANGE_MASK);      /*  Set Range  */
    Throttle_DacTrim();
}


/*******************************************************************************
* Function Name: Throttle_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Throttle_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 Throttle_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    Throttle_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        Throttle_Data = value;
        CyExitCriticalSection(Throttle_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Throttle_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Throttle_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((Throttle_CR0 & Throttle_RANGE_MASK) >> 2) + Throttle_TRIM_M7_1V_RNG_OFFSET;
    Throttle_TR = CY_GET_XTND_REG8((uint8 *)(Throttle_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
