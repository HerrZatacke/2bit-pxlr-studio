#define NUM_MAIN_MENU_OPTIONS 5

#include "typedefs/MenuOption.h"
#include "defines.h"

const MenuOption mainMenuItems[NUM_MAIN_MENU_OPTIONS] = {
//  { MAIN_LOOP_NOT_IMPLEMENTED, "Automatic mode  ", },
  { MAIN_LOOP_SHOOT_MANUAL,    "Manual mode     ", },
  { MAIN_LOOP_SHOOT_BURST,     "Burst mode      ", },
//  { MAIN_LOOP_NOT_IMPLEMENTED, "Settings mode   ", },
//  { MAIN_LOOP_NOT_IMPLEMENTED, "Continuous mode ", },
//  { MAIN_LOOP_NOT_IMPLEMENTED, "Panorama mode   ", },
  { MAIN_LOOP_IMAGE_GALLERY,   "Image Gallery   ", },
//  { MAIN_LOOP_NOT_IMPLEMENTED, "Settings        ", },
  { MAIN_LOOP_DELETE_ALL,      "Clear all images", },
  { MAIN_LOOP_DEBUG,           "Debug           ", },
};
