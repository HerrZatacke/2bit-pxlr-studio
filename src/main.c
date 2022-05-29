#include <gb/gb.h>
#include <gbdk/platform.h>
#include <stdint.h>
#include <string.h>
#include <gbdk/bcd.h>

#include "../res/font.h"
#include "../res/tiles.h"
#include "./bankedData.h"
#include "./camera.h"
#include "./defines.h"
#include "./globals.h"
#include "./imageIndexing.h"
#include "./joypad.h"
#include "./mainLoop.h"
#include "./mainMenu.h"
#include "./overlays/overlays.h"
#include "./splash.h"
#include "./utils.h"

void scanline_isr() {
  if (LYC_REG == 71) {
    LCDC_REG |= LCDCF_BG8000;
    LYC_REG = 144;
  } else if (LYC_REG == 144) {
    LCDC_REG &= ~ LCDCF_BG8000;
    LYC_REG = 71;

    if (!isCapturing) {
      captureJoypadISR();
    }
  }
}

int main(void) {
  init_gfx();

  CRITICAL {
    STAT_REG |= STATF_LYC;
    LYC_REG = 144;
    add_LCD(scanline_isr);
  }
  set_interrupts(VBL_IFLAG | LCD_IFLAG);

  clearBkg();
  set_bkg_data_banked(OFFSET_FONT, NUM_FONT_CHARS, font, 1);
  set_bkg_data_banked(OFFSET_TILES, NUM_CONSTANT_TILES, constantTiles, 1);
  set_data((unsigned char *)0x9700, upperLowerDoubleTiles, 256);
  set_data((unsigned char *)0x8700, upperLowerDoubleTiles, 256);

  init_sound();
  init_cam();
  initOverlays();
  cleanupIndexGaps();
  sortImages();

  unsigned char splashPressed = splash();
  clearBkg();
  BGP_REG = PALETTE_NORMAL;

  if (splashPressed == J_A) {
    menuSelectMode(MAIN_LOOP_SHOOT_MANUAL);
  } else {
    menuSelectMode(MAIN_LOOP_MENU);
  }

  mainLoop();

  return 1;
}
