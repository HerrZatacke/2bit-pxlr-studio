#define DIALOG_ANSWERED 1
#define DIALOG_WAITING 0
#define HALF_IMAGE_SIZE 1792

unsigned char dialogState = 0;
unsigned char nextImageIndex = 0;

unsigned char copyTemp[HALF_IMAGE_SIZE];

void saveImage() {
  if (nextImageIndex == NUM_IMAGES) {
    return;
  }

  SWITCH_RAM(0);
  memcpy(copyTemp, last_seen_upper, HALF_IMAGE_SIZE);

  SWITCH_RAM(images[nextImageIndex]->bank);
  memcpy(images[nextImageIndex]->tilesUpper, copyTemp, HALF_IMAGE_SIZE);

  SWITCH_RAM(0);
  memcpy(copyTemp, last_seen_lower, HALF_IMAGE_SIZE);

  SWITCH_RAM(images[nextImageIndex]->bank);
  memcpy(images[nextImageIndex]->tilesLower, copyTemp, HALF_IMAGE_SIZE);

  nextImageIndex += 1;

  renderMenu();
}

void saveImageDialog() {
  if (nextImageIndex >= NUM_IMAGES) {
    boop();
    waitRelease();
    return;
  }

  beep();
  waitRelease();

  dialogState = DIALOG_WAITING;
  while (dialogState == DIALOG_WAITING) {
    jp = joypad();

    switch(jp) {
      case J_B:
        dialogState = DIALOG_ANSWERED;
        waitRelease();
        jp = 0;
        boop();
        break;
      case J_A:
        dialogState = DIALOG_ANSWERED;
        waitRelease();
        saveImage();
        storeSettings();
        beep();
        break;
    }

    wait_vbl_done();
  }
}
