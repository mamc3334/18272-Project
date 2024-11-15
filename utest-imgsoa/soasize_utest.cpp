#include <gtest/gtest.h>
#include "../imgaos/aossize.hpp"
#include "common/binaryio.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <imgsoa/soasize.hpp>

//Tests reading 2x2 input data that has 2 bytes for each r,g,b
TEST(SOASizeTests, Old16Test) {
  // create metadata and bigArray struct for input to tested function
  const Image_Attributes OldImageData = {.magic_word = "", .width=2, .height=2, .intensity = 1000};
  bigArray oldImage;

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
  soasize_old_image_16(oldImage, OldImageData, mockFile);

  //create the expected struct from reading the file
  const bigArray expectedImage = {.r={100,250,400,550},.g={150,300,450,600}, .b={200,350,500,650}};
  // actual and expected should be equal
  ASSERT_EQ(expectedImage, oldImage);
}

//Tests reading 2x2 input data that has 1 byte for each r,g,b
TEST(SOASizeTests, Old8Test) {
  // create metadata and struct for input to tested function
  const Image_Attributes OldImageData = {.magic_word = "", .width=2, .height=2, .intensity = 255};
  smallArray oldImage;

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
  soasize_old_image_8(oldImage, OldImageData, mockFile);

  //create the expected struct from reading the file
  const smallArray expectedImage = {.r={10,25,40,55},.g={15,30,45,60}, .b={20,35,50,65}};
  // actual and expected should be equal
  ASSERT_EQ(expectedImage, oldImage);
}

// Tests the resize function for 4x4 image to a 2x2 image. Both require 2 bytes for r,g,b
TEST(SOASizeTests, Resize16Test) {
  //Create input data for resize
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=4, .height=4, .intensity = 1500};
  const Image_Attributes NewPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 1500};
  const bigArray oldImage = {.r={100,160,220,280,340,400,460,520,580,640,700,760,820,880,940,1000}, .g={120,180,240,300,360,420,480,540,600,660,720,780,840,900,960,1020}, .b={140,200,260,320,380,440,500,560,620,680,740,800,860,920,980,1040} };

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
  soasize_resize_16(oldImage, OldPhotoData, NewPhotoData, mockOutput);

  // diff -q command should have 0 exit code
  // NOLINTNEXTLINE(*-env33-c)
  const int exitCode = system("diff -q Resize16_output.bin Resize16_expected.bin");
  EXPECT_EQ(exitCode, 0) << "Files are not identical.";
}

// Tests the resize function for 4x4 image to a 2x2 image. Both require 1 byte for r,g,b
TEST(SOASizeTests, Resize8Test) {
  //Create input data for resize
  const Image_Attributes OldPhotoData = {.magic_word = "", .width=4, .height=4, .intensity = 1500};
  const Image_Attributes NewPhotoData = {.magic_word = "", .width=2, .height=2, .intensity = 1500};
  const smallArray oldImage = {.r={10,16,22,28,34,40,46,52,58,64,70,76,82,88,94,100}, .g={12,18,24,30,36,42,48,54,60,66,72,78,84,90,96,102}, .b={14,20,26,32,38,44,50,56,62,68,74,80,86,92,98,104} };

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
  soasize_resize_8(oldImage, OldPhotoData, NewPhotoData, mockOutput);

  //diff command should have 0 exit code
  // NOLINTNEXTLINE(*-env33-c)
  const int exitCode = system("diff -q Resize8_output.bin Resize8_expected.bin");
  EXPECT_EQ(exitCode, 0) << "Files are not identical.";
}

//Tests the interpolation function for uint16_t
TEST(SOASizeTests, Interpolate16Test) {
  //2x2 pixel image
  const bigArray image = {.r={100,250,400,550},.g={150,300,450,600}, .b={200,350,500,650}};

  // Midpoints between corner pixels (0,1), (1,1), (1,0), (0,0)
  constexpr Coords coords = {.x_map=0.5, .x_lo=0, .x_hi=1, .y_map=0.5, .y_lo=0, .y_hi=1};

  //run interpolation
  const bigColor pixel = interpolate_16(image, coords, 2);
  // create expected pixel from interpolation
  constexpr bigColor expectedPixel = {.r=325, .g=375, .b=425};
  // actual should equal expected
  EXPECT_EQ(pixel.r, expectedPixel.r);
  EXPECT_EQ(pixel.g, expectedPixel.g);
  EXPECT_EQ(pixel.b, expectedPixel.b);
}

TEST(SOASizeTests, Interpolate8Test) {
  //2x2 pixel image
  const smallArray image = {.r={10,25,40,55},.g={15,30,45,60}, .b={20,35,50,65}};

  // Midpoints between corner pixels (0,1), (1,1), (1,0), (0,0)
  constexpr Coords coords = {.x_map=0.5, .x_lo=0, .x_hi=1, .y_map=0.5, .y_lo=0, .y_hi=1};
  // run interpolation for midpoint
  const smallColor pixel = interpolate_8(image, coords, 2);
  // create expected result
  constexpr smallColor expectedPixel = {.r=33, .g=38, .b=43};
  // actual should equal expected
  EXPECT_EQ(pixel.r, expectedPixel.r);
  EXPECT_EQ(pixel.g, expectedPixel.g);
  EXPECT_EQ(pixel.b, expectedPixel.b);
}
