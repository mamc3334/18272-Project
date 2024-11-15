#include <gtest/gtest.h>
#include "../imgaos/aossize.hpp"
#include "common/binaryio.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>

//Tests reading 2x2 input data that has 2 bytes for each r,g,b
TEST(AOSSizeTests, Old16Test) {
  // create metadata and pixelArray for input to tested function
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 0};
  vector<vector<bigColor>> pixelArray(OldPhotoData.height, vector<bigColor>(OldPhotoData.width));

  // create the 2x2 input binary data
  const vector<uint16_t> values = {100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650};
  // Open a binary file for writing
  ofstream createMockFile("Old16_input.bin", ios::binary);
  // Write each value to the file
  for (const auto& value : values) {
      write_binary16(createMockFile, value);
  }
  createMockFile.close();

  //open the input file
  ifstream mockFile("Old16_input.bin");
  ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data";
  //read the input file
  aossize_old_photo_16(pixelArray, OldPhotoData, mockFile);

  //create the expected pixelArray from reading the file
  const vector<vector<bigColor>> expectedPixelArray = {
    { {.r=100, .g=150, .b=200}, {.r=250, .g=300, .b=350} },
    { {.r=400, .g=450, .b=500}, {.r=550, .g=600, .b=650} }
  };
  //actual and expected should be equal
  EXPECT_EQ(pixelArray, expectedPixelArray);
}

//Tests reading 2x2 input data that has 1 byte for each r,g,b
TEST(AOSSizeTests, Old8Test){
  // create metadata and pixelArray for input to tested function
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 0};
  vector<vector<smallColor>> pixelArray(OldPhotoData.height, vector<smallColor>(OldPhotoData.width));

  // create the 2x2 input binary data
  const vector<uint8_t> values = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65};
  // Open a binary file for writing
  ofstream createMockFile("Old8_input.bin", ios::binary);
  // Write each value to the file
  for (const auto& value : values) {
    write_binary8(createMockFile, value);
  }
  createMockFile.close();

  //open the input file
  ifstream mockFile("Old8_input.bin");
  ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data";
  //read the input file
  aossize_old_photo_8(pixelArray, OldPhotoData, mockFile);

  //create the expected pixelArray from reading the file
  const vector<vector<smallColor>> expectedPixelArray = {
    { {.r=10, .g=15, .b=20}, {.r=25, .g=30, .b=35} },
    { {.r=40, .g=45, .b=50}, {.r=55, .g=60, .b=65} }
  };
  //actual and expected should be equivalent
  EXPECT_EQ(pixelArray, expectedPixelArray);
}

// Tests the resize function for 4x4 image to a 2x2 image. Both require 2 bytes for r,g,b
TEST(AOSSizeTests, Resize16Test) {
  //Create input data for resize
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=4, .height=4, .intensity = 1500};
  const Image_Attributes NewPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 1500};
  const vector<vector<bigColor>> pixelArray = {
    { {.r=100, .g=120, .b=140}, {.r=160, .g=180, .b=200}, {.r=220, .g=240, .b=260}, {.r=280, .g=300, .b=320}, },
    { {.r=340, .g=360, .b=380}, {.r=400, .g=420, .b=440}, {.r=460, .g=480, .b=500}, {.r=520, .g=540, .b=560}, },
    { {.r=580, .g=600, .b=620}, {.r=640, .g=660, .b=680}, {.r=700, .g=720, .b=740}, {.r=760, .g=780, .b=800}, },
    { {.r=820, .g=840, .b=860}, {.r=880, .g=900, .b=920}, {.r=940, .g=960, .b=980}, {.r=1000, .g=1020, .b=1040}, }
  };

  //Create expected output file
  const vector<uint16_t> values = {100,120,140,280,300,320,820,840,860,1000,1020,1040};
  ofstream createExpectedFile("Resize16_expected.bin", ios::binary);
  for (const auto& value : values) {
    write_binary16(createExpectedFile, value);
  }
  createExpectedFile.close();

  //Open output file and run resize function
  ofstream mockOutput("Resize16_output.bin", ios::binary);
  ASSERT_TRUE(mockOutput.is_open()) << "Failed to open output file";
  aossize_resize_16(pixelArray, OldPhotoData, NewPhotoData, mockOutput);

  // diff -q command should have 0 exit code
  // NOLINTNEXTLINE(*-env33-c)
  const int exitCode = system("diff -q Resize16_expected.bin Resize16_output.bin");
  EXPECT_EQ(exitCode, 0);
}

// Tests the resize function for 4x4 image to a 2x2 image. Both require 1 byte for r,g,b
TEST(AOSSizeTests, Resize8Test) {
  //Create input data for resize
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=4, .height=4, .intensity = 255};
  const Image_Attributes NewPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 255};
  const vector<vector<smallColor>> pixelArray = {
    { {.r=10, .g=12, .b=14}, {.r=16, .g=18, .b=20}, {.r=22, .g=24, .b=26}, {.r=28, .g=30, .b=32}, },
    { {.r=34, .g=36, .b=38}, {.r=40, .g=42, .b=44}, {.r=46, .g=48, .b=50}, {.r=52, .g=54, .b=56}, },
    { {.r=58, .g=60, .b=62}, {.r=64, .g=66, .b=68}, {.r=70, .g=72, .b=74}, {.r=76, .g=78, .b=80}, },
    { {.r=82, .g=84, .b=86}, {.r=88, .g=90, .b=92}, {.r=94, .g=96, .b=98}, {.r=100, .g=102, .b=104}, }
  };

  //Create expected output file
  const vector<uint8_t> values = {10,12,14,28,30,32,82,84,86,100,102,104};
  ofstream createExpectedFile("Resize8_expected.bin", ios::binary);
  for (const auto& value : values) {
    write_binary8(createExpectedFile, value);
  }
  createExpectedFile.close();

  //Open output file and run resize function
  ofstream mockOutput("Resize8_output.bin", ios::binary);
  ASSERT_TRUE(mockOutput.is_open()) << "Failed to open output file";
  aossize_resize_8(pixelArray, OldPhotoData, NewPhotoData, mockOutput);

  //diff command should have 0 exit code
  // NOLINTNEXTLINE(*-env33-c)
  const int exitCode = system("diff -q Resize8_expected.bin Resize8_output.bin");
  EXPECT_EQ(exitCode, 0);
}

//Tests the interpolation function for uint16_t
TEST(AOSSizeTests, Interpolate16Test) {
  // 2x2 pixel image
  const vector<vector<bigColor>> pixelArray = {
    { {.r=100, .g=150, .b=200}, {.r=250, .g=300, .b=350} },
    { {.r=400, .g=450, .b=500}, {.r=550, .g=600, .b=650} }
  };
  // Midpoints between corner pixels (0,1), (1,1), (1,0), (0,0)
  constexpr Coords coords = {.x_map=0.5, .x_lo=0, .x_hi=1, .y_map=0.5, .y_lo=0, .y_hi=1};

  // run interpolation for midpoints
  const bigColor pixel = interpolate_16(pixelArray, coords);
  // expected interpolated pixel
  constexpr bigColor expectedPixel = {.r=325, .g=375, .b=425};
  //actual should equal expected
  EXPECT_EQ(pixel.r, expectedPixel.r);
  EXPECT_EQ(pixel.g, expectedPixel.g);
  EXPECT_EQ(pixel.b, expectedPixel.b);
}

//Tests the interpolation function for uint8_t
TEST(AOSSizeTests, Interpolate8Test) {
  // 2x2 pixel photo
  const vector<vector<smallColor>> pixelArray = {
    { {.r=10, .g=15, .b=20}, {.r=25, .g=30, .b=35} },
    { {.r=40, .g=45, .b=50}, {.r=55, .g=60, .b=65} }
  };

  // Midpoints between corner pixels (0,1), (1,1), (1,0), (0,0)
  constexpr Coords coords = {.x_map=0.5, .x_lo=0, .x_hi=1, .y_map=0.5, .y_lo=0, .y_hi=1};
  // run interpolation for midpoint
  const smallColor pixel = interpolate_8(pixelArray, coords);
  // create expected result
  constexpr bigColor expectedPixel = {.r=33, .g=38, .b=43};
  // actual should equal expected
  EXPECT_EQ(pixel.r, expectedPixel.r);
  EXPECT_EQ(pixel.g, expectedPixel.g);
  EXPECT_EQ(pixel.b, expectedPixel.b);
}
