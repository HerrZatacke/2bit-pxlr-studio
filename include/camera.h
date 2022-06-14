#ifndef CAMERA_H
#define CAMERA_H

extern void setDitherMatrix(uint8_t ditherSet, uint8_t contrast) BANKED;
extern void initCam() BANKED;
extern void capture(uint8_t capt, uint8_t edExOpGain, uint16_t expTime, uint8_t edRInvVref, uint8_t zeroVout) BANKED;

#endif
