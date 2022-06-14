#ifndef UTILS_H
#define UTILS_H

#include <gbdk/platform.h>
#include "typedefs/MenuItem.h"

extern void initGfx() BANKED;
extern void initSound() BANKED;
extern void beep() BANKED;
extern void boop() BANKED;
extern void clonk() BANKED;
extern void clearBkg() BANKED;
extern void pause(uint8_t frames) BANKED;
extern void writeNumber(uint8_t x, uint8_t y, uint8_t length, uint8_t number) BANKED;
extern void dead() BANKED;
extern void hexChar(uint8_t *target, uint8_t value) BANKED;
extern void fadeIn() BANKED;
extern void fadeOut() BANKED;
extern void describeExposureTime(uint16_t exposureTime, uint8_t *target) BANKED;

inline uint8_t getMenuValue(MenuItem * menuItem) {
  return menuItem->options[menuItem->value].value;
}

#endif
