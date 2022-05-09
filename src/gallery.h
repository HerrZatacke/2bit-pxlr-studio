void loadAndShowGalleryImage() {
  unsigned char imageSlot = getImageSlot(imageIndex);
  SWITCH_RAM(images[imageSlot]->bank);

  LCDC_REG |= LCDCF_BG8000;
  set_bkg_data(0, 112, images[imageSlot]->tilesLower);
  LCDC_REG &= ~LCDCF_BG8000;
  set_bkg_data(0, 112, images[imageSlot]->tilesUpper);

  set_bkg_based_tiles(13, 16, 5, 2, "Image  /  ", OFFSET_FONT - 32);
  writeNumber(12, 17, 2, imageIndex + 1);
  writeNumber(15, 17, 2, numVisibleImages);
}

void initGallery() {
  sortImages();
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
    imageIndex = (imageIndex + 1) % numVisibleImages;
    loadAndShowGalleryImage();
  } else if (jp == J_LEFT) {
    imageIndex = (imageIndex + numVisibleImages - 1) % numVisibleImages;
    loadAndShowGalleryImage();
  } else if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_MENU);
    jp = 0;
    return;
  }

  waitabit();

  jp = 0;
}
