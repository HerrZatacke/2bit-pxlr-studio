#ifndef UTILS_H
#define UTILS_H

#include <gbdk/platform.h>

extern void init_gfx() BANKED OLDCALL;
extern void init_sound() BANKED OLDCALL;
extern void beep() BANKED OLDCALL;
extern void boop() BANKED OLDCALL;
extern void clonk() BANKED OLDCALL;
extern void clearBkg() BANKED OLDCALL;
extern void pause(unsigned char frames) BANKED OLDCALL;
extern void writeNumber(unsigned char x, unsigned char y, unsigned char length, unsigned char number) BANKED OLDCALL;
extern void dead() BANKED OLDCALL;

#endif
