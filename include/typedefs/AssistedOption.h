#ifndef TYPEDEF_ASSISTED_OPTION_H
#define TYPEDEF_ASSISTED_OPTION_H

#include <gbdk/platform.h>
#include "typedefs/MenuOption.h"

typedef struct AssistedOption {
  uint8_t gain;
  uint8_t vOut;
  uint8_t edgeExclusive;
  uint8_t edgeOperation;
  uint16_t expTime;
} AssistedOption;

#endif
