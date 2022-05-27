#ifndef JOYPAD_H
#define JOYPAD_H

// global joypad store variable
extern unsigned char jp;
extern unsigned char jpCooldown;

extern void joypadConsumed() BANKED;
extern void waitRelease() BANKED;
extern void captureJoypadISR() BANKED;

#endif
