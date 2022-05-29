#pragma bank 2

#include <gb/gb.h>
#include "../typedefs/MenuItem.h"
#include "../values.h"

#define NUM_MENU_ELEMENTS 11
#define MENU_ACTION_NONE 0
#define MENU_ACTION_DITHER 1

MenuItem exposureTimesMenu =  {  0, 0, 0,  2,  NUM_EXPOSURE_TIMES, 15, "ExTime", " ExposureTime (ms)",  &exposureTimes[0], MENU_ACTION_NONE, };
MenuItem gainsMenu =          {  7, 0, 0,  1,     NUM_GAIN_LEVELS,  4, "  Gain", "   Sensor     Gain",          &gains[0], MENU_ACTION_NONE, };
MenuItem voltageOutsMenu =    { 14, 0, 0,  8,    NUM_VOLTAGE_OUTS, 40, " V-Out", "  Voltage   Output",    &voltageOuts[0], MENU_ACTION_NONE, };

MenuItem contrastsMenu =      {  0, 1, 0,  3,       NUM_CONTRASTS,  7, "Cntrst", "   Dither Contrast",      &contrasts[0], MENU_ACTION_DITHER, };
MenuItem ditherSetsMenu =     {  7, 1, 0,  4,      NUM_DITHERSETS,  1, "Dither", "   Dither      Set",     &ditherSets[0], MENU_ACTION_DITHER, };
MenuItem voltageRefsMenu =    { 14, 1, 0,  6,    NUM_VOLTAGE_REFS,  3, " V-Ref", "  VoltageReference",    &voltageRefs[0], MENU_ACTION_NONE, };

MenuItem invertOutputsMenu =  {  4, 2, 0, 11,  NUM_INVERT_OUTPUTS,  0, "InvOut", "   Invert   Output",  &invertOutputs[0], MENU_ACTION_NONE, };
MenuItem zeroPointsMenu =     {  11, 2, 0,  7,     NUM_ZERO_POINTS,  1, "0Point", "     Zero   Points",     &zeroPoints[0], MENU_ACTION_NONE, };

MenuItem edgeOpModesMenu =    {  0, 3, 0,  9,   NUM_EDGE_OP_MODES,  3, "EdOper", "     EdgeOperation",    &edgeOpModes[0], MENU_ACTION_NONE, };
MenuItem edgeModesMenu =      {  7, 3, 0,  5,      NUM_EDGE_MODES,  0, "EdMode", "     Edge     Mode",      &edgeModes[0], MENU_ACTION_NONE, };
MenuItem edgeExclusivesMenu = { 14, 3, 0, 10,  NUM_EDGE_EXCLUSIVE,  1, "EdExcl", "     EdgeExclusive", &edgeExclusives[0], MENU_ACTION_NONE, };

MenuItem captureModesMenu =   { 0, 0, 0, 12,   NUM_CAPTURE_MODES,  0, "Captur", "  Capture     Mode",   &captureModes[0], MENU_ACTION_NONE, };

MenuItem *menuItems[NUM_MENU_ELEMENTS] = {
  &exposureTimesMenu,
  &gainsMenu,
  &voltageOutsMenu,

  &contrastsMenu,
  &ditherSetsMenu,
  &voltageRefsMenu,

  &invertOutputsMenu,
  &zeroPointsMenu,
//  &captureModesMenu,

  &edgeOpModesMenu,
  &edgeModesMenu,
  &edgeExclusivesMenu,
};
