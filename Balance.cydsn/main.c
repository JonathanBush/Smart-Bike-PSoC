/* ========================================
 *
 * This program provides the interface between the
 * high-level control performed on the Raspberry Pi
 * and the sensors and actuators on the Smart Bike.
 *
 * Copyright Arizona State University, 2018
 * All Rights Reserved
 *
 * By Jonathan Bush
 * Arizona State University
 * Ira A. Fulton Schools of Engineering
 * The Polytechnic School
 *
 * Robotics and Intelligent Systems Laboratory
 * Smart Bike
 * Dr. Wenlong Zhang
 *
 * ========================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "project.h"
#include "sbus.h"

//#define DEBUG

#define TEST_SPEED 2.0

#define MIN_THROTTLE_VOLTAGE 0.902
#define MAX_THROTTLE_VOLTAGE 4.0
// 3.659

/* emergency cutoff */
#define CUTOFF_CH 5
/* throttle */
#define THROTTLE_CH 1
#define STEERING_CH 2
#define BRAKE_CH 3
#define LOG_CH 6
#define SPEED_FIX_CH 7
#define KP_CH 8
#define KI_CH 9
#define KD_CH 10
#define BC_ENABLE_CH 11

//#define MAX_BRAKE_VAL (6500)
//#define MIN_BRAKE_VAL (2300)

#define MAX_BRAKE_VAL (4600)
#define MIN_BRAKE_VAL (2500)

#define MOTOR_MAX_COMPARE (2200)
#define MOTOR_CUTOFF  (250)


/* power between 0 and 1 */
void set_throttle(float power);
void set_brake(float brake);

CY_ISR_PROTO(steering_control_loop);
CY_ISR_PROTO(speed_control_loop);
CY_ISR_PROTO(rear_hall_isr);
CY_ISR_PROTO(front_hall_isr);
CY_ISR_PROTO(timer_isr);
CY_ISR_PROTO(rpi_tx_isr);

volatile int steeringTarget;
volatile int rpi_steeringTarget;
volatile uint16 speedTarget;
volatile float speedValue;
uint16 speed_r;  // speed in m/s * 4096
uint16 speed_f;
int hall_ct;
volatile uint32 time_r;
volatile uint32 time_f;

void send_data();

int main(void)
{
    PWM_Steer_WriteCompare(0);
    
    
    CyGlobalIntEnable; /* Enable interrupts. */
    //float speed;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Throttle_Start();
    
    Handle_Encoder_Start();
    Handle_Encoder_SetCounter(0);
    
    PWM_Steer_Start();
    PWM_Brake_Start();
    Opamp_Throttle_Start();

    VDAC8_1_Start();
    UART_Start();
    
    sbus_init();
    sbus_begin();
    
    speed_r = 0;
    speed_f = 0;
    hall_ct = 0;
    time_r = 0;
    time_f = 0;

    Control_Loop_Interrupt_StartEx(steering_control_loop);
    Speed_Control_Interrupt_StartEx(speed_control_loop);
    Rpi_Tx_Interrupt_StartEx(rpi_tx_isr);    
    
    CyDelay(10000);
    steeringTarget = 0;
    rpi_steeringTarget = 0;
    speedTarget = 0;
    speedValue = 0;
    
    Hall_Interrupt_Rear_StartEx(rear_hall_isr);
    Hall_Interrupt_Front_StartEx(front_hall_isr);
    Timer_Interrupt_StartEx(timer_isr);
    
    Steering_Timer_Start();    // Start the control loop
    Speed_Timer_Start();
    //uint8 loopCt = 0;
    for(;;)
    {
        if (sbus_getNormalizedChannel(CUTOFF_CH) < 0 && !sbus_getFailsafeStatus()) { // cutoff switch is not thrown, not in failsafe
            if (sbus_getNormalizedChannel(BC_ENABLE_CH) >= 0) { // if balance control not enabled
                steeringTarget = 3 * sbus_getNormalizedChannel(STEERING_CH);
            } else {
                steeringTarget = rpi_steeringTarget + (int)(sbus_getNormalizedChannel(KI_CH) / 10.0);      
            }
            if (sbus_getNormalizedChannel(BRAKE_CH) > -5) { // brake is not applied
                set_brake(0);
                if (sbus_getNormalizedChannel(SPEED_FIX_CH) < 0) {
                    speedTarget = (int)(4096.0 * TEST_SPEED);
                    //speedTarget = (10240 * (sbus_getNormalizedChannel(KI_CH) + 100)) / 200;
                } else {
                    speedTarget = (uint16)(((uint32)32189ul*((uint32)sbus_getNormalizedChannel(THROTTLE_CH) + 100ul)) / 200ul);
                }
                //set_throttle((float)(sbus_getNormalizedChannel(THROTTLE_CH) + 100) / 200.);
                
            } else { // brake is applied
                //set_throttle(0);
                speedTarget = 0;
                set_brake(((float)sbus_getNormalizedChannel(BRAKE_CH))/-100.0);
                // braking action here
            }
        } else {
            //steeringTarget = 0;
            speedTarget = 0;
            //set_throttle(0);
            set_brake(.7);
            // emergency braking and actions
        }
            
        #ifdef DEBUG
        char sendStr[20];
        sprintf(sendStr, "%d\n\r", speed_r);
        UART_PutString(sendStr);
        #endif
        #ifndef DEBUG
        send_data();
        #endif        
        
        if (!SW_Read() || sbus_getNormalizedChannel(BC_ENABLE_CH) > 50) {
            Handle_Encoder_SetCounter(steeringTarget);
        }
        CyDelay(10);

    }
    
}

void send_data()
{
    UART_PutChar(0xC3); // startbyte
    
    UART_PutChar((uint8)((int)sbus_getNormalizedChannel(LOG_CH) + 127));
    UART_PutChar((uint8)((int)sbus_getNormalizedChannel(BC_ENABLE_CH) + 127));
                
    UART_PutChar(speed_r >> 8);     // speed
    UART_PutChar(speed_r & 0x00FF);
    uint16 steeringEncoder = (uint16)(Handle_Encoder_GetCounter() + 32768);
    UART_PutChar(steeringEncoder >> 8);     // steering angle
    UART_PutChar(steeringEncoder & 0x00FF);
    
    /* send the values for the balance PID controller */
    UART_PutChar((uint8)((int)sbus_getNormalizedChannel(KP_CH) + 127));
    UART_PutChar((uint8)((int)0 + 127));
    UART_PutChar((uint8)((int)sbus_getNormalizedChannel(KD_CH) + 127));
    
    //UART_PutChar((uint8)((int)sbus_getNormalizedChannel(BC_ENABLE_CH)));
}


int SameSign(int x, int y)
{
    return (x >= 0) ^ (y < 0);
}

void inline set_throttle(float power)
{
    Throttle_SetValue((char)(255.0 * (((MAX_THROTTLE_VOLTAGE - MIN_THROTTLE_VOLTAGE) * power + MIN_THROTTLE_VOLTAGE)/4.096)));
}

void inline set_brake(float brake) {
    PWM_Brake_WriteCompare(MIN_BRAKE_VAL + (int)((MAX_BRAKE_VAL-MIN_BRAKE_VAL)*brake));
    //PWM_Brake_WriteCompare(MAX_BRAKE_VAL - (int)((MAX_BRAKE_VAL-MIN_BRAKE_VAL)*brake));
}

/* Control loop for speed control, 10 Hz */
CY_ISR(speed_control_loop)
{
    static const float Kp = 2e-6;  //8e-7
    static const float Ki = 4e-10;
    static const float Kd = 6e-7;
    static const float dt = 0.02;
    
    static int previous_error = 0;
    static float integral = 0;
    static float derivative = 0;
    
    static uint16 speed_reading = 0;
    
    Speed_Timer_ReadStatusRegister();
    
    speed_reading = (uint16)(((uint32)speed_reading + (uint32)speed_r + (uint32)speed_r) / (uint32)3ul);
    
    //speedTarget = 10240;
    
    if (speedTarget > 100) {
//        if (speed_reading < 100 && speedValue == 0) {
//            speedValue = ((float)speedTarget + 15255.0) / 48565.0 ;
//        } else {
            int error = (speedTarget - speed_reading) * dt;
            integral += error * dt;
            derivative = (error - previous_error) / dt;
            float output = (Kp * error + Ki * integral + Kd*derivative);
            previous_error = error;
            float temp = speedValue + output;
            if (temp < 0.0) {
                temp = 0.0;
            } else if (temp > 1.0) {
                temp = 1.0;
            }
            speedValue = temp;
//        }
    } else {
        previous_error = 0.0;
        integral = 0.0;
        speedValue = 0;
    }
    
    set_throttle(speedValue);
//    if (speedTarget > 1700) {
//        set_throttle(((float)speedTarget + 15255.0) / 48565.0 );
//    } else {
//        set_throttle(0.0);
//    }
    
    
}

/* PID control loop for steering control, 100Hz */
CY_ISR(steering_control_loop)
{
    static const float Kp = 11.0;
    static const float Ki = 8.0;
    static const float Kd = 0.5;
    static const float dt = 0.01;

    static int previous_error = 0;
    //static int previous_encoder = 0;
    static float integral = 0;
    static float derivative = 0;
    
    //Control_Loop_Interrupt_ClearPending();
    Steering_Timer_ReadStatusRegister();
    
    int error = steeringTarget - Handle_Encoder_GetCounter();
    integral += error * dt;
    derivative = (error - previous_error) / dt;
    int output = (int)(Kp*error + Ki*integral + Kd*derivative);
    previous_error = error;
    
    Steering_Dir_Write(output < 0);
    output = (abs(output) > MOTOR_MAX_COMPARE) ? MOTOR_MAX_COMPARE : abs(output);
    if (output < MOTOR_CUTOFF) output = 0;
//    if ((output > MOTOR_MAX_COMPARE - 10 && abs(Handle_Encoder_GetCounter() - previous_encoder) < 2)) {
//        output = 0;
//        integral = 0;
//    }
    PWM_Steer_WriteCompare(output);
    //previous_encoder = Handle_Encoder_GetCounter();
   
}

/* Triggered on rising edge of rear hall effect sensor output */
CY_ISR(rear_hall_isr) {
    TestPin_Write(!TestPin_Read());
    const uint32 multiplier = 2832657; // (C)(1000)(4096)/3, C=2.0747m
    speed_r = (uint16)(multiplier / time_r);;
    time_r = 0;
}

/* Triggered on rising edge of front hall effect sensor output */
CY_ISR(front_hall_isr) {
    const uint32 multiplier = 2878396;  //(C)(1000)(4096)/3, C=2.108m
    speed_f = (uint16)(multiplier / time_f);
    time_f = 0;
}
    
/* Triggered every millisecond */
CY_ISR(timer_isr) {
    if(++time_r > 3000ul) {
        time_r = 0;
        speed_r = 0;
    }
    if (++time_f > 3000ul) {
        time_f = 0;
        speed_f = 0;
    }
}

CY_ISR(rpi_tx_isr) {
    rpi_steeringTarget = 3*(((signed int)UART_GetChar() - 127) * 100) / 127;
}

/* [] END OF FILE */
