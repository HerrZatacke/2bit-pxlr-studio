#define DIALOG_ANSWERED 1
#define DIALOG_WAITING 0
#define HALF_IMAGE_SIZE 1792

unsigned char dialogState = 0;

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

  beep();
  waitRelease();

  dialogState = DIALOG_WAITING;
  while (dialogState == DIALOG_WAITING) {
    if (jp == J_B) {
      dialogState = DIALOG_ANSWERED;
      waitRelease();
      joypadConsumed();
      boop();
    } else if (jp == J_A) {
      dialogState = DIALOG_ANSWERED;
      waitRelease();
      saveImage();
      storeSettings();
      beep();
    }

    wait_vbl_done();
  }
}
