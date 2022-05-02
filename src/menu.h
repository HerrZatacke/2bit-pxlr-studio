unsigned char jp = 0;
unsigned char menuPos = 0;

unsigned char numMenuElements = 10;

unsigned char numGainLevels = sizeof gains / sizeof gains[0];
unsigned char numExposureTimes = sizeof exposureTimes / sizeof exposureTimes[0];
unsigned char numDithers = 16; //sizeof ditherLowLight;
unsigned char numEdgeModes = sizeof edgeModes;
unsigned char numVoltageRefs = sizeof voltageRefs;
unsigned char numZeroPoints = sizeof zeroPoints;
unsigned char numVoltageOuts = sizeof voltageOuts;
unsigned char numEdgeOpModes = sizeof edgeOpModes;
unsigned char numEdgeExclusive = sizeof edgeExclusives;

unsigned char gain = 0;
unsigned char exposureTime = 0;
unsigned char ditherIndex = 0;
unsigned char highLow = 0;
unsigned char edgeMode = 0;
unsigned char voltageRef = 0;
unsigned char zeroPoint = 0;
unsigned char voltageOut = 0;
unsigned char edgeOpMode = 0;
unsigned char edgeExclusive = 0;

extern unsigned char nextImageIndex;

inline void captureMenuJp() {
  if (jp == 0) {
    jp = joypad();
  }
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
      posOffsetX = 42;
      break;
    case 2:
      posOffsetX = 74;
      break;
    case 3:
      posOffsetX = 106;
      break;
    case 4:
      posOffsetX = 138;
      break;
  }

  move_sprite(SPRITE_MENU_INDICATOR_L, posOffsetX, posOffsetY);
  move_sprite(SPRITE_MENU_INDICATOR_R, posOffsetX + 20, posOffsetY);

  showDigit(edgeMode + 1, 2, 1, 1);
  showDigit(edgeExclusive, 2, 5, 1);
  showDigit(voltageRef + 1, 2, 9, 1);
  showDigit(zeroPoint + 1, 2, 13, 1);
  showDigit(voltageOut + 1, 2, 17, 1);

  showDigit(gain + 1, 2, 1, 17);
  showDigit(exposureTime + 1, 2, 5, 17);
  showDigit(ditherIndex + 1, 2, 9, 17);
  showDigit(highLow, 2, 13, 17);
  showDigit(edgeOpMode, 2, 17, 17);

  // nextImageIndex is also the "number of taken images"
  showDigit(nextImageIndex, 2, 18, 3);
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
          gain = (gain + 1) % numGainLevels;
          renderMenu();
          break;
        case 1:
          exposureTime = (exposureTime + 1) % numExposureTimes;
          renderMenu();
          break;
        case 2:
          ditherIndex = (ditherIndex + 1) % numDithers;
          renderMenu();
          break;
        case 3:
          highLow = (highLow + 1) % 2;
          renderMenu();
          break;
        case 4:
          edgeOpMode = (edgeOpMode + 1) % numEdgeOpModes;
          renderMenu();
          break;
        case 5:
          edgeMode = (edgeMode + 1) % numEdgeModes;
          renderMenu();
          break;
        case 6:
          edgeExclusive = (edgeExclusive + 1) % numEdgeExclusive;
          renderMenu();
          break;
        case 7:
          voltageRef = (voltageRef + 1) % numVoltageRefs;
          renderMenu();
          break;
        case 8:
          zeroPoint = (zeroPoint + 1) % numZeroPoints;
          renderMenu();
          break;
        case 9:
          voltageOut = (voltageOut + 1) % numVoltageOuts;
          renderMenu();
          break;
      }
      break;

    case J_DOWN:
      switch (menuPos) {
        case 0:
          gain = (gain + numGainLevels - 1) % numGainLevels;
          renderMenu();
          break;
        case 1:
          exposureTime = (exposureTime + numExposureTimes - 1) % numExposureTimes;
          renderMenu();
          break;
        case 2:
          ditherIndex = (ditherIndex + numDithers - 1) % numDithers;
          renderMenu();
          break;
        case 3:
          highLow = (highLow + 2 - 1) % 2;
          renderMenu();
          break;
        case 4:
          edgeOpMode = (edgeOpMode + numEdgeOpModes - 1) % numEdgeOpModes;
          renderMenu();
          break;
        case 5:
          edgeMode = (edgeMode + numEdgeModes - 1) % numEdgeModes;
          renderMenu();
          break;
        case 6:
          edgeExclusive = (edgeExclusive + numEdgeExclusive - 1) % numEdgeExclusive;
          renderMenu();
          break;
        case 7:
          voltageRef = (voltageRef + numVoltageRefs - 1) % numVoltageRefs;
          renderMenu();
          break;
        case 8:
          zeroPoint = (zeroPoint + numZeroPoints - 1) % numZeroPoints;
          renderMenu();
          break;
        case 9:
          voltageOut = (voltageOut + numVoltageOuts - 1) % numVoltageOuts;
          renderMenu();
          break;
      }
      break;
  }

  jp = 0;
}
