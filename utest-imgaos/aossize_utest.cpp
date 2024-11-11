#include <gtest/gtest.h>
#include "../imgaos/aossize.hpp"
#include "../utest-common/utest-helpers.hpp"
#include <filesystem>


TEST(AOSSizeTests, Old16Test) {
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 0};
  vector<vector<bigColor>> pixelArray(OldPhotoData.height, vector<bigColor>(OldPhotoData.width));

  ifstream mockDataFile("../test-data/aossize_old16.bin");
  ASSERT_TRUE(mockDataFile.is_open()) << "Failed to open test data";

  aossize_old_photo_16(pixelArray, OldPhotoData, mockDataFile);
  const vector<vector<bigColor>> expectedPixelArray = {
    { {.r=100, .g=150, .b=200}, {.r=250, .g=300, .b=350} },
    { {.r=400, .g=450, .b=500}, {.r=550, .g=600, .b=650} }
  };

  EXPECT_EQ(pixelArray, expectedPixelArray);
}

TEST(AOSSizeTests, Old8Test){
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 0};
  vector<vector<smallColor>> pixelArray(OldPhotoData.height, vector<smallColor>(OldPhotoData.width));
  ifstream mockDataFile("../test-data/aossize_old8.bin");

  ASSERT_TRUE(mockDataFile.is_open()) << "Failed to open test data";

  aossize_old_photo_8(pixelArray, OldPhotoData, mockDataFile);

  const vector<vector<smallColor>> expectedPixelArray = {
    { {.r=10, .g=15, .b=20}, {.r=25, .g=30, .b=35} },
    { {.r=40, .g=45, .b=50}, {.r=55, .g=60, .b=65} }
  };

  EXPECT_EQ(pixelArray, expectedPixelArray);
}

TEST(AOSSizeTests, Resize16Test) {
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 0};
  const Image_Attributes NewPhotoData = {.magic_word = "", .width=1, .height=3, .intensity = 0};

  vector<vector<bigColor>> pixelArray = {
    { {.r=100, .g=150, .b=200}, {.r=250, .g=300, .b=350} },
    { {.r=400, .g=450, .b=500}, {.r=550, .g=600, .b=650} }
  };

  ofstream mockOutFile("../test-data/outputs/aossize_resize16_out.bin");
  ASSERT_TRUE(mockOutFile.is_open()) << "Failed to open output file";

  aossize_resize_16(pixelArray, OldPhotoData, NewPhotoData, mockOutFile);

  EXPECT_TRUE(compareBinaryFiles("../test-data/outputs/aossize_resize16_out.txt", "../test-data/expected/aossize_resize16.txt"));
}

TEST(AOSSizeTests, Resize8Test) {
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 0};
  const Image_Attributes NewPhotoData = {.magic_word = "", .width=1, .height=3, .intensity = 0};

  vector<vector<smallColor>> pixelArray = {
    { {.r=10, .g=15, .b=20}, {.r=25, .g=30, .b=35} },
    { {.r=40, .g=45, .b=50}, {.r=55, .g=60, .b=65} }
  };

  ofstream mockOutFile("../test-data/outputs/aossize_resize8_out.bin");
  ASSERT_TRUE(mockOutFile.is_open()) << "Failed to open output file before performing function";

  aossize_resize_8(pixelArray, OldPhotoData, NewPhotoData, mockOutFile);

  EXPECT_TRUE(compareBinaryFiles("../test-data/outputs/aossize_resize8_out.txt", "../test-data/expected/aossize_resize8.txt"));
}

TEST(AOSSizeTests, Interpolate16Test) {
  // 2x2 pixel photo
  const vector<vector<bigColor>> pixelArray = {
    { {.r=100, .g=150, .b=200}, {.r=250, .g=300, .b=350} },
    { {.r=400, .g=450, .b=500}, {.r=550, .g=600, .b=650} }
  };
  // Midpoints between corner pixels (0,1), (1,1), (1,0), (0,0)
  constexpr Coords coords = {.x_map=0.5, .x_lo=0, .x_hi=1, .y_map=0.5, .y_lo=0, .y_hi=1};

  const bigColor pixel = interpolate_16(pixelArray, coords);
  constexpr bigColor expectedPixel = {.r=325, .g=375, .b=425};

  EXPECT_EQ(pixel.r, expectedPixel.r);
  EXPECT_EQ(pixel.g, expectedPixel.g);
  EXPECT_EQ(pixel.b, expectedPixel.b);
}

TEST(AOSSizeTests, Interpolate8Test) {
  // 2x2 pixel photo
  const vector<vector<smallColor>> pixelArray = {
    { {.r=10, .g=15, .b=20}, {.r=25, .g=30, .b=35} },
    { {.r=40, .g=45, .b=50}, {.r=55, .g=60, .b=65} }
  };

  // Midpoints between corner pixels (0,1), (1,1), (1,0), (0,0)
  constexpr Coords coords = {.x_map=0.5, .x_lo=0, .x_hi=1, .y_map=0.5, .y_lo=0, .y_hi=1};

  const smallColor pixel = interpolate_8(pixelArray, coords);
  constexpr bigColor expectedPixel = {.r=32, .g=37, .b=42};

  EXPECT_EQ(pixel.r, expectedPixel.r);
  EXPECT_EQ(pixel.g, expectedPixel.g);
  EXPECT_EQ(pixel.b, expectedPixel.b);
}

