unsigned char burstActive = 0;
extern unsigned char numVisibleImages;

extern void saveImage();

inline void renderBurstMenu() {
  set_bkg_based_tiles(12, 16, 6, 2, "   /30Images", OFFSET_FONT - 32);
  writeNumber(12, 16, 2, numVisibleImages);
}

inline void initBurstMode() {
  clearBkg();
  set_bkg_tiles(0, 0, 20, 18, map_normal);
  sortImages();
  showViewfinderSprites();
  renderBurstMenu();
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);
  burstActive = 0;
}

inline void burstShootMenu() {
  if (jp == J_B) {
    burstActive = 0;
    menuSelectMode(MAIN_LOOP_MENU);
    joypadConsumed();
  } else if (jp == J_A) {
    burstActive = 1;
    beep();
    joypadConsumed();
  }

  if (burstActive == 1) {
    if (findFirstFreeSlot() != NUM_IMAGES) {
      saveImage();
      renderBurstMenu();
    } else {
      boop();
      burstActive = 0;
    }
  }
}
