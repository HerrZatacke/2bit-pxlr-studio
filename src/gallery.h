#define NUM_IMAGES 30

#define getImageIndex() imageIndex
unsigned char imageIndex = 0;

void loadAndShowGalleryImage() {
  SWITCH_RAM(images[getImageIndex()]->bank);

  LCDC_REG |= LCDCF_BG8000;
  set_bkg_data(0, 112, images[getImageIndex()]->tilesLower);
  LCDC_REG &= ~LCDCF_BG8000;
  set_bkg_data(0, 112, images[getImageIndex()]->tilesUpper);

  set_bkg_based_tiles(13, 16, 5, 2, "Image  /30", OFFSET_FONT - 32);
  writeNumber(12, 17, imageIndex + 1);
}

void initGallery() {
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);
  imageIndex = 0;
  loadAndShowGalleryImage();
}

void galleryMenu() {
  captureMenuJp();

  if ( jp == 0 || jp == J_A || jp == J_DOWN ||  jp == J_UP || jp == J_SELECT || jp == J_START ) {
    jp = 0;
    return;
  } else if (jp == J_RIGHT) {
    imageIndex = (imageIndex + 1) % NUM_IMAGES;
    loadAndShowGalleryImage();
  } else if (jp == J_LEFT) {
    imageIndex = (imageIndex + NUM_IMAGES - 1) % NUM_IMAGES;
    loadAndShowGalleryImage();
  } else if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_MENU);
    jp = 0;
    return;
  }

  waitabit();

  jp = 0;
}
