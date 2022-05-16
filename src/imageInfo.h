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
  unsigned char ditherHighLow = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_DITHERHIGHLOW]; // getMenuValue(ditherHighLowsMenu);
  unsigned char ditherMatrix = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_DITHERSET]; // getMenuValue(ditherSetsMenu);

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
    ditherHighLow == 0xFF &&
    ditherMatrix == 0xFF
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
    "Exposure Time   ????"
    "Sensor Gain     ????"
    "Voltage Refer.  ????"
    "Voltage Output  ????"
    "Invert Output   ????"
    "Zero Point      ????"
    "Dither Set      ????"
    "Dither Matrix   ????"
    "Edge Operation  ????"
    "Edge Mode       ????"
    "Edge Exclusive  ????"
    "                    "
    "Registers           "
    " 0x?? 0x?? 0x?? 0x??"
    " 0x?? 0x?? 0x?? 0x??",
  360);

  for (i = 0; i < NUM_EXPOSURE_TIMES; i += 1) {
    if (exposureTimes[i].value == exposureTime) {
      memcpy(&tileMap[76], exposureTimes[i].title, 4);
    }
  }

  for (i = 0; i < NUM_GAIN_LEVELS; i += 1) {
    if (gains[i].value == gain) {
      memcpy(&tileMap[96], gains[i].title, 4);
    }
  }

  for (i = 0; i < NUM_VOLTAGE_REFS; i += 1) {
    if (voltageRefs[i].value == vRef) {
      memcpy(&tileMap[116], voltageRefs[i].title, 4);
    }
  }

  for (i = 0; i < NUM_VOLTAGE_OUTS; i += 1) {
    if (voltageOuts[i].value == vOut) {
      memcpy(&tileMap[136], voltageOuts[i].title, 4);
    }
  }

  for (i = 0; i < NUM_INVERT_OUTPUTS; i += 1) {
    if (invertOutputs[i].value == invertOut) {
      memcpy(&tileMap[156], invertOutputs[i].title, 4);
    }
  }

  for (i = 0; i < NUM_ZERO_POINTS; i += 1) {
    if (zeroPoints[i].value == zeroPoint) {
      memcpy(&tileMap[176], zeroPoints[i].title, 4);
    }
  }

  // ToDo Rename to Dither Modes everywhere?
  for (i = 0; i < NUM_DITHER_HIGHLOWS; i += 1) {
    if (ditherHighLows[i].value == ditherHighLow) {
      memcpy(&tileMap[196], ditherHighLows[i].title, 4);
    }
  }

  // ToDo Rename to Dither Matrices everywhere?
  for (i = 0; i < NUM_DITHERS; i += 1) {
    if (ditherSets[i].value == ditherMatrix) {
      memcpy(&tileMap[216], ditherSets[i].title, 4);
    }
  }

  for (i = 0; i < NUM_EDGE_OP_MODES; i += 1) {
    if (edgeOpModes[i].value == edgeOperation) {
      memcpy(&tileMap[236], edgeOpModes[i].title, 4);
    }
  }

  for (i = 0; i < NUM_EDGE_MODES; i += 1) {
    if (edgeModes[i].value == edgeMode) {
      memcpy(&tileMap[256], edgeModes[i].title, 4);
    }
  }

  for (i = 0; i < NUM_EDGE_EXCLUSIVE; i += 1) {
    if (edgeExclusives[i].value == edgeExclusive) {
      memcpy(&tileMap[276], edgeExclusives[i].title, 4);
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
  hexChar(&tileMap[353], ditherHighLow);
  hexChar(&tileMap[358], ditherMatrix);
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
