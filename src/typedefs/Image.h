#ifndef TYPEDEF_IMAGE_H
#define TYPEDEF_IMAGE_H

typedef struct {
  const unsigned char bank;
  unsigned char* const tilesUpper;
  unsigned char* const tilesLower;
  unsigned char* const thumbnail;
  unsigned char* const meta;
  unsigned char* const metaEcho;
} Image;

#endif
