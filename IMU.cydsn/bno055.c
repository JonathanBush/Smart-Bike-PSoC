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

#define DEVICE_ADDRESS 0x28

volatile euler_angles orientation = {.roll = 0, .pitch = 0, .yaw = 0};

void bno_init() {
    I2C_Start();
    CyDelay(1000);
    LED_Write(1);
    bno_write(BNO055_PWR_MODE_ADDR, POWER_MODE_NORMAL);
    bno_write(BNO055_OPR_MODE_ADDR, OPERATION_MODE_IMUPLUS);
}

/* writes a single byte register */
void bno_write(uint8 reg, uint8 data) {
    I2C_MasterSendStart(DEVICE_ADDRESS, 0);
    
    I2C_MasterWriteByte(reg);
    
    I2C_MasterWriteByte(data);
    
    I2C_MasterSendStop();
    
}

/* reads a single byte register */
uint8 bno_read(uint8 reg) {
    I2C_MasterSendStart(DEVICE_ADDRESS, 0);
    I2C_MasterWriteByte(reg);
    I2C_MasterSendStart(DEVICE_ADDRESS, 1);
    uint8 data = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
    return data;
}

/* read data register into rdData buffer */
void bno_readbuf(uint8 reg, uint8 * rdData, uint8 cnt) {
    I2C_MasterSendStart(DEVICE_ADDRESS, 0);
    I2C_MasterWriteByte(reg);
    I2C_MasterReadBuf(DEVICE_ADDRESS, rdData, cnt, I2C_MODE_COMPLETE_XFER);
}

void bno_update() {
    uint8 buffer[6];
    bno_readbuf(BNO055_EULER_H_LSB_ADDR, buffer, 6);
    orientation.yaw   = (int16)((uint16)buffer[1] << 8 | (uint16)buffer[0]) / 900.0;
    orientation.roll  = (int16)((uint16)buffer[3] << 8 | (uint16)buffer[2]) / 900.0;
    orientation.pitch = (int16)((uint16)buffer[5] << 8 | (uint16)buffer[4]) / 900.0;   
}

/* [] END OF FILE */
