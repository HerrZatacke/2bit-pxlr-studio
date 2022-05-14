unsigned char imageIndex = 0;
unsigned char imageMenuIndex = 0;

void loadAndShowGalleryImage();

#include "menus/imageMenuItems.h"
#include "./bleep.h"
#include "./expose.h"
#include "./printCmd.h"

inline void appearImageMenu() {
  HIDE_SPRITES;
  while (SCX_REG < 90) {
    SCX_REG += 5;
    wait_vbl_done();
  };
  SHOW_SPRITES;
}

inline void disappearImageMenu() {
  HIDE_SPRITES;
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);
  while (SCX_REG > 0) {
    SCX_REG -= 5;
    wait_vbl_done();
  };
  SHOW_SPRITES;
}

void loadAndShowGalleryImage() {
  if (numVisibleImages > 0) {
    unsigned char imageSlot = getImageSlot(imageIndex);
    SWITCH_RAM(images[imageSlot]->bank);

    LCDC_REG &= ~LCDCF_BG8000;
    set_bkg_data(0, 112, images[imageSlot]->tilesUpper);
    LCDC_REG |= LCDCF_BG8000;
    set_bkg_data(0, 112, images[imageSlot]->tilesLower);

    set_bkg_based_tiles(13, 16, 5, 2, "Image  /  ", OFFSET_FONT - 32);
    writeNumber(12, 17, 2, imageIndex + 1);
    writeNumber(15, 17, 2, numVisibleImages);
  //  writeNumber(2, 16, 3, findFirstFreeSlot());
  } else {
    LCDC_REG &= ~LCDCF_BG8000;
    set_bkg_data(0, 112, nope_tiles);
    LCDC_REG |= LCDCF_BG8000;
    set_bkg_data(0, 112, nope_tiles);

    set_bkg_based_tiles(13, 16, 5, 2, "   NoImage", OFFSET_FONT - 32);
  }
}

void initGallery() {
  set_bkg_tiles(0, 0, 20, 18, map_normal);
  disappearImageMenu();
  sortImages();
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);
  loadAndShowGalleryImage();
}


void renderImageMenu() {
  move_sprite(SPRITE_MENU_INDICATOR, 87, yMenuSprite(imageMenuIndex));
}

void initImageMenu() {
  set_bkg_tiles(20, 0, 12, 18, map_sideMenu);
  set_bkg_tiles(0, 0, 20, 18, map_normal);

  for (unsigned char index = 0; index < NUM_IMAGE_MENU_OPTIONS; index += 1) {
    set_bkg_based_tiles(22, yMenu(index), 8, 1, imageMenuItems[index].title, OFFSET_FONT - 32);
  }

  appearImageMenu();
  loadAndShowGalleryImage();
  renderImageMenu();
}

void galleryMenu() {
  captureMenuJp();

  if ( jp == 0 || jp == J_DOWN ||  jp == J_UP || jp == J_SELECT || jp == J_START ) {
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
  } else if (jp == J_A) {
    menuSelectMode(MAIN_LOOP_IMAGE);
  }

  waitabit();

  jp = 0;
}


inline void imageMenuAction(unsigned char value) {
  unsigned char address = getImageSlot(imageIndex);

  if (address >= NUM_IMAGES) {
    boop();
    return;
  }

  if (value == IMAGE_MENU_DELETE) {
    setImageSlot(address, 0xff);
    reduceIndexAfterDelete(imageIndex);
    sortImages();
    if (imageIndex > 0) {
      imageIndex = (imageIndex + numVisibleImages - 1) % numVisibleImages;
    }
    loadAndShowGalleryImage();
    clonk();
  } else if (value == IMAGE_MENU_PRINT) {
    printerInit();
    if (getPrinterStatus()) {
      boop();
    } else {
      disappearImageMenu();
      unsigned char imageSlot = getImageSlot(imageIndex);
      printImage(images[imageSlot]->tilesLower, images[imageSlot]->tilesUpper, images[imageSlot]->bank);
      beep();
      appearImageMenu();
    }
  } else if (value == IMAGE_MENU_BLEEP) {
    disappearImageMenu();
    bleep();
    appearImageMenu();
  } else if (value == IMAGE_MENU_EXPOSE) {
    disappearImageMenu();
    expose();
    appearImageMenu();
  }
}

void imageMenu() {
  captureMenuJp();
  if ( jp == 0 || jp == J_SELECT || jp == J_START ) {
    jp = 0;
    return;
  } else if (jp == J_UP) {
    imageMenuIndex = (imageMenuIndex + NUM_IMAGE_MENU_OPTIONS - 1) % NUM_IMAGE_MENU_OPTIONS;
    clonk();
  } else if (jp == J_DOWN) {
    imageMenuIndex = (imageMenuIndex + 1) % NUM_IMAGE_MENU_OPTIONS;
    clonk();
  } else if (jp == J_RIGHT) {
    imageIndex = (imageIndex + 1) % numVisibleImages;
    loadAndShowGalleryImage();
  } else if (jp == J_LEFT) {
    imageIndex = (imageIndex + numVisibleImages - 1) % numVisibleImages;
    loadAndShowGalleryImage();
  } else if (jp == J_A) {
    if (numVisibleImages > 0) {
      imageMenuAction(imageMenuItems[imageMenuIndex].value);
    } else {
      boop();
    }
    jp = 0;
  } else if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_IMAGE_GALLERY);
    jp = 0;
    return;
  }

  renderImageMenu();
  waitabit();

  jp = 0;
}
