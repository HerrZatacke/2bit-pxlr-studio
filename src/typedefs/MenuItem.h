
typedef struct {
  const unsigned char x;
  const unsigned char page;
  unsigned char value;
  const unsigned char storeOffset;
  const unsigned char numOptions;
  const unsigned char defaultValue;
  const unsigned char* title;
  const unsigned char* description;
  const MenuOption* options;
} MenuItem;
