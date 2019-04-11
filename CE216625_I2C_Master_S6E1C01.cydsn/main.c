/*******************************************************************************
* File: main.c
* 
* Version : 1.10
*
* Description: 
*   This application demonstrates I2C communication between a master (this
*   project) and slave (CE216626_I2C_Slave_S6E1C). The master periodically
*   sends an on/off command to the slave, which controls an LED accordingly.
*
*   The LED on the master is used to indicate an error condition.
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include "project.h"


/*******************************************************************************
* Defines for LED and I2C communication
*******************************************************************************/
#define LED_ON              (0u)
#define LED_OFF             (1u)

#define I2C_SLAVE_ADDR      (0x10u)
#define I2C_SLAVE_ADDR_W    (I2C_SLAVE_ADDR | 0u)
#define I2C_SLAVE_ADDR_R    (I2C_SLAVE_ADDR | 1u)
#define PULLUP              (1u)


/*******************************************************************************
* Function Name: simpledelay
********************************************************************************
*
* Summary:
*  simpledelay function uses a volatile variable to implement a blocking delay
*  of about one half of a second.
* 
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void simpledelay( void )
{
    /* 
    __CLKMO is the CPU clock frequency and the loop contains 5 instructions
    (in debug configuration) and so dividing by ten produces a 0.5s delay
    (approximately). The variable is declared volatile to disable optimization.
    */ 
    volatile uint32_t period = __CLKMO / 10;
    
    while( --period )
    {
        /* Do nothing */
    }
}


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1: Initialize the master LED (off)
*   2: Select the I2C pins and enable pull-up resistors
*   3: Initialize the MFS block for I2C
*   4: Send the slave address
*   5: Start a transmit communication
*   6: Send the one-byte command
*   7: Complete the transmit communication
*   8: Toggle the master LED
*   9: Change the command
*   10: Send another command (step #4)
* 
* Parameters:
*  None.
*
* Return:
*  Not used.
*
*******************************************************************************/
int main(void)
{
    uint8_t command = LED_ON;       /* Byte of data to send to the slave */
    
    /* Initialize the LED pin as digital output, initially off */
    Green_LED_GpioInitOut( LED_OFF );

    /* Select the I2C pins and enable pull-up resistors in P12 and P13 */
    Master_SetPinFunc_SCL();
    Master_SetPinFunc_SDA();
    
    bFM_GPIO_PCR1_P2 = PULLUP;
    bFM_GPIO_PCR1_P3 = PULLUP;
    
    /* Initialize the MFS block for I2C */
    while( Ok != Mfs_I2c_Init( &Master_HW, &Master_Config ) )
    {
        /* Light the LED to indicate an error condition */
        Green_LED_GpioPut( LED_ON );
        /* Loop forever - ErrorInvalidParameter */
    }
    
    for(;;)
    {       
        /* Send I2C slave address to select the target I2C device */
        while( Ok != Mfs_I2c_SendData( &Master_HW, I2C_SLAVE_ADDR_W ) )
        {
            /* Light the LED to indicate an error condition */
            Green_LED_GpioPut( LED_ON );
            /* Loop forever - ErrorInvalidParameter */
        }        
        
        /* Start the packet communication */
        while( Ok != Mfs_I2c_GenerateStart( &Master_HW ) )
        {
            /* Light the LED to indicate an error condition */
            Green_LED_GpioPut( LED_ON );
            /* Loop forever - ErrorInvalidParameter or ErrorTimeout */
        }         
          
        /* Wait for the transmit buffer to be empty */
        while( FALSE == Mfs_I2c_GetStatus( &Master_HW, I2cTxEmpty ) )
        {
            /* Do nothing - wait for completion */
        }
        
        /* Send the command byte */
        while( Ok != Mfs_I2c_SendData( &Master_HW, command ) )
        {
            /* Light the LED to indicate an error condition */
            Green_LED_GpioPut( LED_ON );
            /* Loop forever - ErrorInvalidParameter */
        } 

        /* Wait for the transmission to complete */
        while( FALSE == Mfs_I2c_GetStatus( &Master_HW, I2cTxEmpty ) )
        {
            /* Do nothing - wait for completion */
        }
            
        /* Complete the transaction */
        while( Mfs_I2c_GenerateStop( &Master_HW ) )
        {
            /* Light the LED to indicate an error condition */
            Green_LED_GpioPut( LED_ON );
            /* Loop forever - ErrorInvalidParameter */
        } 
                
        /* Wait for the stop command to complete */     
        while( FALSE == Mfs_I2c_GetStatus( &Master_HW, I2cStopDetect ) )
        {
            /* Do nothing - wait for completion */
        }
        
        /* Make the master and slave LEDs blink together */
        Green_LED_GpioPut( command );        
    
        /* Toggle the command */
        command = ( command == LED_ON ) ? LED_OFF : LED_ON;
        
        /* Wait a while before sending a new command */
        simpledelay();
    }
}

/* [] END OF FILE */
