/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <string.h>
#include <stdio.h>

#define STARTBYTE ((uint8)0xAA)
#define REAR_SPEED_IDENT        ((uint8)0x01)
#define FRONT_SPEED_IDENT       ((uint8)0x02)
#define HAND_THROTTLE_IDENT     ((uint8)0x03)
#define REMOTE_THROTTLE_IDENT   ((uint8)0x04)
#define REMOTE_STEERING_IDENT   ((uint8)0x05)
#define REMOTE_BRAKE_IDENT      ((uint8)0x06)
#define PEDAL_HALL_IDENT        ((uint8)0x07)
#define STEERING_ANGLE_IDENT    ((uint8)0x08)

CY_ISR_PROTO(rear_hall_isr);

uint16 speed;  // speed in m/s * 4096
uint16 time;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char sendStr[50];
    
    speed = 0;

    USBUART_1_Start(0, USBUART_1_5V_OPERATION); // Start the USB UART
    while(!USBUART_1_bGetConfiguration());
    USBUART_1_CDC_Init();
    
    Timer_Start();
    Hall_Interrupt_StartEx(rear_hall_isr);
    
    for(;;)
    {
        CyDelay(100);
        const uint32 multiplier = 8497971; // (C)(1000)(4096), C=2.0747m
        speed = (uint16)(multiplier / (uint32)time);
        USBUART_1_PutChar(STARTBYTE);
        USBUART_1_PutChar(REAR_SPEED_IDENT);
        USBUART_1_PutData((uint8 *)&speed, 2);
        //sprintf(sendStr, "%d\n\r", speed);
        //USBUART_1_PutString(sendStr);
        
        /* Place your application code here. */
    }
}

CY_ISR(rear_hall_isr) {
    time = Timer_ReadCounter(); // time in ms since last
    Timer_WriteCounter(0);  // Clear the counter
}
    

/* [] END OF FILE */
