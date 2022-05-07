unsigned char jp = 0;
unsigned char menuPos = 0;

#define NUM_MENU_ELEMENTS 11

// same as readable number of "images taken"
extern unsigned char nextImageIndex;

typedef struct {
  const unsigned char x;
  const unsigned char page;
  unsigned char value;
  const unsigned char storeOffset;
  const unsigned char numOptions;
  const unsigned char defaultValue;
  const unsigned char* title;
  const unsigned char* description;
  const MenuOption* options;
} MenuItem;

MenuItem gainsMenu =          {  0, 0, 0,  1,     NUM_GAIN_LEVELS,     (NUM_GAIN_LEVELS >> 1) - 1, "Gain", "   Sensor     Gain",          &gains[0], };
MenuItem exposureTimesMenu =  {  5, 0, 0,  2,  NUM_EXPOSURE_TIMES,  (NUM_EXPOSURE_TIMES >> 1) - 1, "ExpT", " Exposure     Time",  &exposureTimes[0], };
MenuItem voltageRefsMenu =    { 10, 0, 0,  6,    NUM_VOLTAGE_REFS,    (NUM_VOLTAGE_REFS >> 1) - 1, "vRef", "  VoltageReference",    &voltageRefs[0], };
MenuItem voltageOutsMenu =    { 15, 0, 0,  8,    NUM_VOLTAGE_OUTS,    (NUM_VOLTAGE_OUTS >> 1) - 1, "vOut", "  Voltage   Output",    &voltageOuts[0], };
MenuItem invertOutputsMenu =  {  0, 1, 0, 11,  NUM_INVERT_OUTPUTS,                              0, "InvO", "   Invert   Output",  &invertOutputs[0], };
MenuItem zeroPointsMenu =     {  5, 1, 0,  7,     NUM_ZERO_POINTS,                              1, "0 Pt", "     Zero   Points",     &zeroPoints[0], };
MenuItem ditherHighLowsMenu = { 10, 1, 0,  4, NUM_DITHER_HIGHLOWS,                              1, "dSet", "   Dither      set", &ditherHighLows[0], };
MenuItem ditherSetsMenu =     { 15, 1, 0,  3,         NUM_DITHERS,                              1, "Dith", "   Dither   Matrix",     &ditherSets[0], };
MenuItem edgeOpModesMenu =    {  0, 2, 0,  9,   NUM_EDGE_OP_MODES,                              0, "EdOp", "     EdgeOperation",    &edgeOpModes[0], };
MenuItem edgeModesMenu =      {  5, 2, 0,  5,      NUM_EDGE_MODES,      (NUM_EDGE_MODES >> 1) - 1, "EdMo", "     Edge     Mode",      &edgeModes[0], };
MenuItem edgeExclusivesMenu = { 10, 2, 0, 10,  NUM_EDGE_EXCLUSIVE,                              0, "EdEx", "     EdgeExclusive", &edgeExclusives[0], };

MenuItem *menuItems[NUM_MENU_ELEMENTS] = {
  &gainsMenu,
  &exposureTimesMenu,
  &voltageRefsMenu,
  &voltageOutsMenu,
  &invertOutputsMenu,
  &zeroPointsMenu,
  &ditherHighLowsMenu,
  &ditherSetsMenu,
  &edgeOpModesMenu,
  &edgeModesMenu,
  &edgeExclusivesMenu,
};

#define getMenuValue(menuItem) menuItem.options[menuItem.value].value

inline void captureMenuJp() {
  if (jp == 0) {
    jp = joypad();
  }
}

inline void storeSettings() {
  SWITCH_RAM(1);
  image_01_unused[0] = nextImageIndex;
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
    nextImageIndex = image_01_unused[0] > 30 ? 30 : image_01_unused[0];

    for (i = 0; i < NUM_MENU_ELEMENTS; i += 1) {
      menuItems[i]->value = image_01_unused[menuItems[i]->storeOffset];
    }

    return 0;
  }

  // 1 forces a reset to defaults
  return 1;
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
  writeNumber(12, 16, nextImageIndex);

  unsigned char spriteX = (menuItems[menuPos]->x * 8) + 38;
  move_sprite(SPRITE_MENU_INDICATOR, spriteX, 20);
}

inline void menu() {
  if ( jp == 0 || jp == J_A || jp == J_B || jp == J_SELECT || jp == J_START
  ) {
    jp = 0;
    return;
  } else if (jp == J_RIGHT) {
    menuPos = (menuPos + 1) % NUM_MENU_ELEMENTS;
  } else if (jp == J_LEFT) {
    menuPos = (menuPos + NUM_MENU_ELEMENTS - 1) % NUM_MENU_ELEMENTS;
  } else if (jp == J_UP) {
    menuItems[menuPos]->value = (menuItems[menuPos]->value + 1) % menuItems[menuPos]->numOptions;
  } else if (jp == J_DOWN) {
    menuItems[menuPos]->value = (menuItems[menuPos]->value + menuItems[menuPos]->numOptions - 1) % menuItems[menuPos]->numOptions;
  }

  storeSettings();
  renderMenu();

  jp = 0;
}
