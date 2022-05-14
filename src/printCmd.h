// Original library by DragonEagles from http://shen.mansell.tripod.com/games/gameboy/gameboy.html
// Ported to GBDK 2020 by T0biasCZe			
// Print Screen function added by Christianr
// Print Screen (360 tile mode) added by T0biasCZe

#include <gb/gb.h>

extern unsigned char PrinterStatus[3];

extern void PrinterInit (void);
extern void SendByte(unsigned char byte);
extern void SendPrinterCommand(unsigned char *Command);
extern int CheckLinkCable();
extern int GetPrinterStatus();
extern int CheckForErrors();
extern void PrintTileData(unsigned char *TileData, uint8_t lf, uint8_t num_packets);
extern uint8_t CheckBusy();
extern void PrintScreen(uint8_t linefeed);
extern void PrintImage(uint8_t* lower, uint8_t* upper);
