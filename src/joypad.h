#ifndef JOYPAD_H
#define JOYPAD_H

// global joypad store variable
extern unsigned char jp;
extern unsigned char jpCooldown;

extern void joypadConsumed() BANKED OLDCALL;
extern void waitRelease() BANKED OLDCALL;
extern void captureJoypadISR() BANKED OLDCALL;

#endif
