#include <gb/gb.h>
#include <gbdk/platform.h>

#include "globals.h"
#include "defines.h"
#include "utils.h"
#include "joypad.h"
#include "saveImage.h"
#include "maps.h"
#include "overlays/overlays.h"
#include "imageIndexing.h"
#include "bankedData.h"
#include "mainMenu.h"

uint8_t burstActive = 0;

void renderBurstMenu() {
  set_bkg_based_tiles(12, 16, 6, 2, "   /30Images", OFFSET_FONT - 32);
  writeNumber(12, 16, 2, numVisibleImages);
}

void initBurstMode() {
  clearBkg();
  set_bkg_tiles_banked(2, 2, 16, 14, map_normal, 1);
  sortImages();
  showOverlay();
  renderBurstMenu();
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);
  burstActive = 0;
}

void burstShootMenu() {
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
      saveImage();
      renderBurstMenu();
    } else {
      boop();
      burstActive = 0;
    }
  }
}
