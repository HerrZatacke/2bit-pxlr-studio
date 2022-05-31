#ifndef TYPEDEF_MENUITEM_H
#define TYPEDEF_MENUITEM_H

#include <gbdk/platform.h>
#include "typedefs/MenuOption.h"

typedef struct MenuItem {
  const uint8_t x;
  const uint8_t page;
  uint8_t value;
  const uint8_t storeOffset;
  const uint8_t numOptions;
  const uint8_t defaultValue;
  const int8_t* title;
  const int8_t* description;
  const MenuOption* options;
  const uint8_t action;
} MenuItem;

#endif
