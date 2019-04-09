#ifndef SBUS_h
#define SBUS_h

/* intialize the SBUS */
void sbus_init();

/* Start receiving SBUS data */
void sbus_begin();

/* Get the last read value for this channel */
int sbus_getChannel(int channel);

/* Get the channel value between -100 and 100 */
int sbus_getNormalizedChannel(int channel);

int sbus_getFailsafeStatus();
int sbus_getFrameLoss();
long sbus_getGoodFrames();
long sbus_getLostFrames();
long sbus_getDecoderErrorFrames();





#endif