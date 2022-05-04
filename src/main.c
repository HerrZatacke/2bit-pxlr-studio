#define OFFSET_TILES 160
  #define OFFSET_MENU_ARROW 162

#define SPRITE_MENU_INDICATOR_L 0
#define SPRITE_MENU_INDICATOR_R 1

#define PALETTE_SPRITES 0b11100100u
#define PALETTE_NORMAL 0b11100100u
#define PALETTE_INVERTED 0b00011011u
#define PALETTE_BLANK 0b11111111u

#define FILL 0xA0
#define BLNK 0xA1

#include <gb/gb.h>
#include <stdint.h>
#include <gbdk/bcd.h>
#include <gbdk/font.h>
#include "banks/banks.h"
#include "values.h"
#include "utils.h"
#include "menu.h"
#include "saveImage.h"
#include "../res/gbps-logo.h"

const unsigned char tiles[] = {
  // Blank (black)
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  // Blank (white)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // Arrow,
  0x00, 0x00, 0x10, 0x10, 0x18, 0x18, 0x1c, 0x1c, 0x18, 0x1c, 0x10, 0x18, 0x00, 0x10, 0x00, 0x00,
};

const unsigned char map_normal[] = {
  BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK,
  BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
  BLNK, BLNK, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, FILL, BLNK, BLNK,
//  BLNK, BLNK, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, BLNK, BLNK,
//  BLNK, BLNK, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, BLNK, BLNK,
//  BLNK, BLNK, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, BLNK, BLNK,
//  BLNK, BLNK, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, BLNK, BLNK,
//  BLNK, BLNK, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, BLNK, BLNK,
//  BLNK, BLNK, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, BLNK, BLNK,
//  BLNK, BLNK, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, BLNK, BLNK,
//  BLNK, BLNK, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, BLNK, BLNK,
//  BLNK, BLNK, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, BLNK, BLNK,
//  BLNK, BLNK, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, BLNK, BLNK,
//  BLNK, BLNK, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, BLNK, BLNK,
//  BLNK, BLNK, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, BLNK, BLNK,
//  BLNK, BLNK, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, BLNK, BLNK,
//  BLNK, BLNK, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, BLNK, BLNK,
  BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK,
  BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK, BLNK,
};


void fastLoadImageTiles() {
  SWITCH_RAM(0);
//  LCDC_REG &= ~ LCDCF_BG8000;
//  set_bkg_data(0, 112, last_seen_upper);
//  LCDC_REG |= LCDCF_BG8000;
//  set_bkg_data(0, 112, last_seen_lower);
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
    if (getMenuValue(ditherHighLowsMenu) == DITHER_SET_HIGH) {
      A006A035[i] = ditherHighLightValues[getMenuValue(ditherSetsMenu)][i];
    } else {
      A006A035[i] = ditherLowLightValues[getMenuValue(ditherSetsMenu)][i];
    }
  }
}

void init_cam() {
  if (
    restoreSettings() ||
    (joypad() == (J_START | J_SELECT)) // "factory" reset
  ) {
    nextImageIndex = 0; // reset "images taken"
    restoreDefaults(); // reset all sensor params to default
    boop();
    pause(20);
    beep();
  }
}

unsigned char readA000() {
  return A000;
}

void capture() {
  SWITCH_RAM(16);

  unsigned int exposureTime = exposureTimesValues[getMenuValue(exposureTimesMenu)];

  A001 = getMenuValue(edgeOpModesMenu) | getMenuValue(gainsMenu) | getMenuValue(edgeExclusivesMenu);
  A002 = exposureTime >> 8;
  A003 = exposureTime;
  A004 = getMenuValue(edgeModesMenu) | getMenuValue(voltageRefsMenu) | getMenuValue(invertOutputsMenu);
  A005 = getMenuValue(voltageOutsMenu) | getMenuValue(zeroPointsMenu);

  setDitherMatrix();

#define NO_CAPTURE
#ifdef NO_CAPTURE
    pause(10);
#else
  A000 = A000_CAPTURE_POSITIVE | A000_START_CAPTURE;
#endif

  captureMenuJp(); // this call is only for the emulator to get some joypad input

  while (readA000() % 2) {
    captureMenuJp();
  }
}


int main(void) {

  init_gfx();
  init_sound();
  init_cam();

  splash();
  waitPush(J_A);
  waitRelease();

  font_init();
  font_set(font_load(font_ibm));

//  CRITICAL {
//    STAT_REG |= STATF_LYC;
//    LYC_REG = 144;
//    add_LCD(scanline_isr);
//  }
  set_interrupts(VBL_IFLAG | LCD_IFLAG);

  set_bkg_data(OFFSET_TILES, 8, tiles);
  set_bkg_tiles(0, 0, 20, 18, map_normal);

  renderMenu();

  // Loop forever
  while (1) {
    capture();

    fastLoadImageTiles();

    menu();

    if (joypad() == J_A) {
      saveImageDialog();
    }

    wait_vbl_done();
  }
}
