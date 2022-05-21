
void saveImage() {
  unsigned char firstFreeSlot = findFirstFreeSlot();

  if (firstFreeSlot >= NUM_IMAGES) {
    return;
  }

  sortImages();

  SWITCH_RAM(images[firstFreeSlot]->bank);
  get_data(images[firstFreeSlot]->tilesUpper, VRAM_9000, HALF_IMAGE_SIZE);
  get_data(images[firstFreeSlot]->tilesLower, VRAM_8000, HALF_IMAGE_SIZE);

  memcpy(images[firstFreeSlot]->thumbnail, tiles_thumbnail, 256);

  unsigned int exposureTime = exposureTimesValues[getMenuValue(exposureTimesMenu)];

  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_CAPTURE] = getMenuValue(captureModesMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EDGEGAINS] = getMenuValue(edgeOpModesMenu) | getMenuValue(gainsMenu) | getMenuValue(edgeExclusivesMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_HIGH] = (char)(exposureTime >> 8);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_LOW] = (char)exposureTime;
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EDMOVOLT] = getMenuValue(edgeModesMenu) | getMenuValue(voltageRefsMenu) | getMenuValue(invertOutputsMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_VOUTZERO] = getMenuValue(voltageOutsMenu) | getMenuValue(zeroPointsMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_DITHERSET] = getMenuValue(ditherSetsMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_CONTRAST] = getMenuValue(contrastsMenu);

  setImageSlot(firstFreeSlot, numVisibleImages);

  sortImages();
  if (mainLoopState == MAIN_LOOP_SHOOT_MANUAL) {
    renderManualMenu();
  } else {
    clonk();
  }
}

void saveImageDialog() {
  if (findFirstFreeSlot() >= NUM_IMAGES) {
    boop();
    waitRelease();
    return;
  }

  hideLowerViewfinderSprites();

  if (dialog("Save Image?     ")) {
    saveImage();
  }

  showViewfinderSprites();
}
