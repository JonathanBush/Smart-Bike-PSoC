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
#include "bno055.h"
#include <stdio.h>

#define STARTBYTE 0xFF
#define ENDBYTE 0x77

#define OVERSAMPLING (10)

CY_ISR_PROTO(sample_isr);
CY_ISR_PROTO(enc_high_isr);
CY_ISR_PROTO(enc_low_isr);

volatile int take_sample = 0;

struct packet {
    uint8 startbyte;
    uint8 checksum;
    int16 channels[3];
};

void set_checksum(struct packet *pkt)
{
    uint8 *data = (uint8 *)(&(pkt->channels[0]));
    uint8 checksum = 0;
    for (int i = 0; i < 6; ++i) {
        checksum = (uint8)(((uint16)checksum + (uint16)data[i]) % 255);
    }
    pkt->checksum = checksum;
}

CY_ISR(sample_isr) {
    Sample_Timer_ReadStatusRegister();
    take_sample = 1;
}

CY_ISR(enc_high_isr) {
    
}

CY_ISR(enc_low_isr) {
    
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    struct packet data = {.startbyte = STARTBYTE};
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Seat_ADC_Start();

    USBUART_Init();
    USBUART_CDC_Init();
    USBUART_Start(0, USBUART_5V_OPERATION);
    
    Sample_Interrupt_StartEx(sample_isr);
    Sample_Timer_Start();
    
    char output[40];
    
    
    bno_init();
    
    
    for(;;)
    {
        
        bno_update();
        LED_Write(0);
        sprintf(output, "h: %3.3f, r: %3.3f, p: %3.3f\n\r", orientation.yaw, orientation.roll, orientation.pitch);
        USBUART_PutString(output);
        CyDelay(100);
//        if (take_sample) {
//            int32 accumulator[3];
//            
//            take_sample = 0;
//            LED_Write(!LED_Read());
//            
//            
//            for (int i = 0; i < 3; ++i) {
//                accumulator[i] = 0;
//            }
//            for (int i = 0; i < OVERSAMPLING; ++i) {
//                    Seat_ADC_StartConvert();
//                    Seat_ADC_IsEndConversion(Seat_ADC_WAIT_FOR_RESULT);
//                    
//                for (int n = 0; n < 3; ++n) {
//                    accumulator[n] += Seat_ADC_GetResult16(n);
//                    
//                }
//            }
//            for (int i = 0; i < 3; ++i) {
//                data.channels[i] = (int16)(accumulator[i] / OVERSAMPLING);
//            }
//            
//            set_checksum(&data);
//            
//            if (USBUART_CDCIsReady()) {
//                USBUART_PutData((uint8 *)&data, sizeof(struct packet));
//                //sprintf(output, "a: %4d, b: %4d, c: %4d\n\r", data.channels[0], data.channels[1], data.channels[2]);
//                //USBUART_PutString(output);
//            }
//        }
    }
        
}

/* [] END OF FILE */
