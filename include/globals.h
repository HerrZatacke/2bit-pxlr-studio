#ifndef GLOBALS_H
#define GLOBALS_H

#include <gbdk/platform.h>
#include "imageIndexing.h"

extern uint8_t mainLoopState;
extern uint8_t isCapturing;
extern uint8_t imageMenuIndex;
extern uint8_t imageInfo[360];
extern uint8_t imageIndex;
extern uint8_t numVisibleImages;
extern uint8_t sortedIndices[NUM_IMAGES];
extern uint8_t savedBank;

#endif
