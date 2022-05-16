
void saveImage() {
  unsigned char firstFreeSlot = findFirstFreeSlot();

  if (firstFreeSlot >= NUM_IMAGES) {
    return;
  }

  sortImages();

  SWITCH_RAM(images[firstFreeSlot]->bank);
  get_data(images[firstFreeSlot]->tilesUpper, VRAM_9000, HALF_IMAGE_SIZE);
  get_data(images[firstFreeSlot]->tilesLower, VRAM_8000, HALF_IMAGE_SIZE);

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
