#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>

#include "globals.h"
#include "defines.h"
#include "utils.h"
#include "joypad.h"
#include "saveImage.h"
#include "maps.h"
#include "menus/shootingManualMenuItems.h"
#include "overlays/overlays.h"
#include "imageIndexing.h"
#include "bankedData.h"
#include "mainMenu.h"
#include "camera.h"
#include "values.h"

uint8_t burstActive = 0;

static void renderBurstMenu() {
  set_bkg_based_tiles(12, 16, 6, 2, "   /30Images", OFFSET_FONT - 32);
  writeNumber(12, 16, 2, numVisibleImages);
}

void initBurstMode() BANKED {
  clearBkg();
  set_bkg_tiles_banked(2, 2, 16, 14, map_normal, 1);
  sortImages();
  showOverlay();
  renderBurstMenu();
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);
  burstActive = 0;
}

void burstShootLoop() BANKED {
  uint8_t capt = getMenuValue(&captureModesMenu);
  uint8_t edExOpGain = getMenuValue(&edgeOpModesMenu) | getMenuValue(&gainsMenu) | getMenuValue(&edgeExclusivesMenu);
  uint16_t expTime = exposureTimesValues[getMenuValue(&exposureTimesMenu)];
  uint8_t edRInvVref = getMenuValue(&edgeModesMenu) | getMenuValue(&voltageRefsMenu) | getMenuValue(&invertOutputsMenu);
  uint8_t zeroVout = getMenuValue(&voltageOutsMenu) | getMenuValue(&zeroPointsMenu);

  uint8_t ditherSet = getMenuValue(&ditherSetsMenu);
  uint8_t contrast = getMenuValue(&contrastsMenu);

  capture(capt, edExOpGain, expTime, edRInvVref, zeroVout);

  if (jp == J_B) {
    burstActive = 0;
    menuSelectMode(MAIN_LOOP_MENU);
    joypadConsumed();
  } else if (jp == J_A) {
    burstActive = 1;
    beep();
    joypadConsumed();
  }

  if (burstActive == 1) {
    if (findFirstFreeSlot() != NUM_IMAGES) {
      saveImage(capt, edExOpGain, expTime, edRInvVref, zeroVout, ditherSet, contrast);
      renderBurstMenu();
    } else {
      boop();
      burstActive = 0;
    }
  }
}
