extern unsigned char last_seen_upper[]; extern unsigned char last_seen_lower[]; extern unsigned char last_seen_meta[]; extern unsigned char last_seen_meta_echo[];
extern unsigned char game_data_meta[];
extern unsigned char image_01_upper[]; extern unsigned char image_01_lower[]; extern unsigned char image_01_meta[]; extern unsigned char image_01_meta_echo[];
extern unsigned char image_02_upper[]; extern unsigned char image_02_lower[]; extern unsigned char image_02_meta[]; extern unsigned char image_02_meta_echo[];
extern unsigned char image_03_upper[]; extern unsigned char image_03_lower[]; extern unsigned char image_03_meta[]; extern unsigned char image_03_meta_echo[];
extern unsigned char image_04_upper[]; extern unsigned char image_04_lower[]; extern unsigned char image_04_meta[]; extern unsigned char image_04_meta_echo[];
extern unsigned char image_05_upper[]; extern unsigned char image_05_lower[]; extern unsigned char image_05_meta[]; extern unsigned char image_05_meta_echo[];
extern unsigned char image_06_upper[]; extern unsigned char image_06_lower[]; extern unsigned char image_06_meta[]; extern unsigned char image_06_meta_echo[];
extern unsigned char image_07_upper[]; extern unsigned char image_07_lower[]; extern unsigned char image_07_meta[]; extern unsigned char image_07_meta_echo[];
extern unsigned char image_08_upper[]; extern unsigned char image_08_lower[]; extern unsigned char image_08_meta[]; extern unsigned char image_08_meta_echo[];
extern unsigned char image_09_upper[]; extern unsigned char image_09_lower[]; extern unsigned char image_09_meta[]; extern unsigned char image_09_meta_echo[];
extern unsigned char image_10_upper[]; extern unsigned char image_10_lower[]; extern unsigned char image_10_meta[]; extern unsigned char image_10_meta_echo[];
extern unsigned char image_11_upper[]; extern unsigned char image_11_lower[]; extern unsigned char image_11_meta[]; extern unsigned char image_11_meta_echo[];
extern unsigned char image_12_upper[]; extern unsigned char image_12_lower[]; extern unsigned char image_12_meta[]; extern unsigned char image_12_meta_echo[];
extern unsigned char image_13_upper[]; extern unsigned char image_13_lower[]; extern unsigned char image_13_meta[]; extern unsigned char image_13_meta_echo[];
extern unsigned char image_14_upper[]; extern unsigned char image_14_lower[]; extern unsigned char image_14_meta[]; extern unsigned char image_14_meta_echo[];
extern unsigned char image_15_upper[]; extern unsigned char image_15_lower[]; extern unsigned char image_15_meta[]; extern unsigned char image_15_meta_echo[];
extern unsigned char image_16_upper[]; extern unsigned char image_16_lower[]; extern unsigned char image_16_meta[]; extern unsigned char image_16_meta_echo[];
extern unsigned char image_17_upper[]; extern unsigned char image_17_lower[]; extern unsigned char image_17_meta[]; extern unsigned char image_17_meta_echo[];
extern unsigned char image_18_upper[]; extern unsigned char image_18_lower[]; extern unsigned char image_18_meta[]; extern unsigned char image_18_meta_echo[];
extern unsigned char image_19_upper[]; extern unsigned char image_19_lower[]; extern unsigned char image_19_meta[]; extern unsigned char image_19_meta_echo[];
extern unsigned char image_20_upper[]; extern unsigned char image_20_lower[]; extern unsigned char image_20_meta[]; extern unsigned char image_20_meta_echo[];
extern unsigned char image_21_upper[]; extern unsigned char image_21_lower[]; extern unsigned char image_21_meta[]; extern unsigned char image_21_meta_echo[];
extern unsigned char image_22_upper[]; extern unsigned char image_22_lower[]; extern unsigned char image_22_meta[]; extern unsigned char image_22_meta_echo[];
extern unsigned char image_23_upper[]; extern unsigned char image_23_lower[]; extern unsigned char image_23_meta[]; extern unsigned char image_23_meta_echo[];
extern unsigned char image_24_upper[]; extern unsigned char image_24_lower[]; extern unsigned char image_24_meta[]; extern unsigned char image_24_meta_echo[];
extern unsigned char image_25_upper[]; extern unsigned char image_25_lower[]; extern unsigned char image_25_meta[]; extern unsigned char image_25_meta_echo[];
extern unsigned char image_26_upper[]; extern unsigned char image_26_lower[]; extern unsigned char image_26_meta[]; extern unsigned char image_26_meta_echo[];
extern unsigned char image_27_upper[]; extern unsigned char image_27_lower[]; extern unsigned char image_27_meta[]; extern unsigned char image_27_meta_echo[];
extern unsigned char image_28_upper[]; extern unsigned char image_28_lower[]; extern unsigned char image_28_meta[]; extern unsigned char image_28_meta_echo[];
extern unsigned char image_29_upper[]; extern unsigned char image_29_lower[]; extern unsigned char image_29_meta[]; extern unsigned char image_29_meta_echo[];
extern unsigned char image_30_upper[]; extern unsigned char image_30_lower[]; extern unsigned char image_30_meta[]; extern unsigned char image_30_meta_echo[];

typedef struct {
  const unsigned char bank;
  unsigned char* const tilesUpper;
  unsigned char* const tilesLower;
  unsigned char* const meta;
  unsigned char* const metaEcho;
} Image;

Image images[] = {
  { 1, image_01_upper, image_01_lower, image_01_meta, image_01_meta_echo },
  { 1, image_02_upper, image_02_lower, image_02_meta, image_02_meta_echo },
  { 2, image_03_upper, image_03_lower, image_03_meta, image_03_meta_echo },
  { 2, image_04_upper, image_04_lower, image_04_meta, image_04_meta_echo },
  { 3, image_05_upper, image_05_lower, image_05_meta, image_05_meta_echo },
  { 3, image_06_upper, image_06_lower, image_06_meta, image_06_meta_echo },
  { 4, image_07_upper, image_07_lower, image_07_meta, image_07_meta_echo },
  { 4, image_08_upper, image_08_lower, image_08_meta, image_08_meta_echo },
  { 5, image_09_upper, image_09_lower, image_09_meta, image_09_meta_echo },
  { 5, image_10_upper, image_10_lower, image_10_meta, image_10_meta_echo },
  { 6, image_11_upper, image_11_lower, image_11_meta, image_11_meta_echo },
  { 6, image_12_upper, image_12_lower, image_12_meta, image_12_meta_echo },
  { 7, image_13_upper, image_13_lower, image_13_meta, image_13_meta_echo },
  { 7, image_14_upper, image_14_lower, image_14_meta, image_14_meta_echo },
  { 8, image_15_upper, image_15_lower, image_15_meta, image_15_meta_echo },
  { 8, image_16_upper, image_16_lower, image_16_meta, image_16_meta_echo },
  { 9, image_17_upper, image_17_lower, image_17_meta, image_17_meta_echo },
  { 9, image_18_upper, image_18_lower, image_18_meta, image_18_meta_echo },
  {10, image_19_upper, image_19_lower, image_19_meta, image_19_meta_echo },
  {10, image_20_upper, image_20_lower, image_20_meta, image_20_meta_echo },
  {11, image_21_upper, image_21_lower, image_21_meta, image_21_meta_echo },
  {11, image_22_upper, image_22_lower, image_22_meta, image_22_meta_echo },
  {12, image_23_upper, image_23_lower, image_23_meta, image_23_meta_echo },
  {12, image_24_upper, image_24_lower, image_24_meta, image_24_meta_echo },
  {13, image_25_upper, image_25_lower, image_25_meta, image_25_meta_echo },
  {13, image_26_upper, image_26_lower, image_26_meta, image_26_meta_echo },
  {14, image_27_upper, image_27_lower, image_27_meta, image_27_meta_echo },
  {14, image_28_upper, image_28_lower, image_28_meta, image_28_meta_echo },
  {15, image_29_upper, image_29_lower, image_29_meta, image_29_meta_echo },
  {15, image_30_upper, image_30_lower, image_30_meta, image_30_meta_echo },
  { 0, last_seen_upper, last_seen_lower, last_seen_meta, last_seen_meta_echo },
};

extern unsigned char A000;
extern unsigned char A001;
extern unsigned char A002;
extern unsigned char A003;
extern unsigned char A004;
extern unsigned char A005;
extern unsigned char A006A035[48];

extern unsigned char image_01_unused[];
extern unsigned char image_02_unused[];
