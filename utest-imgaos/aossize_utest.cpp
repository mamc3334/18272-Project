#include <cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h>
#include "../imgaos/aossize.hpp"  // Include your common header file
#include "../utest-common/utest-helpers.hpp"

TEST(AOSSizeTests, Old16Test){
  const unsigned int rows = 2;
  const unsigned int cols = 2;
  vector<vector<bigColor>> pixelArray(rows, vector<bigColor>(cols));

  ifstream mockDataFile("../test-data/aossize_old16.bin");
  ASSERT_TRUE(mockDataFile.is_open()) << "Failed to open test data";

  aossize_old_photo_16(pixelArray, rows, cols, mockDataFile);
  const vector<vector<bigColor>> expectedPixelArray = {
    { {.r=100, .g=150, .b=200}, {.r=250, .g=300, .b=350} },
    { {.r=400, .g=450, .b=500}, {.r=550, .g=600, .b=650} }
  };

  EXPECT_EQ(pixelArray, expectedPixelArray);
}

TEST(AOSSizeTests, Old8Test){
  const unsigned int rows = 2;
  const unsigned int cols = 2;
  vector<vector<smallColor>> pixelArray(rows, vector<smallColor>(cols));
  ifstream mockDataFile("../test-data/aossize_old8.bin");

  ASSERT_TRUE(mockDataFile.is_open()) << "Failed to open test data";

  aossize_old_photo_8(pixelArray, rows, cols, mockDataFile);

  const vector<vector<bigColor>> expectedPixelArray = {
    { {.r=10, .g=15, .b=20}, {.r=25, .g=30, .b=35} },
    { {.r=40, .g=45, .b=50}, {.r=55, .g=60, .b=65} }
  };

  EXPECT_EQ(pixelArray, expectedPixelArray);
}

TEST(AOSSizeTests, Resize16Test) {
  constexpr unsigned int oRows = 2;
  constexpr unsigned int oCols = 2;
  constexpr int nRows =  1;
  constexpr int nCols = 1;
  vector<vector<bigColor>> pixelArray = {
    { {.r=100, .g=150, .b=200}, {.r=250, .g=300, .b=350} },
    { {.r=400, .g=450, .b=500}, {.r=550, .g=600, .b=650} }
  };

  ofstream mockOutFile("../test-data/outputs/aossize_resize16_out.txt");
  ASSERT_TRUE(mockOutFile.is_open()) << "Failed to open output file";

  aossize_resize_16(pixelArray, oRows, oCols, nRows, nCols, mockOutFile);

  EXPECT_TRUE(compareBinaryFiles("../test-data/outputs/aossize_resize16_out.txt", "../test-data/expected/aossize_resize16.txt"));
}

TEST(AOSSizeTests, Resize8Test) {
  constexpr unsigned int oRows = 2;
  constexpr unsigned int oCols = 2;
  constexpr int nRows =  1;
  constexpr int nCols = 1;
  vector<vector<smallColor>> pixelArray = {
    { {.r=10, .g=15, .b=20}, {.r=25, .g=30, .b=35} },
    { {.r=40, .g=45, .b=50}, {.r=55, .g=60, .b=65} }
  };

  ofstream mockOutFile("../test-data/outputs/aossize_resize8_out.bin");
  ASSERT_TRUE(mockOutFile.is_open()) << "Failed to open output file before performing function";

  aossize_resize_8(pixelArray, oRows, oCols, nRows, nCols, mockOutFile);

  EXPECT_TRUE(compareBinaryFiles("../test-data/outputs/aossize_resize8_out.txt", "../test-data/expected/aossize_resize8.txt"));
}

TEST(AOSSizeTests, Interpolate16Test) {
  // 2x2 pixel photo
  vector<vector<bigColor>> pixelArray = {
    { {.r=100, .g=150, .b=200}, {.r=250, .g=300, .b=350} },
    { {.r=400, .g=450, .b=500}, {.r=550, .g=600, .b=650} }
  };
  // Midpoints between corner pixels (0,1), (1,1), (1,0), (0,0)
  const float x = 0.5F;
  const float y = 0.5F;
  const float xl = 0.0F;
  const float xh = 1.0F;
  const float yl = 0.0F;
  const float yh = 1.0F;

  const bigColor pixel = interpolate_16(pixelArray, x,y,xl,xh,yl,yh);
  const bigColor expectedPixel = {.r=325, .g=375, .b=425};

  EXPECT_EQ(pixel.r, expectedPixel.r);
  EXPECT_EQ(pixel.g, expectedPixel.g);
  EXPECT_EQ(pixel.b, expectedPixel.b);
}

TEST(AOSSizeTests, Interpolate8Test) {
  // 2x2 pixel photo
  vector<vector<bigColor>> pixelArray = {
    { {.r=10, .g=15, .b=20}, {.r=25, .g=30, .b=35} },
    { {.r=40, .g=45, .b=50}, {.r=55, .g=60, .b=65} }
  };
  // Midpoints between corner pixels (0,1), (1,1), (1,0), (0,0)
  const float x = 0.5F;
  const float y = 0.5f;
  const float xl = 0.0f;
  const float xh = 1.0f;
  const float yl = 0.0f;
  const float yh = 1.0f;

  const bigColor pixel = interpolate_16(pixelArray, x,y,xl,xh,yl,yh);
  const bigColor expectedPixel = {.r=32, .g=37, .b=42};

  EXPECT_EQ(pixel.r, expectedPixel.r);
  EXPECT_EQ(pixel.g, expectedPixel.g);
  EXPECT_EQ(pixel.b, expectedPixel.b);
}