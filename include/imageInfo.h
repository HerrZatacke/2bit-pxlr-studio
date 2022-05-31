#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <gbdk/platform.h>

void getImageInfo(uint8_t imageIndex, uint8_t *tileMap) BANKED;
void displayImageInfo(uint8_t imageIndex) BANKED;

#endif
