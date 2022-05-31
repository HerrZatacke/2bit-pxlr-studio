#pragma bank 2

#include <gb/gb.h>
#include <gbdk/platform.h>
#include <string.h>
#include <gbdk/bcd.h>
#include "defines.h"
#include "values.h"
#include "globals.h"
#include "utils.h"
#include "joypad.h"
#include "banks.h"
#include "menus/shootingManualMenuItems.h"

void getImageInfo(uint8_t imageIndex, uint8_t *tileMap) BANKED {
  uint8_t imageSlot = getImageSlot(imageIndex);
  uint8_t i;

  SWITCH_RAM(images[imageSlot]->bank);

  uint8_t capture = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_CAPTURE];
  uint8_t edgeGains = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_EDGEGAINS];
  uint8_t exposureHigh = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_HIGH];
  uint8_t exposureLow = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_EXPOSURE_LOW];
  uint8_t edgeModeVolt = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_EDMOVOLT];
  uint8_t voltageZeroPoint = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_VOUTZERO];
  uint8_t ditherSet = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_DITHERSET];
  uint8_t contrast = images[imageSlot]->thumbnail[THUMBNAIL_BYTE_CONTRAST];

  uint8_t captureMode   = capture          & A000_MASK_CAPTURE;
  uint8_t edgeExclusive = edgeGains        & A001_MASK_EDGE_EXCLUSIVE;
  uint8_t edgeOperation = edgeGains        & A001_MASK_EDGE_OP_MODE;
  uint8_t gain          = edgeGains        & A001_MASK_GAIN;
  uint8_t edgeMode      = edgeModeVolt     & A004_MASK_EDGE_RATIO;
  uint8_t invertOut     = edgeModeVolt     & A004_MASK_INVERT_OUTPUT;
  uint8_t vRef          = edgeModeVolt     & A004_MASK_VOLTAGE_REF;
  uint8_t zeroPoint     = voltageZeroPoint & A005_MASK_ZERO;
  uint8_t vOut          = voltageZeroPoint & A005_MASK_VOLTAGE_OUT;

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
         "Image #??? Slot #???"
         "                    "
         "Exposure Time ??????"
         "Sensor Gain   ??????"
         "Voltage Output??????"
         "Dith. Contrast??????"
         "Dither Set    ??????"
         "Voltage Ref   ??????"
         "Invert Output ??????"
         "Zero Point    ??????"
         "Capture Mode  ??????"
         "Edge Operation??????"
         "Edge Mode     ??????"
         "Edge Exclusive??????"
         "                    "
         "Registers           "
         " 0x?? 0x?? 0x?? 0x??"
         " 0x?? 0x?? 0x?? 0x??",
         360);

#define POS_IMG 7
#define POS_SLOT 17
#define POS_01 54
#define POS_02 74
#define POS_03 94
#define POS_04 114
#define POS_05 134
#define POS_06 154
#define POS_07 174
#define POS_08 194
#define POS_09 214
#define POS_10 234
#define POS_11 254
#define POS_12 274

  uint16_t exposureTimeInt = (exposureHigh << 8) + exposureLow;
  uint8_t exposureTime = 0xFF;
  for (i = 0; i < NUM_EXPOSURE_TIMES; i += 1) {
    if (exposureTimesValues[i] == exposureTimeInt) {
      exposureTime = i;
    }
  }

  for (i = 0; i < NUM_EXPOSURE_TIMES; i += 1) {
    if (exposureTimes[i].value == exposureTime) {
      memcpy(&tileMap[POS_01], exposureTimes[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_GAIN_LEVELS; i += 1) {
    if (gains[i].value == gain) {
      memcpy(&tileMap[POS_02], gains[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_VOLTAGE_OUTS; i += 1) {
    if (voltageOuts[i].value == vOut) {
      memcpy(&tileMap[POS_03], voltageOuts[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_CONTRASTS; i += 1) {
    if (contrasts[i].value == contrast) {
      memcpy(&tileMap[POS_04], contrasts[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_DITHERSETS; i += 1) {
    if (ditherSets[i].value == ditherSet) {
      memcpy(&tileMap[POS_05], ditherSets[i].title, MENU_TEXT_LENGTH);
    }
  }


  for (i = 0; i < NUM_VOLTAGE_REFS; i += 1) {
    if (voltageRefs[i].value == vRef) {
      memcpy(&tileMap[POS_06], voltageRefs[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_INVERT_OUTPUTS; i += 1) {
    if (invertOutputs[i].value == invertOut) {
      memcpy(&tileMap[POS_07], invertOutputs[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_ZERO_POINTS; i += 1) {
    if (zeroPoints[i].value == zeroPoint) {
      memcpy(&tileMap[POS_08], zeroPoints[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_CAPTURE_MODES; i += 1) {
    if (captureModes[i].value == captureMode) {
      memcpy(&tileMap[POS_09], captureModes[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_EDGE_OP_MODES; i += 1) {
    if (edgeOpModes[i].value == edgeOperation) {
      memcpy(&tileMap[POS_10], edgeOpModes[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_EDGE_MODES; i += 1) {
    if (edgeModes[i].value == edgeMode) {
      memcpy(&tileMap[POS_11], edgeModes[i].title, MENU_TEXT_LENGTH);
    }
  }

  for (i = 0; i < NUM_EDGE_EXCLUSIVE; i += 1) {
    if (edgeExclusives[i].value == edgeExclusive) {
      memcpy(&tileMap[POS_12], edgeExclusives[i].title, MENU_TEXT_LENGTH);
    }
  }

  uint8_t digits[10];
  BCD bcd = MAKE_BCD(0);

  uint2bcd(imageIndex, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[POS_IMG], &digits[5], 3);

  uint2bcd(imageSlot, &bcd);
  bcd2text(&bcd, 48u, digits);
  memcpy(&tileMap[POS_SLOT], &digits[5], 3);

  hexChar(&tileMap[323], capture);
  hexChar(&tileMap[328], edgeGains);
  hexChar(&tileMap[333], exposureHigh);
  hexChar(&tileMap[338], exposureLow);
  hexChar(&tileMap[343], edgeModeVolt);
  hexChar(&tileMap[348], voltageZeroPoint);
  hexChar(&tileMap[353], ditherSet);
  hexChar(&tileMap[358], contrast);
}

void displayImageInfo(uint8_t imageIndex) BANKED {
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
