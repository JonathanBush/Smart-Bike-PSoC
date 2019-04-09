/*******************************************************************************
* File Name: Seat_MUX.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the AMuxSeq.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUXSEQ_Seat_MUX_H)
#define CY_AMUXSEQ_Seat_MUX_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Seat_MUX_MUX_SINGLE 1
#define Seat_MUX_MUX_DIFF   2
#define Seat_MUX_MUXTYPE    2


/***************************************
*        Function Prototypes
***************************************/

void Seat_MUX_Start(void);
void Seat_MUX_Init(void);
void Seat_MUX_Stop(void);
#if (Seat_MUX_MUXTYPE == Seat_MUX_MUX_DIFF)
void Seat_MUX_Next(void);
void Seat_MUX_DisconnectAll(void);
#else
/* The Next and DisconnectAll functions are declared in cyfitter_cfg.h. */
/* void Seat_MUX_Next(void); */
/* void Seat_MUX_DisconnectAll(void); */
#endif
int8 Seat_MUX_GetChannel(void);


/***************************************
*           Global Variables
***************************************/

extern uint8 Seat_MUX_initVar;


/***************************************
*         Parameter Constants
***************************************/
#define Seat_MUX_CHANNELS 3


#endif /* CY_AMUXSEQ_Seat_MUX_H */


/* [] END OF FILE */
