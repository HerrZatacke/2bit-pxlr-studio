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
#include "menus/shootingManualMenuItems.h"
#include "valuesAssisted.h"
#include "valuesDefs.h"

uint8_t assistedOptionIndex = NUM_ASSISTED_OPTIONS >> 1;

static void renderAssistedMenu() {
  set_bkg_based_tiles(3, 0, 10, 1, "Mode   /  ", OFFSET_FONT - 32);
  writeNumber(7, 0, 2, assistedOptionIndex + 1);
  writeNumber(10, 0, 2, NUM_ASSISTED_OPTIONS);

  set_bkg_based_tiles(12, 16, 6, 2, "   /30Images", OFFSET_FONT - 32);
  writeNumber(12, 16, 2, numVisibleImages);
}

void initAssistedMode() BANKED {
  clearBkg();
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);
  set_bkg_tiles_banked(2, 2, 16, 14, map_normal, 1);
  sortImages();
  showOverlay();
  renderAssistedMenu();
}

void assistedShootLoop() BANKED {

  uint8_t capt = A000_START_CAPTURE_POSITIVE;
  uint8_t edExOpGain = assistedOptions[assistedOptionIndex].edgeOperation | assistedOptions[assistedOptionIndex].gain | assistedOptions[assistedOptionIndex].edgeExclusive;
  uint16_t expTime = assistedOptions[assistedOptionIndex].expTime;
  uint8_t edRInvVref = A004_EDGE_RATIO_050 | A004_VOLTAGE_REF_15 | A004_INVERT_OUTPUT_OFF;
  uint8_t zeroVout = assistedOptions[assistedOptionIndex].vOut | A005_ZERO_POSITIVE;
  uint8_t ditherSet = assistedOptions[assistedOptionIndex].ditherSet | DITHER_ON;

  uint8_t contrast = getMenuValue(&contrastsMenu);

  capture(capt, edExOpGain, expTime, edRInvVref, zeroVout);

  if (jp == J_UP) {
    assistedOptionIndex = (assistedOptionIndex + 1) % NUM_ASSISTED_OPTIONS;
    ditherSet = assistedOptions[assistedOptionIndex].ditherSet | DITHER_ON;
    setDitherMatrix(ditherSet, getMenuValue(&contrastsMenu));
    renderAssistedMenu();
    joypadConsumed();
  } else if (jp == J_DOWN) {
    assistedOptionIndex = (assistedOptionIndex + NUM_ASSISTED_OPTIONS - 1) % NUM_ASSISTED_OPTIONS;
    ditherSet = assistedOptions[assistedOptionIndex].ditherSet | DITHER_ON;
    setDitherMatrix(ditherSet, getMenuValue(&contrastsMenu));
    renderAssistedMenu();
    joypadConsumed();
  } else if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_MENU);
    joypadConsumed();
  } else if (jp == J_A) {
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
