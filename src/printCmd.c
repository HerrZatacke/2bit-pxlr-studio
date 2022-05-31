// Original library by DragonEagles from http://shen.mansell.tripod.com/games/gameboy/gameboy.html
// Ported to GBDK 2020 by T0biasCZe
// Print Screen function added by Christianr
// Print Screen (360 tile mode) added by T0biasCZe

#pragma bank 1

#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>
#include "frame_pxlr.h"
#include "font.h"

uint8_t printerStatus[3];

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

const uint8_t PRINTER_INIT[] =   { 6, MAGIC_1, MAGIC_2, COMMAND_INIT,   0x00, 0x00, 0x00, };
const uint8_t PRINTER_STATUS[] = { 6, MAGIC_1, MAGIC_2, COMMAND_STATUS, 0x00, 0x00, 0x00, };
const uint8_t PRINTER_START[] =  { 6, MAGIC_1, MAGIC_2, COMMAND_PRINT,  0x00, 0x04, 0x00, }; // 0x04, 0x00 = length 4 Bytes
const uint8_t PRINTER_EOF[] =    { 6, MAGIC_1, MAGIC_2, COMMAND_DATA,   0x00, 0x00, 0x00, };
const uint8_t PRINT_TILE[] =     { 6, MAGIC_1, MAGIC_2, COMMAND_DATA,   0x00, 0x80, 0x02, }; // 0x80, 0x02 = length 640 Bytes

uint8_t tile_num, packet_num;

uint16_t CRC;

uint8_t sendPrinterByte(uint8_t byte) BANKED {
  uint8_t result;
  disable_interrupts();
  SB_REG = byte; //data to send
  SC_REG = 0x81; //1000 0001 - start, internal clock
  while (SC_REG & 0x80) {} //wait until b1 reset
  result = SB_REG; //return response stored in SB_REG
  enable_interrupts();
  return result;
}

void sendByte(uint8_t dataByte, uint8_t addToChecksum) BANKED {
  if (addToChecksum) {
    CRC += dataByte;
  }

  uint8_t result;
  result = sendPrinterByte(dataByte);
  printerStatus[0] = printerStatus[1];
  printerStatus[1] = printerStatus[2];
  printerStatus[2] = result;
}

void sendPrinterCommand(const uint8_t *command) BANKED {
  uint8_t length, index;
  index = 0;
  length = *command;
  CRC = 0;

  while (index < length) {
    index++;
    sendByte(*(command + index), index > 2);
  }
}


inline uint8_t getHigh(uint16_t w) {
  return (w & 0xFF00u) >> 8;
}

inline uint8_t getLow(uint16_t w) {
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

uint8_t checkLinkCable() BANKED {
  if (printerStatus[0] != 0) {
    return 2;
  }
  if ((printerStatus[1] & 0xF0) != 0x80) {
    return 2;
  }
  return 0;
}

uint8_t getPrinterStatus() BANKED {
  sendPrinterCommand(PRINTER_STATUS);
  sendChecksum();
  return checkLinkCable();
}

uint8_t checkForErrors() BANKED {
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

uint8_t printerBusy() BANKED {
  sendPrinterCommand(PRINTER_STATUS);
  sendChecksum();
  return (printerStatus[2] & STATUS_BUSY);
}


void waitPrinterReady() BANKED {
  // Wait for max 30s to give the printer time to become ready.
  // If not ready after 30s, return anyway to not hang the program
  for (uint16_t wait = 0; wait < 1800; wait++) {
    wait_vbl_done();
    if (!printerBusy()) {
      return;
    }
  }
}


void printTileData(const uint8_t *tileData, uint8_t num_packets, uint8_t margins, uint8_t palette, uint8_t exposure) BANKED {
  uint8_t tileIndex;

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
      for (uint8_t wait = 0; wait < 120; wait++) {
        wait_vbl_done();
        if (printerBusy()) {
          return;
        }
      }

    }
  }
}

static void printImage(uint8_t *lower, uint8_t *upper, uint8_t bank) NONBANKED {
  uint8_t save = _current_bank;
  SWITCH_ROM(frame_pxlr_tiles);

  printerInit();
  SWITCH_RAM(bank);
  uint8_t x, y;
  uint16_t frameTileIndex = 0;

  uint8_t *image = upper;
  for (y = 0; y < 18; y++) {
    for (x = 0; x < 20; x++) {
      if (x == 0 && y == 9) {
        image = lower;
      }
      if (x < 2 || y < 2 || x >= 18 || y >= 16) {
        printTileData(&frame_pxlr_tiles[frame_pxlr_map[frameTileIndex] * 16], 9, 0x02, PALETTE_NORMAL, EXPOSURE_DEFAULT);
      } else {
        printTileData(image, 9, 0x03, PALETTE_NORMAL, EXPOSURE_DEFAULT);
        image += 16;
      }

      frameTileIndex++;
    }
  }

  SWITCH_ROM(save);
}

static void printImageInfo(uint8_t *imageInfo) NONBANKED {
  uint8_t save = _current_bank;
  SWITCH_ROM(frame_pxlr_tiles);

  uint16_t index;
  printerInit();

  for (index = 0; index < 40; index++) {
    printTileData(&frame_pxlr_tiles[frame_pxlr_map[index] * 16], 1, 0x00, PALETTE_INVERTED, EXPOSURE_DEFAULT);
  }

  waitPrinterReady();
  printerInit();

  for (index = 0; index < 360; index++) {
    printTileData(&font[(imageInfo[index] - 32) * 16], 9, 0x00, PALETTE_INVERTED, EXPOSURE_DARK);
  }


  waitPrinterReady();
  printerInit();

  for (index = 320; index < 360; index++) {
    printTileData(&frame_pxlr_tiles[frame_pxlr_map[index] * 16], 1, 0x03, PALETTE_INVERTED, EXPOSURE_DEFAULT);
  }

  SWITCH_ROM(save);
}
