#ifndef TYPEDEF_IMAGE_H
#define TYPEDEF_IMAGE_H

#include <gbdk/platform.h>

typedef struct {
  const uint8_t bank;
  uint8_t* const tilesUpper;
  uint8_t* const tilesLower;
  uint8_t* const thumbnail;
  uint8_t* const meta;
  uint8_t* const metaEcho;
} Image;

#endif
