#define NUM_IMAGES 30
#define IMAGE_DELETED 0xFF
#define IMAGE_UNDEFINED 0xFE

unsigned char numVisibleImages = 0;
unsigned char imageIndex = 0;
unsigned char sortedIndices[NUM_IMAGES] = {
    IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED,
    IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED,
    IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED, IMAGE_UNDEFINED,
};

void setImageSlot(unsigned char imageSlot, unsigned char newValue) {
  SWITCH_RAM(0);

  unsigned char oldIndex = game_data_meta_imageslots[imageSlot];

  // Update value for imageslot
  game_data_meta_imageslots_echo[imageSlot] = game_data_meta_imageslots[imageSlot] = newValue;

  // Update checksum XOR
  game_data_meta_imageslots_echo_checksum[0] = game_data_meta_imageslots_checksum[0] = game_data_meta_imageslots_checksum[0] + newValue - oldIndex;

  // Update checksum SUM
  game_data_meta_imageslots_echo_checksum[1] = game_data_meta_imageslots_checksum[1] = game_data_meta_imageslots_checksum[1] ^ newValue ^ oldIndex;
}

inline unsigned char getImageSlot(unsigned char index) {
  if (index >= NUM_IMAGES) {
    return NUM_IMAGES;
  }

  return sortedIndices[index];
}

void sortImages() {
  SWITCH_RAM(0);

  unsigned char deletedIndex = 0;
  unsigned char visibleIndex = 0;
  unsigned char sortedDeletedIndices[NUM_IMAGES];
  unsigned char i = 0;

  for (i = 0; i < NUM_IMAGES; i++) {
    unsigned char current = game_data_meta_imageslots[i];

    if (current == IMAGE_DELETED) {
      sortedDeletedIndices[deletedIndex] = i;
      deletedIndex += 1;
    } else {
      sortedIndices[visibleIndex] = i;
      visibleIndex += 1;
    }
  }

  numVisibleImages = visibleIndex;

  deletedIndex = 0;
  for (i = 0; i < NUM_IMAGES; i++) {
    if (sortedIndices[i] == IMAGE_UNDEFINED) {
      sortedIndices[i] = sortedDeletedIndices[deletedIndex];
      deletedIndex += 1;
    }
  }

  // Cleanup indices: deleting an image on the original rom just marks
  // that slot as 0xff but higher numbered images are not corrected.

  for (i = 0; i < numVisibleImages; i++) {
    // ToDo: YES PLEASE ???
  }
}

inline unsigned char findFirstFreeSlot() {
  SWITCH_RAM(0);

  for (unsigned char i = 0; i < NUM_IMAGES; i++) {
    if (game_data_meta_imageslots[i] == IMAGE_DELETED) {
      return i;
    }
  }

  return NUM_IMAGES;
}
