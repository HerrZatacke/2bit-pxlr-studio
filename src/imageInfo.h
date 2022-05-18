const unsigned char hexCharLUT[] = "0123456789ABCDEF";

inline void hexChar(unsigned char *target, unsigned char value) {
  target[0] = hexCharLUT[(value >> 4) & 0b00001111];
  target[1] = hexCharLUT[value & 0b00001111];
}


void getImageInfo(unsigned char imageIndex, unsigned char *tileMap) {
  unsigned char imageSlot = getImageSlot(imageIndex);
  unsigned char i;

  SWITCH_RAM(images[imageSlot]->bank);

  unsigned char capture = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_CAPTURE]; // A000_CAPTURE_POSITIVE | A000_START_CAPTURE;
  unsigned char edgeGains = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_EDGEGAINS]; // getMenuValue(edgeOpModesMenu) | getMenuValue(gainsMenu) | getMenuValue(edgeExclusivesMenu);
  unsigned char exposureHigh = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_HIGH]; // (char)(exposureTime >> 8);
  unsigned char exposureLow = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_LOW]; // (char)exposureTime;
  unsigned char edgeModeVolt = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_EDMOVOLT]; // getMenuValue(edgeModesMenu) | getMenuValue(voltageRefsMenu) | getMenuValue(invertOutputsMenu);
  unsigned char voltageZeroPoint = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_VOUTZERO]; // getMenuValue(voltageOutsMenu) | getMenuValue(zeroPointsMenu);
  unsigned char ditherSet = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_DITHERSET]; // getMenuValue(ditherSetsMenu);
  unsigned char contrast = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_CONTRAST]; // getMenuValue(contrastsMenu);

  unsigned int exposureTimeInt = (exposureHigh << 8) + exposureLow;
  unsigned char exposureTime = 0xFF;
  for (i = 0; i < NUM_EXPOSURE_TIMES; i += 1) {
    if (exposureTimesValues[i] == exposureTimeInt) {
      exposureTime = i;
    }
  }

  unsigned char edgeExclusive = edgeGains        & A001_MASK_EDGE_EXCLUSIVE;
  unsigned char edgeOperation = edgeGains        & A001_MASK_EDGE_OP_MODE;
  unsigned char gain          = edgeGains        & A001_MASK_GAIN;
  unsigned char edgeMode      = edgeModeVolt     & A004_MASK_EDGE_RATIO;
  unsigned char invertOut     = edgeModeVolt     & A004_MASK_INVERT_OUTPUT;
  unsigned char vRef          = edgeModeVolt     & A004_MASK_VOLTAGE_REF;
  unsigned char zeroPoint     = voltageZeroPoint & A005_MASK_ZERO;
  unsigned char vOut          = voltageZeroPoint & A005_MASK_VOLTAGE_OUT;

  if (
    capture == 0xFF &&
    edgeGains == 0xFF &&
    exposureHigh == 0xFF &&
    exposureLow == 0xFF &&
    edgeModeVolt == 0xFF &&
    voltageZeroPoint == 0xFF &&
    ditherSet == 0xFF &&
    contrast == 0xFF
  ) {
    memcpy(&tileMap[0],
     "                    "
     "                    "
     "                    "
     "                    "
     "                    "
     "                    "
     "   Image was not    "
     "                    "
     "     taken with     "
     "                    "
     "  2bit PXLR Studio  "
     "                    "
     "                    "
     "                    "
     "                    "
     "                    "
     "                    "
     "                    ",
   360);
    return;
  }


  memcpy(&tileMap[0],
    "                    "
    "Image #??? Slot #???"
    "                    "
    "Exposure Time ??????"
    "Sensor Gain   ??????"
    "Voltage Refer.??????"
    "Voltage Output??????"
    "Invert Output ??????"
    "Zero Point    ??????"
    "Dither Set    ??????"
    "Dither Matrix ??????"
    "Edge Operation??????"
    "Edge Mode     ??????"
    "Edge Exclusive??????"
    "                    "
    "Registers           "
    " 0x?? 0x?? 0x?? 0x??"
    " 0x?? 0x?? 0x?? 0x??",
  360);

  for (i = 0; i < NUM_EXPOSURE_TIMES; i += 1) {
    if (exposureTimes[i].value == exposureTime) {
      memcpy(&tileMap[74], exposureTimes[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_GAIN_LEVELS; i += 1) {
    if (gains[i].value == gain) {
      memcpy(&tileMap[94], gains[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_VOLTAGE_REFS; i += 1) {
    if (voltageRefs[i].value == vRef) {
      memcpy(&tileMap[114], voltageRefs[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_VOLTAGE_OUTS; i += 1) {
    if (voltageOuts[i].value == vOut) {
      memcpy(&tileMap[134], voltageOuts[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_INVERT_OUTPUTS; i += 1) {
    if (invertOutputs[i].value == invertOut) {
      memcpy(&tileMap[154], invertOutputs[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_ZERO_POINTS; i += 1) {
    if (zeroPoints[i].value == zeroPoint) {
      memcpy(&tileMap[174], zeroPoints[i].title, MENU_TEXT_LENGTH);
    }
  }

  // ToDo Rename to Dither Modes everywhere?
  for (i = 0; i < NUM_DITHERSETS; i += 1) {
    if (ditherSets[i].value == ditherSet) {
      memcpy(&tileMap[194], ditherSets[i].title, MENU_TEXT_LENGTH);
    }
  }

  // ToDo Rename to Dither Matrices everywhere?
  for (i = 0; i < NUM_CONTRASTS; i += 1) {
    if (contrasts[i].value == contrast) {
      memcpy(&tileMap[214], contrasts[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_EDGE_OP_MODES; i += 1) {
    if (edgeOpModes[i].value == edgeOperation) {
      memcpy(&tileMap[234], edgeOpModes[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_EDGE_MODES; i += 1) {
    if (edgeModes[i].value == edgeMode) {
      memcpy(&tileMap[254], edgeModes[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_EDGE_EXCLUSIVE; i += 1) {
    if (edgeExclusives[i].value == edgeExclusive) {
      memcpy(&tileMap[274], edgeExclusives[i].title, MENU_TEXT_LENGTH);
    }
  }

  unsigned char digits[10];
  BCD bcd = MAKE_BCD(0);

  uint2bcd(imageIndex, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[27], &digits[5], 3);

  uint2bcd(imageSlot, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[37], &digits[5], 3);

  hexChar(&tileMap[323], capture);
  hexChar(&tileMap[328], edgeGains);
  hexChar(&tileMap[333], exposureHigh);
  hexChar(&tileMap[338], exposureLow);
  hexChar(&tileMap[343], edgeModeVolt);
  hexChar(&tileMap[348], voltageZeroPoint);
  hexChar(&tileMap[353], ditherSet);
  hexChar(&tileMap[358], contrast);
}

inline void displayImageInfo(unsigned char imageIndex) {
  move_sprite(SPRITE_MENU_INDICATOR, 0, 0);

  getImageInfo(imageIndex, imageInfo);

  waitRelease();

  fill_win_rect(0, 0, 20, 18, OFFSET_BLANK);
  move_win(6, 0);
  set_win_based_tiles(0, 0, 20, 18, imageInfo, OFFSET_FONT - 32);

  while (jp != J_B && jp != J_A) {
    wait_vbl_done();
  }

  fill_win_rect(0, 0, 20, 18, OFFSET_BLANK);
  move_win(78, 0);
}
