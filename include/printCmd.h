// Original library by DragonEagles from http://shen.mansell.tripod.com/games/gameboy/gameboy.html
// Ported to GBDK 2020 by T0biasCZe
// Print Screen function added by Christianr
// Print Screen (360 tile mode) added by T0biasCZe

#ifndef PRINTCMD_H
#define PRINTCMD_H

#include <gbdk/platform.h>

extern void printerInit(void) BANKED;
extern uint8_t getPrinterStatus() BANKED;
extern void printImage(uint8_t *lower, uint8_t *upper, uint8_t bank) NONBANKED;
extern void printImageInfo(uint8_t *imageInfo, uint8_t *font) NONBANKED;
extern void waitPrinterReady() BANKED;

#endif
