#ifndef IMAGEINDEXING_H
#define IMAGEINDEXING_H

#include <gb/gb.h>
#include <gbdk/platform.h>

#define NUM_IMAGES 30
#define IMAGE_DELETED 0xFF
#define IMAGE_UNDEFINED 0xFE

extern void setImageSlot(uint8_t address, uint8_t newValue) BANKED;
extern uint8_t getImageSlot(uint8_t index) BANKED;
extern uint8_t getAddressForIndex(uint8_t index) BANKED;
extern uint8_t getNextHighestAddress(uint8_t searchIndex) BANKED;
extern void reduceIndexAfterDelete(uint8_t deletedIndex) BANKED;
extern void cleanupIndexGaps() BANKED;
extern void sortImages() BANKED;
extern uint8_t findFirstFreeSlot() BANKED;
extern void deleteAllImages() BANKED;

#endif
