#ifndef UTILS_H
#define UTILS_H

#include <gbdk/platform.h>

extern void initGfx() BANKED;
extern void initSound() BANKED;
extern void beep() BANKED;
extern void boop() BANKED;
extern void clonk() BANKED;
extern void clearBkg() BANKED;
extern void pause(unsigned char frames) BANKED;
extern void writeNumber(unsigned char x, unsigned char y, unsigned char length, unsigned char number) BANKED;
extern void dead() BANKED;
extern void hexChar(unsigned char *target, unsigned char value) BANKED;
extern void fadeIn() BANKED;
extern void fadeOut() BANKED;

#endif
