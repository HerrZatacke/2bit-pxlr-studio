#define OFFSET_FONT 128u
  #define OFFSET_BLANK 128u
#define OFFSET_TILES 219u
  #define OFFSET_FILL 219u
  #define OFFSET_MENU_ARROW 220u
  #define OFFSET_BORDER_H 221u
  #define OFFSET_BORDER_V 222u
  #define MENU_BORDER_LEFT 223u
  #define MENU_BORDER_TOP 224u
  #define OFFSET_BLEEP_CURSOR 225u

#define SPRITE_MENU_INDICATOR 0
#define SPRITE_BORDER_H_1 1
#define SPRITE_BORDER_H_2 2
#define SPRITE_BORDER_H_3 3
#define SPRITE_BORDER_H_4 4
#define SPRITE_BORDER_H_5 5
#define SPRITE_BORDER_H_6 6
#define SPRITE_BORDER_H_7 7
#define SPRITE_BORDER_H_8 8
#define SPRITE_BORDER_V_1 9
#define SPRITE_BORDER_V_2 10
#define SPRITE_BORDER_V_3 11
#define SPRITE_BORDER_V_4 12
#define SPRITE_BORDER_V_5 13
#define SPRITE_BORDER_V_6 14
#define SPRITE_BORDER_V_7 15
#define SPRITE_BORDER_V_8 16
#define SPRITE_BLEEP_CURSOR 17

#define PALETTE_SPRITES 0b11100100u
#define PALETTE_NORMAL 0b11100100u
#define PALETTE_INVERTED 0b00011011u
#define PALETTE_BLANK 0b11111111u

#define MAIN_LOOP_MENU 0
#define MAIN_LOOP_SHOOT_MANUAL 1
#define MAIN_LOOP_IMAGE_GALLERY 2
#define MAIN_LOOP_IMAGE 3
#define MAIN_LOOP_DELETE_ALL 4
#define MAIN_LOOP_DEBUG 254
#define MAIN_LOOP_NOT_IMPLEMENTED 255

#define IMAGE_MENU_INFO 0
#define IMAGE_MENU_DELETE 1
#define IMAGE_MENU_PRINT 2
#define IMAGE_MENU_BLEEP 3
#define IMAGE_MENU_EXPOSE 4

#define HALF_IMAGE_SIZE 1792
#define VRAM_9000 (unsigned char *)0x9000
#define VRAM_8000 (unsigned char *)0x8000

unsigned char mainLoopState = 0;
unsigned char isCapturing = 0;

void menuSelectMode(unsigned char loopState);
void setDitherMatrix();

#include <gb/gb.h>
#include <stdint.h>
#include <string.h>
#include <gbdk/bcd.h>

#include "typedefs/MenuOption.h"
#include "typedefs/MenuItem.h"
#include "typedefs/Image.h"

#include "./joypad.h"
#include "./utils.h"
#include "./dialog.h"
#include "../res/frames/frame_pxlr.h"
#include "../res/map.h"
#include "../res/gbps-logo.h"
#include "../res/font.h"
#include "../res/nope.h"
#include "./banks/banks.h"
#include "./imageIndexing.h"
#include "./values.h"
#include "./mainMenu.h"
#include "./debug.h"
#include "./menu.h"
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

void setDitherMatrix() {
  SWITCH_RAM(16);
  unsigned char ditherSet = getMenuValue(ditherHighLowsMenu);

  for (unsigned int i = 0; i < 48; i += 1) {
    if (ditherSet == DITHER_SET_HIGH) {
      memcpy(A006A035, ditherHighLightValues[getMenuValue(ditherSetsMenu)], 48);
    } else if (ditherSet == DITHER_SET_LOW) {
      memcpy(A006A035, ditherLowLightValues[getMenuValue(ditherSetsMenu)], 48);
    } else if (ditherSet == DITHER_SET_NO_HIGH) {
      memcpy(A006A035, ditherNoHighLightValues[getMenuValue(ditherSetsMenu)], 48);
    } else if (ditherSet == DITHER_SET_NO_LOW) {
      memcpy(A006A035, ditherNoLowLightValues[getMenuValue(ditherSetsMenu)], 48);
    }
  }
}

void init_cam() {
  if (
    restoreSettings() ||
    (joypad() == (J_START | J_SELECT)) // "factory" reset
  ) {
    restoreDefaults(); // reset all sensor params to default
    storeSettings();
    boop();
    pause(20);
    beep();
  }

  imageIndex = 0; // gallery
  setDitherMatrix();
}

void capture() {
  SWITCH_RAM(16);

  unsigned int exposureTime = exposureTimesValues[getMenuValue(exposureTimesMenu)];

  A001 = getMenuValue(edgeOpModesMenu) | getMenuValue(gainsMenu) | getMenuValue(edgeExclusivesMenu);
  A002 = exposureTime >> 8;
  A003 = exposureTime;
  A004 = getMenuValue(edgeModesMenu) | getMenuValue(voltageRefsMenu) | getMenuValue(invertOutputsMenu);
  A005 = getMenuValue(voltageOutsMenu) | getMenuValue(zeroPointsMenu);

  isCapturing = 1;

  A000 = A000_CAPTURE_POSITIVE | A000_START_CAPTURE;

  captureJoypadISR();

  while (A000 % 2) {
    if (!jp) {
      captureJoypadISR();
    }
  }

  isCapturing = 0;
}

void menuSelectMode(unsigned char loopState) {
  mainLoopState = loopState;
  if (loopState == MAIN_LOOP_SHOOT_MANUAL) {
    initManualMode();
  } else if (loopState == MAIN_LOOP_MENU) {
    initMainMenu();
  } else if (loopState == MAIN_LOOP_IMAGE_GALLERY) {
    initGallery();
  } else if (loopState == MAIN_LOOP_IMAGE) {
    initImageMenu();
  } else if (loopState == MAIN_LOOP_DELETE_ALL) {
    deleteAllImages();
    mainLoopState = MAIN_LOOP_MENU;
  } else if (loopState == MAIN_LOOP_DEBUG) {
    initDebug();
  } else { // fallback to main menu
    clearBkg();
    boop();
    mainLoopState = MAIN_LOOP_MENU;
    hideManualModeSprites();
    initMainMenu();
  }
}

int main(void) {
  CRITICAL {
    STAT_REG |= STATF_LYC;
    LYC_REG = 144;
    add_LCD(scanline_isr);
  }
  set_interrupts(VBL_IFLAG | LCD_IFLAG);

  init_gfx();
  init_sound();
  init_cam();

  fill_bkg_rect(0, 0, 20, 18, BLNK);

  set_bkg_data(OFFSET_FONT, NUM_FONT_CHARS, font);
  set_bkg_data(OFFSET_TILES, NUM_CONSTANT_TILES, constantTiles);

  cleanupIndexGaps();

  HIDE_SPRITES;
  unsigned char splashPressed = splash();

  SHOW_SPRITES;
  // ToDo: Fade-effect?

  set_data((unsigned char *)0x9700, upperLowerDoubleTiles, 256);
  set_data((unsigned char *)0x8700, upperLowerDoubleTiles, 256);

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
