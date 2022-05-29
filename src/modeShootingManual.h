#include "./typedefs/MenuItem.h"
#include "./globals.h"

unsigned char menuPos = 0;
MenuItem tmpMenuItem;
extern void saveImageDialog();
extern unsigned char numVisibleImages;

#define getMenuValue(menuItem) menuItem.options[menuItem.value].value

void renderManualMenu();

void initManualMode() {
  clearBkg();
  set_bkg_tiles_banked(2, 2, 16, 14, map_normal, 1);
  sortImages();
  showOverlay();
  renderManualMenu();
}

void storeSettings() {
  SWITCH_RAM(1);
  savedBank = _current_bank;
  SWITCH_ROM(2);
  for (unsigned char i = 0; i < NUM_MENU_ELEMENTS; i += 1) {
    image_01_unused[menuItems[i]->storeOffset] = menuItems[i]->value;
  }
  SWITCH_ROM(savedBank);
}

void restoreDefaults() {
  savedBank = _current_bank;
  SWITCH_ROM(2);
  for (unsigned char i = 0; i < NUM_MENU_ELEMENTS; i += 1) {
    menuItems[i]->value = menuItems[i]->defaultValue;
  }
  SWITCH_ROM(savedBank);

  setDitherMatrix();
}

unsigned char restoreSettings() {
  SWITCH_RAM(1);

  unsigned char i = 0;
  unsigned char noAA = 0;

  savedBank = _current_bank;
  SWITCH_ROM(2);
  // check if any of the storage cells already has a valid value
  // the initial value which is never changes on an original cart is 0xAA
  for (i = 0; i < NUM_MENU_ELEMENTS; i += 1) {
    if (image_01_unused[menuItems[i]->storeOffset] != 0xAA) {
      noAA = 1;
    }
  }
  SWITCH_ROM(savedBank);

  // load initial values from storage cells
  if (noAA) {

    savedBank = _current_bank;
    SWITCH_ROM(2);
    for (i = 0; i < NUM_MENU_ELEMENTS; i += 1) {
      menuItems[i]->value = image_01_unused[menuItems[i]->storeOffset];
    }
    SWITCH_ROM(savedBank);

    return 0;
  }

  // 1 forces a reset to defaults
  return 1;
}

void renderManualMenu() {
  clonk();
  fill_bkg_rect(0, 0, 20, 2, BLNK);
  fill_bkg_rect(0, 16, 20, 2, BLNK);

  savedBank = _current_bank;
  SWITCH_ROM(2);

  unsigned char currentPage = menuItems[menuPos]->page;
  unsigned char spriteX = (menuItems[menuPos]->x * 8) + 8;
  move_sprite(SPRITE_MENU_INDICATOR, spriteX, 23);

  for (unsigned char i = 0; i < NUM_MENU_ELEMENTS; i += 1) {

    if (menuItems[i]->page == currentPage) {

      unsigned char value = menuItems[i]->value;
      set_bkg_based_tiles(menuItems[i]->x, 0, MENU_TEXT_LENGTH, 1, menuItems[i]->title, OFFSET_FONT - 32);
      set_bkg_based_tiles(menuItems[i]->x, 1, MENU_TEXT_LENGTH, 1, menuItems[i]->options[value].title, OFFSET_FONT - 32);

    }
  }

  set_bkg_based_tiles(0, 16, 9, 2, menuItems[menuPos]->description, OFFSET_FONT - 32);

  SWITCH_ROM(savedBank);

  set_bkg_based_tiles(12, 16, 6, 2, "   /30Images", OFFSET_FONT - 32);
  writeNumber(12, 16, 2, numVisibleImages);
}

void menuAction() {
  savedBank = _current_bank;
  SWITCH_ROM(2);
  if (menuItems[menuPos]->action == MENU_ACTION_DITHER) {
    setDitherMatrix();
  }
  SWITCH_ROM(savedBank);
}

void manualShootMenu() {
  if (jp == J_RIGHT) {
    menuPos = (menuPos + 1) % NUM_MENU_ELEMENTS;
    renderManualMenu();
    joypadConsumed();
  } else if (jp == J_LEFT) {
    menuPos = (menuPos + NUM_MENU_ELEMENTS - 1) % NUM_MENU_ELEMENTS;
    renderManualMenu();
    joypadConsumed();
  } else if (jp == J_UP) {

    savedBank = _current_bank;
    SWITCH_ROM(2);
    menuItems[menuPos]->value = (menuItems[menuPos]->value + 1) % menuItems[menuPos]->numOptions;
    SWITCH_ROM(savedBank);

    menuAction();
    storeSettings();
    renderManualMenu();
    joypadConsumed();
  } else if (jp == J_DOWN) {

    savedBank = _current_bank;
    SWITCH_ROM(2);
    menuItems[menuPos]->value = (menuItems[menuPos]->value + menuItems[menuPos]->numOptions - 1) % menuItems[menuPos]->numOptions;
    SWITCH_ROM(savedBank);

    menuAction();
    storeSettings();
    renderManualMenu();
    joypadConsumed();
  } else if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_MENU);
    joypadConsumed();
  } else if (jp == (J_SELECT | J_START)) {
    restoreDefaults();
    beep();
    storeSettings();
    renderManualMenu();
    waitRelease();
    joypadConsumed();
  } else if (jp == J_A) {
    saveImageDialog();
    joypadConsumed();
  } else if (jp == J_SELECT) {
    nextOverlay();
    clonk();
    showOverlay();
    joypadConsumed();
  }
}
