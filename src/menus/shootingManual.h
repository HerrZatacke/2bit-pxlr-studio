#define NUM_MENU_ELEMENTS 11

#define MENU_ACTION_NONE 0
#define MENU_ACTION_DITHER 1

MenuItem gainsMenu =          {  1, 0, 0,  1,     NUM_GAIN_LEVELS,  4, "Gain", "   Sensor     Gain",          &gains[0], MENU_ACTION_NONE, };
MenuItem exposureTimesMenu =  {  6, 0, 0,  2,  NUM_EXPOSURE_TIMES,  4, "ExpT", " Exposure     Time",  &exposureTimes[0], MENU_ACTION_NONE, };
MenuItem voltageRefsMenu =    { 11, 0, 0,  6,    NUM_VOLTAGE_REFS,  3, "vRef", "  VoltageReference",    &voltageRefs[0], MENU_ACTION_NONE, };
MenuItem voltageOutsMenu =    { 16, 0, 0,  8,    NUM_VOLTAGE_OUTS, 40, "vOut", "  Voltage   Output",    &voltageOuts[0], MENU_ACTION_NONE, };
MenuItem invertOutputsMenu =  {  1, 1, 0, 11,  NUM_INVERT_OUTPUTS,  0, "InvO", "   Invert   Output",  &invertOutputs[0], MENU_ACTION_NONE, };
MenuItem zeroPointsMenu =     {  6, 1, 0,  7,     NUM_ZERO_POINTS,  1, "0 Pt", "     Zero   Points",     &zeroPoints[0], MENU_ACTION_NONE, };
MenuItem ditherHighLowsMenu = { 11, 1, 0,  4, NUM_DITHER_HIGHLOWS,  1, "dSet", "   Dither      set", &ditherHighLows[0], MENU_ACTION_DITHER, };
MenuItem ditherSetsMenu =     { 16, 1, 0,  3,         NUM_DITHERS,  7, "Dith", "   Dither   Matrix",     &ditherSets[0], MENU_ACTION_DITHER, };
MenuItem edgeOpModesMenu =    {  3, 2, 0,  9,   NUM_EDGE_OP_MODES,  3, "EdOp", "     EdgeOperation",    &edgeOpModes[0], MENU_ACTION_NONE, };
MenuItem edgeModesMenu =      {  8, 2, 0,  5,      NUM_EDGE_MODES,  0, "EdMo", "     Edge     Mode",      &edgeModes[0], MENU_ACTION_NONE, };
MenuItem edgeExclusivesMenu = { 13, 2, 0, 10,  NUM_EDGE_EXCLUSIVE,  1, "EdEx", "     EdgeExclusive", &edgeExclusives[0], MENU_ACTION_NONE, };

MenuItem *menuItems[NUM_MENU_ELEMENTS] = {
  &gainsMenu,
  &exposureTimesMenu,
  &voltageRefsMenu,
  &voltageOutsMenu,
  &invertOutputsMenu,
  &zeroPointsMenu,
  &ditherHighLowsMenu,
  &ditherSetsMenu,
  &edgeOpModesMenu,
  &edgeModesMenu,
  &edgeExclusivesMenu,
};
