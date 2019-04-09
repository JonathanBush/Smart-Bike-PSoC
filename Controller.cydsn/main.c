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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "project.h"
#include "sbus.h"
#define MIN_THROTTLE_VOLTAGE 0.902
#define MAX_THROTTLE_VOLTAGE 4.0
// 3.659

#define CUTOFF_CH 5
#define THROTTLE_CH 1
#define STEERING_CH 2
#define BRAKE_CH 3

#define MAX_BRAKE_VAL (6500)
#define MIN_BRAKE_VAL (2300)

#define MOTOR_MAX_COMPARE (2200)
#define MOTOR_CUTOFF  (300)


/* power between 0 and 1 */
void set_throttle(float power);
void set_brake(float brake);
///void set_steering(int setpoint);

CY_ISR_PROTO(control_loop);

volatile int steeringTarget;



int main(void)
{
    PWM_Steer_WriteCompare(0);
    steeringTarget = 0;
    char sendStr[50];
    CyGlobalIntEnable; /* Enable interrupts. */
    //float speed;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Throttle_Start();
    
    Handle_Encoder_Start();
    Handle_Encoder_SetCounter(0);
    
    PWM_Brake_Start();
    PWM_Steer_Start();
    Opamp_Throttle_Start();
    
    sbus_init();
    
    //sbus_begin();
    CyDelay(50); // Wait for the SBUS to receive data
    //USBUART_1_Init();
    //USBUART_1_Start(0, USBUART_1_5V_OPERATION); // Start the USB UART
    //while(!USBUART_1_bGetConfiguration());
    //USBUART_1_CDC_Init();
    
    Control_Loop_Interrupt_StartEx(control_loop);
    Timer_1_Enable();
    Timer_1_Start();
    
    
    for(;;)
    {
        
        if (sbus_getNormalizedChannel(CUTOFF_CH) < 0 && !sbus_getFailsafeStatus()) { // cutoff switch is not thrown, not in failsafe
            steeringTarget = sbus_getNormalizedChannel(STEERING_CH);
            if (sbus_getNormalizedChannel(BRAKE_CH) > -5) { // brake is not applied
                set_brake(0);
                set_throttle((float)(sbus_getNormalizedChannel(THROTTLE_CH) + 100) / 200.);
                
            } else { // brake is applied
                set_throttle(0);
                set_brake(((float)sbus_getNormalizedChannel(BRAKE_CH))/-100.0);
                // braking action here
            }
        } else {
            //steeringTarget = 0;
            set_throttle(0);
            set_brake(.7);
            // emergency braking and actions
        }
        
//        if (USBUART_1_DataIsReady()) {
//            steeringTarget = ((int)((signed char)USBUART_1_GetChar() - (signed char)127) * 100) / (int)127;
//        }
        

        //CyDelay(50);
        //sprintf(sendStr, "%ld\n\n", sbus_getDecoderErrorFrames());
        //sprintf(sendStr, "%04d %04d\r", Handle_Encoder_GetCounter(), steeringTarget);
        
        //USBUART_1_PutString("hello");
        //USBUART_1_PutString(sendStr);
        //CyDelay(100);        

    }
}

void inline set_throttle(float power)
{
    Throttle_SetValue((char)(255.0 * (((MAX_THROTTLE_VOLTAGE - MIN_THROTTLE_VOLTAGE) * power + MIN_THROTTLE_VOLTAGE)/4.096)));
}

void inline set_brake(float brake) {
    PWM_Brake_WriteCompare(MIN_BRAKE_VAL + (int)((MAX_BRAKE_VAL-MIN_BRAKE_VAL)*brake));
}


static const float Kp = 3.0;
static const float Ki = 0.0;
static const float Kd = 0;//-0.05;//0.05;
static const float dt = 0.02;

static int previous_error = 0;
static float integral = 0;
static float derivative = 0;


CY_ISR(control_loop)
{
    Timer_1_ReadStatusRegister();
    //steeringTarget = sbus_getNormalizedChannel(STEERING_CH);
    steeringTarget = 0;
    int error = 3*steeringTarget - Handle_Encoder_GetCounter();
    integral += error * dt;
    derivative = (error - previous_error) / dt;
    int output = (int)(Kp*error + Ki*integral + Kd*derivative);
    previous_error = error;
    
    Steering_Direction_Write(output < 0);
    output = (abs(output) > MOTOR_MAX_COMPARE) ? MOTOR_MAX_COMPARE : abs(output);
    if (output < MOTOR_CUTOFF) output = 0;
    PWM_Steer_WriteCompare(output);
    
}

/* [] END OF FILE */
