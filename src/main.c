#define OFFSET_FONT 128
#define OFFSET_TILES 219
  #define FILL 219
  #define BLNK 220
  #define OFFSET_MENU_ARROW 221

#define SPRITE_MENU_INDICATOR_L 0
#define SPRITE_MENU_INDICATOR_R 1

#define PALETTE_SPRITES 0b11100100u
#define PALETTE_NORMAL 0b11100100u
#define PALETTE_INVERTED 0b00011011u
#define PALETTE_BLANK 0b11111111u


#include <gb/gb.h>
#include <stdint.h>
#include <gbdk/bcd.h>
#include "./utils.h"
#include "../res/map.h"
#include "../res/gbps-logo.h"
#include "../res/font.h"
#include "./banks/banks.h"
#include "./values.h"
#include "./menu.h"
#include "./saveImage.h"

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

  A000 = A000_CAPTURE_POSITIVE | A000_START_CAPTURE;

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
  // ToDo: Fade-effect?

  set_bkg_tiles(0, 0, 20, 18, map_normal);
  set_bkg_data(OFFSET_FONT, 96, font);
  set_bkg_data(OFFSET_TILES, 3, tiles);

  CRITICAL {
    STAT_REG |= STATF_LYC;
    LYC_REG = 144;
    add_LCD(scanline_isr);
  }
  set_interrupts(VBL_IFLAG | LCD_IFLAG);

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
