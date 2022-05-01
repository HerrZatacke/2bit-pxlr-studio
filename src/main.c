#define OFFSET_TILES 160
  #define OFFSET_MENU_ARROW 162
#define OFFSET_FONT 163
#define OFFSET_MENU_TILES 173

#define SPRITE_MENU_INDICATOR_L 0
#define SPRITE_MENU_INDICATOR_R 1

#define PALETTE_SPRITES 0b11100100u
#define PALETTE_NORMAL 0b11100100u
#define PALETTE_INVERTED 0b00011011u
#define PALETTE_BLANK 0b11111111u

#define A000_CAPTURE_POSITIVE 0b00000010
#define A000_START_CAPTURE    0b00000001

#define A004_EDGE_RATIO_050   0b00000000
#define A004_EDGE_RATIO_075   0b00010000
#define A004_EDGE_RATIO_100   0b00100000
#define A004_EDGE_RATIO_125   0b00110000
#define A004_EDGE_RATIO_200   0b01000000
#define A004_EDGE_RATIO_300   0b01010000
#define A004_EDGE_RATIO_400   0b01100000
#define A004_EDGE_RATIO_500   0b01110000

#define A004_INVERT_OUTPUT    0b00001000

#define A004_VOLTAGE_REF_00   0b00000000
#define A004_VOLTAGE_REF_05   0b00000001
#define A004_VOLTAGE_REF_10   0b00000010
#define A004_VOLTAGE_REF_15   0b00000011
#define A004_VOLTAGE_REF_20   0b00000100
#define A004_VOLTAGE_REF_25   0b00000101
#define A004_VOLTAGE_REF_30   0b00000110
#define A004_VOLTAGE_REF_35   0b00000111

#define A005_ZERO_DISABLED    0b00000000
#define A005_ZERO_POSITIVE    0b10000000
#define A005_ZERO_NEGATIVE    0b01000000

#define A005_VOLTAGE_OUT_NEG_992 0b00011111 // -0.992mV
#define A005_VOLTAGE_OUT_NEG_960 0b00011110 // -0.960mV
#define A005_VOLTAGE_OUT_NEG_928 0b00011101 // -0.928mV
#define A005_VOLTAGE_OUT_NEG_896 0b00011100 // -0.896mV
#define A005_VOLTAGE_OUT_NEG_864 0b00011011 // -0.864mV
#define A005_VOLTAGE_OUT_NEG_832 0b00011010 // -0.832mV
#define A005_VOLTAGE_OUT_NEG_800 0b00011001 // -0.800mV
#define A005_VOLTAGE_OUT_NEG_768 0b00011000 // -0.768mV
#define A005_VOLTAGE_OUT_NEG_736 0b00010111 // -0.736mV
#define A005_VOLTAGE_OUT_NEG_704 0b00010110 // -0.704mV
#define A005_VOLTAGE_OUT_NEG_672 0b00010101 // -0.672mV
#define A005_VOLTAGE_OUT_NEG_640 0b00010100 // -0.640mV
#define A005_VOLTAGE_OUT_NEG_608 0b00010011 // -0.608mV
#define A005_VOLTAGE_OUT_NEG_576 0b00010010 // -0.576mV
#define A005_VOLTAGE_OUT_NEG_544 0b00010001 // -0.544mV
#define A005_VOLTAGE_OUT_NEG_512 0b00010000 // -0.512mV
#define A005_VOLTAGE_OUT_NEG_480 0b00001111 // -0.480mV
#define A005_VOLTAGE_OUT_NEG_448 0b00001110 // -0.448mV
#define A005_VOLTAGE_OUT_NEG_416 0b00001101 // -0.416mV
#define A005_VOLTAGE_OUT_NEG_384 0b00001100 // -0.384mV
#define A005_VOLTAGE_OUT_NEG_352 0b00001011 // -0.352mV
#define A005_VOLTAGE_OUT_NEG_320 0b00001010 // -0.320mV
#define A005_VOLTAGE_OUT_NEG_288 0b00001001 // -0.288mV
#define A005_VOLTAGE_OUT_NEG_256 0b00001000 // -0.256mV
#define A005_VOLTAGE_OUT_NEG_224 0b00000111 // -0.224mV
#define A005_VOLTAGE_OUT_NEG_192 0b00000110 // -0.192mV
#define A005_VOLTAGE_OUT_NEG_160 0b00000101 // -0.160mV
#define A005_VOLTAGE_OUT_NEG_128 0b00000100 // -0.128mV
#define A005_VOLTAGE_OUT_NEG_096 0b00000011 // -0.096mV
#define A005_VOLTAGE_OUT_NEG_064 0b00000010 // -0.064mV
#define A005_VOLTAGE_OUT_NEG_032 0b00000001 // -0.032mV
#define A005_VOLTAGE_OUT_NEG_000 0b00000000 // -0.000mV
#define A005_VOLTAGE_OUT_POS_000 0b00100000 //  0.000mV
#define A005_VOLTAGE_OUT_POS_032 0b00100001 //  0.032mV
#define A005_VOLTAGE_OUT_POS_064 0b00100010 //  0.064mV
#define A005_VOLTAGE_OUT_POS_096 0b00100011 //  0.096mV
#define A005_VOLTAGE_OUT_POS_128 0b00100100 //  0.128mV
#define A005_VOLTAGE_OUT_POS_160 0b00100101 //  0.160mV
#define A005_VOLTAGE_OUT_POS_192 0b00100110 //  0.192mV
#define A005_VOLTAGE_OUT_POS_224 0b00100111 //  0.224mV
#define A005_VOLTAGE_OUT_POS_256 0b00101000 //  0.256mV
#define A005_VOLTAGE_OUT_POS_288 0b00101001 //  0.288mV
#define A005_VOLTAGE_OUT_POS_320 0b00101010 //  0.320mV
#define A005_VOLTAGE_OUT_POS_352 0b00101011 //  0.352mV
#define A005_VOLTAGE_OUT_POS_384 0b00101100 //  0.384mV
#define A005_VOLTAGE_OUT_POS_416 0b00101101 //  0.416mV
#define A005_VOLTAGE_OUT_POS_448 0b00101110 //  0.448mV
#define A005_VOLTAGE_OUT_POS_480 0b00101111 //  0.480mV
#define A005_VOLTAGE_OUT_POS_512 0b00110000 //  0.512mV
#define A005_VOLTAGE_OUT_POS_544 0b00110001 //  0.544mV
#define A005_VOLTAGE_OUT_POS_576 0b00110010 //  0.576mV
#define A005_VOLTAGE_OUT_POS_608 0b00110011 //  0.608mV
#define A005_VOLTAGE_OUT_POS_640 0b00110100 //  0.640mV
#define A005_VOLTAGE_OUT_POS_672 0b00110101 //  0.672mV
#define A005_VOLTAGE_OUT_POS_704 0b00110110 //  0.704mV
#define A005_VOLTAGE_OUT_POS_736 0b00110111 //  0.736mV
#define A005_VOLTAGE_OUT_POS_768 0b00111000 //  0.768mV
#define A005_VOLTAGE_OUT_POS_800 0b00111001 //  0.800mV
#define A005_VOLTAGE_OUT_POS_832 0b00111010 //  0.832mV
#define A005_VOLTAGE_OUT_POS_864 0b00111011 //  0.864mV
#define A005_VOLTAGE_OUT_POS_896 0b00111100 //  0.896mV
#define A005_VOLTAGE_OUT_POS_928 0b00111101 //  0.928mV
#define A005_VOLTAGE_OUT_POS_960 0b00111110 //  0.960mV
#define A005_VOLTAGE_OUT_POS_992 0b00111111 //  0.992mV

#include <gb/gb.h>
#include <stdint.h>
#include <gbdk/bcd.h>
#include "banks/banks.h"
#include "values.h"
#include "utils.h"
#include "menu.h"
#include "saveImage.h"
#include "../res/font.h"
#include "../res/menu_labels.h"
#include "../res/gbps-logo.h"

const unsigned char tiles[] = {
  // Blank (black)
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  // Blank (white)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // Arrow,
  0x00, 0x00, 0x10, 0x10, 0x18, 0x18, 0x1c, 0x1c, 0x18, 0x1c, 0x10, 0x18, 0x00, 0x10, 0x00, 0x00,
};

#define BLNK 0xA1

const unsigned char map_normal[] = {
  BLNK, 0xBD, 0xBE, 0xBF, 0xC0, BLNK, 0xC1, 0xC2, 0xC3, BLNK, 0xC7, 0xC8, 0xC9, 0xCA, BLNK, BLNK, 0xC4, 0xC5, 0xC6, BLNK,
  BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK,
  BLNK, BLNK, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, BLNK, BLNK,
  BLNK, BLNK, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, BLNK, BLNK,
  BLNK, BLNK, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, BLNK, BLNK,
  BLNK, BLNK, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, BLNK, BLNK,
  BLNK, BLNK, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, BLNK, BLNK,
  BLNK, BLNK, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, BLNK, BLNK,
  BLNK, BLNK, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, BLNK, BLNK,
  BLNK, BLNK, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, BLNK, BLNK,
  BLNK, BLNK, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, BLNK, BLNK,
  BLNK, BLNK, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, BLNK, BLNK,
  BLNK, BLNK, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, BLNK, BLNK,
  BLNK, BLNK, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, BLNK, BLNK,
  BLNK, BLNK, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, BLNK, BLNK,
  BLNK, BLNK, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, BLNK, BLNK,
  0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xAD, 0xAE, 0xAF, 0xB0, BLNK, BLNK, 0xB6, 0xB7, 0xB8, 0xB9, BLNK, 0xBA, 0xBB, 0xBC, BLNK,
  BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK,
};


void fastLoadImageTiles() {
  SWITCH_RAM(0);
  LCDC_REG &= ~ LCDCF_BG8000;
  set_bkg_data(0, 112, last_seen_upper);
  LCDC_REG |= LCDCF_BG8000;
  set_bkg_data(0, 112, last_seen_lower);
}

void waitabit() {
  for (unsigned char i = 0; i < 15; i ++) {
    wait_vbl_done();
    if (joypad() == 0) {
      i = 15;
    }
  }
  return;
}

void scanline_isr() {
  if (LYC_REG == 71) {
    LCDC_REG |= LCDCF_BG8000;
    LYC_REG = 144;
  } else if (LYC_REG == 144) {
    LCDC_REG &= ~ LCDCF_BG8000;
    LYC_REG = 71;
  }
}

void setDitherMatrix() {
  SWITCH_RAM(16);
  for (unsigned int i = 0; i < 48; i += 1) {
    if (highLow) {
      A006A035[i] = ditherHighLight[ditherIndex][i];
    } else {
      A006A035[i] = ditherLowLight[ditherIndex][i];
    }
  }
}

void init_cam() {
  gain = (numGainLevels >> 1) - 1;
  exposureTime = (numExposureTimes >> 1) - 1;
  ditherIndex = (numDithers >> 1) - 1;
  highLow = 1;
  edgeMode = (numEdgeModes >> 1) - 1;
  voltageRef = (numVoltageRefs >> 1) - 1;
  zeroPoint = 1;
  voltageOut = (numVoltageOuts >> 1) - 1;
  setDitherMatrix();
}

unsigned char readA000() {
  return A000;
}

void capture() {

  SWITCH_RAM(16);

  // N 7 Exclusively set vertical edge enhancement mode.
  // VH 5-6 Select vertical/horizontal edge operation mode.
  // G 0-4 Analog output gain.
//  A001 = 0b00001010;  // NHVGGGGG

  A001 = 0b00100000 | gains[gain];
  A002 = exposureTimes[exposureTime] >> 8;
  A003 = exposureTimes[exposureTime];
  A004 = edgeModes[edgeMode] | voltageRefs[voltageRef];
  A005 = voltageOuts[voltageOut] | zeroPoints[zeroPoint];

  setDitherMatrix();

  A000 = A000_CAPTURE_POSITIVE | A000_START_CAPTURE;

  captureMenuJp(); // this call is only for the emulator to get some joypad input

  while (readA000() % 2) {
    captureMenuJp();
  }
}


int main(void) {

  init_gfx();
  init_sound();
  splash();

  waitPush(J_A);
  waitRelease();

  CRITICAL {
    STAT_REG |= STATF_LYC;
    LYC_REG = 144;
    add_LCD(scanline_isr);
  }
  set_interrupts(VBL_IFLAG | LCD_IFLAG);

  set_bkg_data(OFFSET_TILES, 8, tiles);
  set_bkg_data(OFFSET_FONT, 10, font);
  set_bkg_data(OFFSET_MENU_TILES, 31, menu_labels_tiles);
  set_bkg_tiles(0, 0, 20, 18, map_normal);

  init_cam();
  renderMenu();

  // Loop forever
  while (1) {
    capture();

    fastLoadImageTiles();

    menu();

    if (joypad() == J_A) {
      saveImageDialog();
    }
  }
}
