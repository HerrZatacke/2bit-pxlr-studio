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
#include "modeShootingManual.h"
#include "images.h"

void saveImage(uint8_t capt, uint8_t edExOpGain, uint16_t expTime, uint8_t edRInvVref, uint8_t zeroVout, uint8_t ditherSet, uint8_t contrast) BANKED {
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

  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_CAPTURE] = capt;
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EDGEGAINS] = edExOpGain;
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_HIGH] = (uint8_t)(expTime >> 8);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_LOW] = (uint8_t)expTime;
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EDMOVOLT] = edRInvVref;
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_VOUTZERO] = zeroVout;
  // ToDo: Add dither and contrasts to save options
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_DITHERSET] = ditherSet;
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_CONTRAST] = contrast;

  setImageSlot(firstFreeSlot, numVisibleImages);

  sortImages();
  if (mainLoopState == MAIN_LOOP_SHOOT_MANUAL) {
    renderManualMenu();
  } else {
    clonk();
  }
}

void saveImageDialog(uint8_t capt, uint8_t edExOpGain, uint16_t expTime, uint8_t edRInvVref, uint8_t zeroVout, uint8_t ditherSet, uint8_t contrast) BANKED {
  if (findFirstFreeSlot() >= NUM_IMAGES) {
    boop();
    waitRelease();
    return;
  }

  if (dialog("Save Image?     ", 1)) {
    saveImage(capt, edExOpGain, expTime, edRInvVref, zeroVout, ditherSet, contrast);
  }
}
