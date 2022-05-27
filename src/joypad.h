#ifndef JOYPAD_H
#define JOYPAD_H

// global joypad store variable
extern unsigned char jp;
extern unsigned char jpCooldown;

extern void joypadConsumed();
extern void waitRelease();
extern void captureJoypadISR();

#endif
