#include "./defines.h"
#include "./globals.h"

void menuSelectMode(unsigned char loopState);
void setDitherMatrix();

#include <gb/gb.h>
#include <gbdk/platform.h>
#include <stdint.h>
#include <string.h>
#include <gbdk/bcd.h>

#include "typedefs/MenuItem.h"
#include "typedefs/Image.h"
#include "typedefs/Overlay.h"

#include "../res/frames/frame_pxlr.h"
#include "../res/tiles.h"
#include "../res/maps.h"
#include "../res/font.h"
#include "../res/nope.h"

#include "./splash.h"
#include "./joypad.h"
#include "./bankedData.h"
#include "./utils.h"
#include "./overlays/overlays.h"
#include "./dialog.h"
#include "./banks/banks.h"
#include "./imageIndexing.h"
#include "./values.h"
#include "./menus/mainMenuItems.h"
#include "./menus/imageMenuItems.h"
#include "./menus/shootingManualMenuItems.h"
#include "./imageInfo.h"
#include "./mainMenu.h"
#include "./debug.h"
#include "./modeShootingManual.h"
#include "./modeShootingBurst.h"
#include "./saveImage.h"
#include "./gallery.h"

void fastLoadImageTiles() {
  SWITCH_RAM(0);
  set_data(VRAM_9000, last_seen_upper, HALF_IMAGE_SIZE);
  set_data(VRAM_8000, last_seen_lower, HALF_IMAGE_SIZE);
}

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

void menuSelectMode(unsigned char loopState) {
  mainLoopState = loopState;
  if (loopState == MAIN_LOOP_SHOOT_MANUAL) {
    initManualMode();
  } else if (loopState == MAIN_LOOP_SHOOT_BURST) {
    initBurstMode();
  } else if (loopState == MAIN_LOOP_MENU) {
    initMainMenu();
  } else if (loopState == MAIN_LOOP_IMAGE_GALLERY) {
    initGallery();
  } else if (loopState == MAIN_LOOP_IMAGE) {
    initImageMenu();
    appearImageMenu();
    loadAndShowGalleryImage();
  } else if (loopState == MAIN_LOOP_DELETE_ALL) {
    deleteAllImages();
    mainLoopState = MAIN_LOOP_MENU;
  } else if (loopState == MAIN_LOOP_DEBUG) {
    initDebug();
  } else { // fallback to main menu
    clearBkg();
    boop();
    mainLoopState = MAIN_LOOP_MENU;
    hideOverlay();
    initMainMenu();
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

  // Loop forever
  while (1) {

    switch (mainLoopState) {
      case MAIN_LOOP_SHOOT_MANUAL:
        fastLoadImageTiles();
        capture();
        manualShootMenu();
        break;
      case MAIN_LOOP_SHOOT_BURST:
        fastLoadImageTiles();
        capture();
        burstShootMenu();
        break;
      case MAIN_LOOP_MENU:
        mainMenu();
        break;
      case MAIN_LOOP_DEBUG:
        debugMenu();
        break;
      case MAIN_LOOP_IMAGE_GALLERY:
        galleryMenu();
        break;
      case MAIN_LOOP_IMAGE:
        imageMenu();
        break;
    }

    wait_vbl_done();
  }
}
