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
#define BNO055_ID (0xA0)

//volatile euler_angles orientation = {.roll = 0, .pitch = 0, .yaw = 0};

int bno_init(uint8 mode) {
    CyDelay(3000);
    uint8_t id = bno_read(BNO055_CHIP_ID_ADDR);
    if (id != BNO055_ID) {
        CyDelay(1000); // hold on for boot
        id = bno_read(BNO055_CHIP_ID_ADDR);
        if (id != BNO055_ID) {
            return 0; // still not? ok bail
        }
    }
    
    bno_write(BNO055_OPR_MODE_ADDR, OPERATION_MODE_CONFIG);
    CyDelay(600);
    bno_write(BNO055_SYS_TRIGGER_ADDR, 0x20);   // reset
    CyDelay(1000);
    while (bno_read(BNO055_CHIP_ID_ADDR) != BNO055_ID) {
        CyDelay(100);
    }
    CyDelay(600);
    
    bno_write(BNO055_PWR_MODE_ADDR, POWER_MODE_NORMAL);
    CyDelay(100);
    
    bno_write(BNO055_PAGE_ID_ADDR, 0);
    CyDelay(100);
    
    bno_write(BNO055_SYS_TRIGGER_ADDR, 0x00);   // 0x80 = use external crystal / 0x00 = use internal crystal
    CyDelay(200);
    
    bno_write(BNO055_OPR_MODE_ADDR, mode);
    CyDelay(600);
    
    return 1;
    
}

/* writes a single byte register */
void bno_write(uint8 reg, uint8 data) {
    uint8 status = I2C_MasterSendStart(DEVICE_ADDRESS, I2C_WRITE_XFER_MODE);
    if (status == I2C_MSTR_NO_ERROR) {
        I2C_MasterWriteByte(reg);
        LED_Write(0);
        I2C_MasterWriteByte(data);
    }
    
    I2C_MasterSendStop();
    
}

/* reads a single byte register */
uint8 bno_read(uint8 reg) {
    uint8 status = I2C_MasterSendStart(DEVICE_ADDRESS, I2C_WRITE_XFER_MODE);
    I2C_MasterWriteByte(reg);
    I2C_MasterSendRestart(DEVICE_ADDRESS, I2C_READ_XFER_MODE);
    uint8 data = I2C_MasterReadByte(I2C_NAK_DATA);
    I2C_MasterSendStop();
    return data;
}

/* read data register into rdData buffer */
void bno_readbuf(uint8 reg, uint8 * rdData, uint8 cnt) {
    uint8 status = I2C_MasterSendStart(DEVICE_ADDRESS, 0);
    //if (status == I2C_MSTR_NO_ERROR) {
        I2C_MasterWriteByte(reg);
        I2C_MasterReadBuf(DEVICE_ADDRESS, rdData, cnt, I2C_MODE_COMPLETE_XFER);
        I2C_MasterSendStop();
    //}
}

void bno_update(euler_angles * orientation) {
    uint8 buffer[6];
    //bno_readbuf(VECTOR_GYROSCOPE, buffer, 6);
    buffer[0] = bno_read(BNO055_EULER_H_LSB_ADDR);
    buffer[1] = bno_read(BNO055_EULER_H_MSB_ADDR);
    buffer[2] = bno_read(BNO055_EULER_R_LSB_ADDR);
    buffer[3] = bno_read(BNO055_EULER_R_MSB_ADDR);
    buffer[4] = bno_read(BNO055_EULER_P_LSB_ADDR);
    buffer[5] = bno_read(BNO055_EULER_P_MSB_ADDR);
    //buffer[5] = 0;
    orientation->yaw   = (int16)((uint16)buffer[1] << 8 | (uint16)buffer[0]) / 16.0;
    orientation->roll  = (int16)((uint16)buffer[3] << 8 | (uint16)buffer[2]) / 16.0;
    orientation->pitch = (int16)((uint16)buffer[5] << 8 | (uint16)buffer[4]) / 16.0;   
}

/* [] END OF FILE */
