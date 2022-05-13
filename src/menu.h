
unsigned char menuPos = 0;

#include "menus/shootingManual.h"

#define getMenuValue(menuItem) menuItem.options[menuItem.value].value

inline void renderMenu();

inline void initManualMode() {
  clearBkg();
  set_bkg_tiles(0, 0, 20, 18, map_normal);
  sortImages();
  initManualModeSprites();
  renderMenu();
}

inline void storeSettings() {
  SWITCH_RAM(1);
  for (unsigned char i = 0; i < NUM_MENU_ELEMENTS; i += 1) {
    image_01_unused[menuItems[i]->storeOffset] = menuItems[i]->value;
  }
}

inline void restoreDefaults() {
  for (unsigned char i = 0; i < NUM_MENU_ELEMENTS; i += 1) {
    menuItems[i]->value = menuItems[i]->defaultValue;
  }
}

inline unsigned char restoreSettings() {
  SWITCH_RAM(1);

  unsigned char i = 0;
  unsigned char noAA = 0;

  // check if any of the storage cells already has a valid value
  // the initial value which is never changes on an original cart is 0xAA
  for (i = 0; i < NUM_MENU_ELEMENTS; i += 1) {
    if (image_01_unused[menuItems[i]->storeOffset] != 0xAA) {
      noAA = 1;
    }
  }

  // load initial values from storage cells
  if (noAA) {

    for (i = 0; i < NUM_MENU_ELEMENTS; i += 1) {
      menuItems[i]->value = image_01_unused[menuItems[i]->storeOffset];
    }

    return 0;
  }

  // 1 forces a reset to defaults
  return 1;
}

const unsigned char hexCharLUT[16] = { 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, };

inline void showRegister(unsigned char y, unsigned char value) {
  unsigned char chars[2] = {
    hexCharLUT[(value >> 4) & 0b00001111],
    hexCharLUT[value & 0b00001111],
  };

  set_bkg_tiles(0, y, 2, 1, chars);
}


// Registers A001-A005 in original ROM
// 0xE4, 0x45, 0x00, 0x03, 0xA7 when getting lighter   // Gain:20.0 / EdOp:2d / EdEx:V-On // ExpT:-Dim // EdMo:50% / vRef:1.5v / InvO:Off // 0 Pt:pos / vOut:+224
// 0xE8, 0x35, 0x00, 0x03, 0xA9 when getting darker    // Gain:xx.x / EdOp:2d / EdEx:V-On // ExpT:+Dim // EdMo:50% / vRef:1.5v / InvO:Off // 0 Pt:pos / vOut:+288

inline void showRegisters() {
  unsigned int exposureTime = exposureTimesValues[getMenuValue(exposureTimesMenu)];

  // BitMask      01100000                        00011111                  10000000
  showRegister(4, getMenuValue(edgeOpModesMenu) | getMenuValue(gainsMenu) | getMenuValue(edgeExclusivesMenu));

  // BitMask      11111111
  showRegister(5, exposureTime >> 8);

  // BitMask      11111111
  showRegister(6, exposureTime);

  // BitMask      01110000                      00000111                        00001000
  showRegister(7, getMenuValue(edgeModesMenu) | getMenuValue(voltageRefsMenu) | getMenuValue(invertOutputsMenu));

  // BitMask      00111111                        01000000
  showRegister(8, getMenuValue(voltageOutsMenu) | getMenuValue(zeroPointsMenu));
}

inline void renderMenu() {
  clonk();
  unsigned char currentPage = menuItems[menuPos]->page;
  fill_bkg_rect(0, 0, 20, 2, BLNK);
  fill_bkg_rect(0, 16, 20, 2, BLNK);

  for (unsigned char i = 0; i < NUM_MENU_ELEMENTS; i += 1) {

    if (menuItems[i]->page == currentPage) {
      unsigned char value = menuItems[i]->value;
      set_bkg_based_tiles(menuItems[i]->x, 0, 4, 1, menuItems[i]->title, OFFSET_FONT - 32);
      set_bkg_based_tiles(menuItems[i]->x, 1, 4, 1, menuItems[i]->options[value].title, OFFSET_FONT - 32);
    }
  }

  set_bkg_based_tiles(0, 16, 9, 2, menuItems[menuPos]->description, OFFSET_FONT - 32);

  set_bkg_based_tiles(12, 16, 6, 2, "   /30Images", OFFSET_FONT - 32);
  writeNumber(12, 16, 2, numVisibleImages);

//  showRegisters();

  unsigned char spriteX = (menuItems[menuPos]->x * 8) + 3;
  move_sprite(SPRITE_MENU_INDICATOR, spriteX, 20);
}

inline void menuAction() {
  if (menuItems[menuPos]->action == MENU_ACTION_DITHER) {
    setDitherMatrix();
  }
}

inline void manualShootMenu() {
  if ( jp == 0 || jp == J_A || jp == J_SELECT || jp == J_START ) {
    jp = 0;
    return;
  } else if (jp == J_RIGHT) {
    menuPos = (menuPos + 1) % NUM_MENU_ELEMENTS;
  } else if (jp == J_LEFT) {
    menuPos = (menuPos + NUM_MENU_ELEMENTS - 1) % NUM_MENU_ELEMENTS;
  } else if (jp == J_UP) {
    menuItems[menuPos]->value = (menuItems[menuPos]->value + 1) % menuItems[menuPos]->numOptions;
    menuAction();
  } else if (jp == J_DOWN) {
    menuItems[menuPos]->value = (menuItems[menuPos]->value + menuItems[menuPos]->numOptions - 1) % menuItems[menuPos]->numOptions;
    menuAction();
  } else if (jp == J_B) {
    menuSelectMode(MAIN_LOOP_MENU);
    jp = 0;
    return;
  }

  storeSettings();
  renderMenu();

  jp = 0;
}
