// Original library by DragonEagles from http://shen.mansell.tripod.com/games/gameboy/gameboy.html
// Ported to GBDK 2020 by T0biasCZe
// Print Screen function added by Christianr
// Print Screen (360 tile mode) added by T0biasCZe

#pragma bank 1

#include <gb/gb.h>
#include <string.h>

/*
extern const unsigned char frame_pxlr_tiles[544];
extern const unsigned char frame_pxlr_map[360];
*/

unsigned char printerStatus[3];

#define PALETTE_NORMAL 0b11100100u
#define PALETTE_INVERTED 0b00011011u

#define MAGIC_1 0x88
#define MAGIC_2 0x33

#define COMMAND_INIT 0x01
#define COMMAND_PRINT 0x02
#define COMMAND_DATA 0x04
#define COMMAND_STATUS 0x0F

#define EXPOSURE_LIGHT 0x00
#define EXPOSURE_DEFAULT 0x40
#define EXPOSURE_DARK 0x7F

#define STATUS_LOWBAT 0x80
#define STATUS_ER2    0x40
#define STATUS_ER1    0x20
#define STATUS_ER0    0x10
#define STATUS_UNTRAN 0x08
#define STATUS_FULL   0x04
#define STATUS_BUSY   0x02
#define STATUS_SUM    0x01

const unsigned char PRINTER_INIT[] =   { 6, MAGIC_1, MAGIC_2, COMMAND_INIT,   0x00, 0x00, 0x00, };
const unsigned char PRINTER_STATUS[] = { 6, MAGIC_1, MAGIC_2, COMMAND_STATUS, 0x00, 0x00, 0x00, };
const unsigned char PRINTER_START[] =  { 6, MAGIC_1, MAGIC_2, COMMAND_PRINT,  0x00, 0x04, 0x00, }; // 0x04, 0x00 = length 4 Bytes
const unsigned char PRINTER_EOF[] =    { 6, MAGIC_1, MAGIC_2, COMMAND_DATA,   0x00, 0x00, 0x00, };
const unsigned char PRINT_TILE[] =     { 6, MAGIC_1, MAGIC_2, COMMAND_DATA,   0x00, 0x80, 0x02, }; // 0x80, 0x02 = length 640 Bytes

unsigned char tile_num, packet_num;

unsigned int CRC;

unsigned char sendPrinterByte(unsigned char byte) BANKED {
  unsigned char result;
  disable_interrupts();
  SB_REG = byte; //data to send
  SC_REG = 0x81; //1000 0001 - start, internal clock
  while (SC_REG & 0x80) {} //wait until b1 reset
  result = SB_REG; //return response stored in SB_REG
  enable_interrupts();
  return result;
}

void sendByte(unsigned char dataByte, unsigned char addToChecksum) BANKED {
  if (addToChecksum) {
    CRC += dataByte;
  }

  unsigned char result;
  result = sendPrinterByte(dataByte);
  printerStatus[0] = printerStatus[1];
  printerStatus[1] = printerStatus[2];
  printerStatus[2] = result;
}

void sendPrinterCommand(const unsigned char *command) BANKED {
  unsigned char length, index;
  index = 0;
  length = *command;
  CRC = 0;

  while (index < length) {
    index++;
    sendByte(*(command + index), index > 2);
  }
}


inline unsigned char getHigh(unsigned int w) {
  return (w & 0xFF00u) >> 8;
}

inline unsigned char getLow(unsigned int w) {
  return (w & 0xFFu);
}


void sendChecksum() BANKED {
  sendByte(getLow(CRC), FALSE);
  sendByte(getHigh(CRC), FALSE);
  sendByte(0x00, FALSE);
  sendByte(0x00, FALSE);
}

void printerInit() BANKED {
  tile_num = 0;
  packet_num = 0;
  sendPrinterCommand(PRINTER_INIT);
  sendChecksum();
}

unsigned char checkLinkCable() BANKED {
  if (printerStatus[0] != 0) {
    return 2;
  }
  if ((printerStatus[1] & 0xF0) != 0x80) {
    return 2;
  }
  return 0;
}

unsigned char getPrinterStatus() BANKED {
  sendPrinterCommand(PRINTER_STATUS);
  sendChecksum();
  return checkLinkCable();
}

unsigned char checkForErrors() BANKED {
  if (printerStatus[2] & STATUS_LOWBAT) {
    return 1;
  }
  if (printerStatus[2] & STATUS_ER2) {
    return 2;
  }
  if (printerStatus[2] & STATUS_ER1) {
    return 3;
  }
  if (printerStatus[2] & STATUS_ER0) {
    return 4;
  }
  if (printerStatus[2] & STATUS_SUM) {
    return 5;
  }
  return 0;
}

unsigned char printerBusy() BANKED {
  sendPrinterCommand(PRINTER_STATUS);
  sendChecksum();
  return (printerStatus[2] & STATUS_BUSY);
}


void waitPrinterReady() BANKED {
  // Wait for max 30s to give the printer time to become ready.
  // If not ready after 30s, return anyway to not hang the program
  for (unsigned int wait = 0; wait < 1800; wait++) {
    wait_vbl_done();
    if (!printerBusy()) {
      return;
    }
  }
}


void printTileData(const unsigned char *tileData, unsigned char num_packets, unsigned char margins, unsigned char palette, unsigned char exposure) BANKED {
  unsigned char tileIndex;

  if (tile_num == 0) {
    sendPrinterCommand(PRINT_TILE);
  }

  tile_num++;

  for (tileIndex = 0; tileIndex < 16; tileIndex++) {
    sendByte(tileData[tileIndex], TRUE);
  }

  // two lines of 20 tiles each
  if (tile_num == 40) {
    sendChecksum();

    tile_num = 0;
    packet_num++;

    if (packet_num == num_packets) { // all done the page
      packet_num = 0;
      sendPrinterCommand(PRINTER_EOF); // data end packet
      sendChecksum();

      sendPrinterCommand(PRINTER_START);
      sendByte(0x01, TRUE); // Sheets
      sendByte(margins, TRUE); // Margin
      sendByte(palette, TRUE); // Palette (normal=0xE4, inverted=0x1B)
      sendByte(exposure, TRUE); // Exposure/Intensity (min=0x00, default=0x40, max=0x7F)
      sendChecksum();

      // Wait for max 2s to give the printer time to become "busy".
      // If not busy after 2s, return anyway to not hang the program
      for (unsigned char wait = 0; wait < 120; wait++) {
        wait_vbl_done();
        if (printerBusy()) {
          return;
        }
      }

    }
  }
}

void printImage(unsigned char *lower, unsigned char *upper, unsigned char bank) BANKED {
  printerInit();
  SWITCH_RAM(bank);
  // We need to print a border of 16x16 pixels (2x2 tiles)
  unsigned char x, y;
  unsigned int frameTileIndex = 0;

  unsigned char *image = upper;
  for (y = 0; y < 18; y++) {
    for (x = 0; x < 20; x++) {
      if (x == 0 && y == 9) {
        image = lower;
      }
      if (x < 2 || y < 2 || x >= 18 || y >= 16) {
/*
        printTileData(&frame_pxlr_tiles[frame_pxlr_map[frameTileIndex] * 16], 9, 0x02, PALETTE_NORMAL, EXPOSURE_DEFAULT);
*/
      } else {
        printTileData(image, 9, 0x03, PALETTE_NORMAL, EXPOSURE_DEFAULT);
        image += 16;
      }

      frameTileIndex++;
    }
  }
}

void printImageInfo(unsigned char *imageInfo, unsigned char *font) BANKED {
  unsigned int index;
  printerInit();

/*
  for (index = 0; index < 40; index++) {
    printTileData(&frame_pxlr_tiles[frame_pxlr_map[index] * 16], 1, 0x00, PALETTE_INVERTED, EXPOSURE_DEFAULT);
  }
*/

  waitPrinterReady();
  printerInit();

/*
  for (index = 0; index < 360; index++) {
    printTileData(&font[(imageInfo[index] - 32) * 16], 9, 0x00, PALETTE_INVERTED, EXPOSURE_DARK);
  }
*/


  waitPrinterReady();
  printerInit();

/*
  for (index = 320; index < 360; index++) {
    printTileData(&frame_pxlr_tiles[frame_pxlr_map[index] * 16], 1, 0x03, PALETTE_INVERTED, EXPOSURE_DEFAULT);
  }
*/
}
