#ifndef JOYPAD_H
#define JOYPAD_H

#include <gbdk/platform.h>

// global joypad store variable
extern uint8_t jp;
extern uint8_t jpCooldown;

extern void joypadConsumed() BANKED;
extern void waitRelease() BANKED;
extern void captureJoypadISR() BANKED;

#endif
