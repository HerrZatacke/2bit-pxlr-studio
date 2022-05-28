// Original library by DragonEagles from http://shen.mansell.tripod.com/games/gameboy/gameboy.html
// Ported to GBDK 2020 by T0biasCZe
// Print Screen function added by Christianr
// Print Screen (360 tile mode) added by T0biasCZe

#ifndef PRINTCMD_H
#define PRINTCMD_H

#include <gbdk/platform.h>

extern void printerInit(void) BANKED;
extern unsigned char getPrinterStatus() BANKED;
extern void printImage(unsigned char *lower, unsigned char *upper, unsigned char bank) BANKED;
extern void printImageInfo(unsigned char *imageInfo, unsigned char *font) BANKED;
extern void waitPrinterReady() BANKED;

#endif
