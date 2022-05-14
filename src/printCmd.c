// Original library by DragonEagles from http://shen.mansell.tripod.com/games/gameboy/gameboy.html
// Ported to GBDK 2020 by T0biasCZe
// Print Screen function added by Christianr
// Print Screen (360 tile mode) added by T0biasCZe

#include <gb/gb.h>

uint8_t printerStatus[3];

const uint8_t PRINTER_INIT[] = {
  10, 0x88, 0x33, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
};
const uint8_t PRINTER_STATUS[] = {
  10, 0x88, 0x33, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00
};
const uint8_t PRINTER_EOF[] = {
  10, 0x88, 0x33, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
};
const uint8_t PRINTER_START[] = {
  14, 0x88, 0x33, 0x02, 0x00, 0x04, 0x00, 0x01, 0x03, 0xE4, 0x7F, 0x6D, 0x01, 0x00, 0x00
};
const uint8_t PRINT_TILE[] = {
  6, 0x88, 0x33, 0x04, 0x00, 0x80, 0x02
};
const uint8_t PRINTER_LINE[] = {
  14, 0x88, 0x33, 0x02, 0x00, 0x04, 0x00, 0x01, 0x00, 0xE4, 0x7F, 0x6A, 0x01, 0x00, 0x00
};

uint8_t tile_num, packet_num;

uint16_t CRC;

uint8_t sendPrinterByte(uint8_t byte) {
  uint8_t result;
  disable_interrupts();
  SB_REG = byte; //data to send
  SC_REG = 0x81; //1000 0001 - start, internal clock
  while (SC_REG & 0x80) {} //wait until b1 reset
  result = SB_REG; //return response stored in SB_REG
  enable_interrupts();
  return result;
}

void sendByte(uint8_t byte) {
  uint8_t result;
  result = sendPrinterByte(byte);
  printerStatus[0] = printerStatus[1];
  printerStatus[1] = printerStatus[2];
  printerStatus[2] = result;
}

void sendPrinterCommand(uint8_t *command) {
  uint8_t length, index;
  index = 0;
  length = *command;
  while (index < length) {
    index++;
    sendByte(*(command + index));
  }
}

void printerInit(void) {
  tile_num = 0;
  CRC = 0;
  packet_num = 0;

  sendPrinterCommand(PRINTER_INIT);
}

uint8_t checkLinkCable() {
  if (printerStatus[0] != 0) {
    return 2;
  }
  if ((printerStatus[1] & 0xF0) != 0x80) {
    return 2;
  }
  return 0;
}

uint8_t getPrinterStatus() {
  sendPrinterCommand(PRINTER_STATUS);
  return checkLinkCable();
}

uint8_t checkForErrors() {
  if (printerStatus[2] & 128) {
    return 1;
  }
  if (printerStatus[2] & 64) {
    return 4;
  }
  if (printerStatus[2] & 32) {
    return 3;
  }
  return 0;
}

uint8_t checkBusy() {
  sendPrinterCommand(PRINTER_STATUS);
  return (printerStatus[2] & 0x02);
}

inline uint8_t getHigh(uint16_t w) {
  return (w & 0xFF00u) >> 8;
}

inline uint8_t getLow(uint16_t w) {
  return (w & 0xFFu);
}

void printTileData(uint8_t *tileData, uint8_t lf, uint8_t num_packets) {
  uint8_t tileIndex;

  if (tile_num == 0) {
    sendPrinterCommand(PRINT_TILE);
    CRC = 0x04 + 0x80 + 0x02;
  }

  tile_num++;

  for (tileIndex = 0; tileIndex < 16; tileIndex++) {
    CRC += tileData[tileIndex];
    sendByte(tileData[tileIndex]);
  }

  if (tile_num == 40) {
    sendByte(getLow(CRC));
    sendByte(getHigh(CRC));
    sendByte(0x00);
    sendByte(0x00);
    tile_num = 0;
    CRC = 0;
    packet_num++;

    if (packet_num == num_packets) { // all done the page
      sendPrinterCommand(PRINTER_EOF); // data end packet
      if (lf)
        sendPrinterCommand(PRINTER_START);
      else
        sendPrinterCommand(PRINTER_LINE);
      packet_num = 0;
      sendPrinterCommand(PRINTER_STATUS);
    }
  }
}

void printImage(uint8_t *lower, uint8_t *upper) {
  // We need to print a border of 16x16 pixels (2x2 tiles)
  uint8_t x, y;
  const uint8_t border[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
  uint8_t *image = upper;
  for (y = 0; y < 18; y++) {
    for (x = 0; x < 20; x++) {
      if (x == 0 && y == 9) {
        image = lower;
      }
      if (x < 2 || y < 2 || x >= 18 || y >= 16) {
        printTileData(border, TRUE, 9);
      } else {
        printTileData(image, TRUE, 9);
        image += 16;
      }
    }
  }
}
