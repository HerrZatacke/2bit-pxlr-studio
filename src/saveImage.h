#define DIALOG_ANSWERED 1
#define DIALOG_WAITING 0
#define HALF_IMAGE_SIZE 1792

unsigned char dialogState = 0;
unsigned char nextImageIndex = 0;

unsigned char copyTemp[HALF_IMAGE_SIZE];

void saveImage() {
  if (nextImageIndex == 30) {
    return;
  }

  unsigned int i;

  SWITCH_RAM(0);
  for (i = 0; i < HALF_IMAGE_SIZE; i += 1) {
    copyTemp[i] = last_seen_upper[i];
  }

  SWITCH_RAM(images[nextImageIndex]->bank);
  for (i = 0; i < HALF_IMAGE_SIZE; i += 1) {
    images[nextImageIndex]->tilesUpper[i] = copyTemp[i];
  }

  SWITCH_RAM(0);
  for (i = 0; i < HALF_IMAGE_SIZE; i += 1) {
    copyTemp[i] = last_seen_lower[i];
  }

  SWITCH_RAM(images[nextImageIndex]->bank);
  for (i = 0; i < HALF_IMAGE_SIZE; i += 1) {
    images[nextImageIndex]->tilesLower[i] = copyTemp[i];
  }

  nextImageIndex += 1;

  renderMenu();
}

void saveImageDialog() {
  if (nextImageIndex >= 30) {
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
