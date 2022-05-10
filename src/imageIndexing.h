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

void setImageSlot(unsigned char address, unsigned char newValue) {
  SWITCH_RAM(0);

  if (address >= NUM_IMAGES) {
    dead();
  }

  unsigned char oldValue = game_data_meta_imageslots[address];

  if (newValue == oldValue) {
    return;
  }

  // Update value for imageslot
  game_data_meta_imageslots_echo[address] = game_data_meta_imageslots[address] = newValue;

  // Update checksum XOR
  game_data_meta_imageslots_echo_checksum[0] = game_data_meta_imageslots_checksum[0] = game_data_meta_imageslots_checksum[0] + newValue - oldValue;

  // Update checksum SUM
  game_data_meta_imageslots_echo_checksum[1] = game_data_meta_imageslots_checksum[1] = game_data_meta_imageslots_checksum[1] ^ newValue ^ oldValue;
}

inline unsigned char getImageSlot(unsigned char index) {
  if (index >= NUM_IMAGES) {
    return NUM_IMAGES;
  }

  return sortedIndices[index];
}



inline unsigned char getAddressForIndex(unsigned char index) {
  SWITCH_RAM(0);
  for (unsigned char address = 0; address < NUM_IMAGES; address++) {
    if (game_data_meta_imageslots[address] == index) {
      return address;
    }
  }

  return NUM_IMAGES;
}


inline unsigned char getNextHighestAddress(unsigned char searchIndex) {
  SWITCH_RAM(0);

  while (searchIndex < NUM_IMAGES) {
    for (unsigned char address = 0; address < NUM_IMAGES; address++) {
      if (game_data_meta_imageslots[address] == searchIndex) {
        return address;
      }
    }

    searchIndex += 1;
  }

  return NUM_IMAGES;
}


void cleanupIndexGaps() {
  SWITCH_RAM(0);
  for (unsigned char index = 0; index < NUM_IMAGES; index++) {
    // image number does not exist in list
    if (getAddressForIndex(index) >= NUM_IMAGES) {
      unsigned char address = getNextHighestAddress(index);
      if (address < NUM_IMAGES) {
        setImageSlot(address, index);
      }
    }
  }
}

void sortImages() {
  SWITCH_RAM(0);

  unsigned char deletedIndex = 0;
  numVisibleImages = 0;
  unsigned char sortedDeletedIndices[NUM_IMAGES];
  unsigned char i = 0;

  for (i = 0; i < NUM_IMAGES; i++) {
    unsigned char current = game_data_meta_imageslots[i];

    if (current == IMAGE_DELETED) {
      sortedDeletedIndices[deletedIndex] = i;
      deletedIndex += 1;
    } else {
      sortedIndices[current] = i;
      numVisibleImages += 1;
    }
  }

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
