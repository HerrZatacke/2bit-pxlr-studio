#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>
#include "tiles.h"
#include "imageIndexing.h"
#include "defines.h"
#include "globals.h"
#include "utils.h"
#include "joypad.h"
#include "dialog.h"
#include "images.h"
#include "values.h"
#include "menus/shootingManualMenuItems.h"
#include "modeShootingManual.h"
#include "images.h"

void saveImage() BANKED {
  uint8_t firstFreeSlot = findFirstFreeSlot();

  if (firstFreeSlot >= NUM_IMAGES) {
    return;
  }

  sortImages();

  SWITCH_RAM(images[firstFreeSlot]->bank);
  get_data(images[firstFreeSlot]->tilesUpper, VRAM_9000, HALF_IMAGE_SIZE);
  get_data(images[firstFreeSlot]->tilesLower, VRAM_8000, HALF_IMAGE_SIZE);

  // ToDo:
  // This crashes if this .c file is in a #pragma bank 2
  memcpy(images[firstFreeSlot]->thumbnail, tiles_thumbnail, 256);

  uint16_t exposureTime = exposureTimesValues[getMenuValue(&exposureTimesMenu)];

  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_CAPTURE] = getMenuValue(&captureModesMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EDGEGAINS] = getMenuValue(&edgeOpModesMenu) | getMenuValue(&gainsMenu) | getMenuValue(&edgeExclusivesMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_HIGH] = (int8_t)(exposureTime >> 8);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_LOW] = (int8_t)exposureTime;
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EDMOVOLT] = getMenuValue(&edgeModesMenu) | getMenuValue(&voltageRefsMenu) | getMenuValue(&invertOutputsMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_VOUTZERO] = getMenuValue(&voltageOutsMenu) | getMenuValue(&zeroPointsMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_DITHERSET] = getMenuValue(&ditherSetsMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_CONTRAST] = getMenuValue(&contrastsMenu);

  setImageSlot(firstFreeSlot, numVisibleImages);

  sortImages();
  if (mainLoopState == MAIN_LOOP_SHOOT_MANUAL) {
    renderManualMenu();
  } else {
    clonk();
  }
}

void saveImageDialog() BANKED {
  if (findFirstFreeSlot() >= NUM_IMAGES) {
    boop();
    waitRelease();
    return;
  }

  if (dialog("Save Image?     ", 1)) {
    saveImage();
  }
}
