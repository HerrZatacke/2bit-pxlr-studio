#define HALF_IMAGE_SIZE 1792

unsigned char copyTemp[HALF_IMAGE_SIZE];

void saveImage() {
  unsigned char firstFreeSlot = findFirstFreeSlot();

  if (firstFreeSlot >= NUM_IMAGES) {
    return;
  }

  sortImages();

  SWITCH_RAM(0);
  memcpy(copyTemp, last_seen_upper, HALF_IMAGE_SIZE);

  SWITCH_RAM(images[firstFreeSlot]->bank);
  memcpy(images[firstFreeSlot]->tilesUpper, copyTemp, HALF_IMAGE_SIZE);

  SWITCH_RAM(0);
  memcpy(copyTemp, last_seen_lower, HALF_IMAGE_SIZE);

  SWITCH_RAM(images[firstFreeSlot]->bank);
  memcpy(images[firstFreeSlot]->tilesLower, copyTemp, HALF_IMAGE_SIZE);

  setImageSlot(firstFreeSlot, numVisibleImages);

  sortImages();
  renderMenu();
}

void saveImageDialog() {
  if (findFirstFreeSlot() >= NUM_IMAGES) {
    boop();
    waitRelease();
    return;
  }

  hideLowerManualModeSprites();

  if (dialog("Save Image?     ")) {
    saveImage();
  }

  showManualModeSprites();
}
