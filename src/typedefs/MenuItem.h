#ifndef TYPEDEF_MENUITEM_H
#define TYPEDEF_MENUITEM_H

#include <gbdk/platform.h>
#include "./MenuOption.h"

typedef struct {
  const uint8_t x;
  const uint8_t page;
  uint8_t value;
  const uint8_t storeOffset;
  const uint8_t numOptions;
  const uint8_t defaultValue;
  const char* title;
  const char* description;
  const MenuOption* options;
  const uint8_t action;
} MenuItem;

#endif
