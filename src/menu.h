unsigned char jp = 0;
unsigned char menuPos = 0;

unsigned char numMenuElements = 11;

unsigned char gain = 0;
unsigned char exposureTime = 0;
unsigned char ditherIndex = 0;
unsigned char ditherHighLow = 0;
unsigned char edgeMode = 0;
unsigned char voltageRef = 0;
unsigned char zeroPoint = 0;
unsigned char voltageOut = 0;
unsigned char edgeOpMode = 0;
unsigned char edgeExclusive = 0;
unsigned char invertOutput = 0;

extern unsigned char nextImageIndex;

inline void captureMenuJp() {
  if (jp == 0) {
    jp = joypad();
  }
}

inline void storeSettings() {
  SWITCH_RAM(1);
  image_01_unused[0] = nextImageIndex;
  image_01_unused[1] = gain;
  image_01_unused[2] = exposureTime;
  image_01_unused[3] = ditherIndex;
  image_01_unused[4] = ditherHighLow;
  image_01_unused[5] = edgeMode;
  image_01_unused[6] = voltageRef;
  image_01_unused[7] = zeroPoint;
  image_01_unused[8] = voltageOut;
  image_01_unused[9] = edgeOpMode;
  image_01_unused[10] = edgeExclusive;
  image_01_unused[11] = invertOutput;
}

inline unsigned char restoreSettings() {
  SWITCH_RAM(1);

  if (
    image_01_unused[0] == 0xAA &&
    image_01_unused[1] == 0xAA &&
    image_01_unused[2] == 0xAA &&
    image_01_unused[3] == 0xAA &&
    image_01_unused[4] == 0xAA &&
    image_01_unused[5] == 0xAA &&
    image_01_unused[6] == 0xAA &&
    image_01_unused[7] == 0xAA &&
    image_01_unused[8] == 0xAA &&
    image_01_unused[9] == 0xAA &&
    image_01_unused[10] == 0xAA &&
    image_01_unused[11] == 0xAA
  ) {
    return 1;
  }

  nextImageIndex = image_01_unused[0] > 30 ? 30 : image_01_unused[10];
  gain = image_01_unused[1] % NUM_GAIN_LEVELS;
  exposureTime = image_01_unused[2] % NUM_EXPOSURE_TIMES;
  ditherIndex = image_01_unused[3] % NUM_DITHERS;
  ditherHighLow = image_01_unused[4] % NUM_DITHER_HIGHLOWS;
  edgeMode = image_01_unused[5] % NUM_EDGE_MODES;
  voltageRef = image_01_unused[6] % NUM_VOLTAGE_REFS;
  zeroPoint = image_01_unused[7] % NUM_ZERO_POINTS;
  voltageOut = image_01_unused[8] % NUM_VOLTAGE_OUTS;
  edgeOpMode = image_01_unused[9] % NUM_EDGE_OP_MODES;
  edgeExclusive = image_01_unused[10] % NUM_EDGE_EXCLUSIVE;
  invertOutput = image_01_unused[11] % NUM_INVERT_OUTPUTS;

  return 0;
}

inline void renderMenu() {
  clonk();

  unsigned char posOffsetX = 0;
  unsigned char posOffsetY = menuPos > 4 ? 24 : 152;

  switch (menuPos % 5) {
    case 0:
      posOffsetX = 10;
      break;
    case 1:
      posOffsetX = 34;
      break;
    case 2:
      posOffsetX = 58;
      break;
    case 3:
      posOffsetX = 82;
      break;
    case 4:
      posOffsetX = 106;
      break;
  }

  if (menuPos == 10) {
    posOffsetX = 130;
    posOffsetY = 24;
  }


  move_sprite(SPRITE_MENU_INDICATOR_L, posOffsetX, posOffsetY);
  move_sprite(SPRITE_MENU_INDICATOR_R, posOffsetX + 20, posOffsetY);

  showDigit(edgeMode + 1, 2, 1, 1);
  showDigit(edgeExclusive, 2, 4, 1);
  showDigit(voltageRef + 1, 2, 7, 1);
  showDigit(zeroPoint + 1, 2, 10, 1);
  showDigit(voltageOut + 1, 2, 13, 1);
  showDigit(invertOutput, 2, 16, 1);

  showDigit(gain + 1, 2, 1, 17);
  showDigit(exposureTime + 1, 2, 4, 17);
  showDigit(ditherIndex + 1, 2, 7, 17);
  showDigit(ditherHighLow, 2, 10, 17);
  showDigit(edgeOpMode, 2, 13, 17);

  // nextImageIndex is also the "number of taken images"
  showDigit(nextImageIndex, 2, 18, 3);

  storeSettings();
}


inline void menu() {
  switch(jp) {
    case 0:
    case J_A:
    case J_B:
    case J_SELECT:
    case J_START:
      jp = 0;
      return;

    case J_RIGHT:
      menuPos = (menuPos + 1) % numMenuElements;
      renderMenu();
      break;
    case J_LEFT:
      menuPos = (menuPos + numMenuElements - 1) % numMenuElements;
      renderMenu();
      break;

    case J_UP:
      switch (menuPos) {
        case 0:
          gain = (gain + 1) % NUM_GAIN_LEVELS;
          renderMenu();
          break;
        case 1:
          exposureTime = (exposureTime + 1) % NUM_EXPOSURE_TIMES;
          renderMenu();
          break;
        case 2:
          ditherIndex = (ditherIndex + 1) % NUM_DITHERS;
          renderMenu();
          break;
        case 3:
          ditherHighLow = (ditherHighLow + 1) % NUM_DITHER_HIGHLOWS;
          renderMenu();
          break;
        case 4:
          edgeOpMode = (edgeOpMode + 1) % NUM_EDGE_OP_MODES;
          renderMenu();
          break;
        case 5:
          edgeMode = (edgeMode + 1) % NUM_EDGE_MODES;
          renderMenu();
          break;
        case 6:
          edgeExclusive = (edgeExclusive + 1) % NUM_EDGE_EXCLUSIVE;
          renderMenu();
          break;
        case 7:
          voltageRef = (voltageRef + 1) % NUM_VOLTAGE_REFS;
          renderMenu();
          break;
        case 8:
          zeroPoint = (zeroPoint + 1) % NUM_ZERO_POINTS;
          renderMenu();
          break;
        case 9:
          voltageOut = (voltageOut + 1) % NUM_VOLTAGE_OUTS;
          renderMenu();
          break;
        case 10:
          invertOutput = (invertOutput + 1) % NUM_INVERT_OUTPUTS;
          renderMenu();
          break;
      }
      break;

    case J_DOWN:
      switch (menuPos) {
        case 0:
          gain = (gain + NUM_GAIN_LEVELS - 1) % NUM_GAIN_LEVELS;
          renderMenu();
          break;
        case 1:
          exposureTime = (exposureTime + NUM_EXPOSURE_TIMES - 1) % NUM_EXPOSURE_TIMES;
          renderMenu();
          break;
        case 2:
          ditherIndex = (ditherIndex + NUM_DITHERS - 1) % NUM_DITHERS;
          renderMenu();
          break;
        case 3:
          ditherHighLow = (ditherHighLow + 2 - 1) % NUM_DITHER_HIGHLOWS;
          renderMenu();
          break;
        case 4:
          edgeOpMode = (edgeOpMode + NUM_EDGE_OP_MODES - 1) % NUM_EDGE_OP_MODES;
          renderMenu();
          break;
        case 5:
          edgeMode = (edgeMode + NUM_EDGE_MODES - 1) % NUM_EDGE_MODES;
          renderMenu();
          break;
        case 6:
          edgeExclusive = (edgeExclusive + NUM_EDGE_EXCLUSIVE - 1) % NUM_EDGE_EXCLUSIVE;
          renderMenu();
          break;
        case 7:
          voltageRef = (voltageRef + NUM_VOLTAGE_REFS - 1) % NUM_VOLTAGE_REFS;
          renderMenu();
          break;
        case 8:
          zeroPoint = (zeroPoint + NUM_ZERO_POINTS - 1) % NUM_ZERO_POINTS;
          renderMenu();
          break;
        case 9:
          voltageOut = (voltageOut + NUM_VOLTAGE_OUTS - 1) % NUM_VOLTAGE_OUTS;
          renderMenu();
          break;
        case 10:
          invertOutput = (invertOutput + NUM_INVERT_OUTPUTS - 1) % NUM_INVERT_OUTPUTS;
          renderMenu();
          break;
      }
      break;
  }

  jp = 0;
}
