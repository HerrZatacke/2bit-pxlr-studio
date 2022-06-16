#define NUM_IMAGE_MENU_OPTIONS 5

#include "typedefs/MenuOption.h"
#include "defines.h"

const MenuOption imageMenuItems[NUM_IMAGE_MENU_OPTIONS] = {
  { IMAGE_MENU_INFO,      "Info    ", },
  { IMAGE_MENU_HISTOGRAM, "Histogrm", },
  { IMAGE_MENU_DELETE,    "Delete  ", },
  { IMAGE_MENU_PRINT,     "Print   ", },
  { IMAGE_MENU_BLEEP,     "Beep Out", },
  { IMAGE_MENU_EXPOSE,    "Expose  ", },
};
