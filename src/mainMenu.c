
#include <gb/gb.h>
#include <gbdk/platform.h>

#include "./menus/mainMenuItems.h"
#include "./joypad.h"
#include "./utils.h"
#include "./defines.h"
#include "./overlays/overlays.h"

extern void menuSelectMode(unsigned char loopState);

unsigned char mainMenuPos = 0;

void mainMenuSprite() {
  move_sprite(SPRITE_MENU_INDICATOR, 16, yMenuSprite(mainMenuPos));
}

void initMainMenu() {
  clearBkg();
  hideOverlay();

  for (unsigned char index = 0; index < NUM_MAIN_MENU_OPTIONS; index += 1) {
    set_bkg_based_tiles(2, yMenu(index), 16, 1, mainMenuItems[index].title, OFFSET_FONT - 32);
  }

  mainMenuSprite();
}

void mainMenu() {
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
