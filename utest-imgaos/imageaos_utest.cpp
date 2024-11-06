#include <gtest/gtest.h>
#include "../imgaos/imageaos.hpp"  // Include your common header file
#include "../common/binaryio.hpp"

TEST(ImageAOSTests, Resize16Test) {
  setInFile("../test-data/test16.ppm");
  setOutFile("../test-data/outputs/resize16.ppm");
  Image_Attributes newImageData = {.width=4, .height=4};
  aos_resize(newImageData);

  ifstream expectedFile("../test-data/expected/resize16.ppm");
  ifstream outputFile(getOutFile());
  ASSERT_TRUE(expectedFile.is_open()) << "Failed to open expected data file";
  ASSERT_TRUE(outputFile.is_open()) << "Failed to open output file";

  const Image_Attributes expectedData = get_image_metadata(expectedFile);
  const Image_Attributes outputData = get_image_metadata(outputFile);

  EXPECT_EQ(expectedData.magic_word, outputData.magic_word) << "Magic word does not match expected value";
  EXPECT_EQ(expectedData.width, outputData.width) << "Image width does not match expected value";
  EXPECT_EQ(expectedData.height, outputData.height) << "Image height does not match expected value";
  EXPECT_EQ(expectedData.intensity, outputData.intensity) << "Image intensity does not match expected value";

  for(unsigned int i = 0; i < 3 * expectedData.width * expectedData.height; i++) {
    EXPECT_EQ(read_binary16(expectedFile), read_binary16(outputFile)) << "One or more pixels have a value that does not match expected value";
  }
}

TEST(ImageAOSTests, Resize8Test) {
  setInFile("../test-data/test8.ppm");
  setOutFile("../test-data/outputs/resize8.ppm");
  Image_Attributes newImageData = {.width=4, .height=4};
  aos_resize(newImageData);

  ifstream expectedFile("../test-data/expected/resize8.ppm");
  ifstream outputFile(getOutFile());
  ASSERT_TRUE(expectedFile.is_open()) << "Failed to open expected data file";
  ASSERT_TRUE(outputFile.is_open()) << "Failed to open output file";

  const Image_Attributes expectedData = get_image_metadata(expectedFile);
  const Image_Attributes outputData = get_image_metadata(outputFile);

  EXPECT_EQ(expectedData.magic_word, outputData.magic_word) << "Magic word does not match expected value";
  EXPECT_EQ(expectedData.width, outputData.width) << "Image width does not match expected value";
  EXPECT_EQ(expectedData.height, outputData.height) << "Image height does not match expected value";
  EXPECT_EQ(expectedData.intensity, outputData.intensity) << "Image intensity does not match expected value";

  for(unsigned int i = 0; i < 3 * expectedData.width * expectedData.height; i++) {
    EXPECT_EQ(read_binary8(expectedFile), read_binary8(outputFile)) << "One or more pixels have a value that does not match expected value";
  }
}

TEST(ImageAOSTests, CutFreqTest) {

}

TEST(ImageAOSTests, CompressTest) {

}