
#include <gb/gb.h>
#include <gbdk/platform.h>

#include "./menus/imageMenuItems.h"
#include "./mainMenu.h"
#include "./joypad.h"
#include "./utils.h"
#include "./defines.h"
#include "./globals.h"
#include "./banks/banks.h"
#include "./bankedData.h"
#include "./printCmd.h"
#include "./expose.h"
#include "./bleep.h"
#include "./imageInfo.h"
#include "../res/font.h"
#include "../res/nope.h"
#include "../res/maps.h"

void renderImageMenu() {
  move_sprite(SPRITE_MENU_INDICATOR, 88, yMenuSprite(imageMenuIndex));
}

void appearImageMenu() {
  move_win(168, 0);

  for (uint8_t i = 0; i < 10; i += 1) {
    scroll_win(-9, 0);
    wait_vbl_done();
  }

  renderImageMenu();
}


void disappearImageMenu() {
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);

  waitRelease();

  for (uint8_t i = 0; i < 10; i += 1) {
    scroll_win(9, 0);
    wait_vbl_done();
  }

  move_win(168, 0);
}

void loadAndShowGalleryImage() {
  if (numVisibleImages > 0) {
    uint8_t imageSlot = getImageSlot(imageIndex);
    SWITCH_RAM(images[imageSlot]->bank);

    set_data(VRAM_9000, images[imageSlot]->tilesUpper, HALF_IMAGE_SIZE);
    set_data(VRAM_8000, images[imageSlot]->tilesLower, HALF_IMAGE_SIZE);

    set_bkg_based_tiles(2, 16, 5, 2, "Image  /  ", OFFSET_FONT - 32);
    writeNumber(1, 17, 2, imageIndex + 1);
    writeNumber(4, 17, 2, numVisibleImages);
  //  writeNumber(2, 16, 3, findFirstFreeSlot());
  } else {
    set_data_banked(VRAM_9000, nope_tiles, HALF_IMAGE_SIZE, 1);
    set_data_banked(VRAM_8000, nope_tiles, HALF_IMAGE_SIZE, 1);

    set_bkg_based_tiles(2, 16, 5, 2, "No   Image", OFFSET_FONT - 32);
  }
}

void initGallery() {
  clearBkg();
  set_bkg_tiles_banked(2, 2, 16, 14, map_normal, 1);

  disappearImageMenu();
  sortImages();
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);
  loadAndShowGalleryImage();
}

void initImageMenu() {
  fill_win_rect(0, 0, 1, 32, MENU_BORDER_LEFT);
  fill_win_rect(1, 0, 31, 32, OFFSET_BLANK);

  for (uint8_t index = 0; index < NUM_IMAGE_MENU_OPTIONS; index += 1) {
    set_win_based_tiles(2, yMenu(index), 8, 1, imageMenuItems[index].title, OFFSET_FONT - 32);
  }
}

void galleryMenu() {

  if (jp == J_RIGHT) {
    imageIndex = (imageIndex + 1) % numVisibleImages;
    loadAndShowGalleryImage();
    joypadConsumed();
  } else if (jp == J_LEFT) {
    imageIndex = (imageIndex + numVisibleImages - 1) % numVisibleImages;
    loadAndShowGalleryImage();
    joypadConsumed();
  } else if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_MENU);
    joypadConsumed();
  } else if (jp == J_A) {
    menuSelectMode(MAIN_LOOP_IMAGE);
    joypadConsumed();
  }
}


void imageMenuAction(uint8_t value) {
  uint8_t address = getImageSlot(imageIndex);

  if (address >= NUM_IMAGES) {
    boop();
    return;
  }

  if (value == IMAGE_MENU_INFO) {
    if (getPrinterStatus()) {
      displayImageInfo(imageIndex);
      initImageMenu();
      renderImageMenu();
    } else {

      getImageInfo(imageIndex, imageInfo);
      printImageInfo(imageInfo, font);

      waitPrinterReady();

      beep();
    }
  } else if (value == IMAGE_MENU_DELETE) {
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
      printImage(images[address]->tilesLower, images[address]->tilesUpper, images[address]->bank);

      waitPrinterReady();

      beep();
    }
  } else if (value == IMAGE_MENU_BLEEP) {
    disappearImageMenu();
    bleep();
    appearImageMenu();
  } else if (value == IMAGE_MENU_EXPOSE) {
    disappearImageMenu();
    expose();
    loadAndShowGalleryImage();
    appearImageMenu();
  }
}

void imageMenu() {

  if (jp == J_UP) {
    imageMenuIndex = (imageMenuIndex + NUM_IMAGE_MENU_OPTIONS - 1) % NUM_IMAGE_MENU_OPTIONS;
    clonk();
    renderImageMenu();
    joypadConsumed();
  } else if (jp == J_DOWN) {
    imageMenuIndex = (imageMenuIndex + 1) % NUM_IMAGE_MENU_OPTIONS;
    clonk();
    renderImageMenu();
    joypadConsumed();
  } else if (jp == J_RIGHT) {
    imageIndex = (imageIndex + 1) % numVisibleImages;
    loadAndShowGalleryImage();
    joypadConsumed();
  } else if (jp == J_LEFT) {
    imageIndex = (imageIndex + numVisibleImages - 1) % numVisibleImages;
    loadAndShowGalleryImage();
    joypadConsumed();
  } else if (jp == J_A) {
    if (numVisibleImages > 0) {
      imageMenuAction(imageMenuItems[imageMenuIndex].value);
    } else {
      boop();
    }
    joypadConsumed();
  } else if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_IMAGE_GALLERY);
    joypadConsumed();
  }

}
