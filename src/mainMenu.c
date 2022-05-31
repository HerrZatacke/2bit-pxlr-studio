#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>

#include "menus/mainMenuItems.h"
#include "globals.h"
#include "joypad.h"
#include "utils.h"
#include "defines.h"
#include "overlays/overlays.h"
#include "debug.h"
#include "gallery.h"
#include "modeShootingBurst.h"
#include "modeShootingManual.h"
#include "imageIndexing.h"
#include "dialog.h"

uint8_t mainMenuPos = 0;

inline void mainMenuSprite() {
  move_sprite(SPRITE_MENU_INDICATOR, 16, yMenuSprite(mainMenuPos));
}

void initMainMenu() BANKED {
  clearBkg();
  hideOverlay();

  for (uint8_t index = 0; index < NUM_MAIN_MENU_OPTIONS; index += 1) {
    set_bkg_based_tiles(2, yMenu(index), 16, 1, mainMenuItems[index].title, OFFSET_FONT - 32);
  }

  mainMenuSprite();
}

void menuSelectMode(uint8_t loopState) BANKED {
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
    if (dialog("Delete all?     ", 0)) {
      deleteAllImages();
    }
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

void mainMenu() BANKED {
  if (jp == J_DOWN) {
    clonk();
    mainMenuPos = (mainMenuPos + 1) % NUM_MAIN_MENU_OPTIONS;
    mainMenuSprite();
    joypadConsumed();
  } else if (jp == J_UP) {
    clonk();
    mainMenuPos = (mainMenuPos + NUM_MAIN_MENU_OPTIONS - 1) % NUM_MAIN_MENU_OPTIONS;
    mainMenuSprite();
    joypadConsumed();
  } else if (jp == J_A) {
    menuSelectMode(mainMenuItems[mainMenuPos].value);
    joypadConsumed();
  }
}
