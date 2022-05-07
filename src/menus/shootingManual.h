#define NUM_MENU_ELEMENTS 11

MenuItem gainsMenu =          {  0, 0, 0,  1,     NUM_GAIN_LEVELS,     (NUM_GAIN_LEVELS >> 1) - 1, "Gain", "   Sensor     Gain",          &gains[0], };
MenuItem exposureTimesMenu =  {  5, 0, 0,  2,  NUM_EXPOSURE_TIMES,  (NUM_EXPOSURE_TIMES >> 1) - 1, "ExpT", " Exposure     Time",  &exposureTimes[0], };
MenuItem voltageRefsMenu =    { 10, 0, 0,  6,    NUM_VOLTAGE_REFS,    (NUM_VOLTAGE_REFS >> 1) - 1, "vRef", "  VoltageReference",    &voltageRefs[0], };
MenuItem voltageOutsMenu =    { 15, 0, 0,  8,    NUM_VOLTAGE_OUTS,    (NUM_VOLTAGE_OUTS >> 1) - 1, "vOut", "  Voltage   Output",    &voltageOuts[0], };
MenuItem invertOutputsMenu =  {  0, 1, 0, 11,  NUM_INVERT_OUTPUTS,                              0, "InvO", "   Invert   Output",  &invertOutputs[0], };
MenuItem zeroPointsMenu =     {  5, 1, 0,  7,     NUM_ZERO_POINTS,                              1, "0 Pt", "     Zero   Points",     &zeroPoints[0], };
MenuItem ditherHighLowsMenu = { 10, 1, 0,  4, NUM_DITHER_HIGHLOWS,                              1, "dSet", "   Dither      set", &ditherHighLows[0], };
MenuItem ditherSetsMenu =     { 15, 1, 0,  3,         NUM_DITHERS,                              1, "Dith", "   Dither   Matrix",     &ditherSets[0], };
MenuItem edgeOpModesMenu =    {  0, 2, 0,  9,   NUM_EDGE_OP_MODES,                              0, "EdOp", "     EdgeOperation",    &edgeOpModes[0], };
MenuItem edgeModesMenu =      {  5, 2, 0,  5,      NUM_EDGE_MODES,      (NUM_EDGE_MODES >> 1) - 1, "EdMo", "     Edge     Mode",      &edgeModes[0], };
MenuItem edgeExclusivesMenu = { 10, 2, 0, 10,  NUM_EDGE_EXCLUSIVE,                              0, "EdEx", "     EdgeExclusive", &edgeExclusives[0], };

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
