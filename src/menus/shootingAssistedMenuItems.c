#include <gb/gb.h>
#include "typedefs/MenuItem.h"
#include "values.h"
#include "valuesAssisted.h"

#define NUM_MENU_ELEMENTS_ASSISTED 3

MenuItem assistedOptionsMenu =   {  0, 0, 0, 2, NUM_ASSISTED_OPTIONS, 22, "   Set", " Exposure  Setting", &assistedOptions[0], 0, };
MenuItem contrastsMenuAssisted = {  7, 1, 0, 3,        NUM_CONTRASTS,  7, "Cntrst", "   Dither Contrast",       &contrasts[0], 0, };
MenuItem ditherToggleMenu =      { 14, 1, 0, 4,    NUM_DITHER_TOGGLE,  0, "Dither", "   Dither   Toggle",    &ditherToggle[0], 0, };

MenuItem *menuItemsAssisted[NUM_MENU_ELEMENTS_ASSISTED] = {
    &assistedOptionsMenu,
    &contrastsMenuAssisted,
    &ditherToggleMenu,
};
