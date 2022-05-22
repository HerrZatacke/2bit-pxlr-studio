#define NUM_OVERLAY_SPRITES 16

const Overlay noOverlayH1 = { SPRITE_BORDER_H_1, 0, 0, };
const Overlay noOverlayH2 = { SPRITE_BORDER_H_2, 0, 0, };
const Overlay noOverlayH3 = { SPRITE_BORDER_H_3, 0, 0, };
const Overlay noOverlayH4 = { SPRITE_BORDER_H_4, 0, 0, };
const Overlay noOverlayH5 = { SPRITE_BORDER_H_5, 0, 0, };
const Overlay noOverlayH6 = { SPRITE_BORDER_H_6, 0, 0, };
const Overlay noOverlayH7 = { SPRITE_BORDER_H_7, 0, 0, };
const Overlay noOverlayH8 = { SPRITE_BORDER_H_8, 0, 0, };
const Overlay noOverlayV1 = { SPRITE_BORDER_V_1, 0, 0, };
const Overlay noOverlayV2 = { SPRITE_BORDER_V_2, 0, 0, };
const Overlay noOverlayV3 = { SPRITE_BORDER_V_3, 0, 0, };
const Overlay noOverlayV4 = { SPRITE_BORDER_V_4, 0, 0, };
const Overlay noOverlayV5 = { SPRITE_BORDER_V_5, 0, 0, };
const Overlay noOverlayV6 = { SPRITE_BORDER_V_6, 0, 0, };
const Overlay noOverlayV7 = { SPRITE_BORDER_V_7, 0, 0, };
const Overlay noOverlayV8 = { SPRITE_BORDER_V_8, 0, 0, };

const Overlay *noOverlay[NUM_OVERLAY_SPRITES] = {
  &noOverlayH1, &noOverlayH2, &noOverlayH3, &noOverlayH4,
  &noOverlayH5, &noOverlayH6, &noOverlayH7, &noOverlayH8,
  &noOverlayV1, &noOverlayV2, &noOverlayV3, &noOverlayV4,
  &noOverlayV5, &noOverlayV6, &noOverlayV7, &noOverlayV8,
};

const Overlay outerBorderH1 = { SPRITE_BORDER_H_1, 24,  32,  };
const Overlay outerBorderH2 = { SPRITE_BORDER_H_2, 32,  32,  };
const Overlay outerBorderH3 = { SPRITE_BORDER_H_3, 136, 32,  };
const Overlay outerBorderH4 = { SPRITE_BORDER_H_4, 144, 32,  };
const Overlay outerBorderH5 = { SPRITE_BORDER_H_5, 24,  143, };
const Overlay outerBorderH6 = { SPRITE_BORDER_H_6, 32,  143, };
const Overlay outerBorderH7 = { SPRITE_BORDER_H_7, 136, 143, };
const Overlay outerBorderH8 = { SPRITE_BORDER_H_8, 144, 143, };
const Overlay outerBorderV1 = { SPRITE_BORDER_V_1, 17,  31,  };
const Overlay outerBorderV2 = { SPRITE_BORDER_V_2, 17,  39,  };
const Overlay outerBorderV3 = { SPRITE_BORDER_V_3, 144, 31,  };
const Overlay outerBorderV4 = { SPRITE_BORDER_V_4, 144, 39,  };
const Overlay outerBorderV5 = { SPRITE_BORDER_V_5, 17,  127, };
const Overlay outerBorderV6 = { SPRITE_BORDER_V_6, 17,  135, };
const Overlay outerBorderV7 = { SPRITE_BORDER_V_7, 144, 127, };
const Overlay outerBorderV8 = { SPRITE_BORDER_V_8, 144, 135, };

const Overlay *outerBorder[NUM_OVERLAY_SPRITES] = {
  &outerBorderH1, &outerBorderH2, &outerBorderH3, &outerBorderH4,
  &outerBorderH5, &outerBorderH6, &outerBorderH7, &outerBorderH8,
  &outerBorderV1, &outerBorderV2, &outerBorderV3, &outerBorderV4,
  &outerBorderV5, &outerBorderV6, &outerBorderV7, &outerBorderV8,
};

const Overlay ruleOfThirdsH1 = { SPRITE_BORDER_H_1, 59,  70,  };
const Overlay ruleOfThirdsH2 = { SPRITE_BORDER_H_2, 66,  70,  };
const Overlay ruleOfThirdsH3 = { SPRITE_BORDER_H_3, 102, 70,  };
const Overlay ruleOfThirdsH4 = { SPRITE_BORDER_H_4, 109, 70,  };
const Overlay ruleOfThirdsH5 = { SPRITE_BORDER_H_5, 59,  107, };
const Overlay ruleOfThirdsH6 = { SPRITE_BORDER_H_6, 66,  107, };
const Overlay ruleOfThirdsH7 = { SPRITE_BORDER_H_7, 102, 107, };
const Overlay ruleOfThirdsH8 = { SPRITE_BORDER_H_8, 109, 107, };
const Overlay ruleOfThirdsV1 = { SPRITE_BORDER_V_1, 59,  62,  };
const Overlay ruleOfThirdsV2 = { SPRITE_BORDER_V_2, 59,  69,  };
const Overlay ruleOfThirdsV3 = { SPRITE_BORDER_V_3, 102, 62,  };
const Overlay ruleOfThirdsV4 = { SPRITE_BORDER_V_4, 102, 69,  };
const Overlay ruleOfThirdsV5 = { SPRITE_BORDER_V_5, 59,  99,  };
const Overlay ruleOfThirdsV6 = { SPRITE_BORDER_V_6, 59,  106, };
const Overlay ruleOfThirdsV7 = { SPRITE_BORDER_V_7, 102, 99,  };
const Overlay ruleOfThirdsV8 = { SPRITE_BORDER_V_8, 102, 106, };

const Overlay *ruleOfThirds[NUM_OVERLAY_SPRITES] = {
  &ruleOfThirdsH1, &ruleOfThirdsH2, &ruleOfThirdsH3, &ruleOfThirdsH4,
  &ruleOfThirdsH5, &ruleOfThirdsH6, &ruleOfThirdsH7, &ruleOfThirdsH8,
  &ruleOfThirdsV1, &ruleOfThirdsV2, &ruleOfThirdsV3, &ruleOfThirdsV4,
  &ruleOfThirdsV5, &ruleOfThirdsV6, &ruleOfThirdsV7, &ruleOfThirdsV8,
};
