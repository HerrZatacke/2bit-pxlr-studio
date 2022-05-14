// Original library by DragonEagles from http://shen.mansell.tripod.com/games/gameboy/gameboy.html
// Ported to GBDK 2020 by T0biasCZe
// Print Screen function added by Christianr
// Print Screen (360 tile mode) added by T0biasCZe

#include <gb/gb.h>

extern unsigned char printerStatus[3];

extern void printerInit(void);
extern void sendByte(unsigned char byte);
extern void sendPrinterCommand(unsigned char *command);
extern uint8_t checkLinkCable();
extern uint8_t getPrinterStatus();
extern uint8_t checkForErrors();
extern void printTileData(unsigned char *tileData, uint8_t lf, uint8_t num_packets);
//extern uint8_t checkBusy();
//extern void printScreen(uint8_t linefeed);
extern void printImage(uint8_t *lower, uint8_t *upper);
