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

/*
 * Notes: Gimbal encoder is 980 cpr
 * Accounting for 18:24 gear ratio, each gimbal revolution is 1306.67 counts
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "project.h"
#include "bno055.h"

#define GIMBAL_MAX_COMPARE (2200)
#define GIMBAL_MOTOR_CUTOFF  (20)

#define STEERING_MAX_COMPARE (2200)
#define STEERING_MOTOR_CUTOFF  (260)

#define signum(X) ((X > 0) ? 1 : ((X < 0) ? -1 : 0))

CY_ISR_PROTO(gimbal_control_loop);
CY_ISR_PROTO(steering_control_loop);
CY_ISR_PROTO(timer_isr);
CY_ISR_PROTO(enc_high_isr);
CY_ISR_PROTO(enc_low_isr);

const uint16 gimbal_pwm_low = 100;
const uint16 gimbal_pwm_high = 200;
const uint16 gimbal_pwm_target = 132;//132; //143; //120

const int16 gimbal_max = 180;
const int16 gimbal_min = -180;

volatile int steeringTarget;    // steering setpoint in encoder counts
volatile float phi_w;           // gimbal angular position
volatile float phi_w_dot;       // gimbal angular velocity in rad/s
volatile float phi_b;
volatile float phi_b_dot;
volatile float speed_reading;   // measured gimbal angular velocity in rad/s

const int gimbal_enc_min = -217;
const int gimbal_enc_max = 217;

const float phi_w_dot_max = 11.5;

uint16 high_ctr = 1;
uint16 low_ctr = 1;

float alpha();  /* the gimbal angle */
float cmg_pid();

euler_angles orientation;   /* orientation data read from the IMU */

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    PWM_CMG_Start();
    PWM_CMG_WriteCompare1(gimbal_pwm_low);
    
    LED1_Write(0);
    
    phi_w_dot = 0;  // set gimbal angular velocity to 0

    Gimbal_Encoder_Start();
    Gimbal_Encoder_SetCounter(0);
    
    steeringTarget = 0;
    Handle_Encoder_Start();
    Handle_Encoder_SetCounter(0);
    PWM_Steer_Start();
    
    Gimbal_Control_Loop_Interrupt_StartEx(gimbal_control_loop);
    Steering_Control_Loop_Interrupt_StartEx(steering_control_loop);
    Timer_Interrupt_StartEx(timer_isr); // start the timer interrupt for gimbal speed measurement
    
    Gimbal_Timer_Start();   // timers control the control loop frequencies
    Steering_Timer_Start();
    
    bno_init(OPERATION_MODE_IMUPLUS, BNO_RADIANS);
    
    for(;;)
    {
        LED1_Write(0);
        
        bno_update(&orientation);   // read the orienation
        
        phi_b = orientation.roll;// - 0.02;
        uint8 phi_b_dot_lsb = bno_read(BNO055_EULER_R_LSB_ADDR);
        uint8 phi_b_dot_msb = bno_read(BNO055_EULER_R_MSB_ADDR);
        phi_b_dot = (float)((int16)((uint16)phi_b_dot_msb << 8 | (uint16)phi_b_dot_lsb)) / BNO_RADIANS;
        
        while (SW1_Read()) {
            phi_w_dot = -0.2 * signum(alpha()) / fabs(cos(alpha()));
        }
        CyDelay(500);
        //while (!SW1_Read());
        
#define FLYWHEEL_ENABLE        
#ifdef FLYWHEEL_ENABLE
        for (uint16 comp = gimbal_pwm_low + 10; comp <= gimbal_pwm_target; ++comp) {
            PWM_CMG_WriteCompare1(comp);
            LED1_Write(1);
            CyDelay(500);
            LED1_Write(0);
            CyDelay(500);
            if (SW1_Read()) {
                break;
            }
        }
        CyDelay(10000);
#endif
        LED1_Write(1);
        
        char reset_flag = 0;

#define BALANCE_PID
 
        /* Sliding Mode control for CMG balancing */
#ifndef BALANCE_PID
        while (!SW1_Read()) {
            //phi_w_dot = M_PI;
            //float phi_w_dot_temp = fabs(12.65 * phi_b + 5.56 * phi_b_dot) * signum(3.0 * phi_b + phi_b_dot);// * 9.5493;
            
            if (phi_b < 0.02 && phi_b > -0.02) {
                phi_w_dot = -0.07 * signum(alpha()) / fabs(cos(alpha()));
                reset_flag = 0;
            } else if (reset_flag || Gimbal_Encoder_GetCounter() > gimbal_max || Gimbal_Encoder_GetCounter() < gimbal_min) {
                phi_w_dot = -0.2 * signum(alpha()) / fabs(cos(alpha()));
                reset_flag = (fabs(alpha()) > 0.02);
            } else {
                float phi_w_dot_temp = -fabs(21.0 * phi_b + 4.0 * phi_b_dot) * signum(3.0 * phi_b + phi_b_dot);   // * 9.5493;
                
                if (fabs(phi_w_dot_temp) > phi_w_dot_max) {
                    phi_w_dot_temp = phi_w_dot_max * signum(phi_w_dot_temp);
                }
                phi_w_dot = phi_w_dot_temp;
            }
        }
#endif

        /* PID control for CMG balancing */
#ifdef BALANCE_PID
        
        while (!SW1_Read()) {
            phi_w_dot = cmg_pid();
            CyDelay(10);
        }
#endif
        phi_w_dot = 0;

        PWM_CMG_WriteCompare1(gimbal_pwm_low);
        
        LED1_Write(0);
        //UART_Stop();

        //while (!SW1_Read());
        CyDelay(1000);
        
    }
    
}

float cmg_pid()
{
    static const float Kp = 20;
    static const float Ki = 0.0;
    static const float Kd = 2.2;
    static const float dt = 0.01;

    //static float previous_error = 0;
    static float integral = 0;
    static float derivative = 0;
    
    float error = 0 - phi_b;
    integral += error * dt;
    derivative = phi_b_dot;
    float output = (Kp*error + Ki*integral + Kd*derivative);
    //previous_error = error;
    
    return output;
    
}

/* 10 kHz */
CY_ISR(timer_isr) {
    static int time_since_change = 0;
    static int last_encoder = 0;
    int new_encoder;
    ++time_since_change;
    new_encoder = Gimbal_Encoder_GetCounter();
    if (new_encoder != last_encoder) {
        speed_reading = (last_encoder - new_encoder) * 38.45 / (float)time_since_change;    //48.07
        last_encoder = new_encoder;
        time_since_change = 0;
    } else if (time_since_change > 4000) {
        speed_reading = 0;
        time_since_change = 0;
    }
}

/* velocity PID control loop for gimbal control, 1000Hz */
CY_ISR(gimbal_control_loop)
{
    static const float Kp = .8;
    static const float Ki = 0.02;
    static const float Kd = 0.002;
    static const float dt = 0.002;

    static float previous_error = 0;
    static float integral = 0;
    static float derivative = 0;
    
    static float speedValue = 0;
    
    Gimbal_Timer_ReadStatusRegister();

    float speedTarget = phi_w_dot;
    float error = (speedTarget - speed_reading) * dt;
    integral += error * dt;
    derivative = (error - previous_error) / dt;
    float output = (Kp * error + Ki * integral + Kd*derivative);
    previous_error = error;
    float temp = speedValue + output;
    if (temp < -1.0) {
        temp = -1.0;
    } else if (temp > 1.0) {
        temp = 1.0;
    }
    speedValue = temp;
    
    gimbal_direction_Write(speedValue < 0);
    
    int gimbal_motor_compare = (int)((float)GIMBAL_MAX_COMPARE * fabs(speedValue));
    
    if (gimbal_motor_compare < GIMBAL_MOTOR_CUTOFF) gimbal_motor_compare = 0;
    
    /* limit gimbal motion */
#ifdef BALANCE_PID
    if (speedValue > 0 && Gimbal_Encoder_GetCounter() < gimbal_min) {
        gimbal_motor_compare = 0;
        integral = 0;
    } else if (speedValue < 0 && Gimbal_Encoder_GetCounter() > gimbal_max) {
        gimbal_motor_compare = 0;
        integral = 0;
    }
#endif

    PWM_CMG_WriteCompare2(gimbal_motor_compare);
   
}

CY_ISR(steering_control_loop)
{
    static const float Kp = 10.0;
    static const float Ki = 4.0;
    static const float Kd = 0.5;
    static const float dt = 0.01;

    static int previous_error = 0;
    //static int previous_encoder = 0;
    static float integral = 0;
    static float derivative = 0;
    
    Steering_Timer_ReadStatusRegister();
    
    int error = steeringTarget - Handle_Encoder_GetCounter();
    integral += error * dt;
    derivative = (error - previous_error) / dt;
    int output = (int)(Kp*error + Ki*integral + Kd*derivative);
    previous_error = error;
    
    Steering_Dir_Write(output > 0);
    output = (abs(output) > STEERING_MAX_COMPARE) ? STEERING_MAX_COMPARE : abs(output);
    if (output < STEERING_MOTOR_CUTOFF) output = 0;
//    if ((output > MOTOR_MAX_COMPARE - 10 && abs(Handle_Encoder_GetCounter() - previous_encoder) < 2)) {
//        output = 0;
//        integral = 0;
//    }
    PWM_Steer_WriteCompare(output);
    //previous_encoder = Handle_Encoder_GetCounter();
   
}



float alpha()
{
    return 6.2832 * low_ctr / high_ctr;
    //return -(float)Gimbal_Encoder_GetCounter() * 0.004807; // M_PI * 2 / 1307
}

CY_ISR(enc_high_isr) {
    high_ctr = 65535 - EncTimer_ReadCounter();
    EncTimer_WriteCounter(65535);
}

CY_ISR(enc_low_isr) {
    low_ctr = 65535 - EncTimer_ReadCounter();
    
}

/* [] END OF FILE */
