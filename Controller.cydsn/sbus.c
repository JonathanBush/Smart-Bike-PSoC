#include "sbus.h"
#include "project.h"
#include <math.h>

#define SBUS_FAILSAFE_INACTIVE 0
#define SBUS_FAILSAFE_ACTIVE   1
#define SBUS_STARTBYTE         0x0f
#define SBUS_ENDBYTE           0x00

typedef unsigned char byte;

int _channels[18];
int _failsafe;
long _goodFrames;
long _lostFrames;
long _decoderErrorFrames;
int _readErrorState;

static byte buffer[25];
static byte buffer_index = 0;

CY_ISR_PROTO(sbus_recv);
void sbus_process();

void sbus_init() {
    buffer_index = 0;
    _readErrorState = 0;
    for (byte i = 0; i<18; i++) {
		_channels[i]      = 0;
	}
    _goodFrames         = 0;
	_lostFrames         = 0;
	_decoderErrorFrames = 0;
	_failsafe           = SBUS_FAILSAFE_ACTIVE;
}

void sbus_begin() {
    
    SBUS_Interrupt_StartEx(sbus_recv);
    SBUS_Interrupt_SetPriority(1);
    SBUS_UART_Start();
}

CY_ISR(sbus_recv) {

    buffer[buffer_index] = SBUS_UART_ReadRxData();
    
    if (buffer_index == 0 && buffer[0] != SBUS_STARTBYTE) return;
    
    if (++buffer_index == 25) {
        buffer_index = 0;
        if (buffer[0] == SBUS_STARTBYTE && buffer[24] == SBUS_ENDBYTE) {
            sbus_process();
            ++_goodFrames;
        } else {
            ++_decoderErrorFrames;
        }
        
    }
    
}

inline void sbus_process() {

	_channels[0]  = ((buffer[1]    |buffer[2]<<8)                 & 0x07FF);
	_channels[1]  = ((buffer[2]>>3 |buffer[3]<<5)                 & 0x07FF);
	_channels[2]  = ((buffer[3]>>6 |buffer[4]<<2 |buffer[5]<<10)  & 0x07FF);
	_channels[3]  = ((buffer[5]>>1 |buffer[6]<<7)                 & 0x07FF);
	_channels[4]  = ((buffer[6]>>4 |buffer[7]<<4)                 & 0x07FF);
	_channels[5]  = ((buffer[7]>>7 |buffer[8]<<1 |buffer[9]<<9)   & 0x07FF);
	_channels[6]  = ((buffer[9]>>2 |buffer[10]<<6)                & 0x07FF);
	_channels[7]  = ((buffer[10]>>5|buffer[11]<<3)                & 0x07FF);
	_channels[8]  = ((buffer[12]   |buffer[13]<<8)                & 0x07FF);
	_channels[9]  = ((buffer[13]>>3|buffer[14]<<5)                & 0x07FF);
	_channels[10] = ((buffer[14]>>6|buffer[15]<<2|buffer[16]<<10) & 0x07FF);
	_channels[11] = ((buffer[16]>>1|buffer[17]<<7)                & 0x07FF);
	_channels[12] = ((buffer[17]>>4|buffer[18]<<4)                & 0x07FF);
	_channels[13] = ((buffer[18]>>7|buffer[19]<<1|buffer[20]<<9)  & 0x07FF);
	_channels[14] = ((buffer[20]>>2|buffer[21]<<6)                & 0x07FF);
	_channels[15] = ((buffer[21]>>5|buffer[22]<<3)                & 0x07FF);

	((buffer[23])      & 0x0001) ? (_channels[16] = 2047) : (_channels[16] = 0);
	((buffer[23] >> 1) & 0x0001) ? (_channels[17] = 2047) : (_channels[17] = 0);

	if ((buffer[23] >> 3) & 0x0001) {
		_failsafe = SBUS_FAILSAFE_ACTIVE;
	} else {
		_failsafe = SBUS_FAILSAFE_INACTIVE;
	}

	if ((buffer[23] >> 2) & 0x0001) {
		_lostFrames++;
	}

}

int sbus_getChannel(int channel) {
	if (channel < 1 || channel > 18) {
		return 0;
	} else {
		return _channels[channel - 1];
	}
}


int sbus_getNormalizedChannel(int channel) {
	if (channel < 1 || channel > 18) {
		return 0;
	} else {
		//return lroundf((_channels[channel - 1] / 10.24)) - 100; //9.92 or 10.24?
        return lroundf((_channels[channel - 1] - 172) / 8.195) - 100;
	}
}

int sbus_getFailsafeStatus() {
	return _failsafe;
}

int sbus_getFrameLoss() {
	return (int) ((_lostFrames + _decoderErrorFrames) * 100 / (_goodFrames + _lostFrames + _decoderErrorFrames));
}

long sbus_getGoodFrames() {
	return _goodFrames;
}

long sbus_getLostFrames() {
	return _lostFrames;
}

long sbus_getDecoderErrorFrames() {
	return _decoderErrorFrames;
}
