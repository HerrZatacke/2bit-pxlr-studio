#pragma bank 255

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
#include "camera.h"
#include "tiles.h"
#include "dialog.h"
#include "menus/shootingAssistedMenuItems.h"
#include "valuesAssisted.h"
#include "valuesDefs.h"

uint8_t assistedMenuPos = 0;

void renderAssistedMenu() BANKED {
  clonk();
  fill_bkg_rect(0, 0, 20, 2, BLNK);
  fill_bkg_rect(0, 16, 20, 2, BLNK);

  uint8_t spriteX = (menuItemsAssisted[assistedMenuPos]->x * 8) + 8;
  move_sprite(SPRITE_MENU_INDICATOR, spriteX, 23);

  for (uint8_t i = 0; i < NUM_MENU_ELEMENTS_ASSISTED; i += 1) {
    uint8_t value = menuItemsAssisted[i]->value;
    set_bkg_based_tiles(menuItemsAssisted[i]->x, 0, MENU_TEXT_LENGTH, 1, menuItemsAssisted[i]->title, OFFSET_FONT - 32);
    set_bkg_based_tiles(menuItemsAssisted[i]->x, 1, MENU_TEXT_LENGTH, 1, menuItemsAssisted[i]->options[value].title, OFFSET_FONT - 32);
  }

  set_bkg_based_tiles(0, 16, 9, 2, menuItemsAssisted[assistedMenuPos]->description, OFFSET_FONT - 32);

  set_bkg_based_tiles(12, 16, 6, 2, "   /30Images", OFFSET_FONT - 32);
  writeNumber(12, 16, 2, numVisibleImages);
}

void restoreAssistedDefaults() BANKED {
  for (uint8_t i = 0; i < NUM_MENU_ELEMENTS_ASSISTED; i += 1) {
    menuItemsAssisted[i]->value = menuItemsAssisted[i]->defaultValue;
  }
}

void updateDithering() BANKED {
  uint8_t assistedOptionIndex = getMenuValue(&assistedOptionsMenu);
  uint8_t ditherOnOff = getMenuValue(&ditherToggleMenu);
  uint8_t contrast = getMenuValue(&contrastsMenuAssisted);
  uint8_t ditherSet = assistedOptionsValues[assistedOptionIndex].ditherSet | getMenuValue(&ditherToggleMenu);

  setDitherMatrix(ditherSet, contrast);
}

void initAssistedMode() BANKED {
  clearBkg();
  set_bkg_tiles_banked(2, 2, 16, 14, map_normal, 1);
  sortImages();
  showOverlay();
  restoreAssistedDefaults();
  updateDithering();
  renderAssistedMenu();
}

void assistedShootLoop() BANKED {
  uint8_t assistedOptionIndex = getMenuValue(&assistedOptionsMenu);

  uint8_t capt = A000_START_CAPTURE_POSITIVE;
  uint8_t edExOpGain = assistedOptionsValues[assistedOptionIndex].edgeOperation | assistedOptionsValues[assistedOptionIndex].gain | assistedOptionsValues[assistedOptionIndex].edgeExclusive;
  uint16_t expTime = assistedOptionsValues[assistedOptionIndex].expTime;
  uint8_t edRInvVref = A004_EDGE_RATIO_050 | A004_VOLTAGE_REF_15 | A004_INVERT_OUTPUT_OFF;
  uint8_t zeroVout = assistedOptionsValues[assistedOptionIndex].vOut | A005_ZERO_POSITIVE;

  capture(capt, edExOpGain, expTime, edRInvVref, zeroVout);

  if (jp == J_RIGHT) {
    assistedMenuPos = (assistedMenuPos + 1) % NUM_MENU_ELEMENTS_ASSISTED;
    renderAssistedMenu();
    joypadConsumed();
  } else if (jp == J_LEFT) {
    assistedMenuPos = (assistedMenuPos + NUM_MENU_ELEMENTS_ASSISTED - 1) % NUM_MENU_ELEMENTS_ASSISTED;
    renderAssistedMenu();
    joypadConsumed();
  } else if (jp == J_UP) {
    menuItemsAssisted[assistedMenuPos]->value = (menuItemsAssisted[assistedMenuPos]->value + 1) % menuItemsAssisted[assistedMenuPos]->numOptions;
    updateDithering();
    renderAssistedMenu();
    joypadConsumed();
  } else if (jp == J_DOWN) {
    menuItemsAssisted[assistedMenuPos]->value = (menuItemsAssisted[assistedMenuPos]->value + menuItemsAssisted[assistedMenuPos]->numOptions - 1) % menuItemsAssisted[assistedMenuPos]->numOptions;
    updateDithering();
    renderAssistedMenu();
    joypadConsumed();
  } else if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_MENU);
    joypadConsumed();
  } else if (jp == J_SELECT) {
    if (dialog("Reset settings? ", 1)) {
      restoreAssistedDefaults();
      updateDithering();
      renderAssistedMenu();
    }
    joypadConsumed();
  } else if (jp == J_A) {
    uint8_t ditherSet = assistedOptionsValues[assistedOptionIndex].ditherSet | getMenuValue(&ditherToggleMenu);
    uint8_t contrast = getMenuValue(&contrastsMenuAssisted);

    saveImageDialog(capt, edExOpGain, expTime, edRInvVref, zeroVout, ditherSet, contrast);
    renderAssistedMenu();
    joypadConsumed();
  } else if (jp == J_START) {
    nextOverlay();
    clonk();
    showOverlay();
    joypadConsumed();
  }
}
