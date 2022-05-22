#define yMenu(index) (index * 2) + 2
#define yMenuSprite(index) (index * 16) + 31

unsigned char mainMenuPos = 0;

inline void mainMenuSprite() {
  move_sprite(SPRITE_MENU_INDICATOR, 16, yMenuSprite(mainMenuPos));
}

inline void initMainMenu() {
  clearBkg();
  hideOverlay();

  for (unsigned char index = 0; index < NUM_MAIN_MENU_OPTIONS; index += 1) {
    set_bkg_based_tiles(2, yMenu(index), 16, 1, mainMenuItems[index].title, OFFSET_FONT - 32);
  }

  mainMenuSprite();
}

inline void mainMenu() {
  if (jp == J_DOWN) {
    clonk();
    mainMenuPos = (mainMenuPos + 1) % NUM_MAIN_MENU_OPTIONS;
    mainMenuSprite();
    joypadConsumed();
  } else if (jp == J_UP) {
    clonk();
    mainMenuPos = (mainMenuPos + NUM_MAIN_MENU_OPTIONS - 1) % NUM_MAIN_MENU_OPTIONS;
    mainMenuSprite();
    joypadConsumed();
  } else if (jp == J_A) {
    menuSelectMode(mainMenuItems[mainMenuPos].value);
    joypadConsumed();
  }
}
