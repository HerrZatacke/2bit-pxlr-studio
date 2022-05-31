#ifndef SHOOTINGMANUAL_MENUITEMS_H
#define SHOOTINGMANUAL_MENUITEMS_H

#define NUM_MENU_ELEMENTS 11
#define MENU_ACTION_NONE 0
#define MENU_ACTION_DITHER 1
#define MENU_TEXT_LENGTH 6

#include "typedefs/MenuItem.h"

extern MenuItem exposureTimesMenu;
extern MenuItem gainsMenu;
extern MenuItem voltageOutsMenu;
extern MenuItem contrastsMenu;
extern MenuItem ditherSetsMenu;
extern MenuItem voltageRefsMenu;
extern MenuItem invertOutputsMenu;
extern MenuItem zeroPointsMenu;
extern MenuItem edgeOpModesMenu;
extern MenuItem edgeModesMenu;
extern MenuItem edgeExclusivesMenu;
extern MenuItem captureModesMenu;

extern MenuItem *menuItems[NUM_MENU_ELEMENTS];

#endif
