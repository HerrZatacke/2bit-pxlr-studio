#ifndef IMAGEINDEXING_H
#define IMAGEINDEXING_H

#include <gb/gb.h>
#include <gbdk/platform.h>

#define NUM_IMAGES 30
#define IMAGE_DELETED 0xFF
#define IMAGE_UNDEFINED 0xFE

extern void setImageSlot(unsigned char address, unsigned char newValue) BANKED OLDCALL;
extern unsigned char getImageSlot(unsigned char index) BANKED OLDCALL;
extern unsigned char getAddressForIndex(unsigned char index) BANKED OLDCALL;
extern unsigned char getNextHighestAddress(unsigned char searchIndex) BANKED OLDCALL;
extern void reduceIndexAfterDelete(unsigned char deletedIndex) BANKED OLDCALL;
extern void cleanupIndexGaps() BANKED OLDCALL;
extern void sortImages() BANKED OLDCALL;
extern unsigned char findFirstFreeSlot() BANKED OLDCALL;
extern void deleteAllImages() BANKED OLDCALL;

#endif
