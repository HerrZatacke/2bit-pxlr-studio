#include <gb/gb.h>
#include <gbdk/platform.h>

#include "camera.h"
#include "defines.h"
#include "globals.h"
#include "imageIndexing.h"
#include "joypad.h"
#include "mainLoop.h"
#include "mainMenu.h"
#include "overlays/overlays.h"
#include "splash.h"
#include "utils.h"

void scanlineIsr() {
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

uint16_t main() {
  CRITICAL {
    STAT_REG |= STATF_LYC;
    LYC_REG = 144;
    add_LCD(scanlineIsr);
  }
  set_interrupts(VBL_IFLAG | LCD_IFLAG);

  initGfx();
  initSound();
  initCam();
  initOverlays();
  cleanupIndexGaps();
  sortImages();

  uint8_t splashPressed = splash();
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
