#ifndef SAVEIMAGE_H
#define SAVEIMAGE_H

#include <gbdk/platform.h>

extern void saveImage(uint8_t capt, uint8_t edExOpGain, uint16_t expTime, uint8_t edRInvVref, uint8_t zeroVout, uint8_t ditherSet, uint8_t contrast) BANKED;
extern void saveImageDialog(uint8_t capt, uint8_t edExOpGain, uint16_t expTime, uint8_t edRInvVref, uint8_t zeroVout, uint8_t ditherSet, uint8_t contrast) BANKED;

#endif
