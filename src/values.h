#ifndef VALUES_H
#define VALUES_H

#include "./valuesDefs.h"
#include "./typedefs/MenuOption.h"

extern unsigned const int exposureTimesValues[NUM_EXPOSURE_TIMES];
extern const MenuOption exposureTimes[NUM_EXPOSURE_TIMES];

extern unsigned const char ditherHighLightValues[NUM_CONTRASTS][NUM_CONTRAST_SIZE];
extern unsigned const char ditherLowLightValues[NUM_CONTRASTS][NUM_CONTRAST_SIZE];
extern unsigned const char ditherNoHighLightValues[NUM_CONTRASTS][NUM_CONTRAST_SIZE];
extern unsigned const char ditherNoLowLightValues[NUM_CONTRASTS][NUM_CONTRAST_SIZE];
extern const MenuOption contrasts[NUM_CONTRASTS];

extern const MenuOption gains[NUM_GAIN_LEVELS];
extern const MenuOption edgeOpModes[NUM_EDGE_OP_MODES];
extern const MenuOption edgeExclusives[NUM_EDGE_EXCLUSIVE];
extern const MenuOption edgeModes[NUM_EDGE_MODES];
extern const MenuOption ditherSets[NUM_DITHERSETS];
extern const MenuOption invertOutputs[NUM_INVERT_OUTPUTS];
extern const MenuOption zeroPoints[NUM_ZERO_POINTS];
extern const MenuOption captureModes[NUM_CAPTURE_MODES];
extern const MenuOption voltageRefs[NUM_VOLTAGE_REFS];
extern const MenuOption voltageOuts[NUM_VOLTAGE_OUTS];

#endif
