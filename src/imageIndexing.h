#ifndef IMAGEINDEXING_H
#define IMAGEINDEXING_H

#include <gb/gb.h>
#include <gbdk/platform.h>

#define NUM_IMAGES 30
#define IMAGE_DELETED 0xFF
#define IMAGE_UNDEFINED 0xFE

extern void setImageSlot(unsigned char address, unsigned char newValue) BANKED;
extern unsigned char getImageSlot(unsigned char index) BANKED;
extern unsigned char getAddressForIndex(unsigned char index) BANKED;
extern unsigned char getNextHighestAddress(unsigned char searchIndex) BANKED;
extern void reduceIndexAfterDelete(unsigned char deletedIndex) BANKED;
extern void cleanupIndexGaps() BANKED;
extern void sortImages() BANKED;
extern unsigned char findFirstFreeSlot() BANKED;
extern void deleteAllImages() BANKED;

#endif
