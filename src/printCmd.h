// Original library by DragonEagles from http://shen.mansell.tripod.com/games/gameboy/gameboy.html
// Ported to GBDK 2020 by T0biasCZe
// Print Screen function added by Christianr
// Print Screen (360 tile mode) added by T0biasCZe

#include <gb/gb.h>
#include <string.h>

extern unsigned char printerStatus[3];

extern void printerInit(void);
extern unsigned char sendPrinterByte(unsigned char byte);
extern void sendByte(unsigned char dataByte, unsigned char addToChecksum);
extern void sendChecksum();
extern void sendPrinterCommand(unsigned char *command);
extern unsigned char checkLinkCable();
extern unsigned char getPrinterStatus();
extern unsigned char checkForErrors();
extern void printTileData(unsigned char *tileData, unsigned char lf, unsigned char num_packets);
extern unsigned char printerBusy();
extern void printImage(unsigned char *lower, unsigned char *upper, unsigned char bank);
extern void printImageInfo(unsigned char *imageInfo, unsigned char *font);
