#include <gbdk/platform.h>
#include "typedefs/Image.h"
#include "gbcamera.h"

static const Image image01 = { 1, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image02 = { 1, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image03 = { 2, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image04 = { 2, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image05 = { 3, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image06 = { 3, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image07 = { 4, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image08 = { 4, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image09 = { 5, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image10 = { 5, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image11 = { 6, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image12 = { 6, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image13 = { 7, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image14 = { 7, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image15 = { 8, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image16 = { 8, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image17 = { 9, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image18 = { 9, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image19 = {10, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image20 = {10, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image21 = {11, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image22 = {11, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image23 = {12, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image24 = {12, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image25 = {13, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image26 = {13, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image27 = {14, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image28 = {14, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };
static const Image image29 = {15, image_first_upper,  image_first_lower,  image_first_thumbnail,  image_first_meta,  image_first_meta_echo  };
static const Image image30 = {15, image_second_upper, image_second_lower, image_second_thumbnail, image_second_meta, image_second_meta_echo };

const Image * const images[30] = {
  &image01, &image02, &image03, &image04, &image05,
  &image06, &image07, &image08, &image09, &image10,
  &image11, &image12, &image13, &image14, &image15,
  &image16, &image17, &image18, &image19, &image20,
  &image21, &image22, &image23, &image24, &image25,
  &image26, &image27, &image28, &image29, &image30,
};
