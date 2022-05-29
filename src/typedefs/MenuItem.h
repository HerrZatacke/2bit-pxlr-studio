#ifndef TYPEDEF_MENUITEM_H
#define TYPEDEF_MENUITEM_H

#include "./MenuOption.h"

typedef struct {
  const unsigned char x;
  const unsigned char page;
  unsigned char value;
  const unsigned char storeOffset;
  const unsigned char numOptions;
  const unsigned char defaultValue;
  const char* title;
  const char* description;
  const MenuOption* options;
  const unsigned char action;
} MenuItem;

#endif
