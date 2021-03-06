#pragma bank 255

#include <gb/gb.h>
#include <gbdk/platform.h>
#include "gbcamera.h"
#include "utils.h"
#include "globals.h"

#define NUM_IMAGES 30
#define IMAGE_DELETED 0xFF
#define IMAGE_UNDEFINED 0xFE

void setImageSlot(uint8_t address, uint8_t newValue) BANKED {
  SWITCH_RAM(0);

  if (address >= NUM_IMAGES) {
    dead();
  }

  uint8_t oldValue = cam_game_data_echo.imageslots[address];

  if (newValue == oldValue) {
    return;
  }

  // Update value for imageslot
  cam_game_data_echo.imageslots[address] = cam_game_data.imageslots[address] = newValue;

  // Update checksum SUM
  cam_game_data_echo.CRC_add = cam_game_data.CRC_add = cam_game_data.CRC_add + newValue - oldValue;

  // Update checksum XOR
  cam_game_data_echo.CRC_xor = cam_game_data.CRC_xor = cam_game_data.CRC_xor ^ newValue ^ oldValue;
}

uint8_t getImageSlot(uint8_t index) BANKED {
  if (index >= NUM_IMAGES) {
    return NUM_IMAGES;
  }

  return sortedIndices[index];
}



uint8_t getAddressForIndex(uint8_t index) BANKED {
  SWITCH_RAM(0);
  for (uint8_t address = 0; address < NUM_IMAGES; address++) {
    if (cam_game_data_echo.imageslots[address] == index) {
      return address;
    }
  }

  return NUM_IMAGES;
}


uint8_t getNextHighestAddress(uint8_t searchIndex) BANKED {
  SWITCH_RAM(0);

  while (searchIndex < NUM_IMAGES) {
    for (uint8_t address = 0; address < NUM_IMAGES; address++) {
      if (cam_game_data_echo.imageslots[address] == searchIndex) {
        return address;
      }
    }

    searchIndex += 1;
  }

  return NUM_IMAGES;
}

void reduceIndexAfterDelete(uint8_t deletedIndex) BANKED {
  SWITCH_RAM(0);
  for (uint8_t address = 0; address < NUM_IMAGES; address++) {
    uint8_t index = cam_game_data_echo.imageslots[address];
    if (index > deletedIndex && index < NUM_IMAGES) {
      setImageSlot(address, index - 1);
    }
  }
}

void cleanupIndexGaps() BANKED {
  SWITCH_RAM(0);
  for (uint8_t index = 0; index < NUM_IMAGES; index++) {
    // image number does not exist in list
    if (getAddressForIndex(index) >= NUM_IMAGES) {
      uint8_t address = getNextHighestAddress(index);
      if (address < NUM_IMAGES) {
        setImageSlot(address, index);
      }
    }
  }
}

void sortImages() BANKED {
  SWITCH_RAM(0);

  uint8_t deletedIndex = 0;
  numVisibleImages = 0;
  uint8_t sortedDeletedIndices[NUM_IMAGES];
  uint8_t i = 0;

  for (i = 0; i < NUM_IMAGES; i++) {
    uint8_t current = cam_game_data_echo.imageslots[i];

    if (current == IMAGE_DELETED) {
      sortedDeletedIndices[deletedIndex] = i;
      deletedIndex += 1;
    } else {
      sortedIndices[current] = i;
      numVisibleImages += 1;
    }
  }

  deletedIndex = 0;
  for (i = 0; i < NUM_IMAGES; i++) {
    if (sortedIndices[i] == IMAGE_UNDEFINED) {
      sortedIndices[i] = sortedDeletedIndices[deletedIndex];
      deletedIndex += 1;
    }
  }
}

uint8_t findFirstFreeSlot() BANKED {
  SWITCH_RAM(0);

  for (uint8_t i = 0; i < NUM_IMAGES; i++) {
    if (cam_game_data_echo.imageslots[i] == IMAGE_DELETED) {
      return i;
    }
  }

  return NUM_IMAGES;
}

void deleteAllImages() BANKED {
  for (uint8_t address = 0; address < 30; address += 1) {
    setImageSlot(address, 0xff);
  }
  sortImages();
  imageIndex = 0;
}
