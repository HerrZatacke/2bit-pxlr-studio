#define NUM_IMAGES 30
#define IMAGE_DELETED 0xFF
#define IMAGE_UNDEFINED 0xFE

unsigned char numVisibleImages = 0;
unsigned char firstFreeSlot = 0;
unsigned char imageIndex = 0;
unsigned char sortedIndices[NUM_IMAGES] = {
    IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED,
    IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED,
    IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED,
};

void sortImages() {
  SWITCH_RAM(0);

  unsigned char deletedIndex = 0;
  unsigned char sortedDeletedIndices[NUM_IMAGES];
  unsigned char i = 0;

  for (i = 0; i < NUM_IMAGES; i++) {
    unsigned char current = game_data_meta_imageslots[i];

    if (current == IMAGE_DELETED) {
      sortedDeletedIndices[deletedIndex] = i;
      deletedIndex += 1;
    } else {
      sortedIndices[current] = i;
    }
  }

  firstFreeSlot = sortedDeletedIndices[0];
  numVisibleImages = NUM_IMAGES - deletedIndex;

  deletedIndex = 0;
  for (i = 0; i < NUM_IMAGES; i++) {
    if (sortedIndices[i] == IMAGE_UNDEFINED) {
      sortedIndices[i] = sortedDeletedIndices[deletedIndex];
      deletedIndex += 1;
    }
  }
}

inline unsigned char getImageSlot(unsigned char index) {
  if (index >= NUM_IMAGES) {
    return NUM_IMAGES;
  }

  return sortedIndices[index];
}
