#define THUMBNAIL_BYTE_CAPTURE       0x00
#define THUMBNAIL_BYTE_EDGEGAINS     0x10
#define THUMBNAIL_BYTE_EXPOSURE_HIGH 0x20
#define THUMBNAIL_BYTE_EXPOSURE_LOW  0x30
#define THUMBNAIL_BYTE_EDMOVOLT      0xC6
#define THUMBNAIL_BYTE_VOUTZERO      0xD6
#define THUMBNAIL_BYTE_DITHERHIGHLOW 0xE6
#define THUMBNAIL_BYTE_DITHERSET     0xF6

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

  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_CAPTURE] = A000_CAPTURE_POSITIVE | A000_START_CAPTURE;
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EDGEGAINS] = getMenuValue(edgeOpModesMenu) | getMenuValue(gainsMenu) | getMenuValue(edgeExclusivesMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_HIGH] = (char)(exposureTime >> 8);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_LOW] = (char)exposureTime;
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_EDMOVOLT] = getMenuValue(edgeModesMenu) | getMenuValue(voltageRefsMenu) | getMenuValue(invertOutputsMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_VOUTZERO] = getMenuValue(voltageOutsMenu) | getMenuValue(zeroPointsMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_DITHERHIGHLOW] = getMenuValue(ditherHighLowsMenu);
  images[firstFreeSlot]->thumbnail[THUMBNAIL_BYTE_DITHERSET] = getMenuValue(ditherSetsMenu);

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
