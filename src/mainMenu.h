#include "./menus/mainMenuItems.h"

#define yMainMenu(index) (index * 2) + 2
#define yMainMenuSprite(index) (index * 16) + 31

unsigned char mainMenuPos = 0;

inline void mainMenuSprite() {
  move_sprite(SPRITE_MENU_INDICATOR, 16, yMainMenuSprite(mainMenuPos));
}

inline void initMainMenu() {
  for (unsigned char index = 0; index < NUM_MAIN_MENU_OPTIONS; index += 1) {
    set_bkg_based_tiles(2, yMainMenu(index), 16, 1, mainMenuItems[index].title, OFFSET_FONT - 32);
  }

  mainMenuSprite();
}

inline void mainMenu() {
  captureMenuJp();

  if ( jp == 0 || jp == J_B || jp == J_RIGHT ||  jp == J_LEFT || jp == J_SELECT || jp == J_START
      ) {
    jp = 0;
    return;
  } else if (jp == J_DOWN) {
    clonk();
    mainMenuPos = (mainMenuPos + 1) % NUM_MAIN_MENU_OPTIONS;
    mainMenuSprite();
  } else if (jp == J_UP) {
    clonk();
    mainMenuPos = (mainMenuPos + NUM_MAIN_MENU_OPTIONS - 1) % NUM_MAIN_MENU_OPTIONS;
    mainMenuSprite();
  } else if (jp == J_A) {
    menuSelectMode(mainMenuItems[mainMenuPos].value);
  }

  waitabit();

  jp = 0;
}
