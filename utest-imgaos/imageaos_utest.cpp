#include <gtest/gtest.h>
#include "../imgaos/imageaos.hpp"  // Include your common header file
#include "../common/binaryio.hpp"

//Large 100 to 1000
// TEST(ImageAOSTests, Resize16_100to1000_Test) {
//   setInFile("../../test-data/lake-large-100.ppm");
//   setOutFile("lake-large-output-1000.ppm");
//   Image_Attributes newImageData = {.magic_word = "", .width=1000, .height=1000, .intensity = 0};
//   aos_resize(newImageData);
//
//   const int result = system("diff -q ../../test-data/lake-large-1000.ppm lake-large-output-1000.ppm"); // NOLINT(*-env33-c)
//   EXPECT_EQ(result, 0);
// }
//
// //Large 1000 to 100
// TEST(ImageAOSTests, Resize16_1000to100_Test) {
//   setInFile("../../test-data/lake-large-1000.ppm");
//   setOutFile("lake-large-output-100.ppm");
//   Image_Attributes newImageData = {.magic_word = "", .width=100, .height=100, .intensity = 0};
//   aos_resize(newImageData);
//
//   const int result = system("diff -q ../../test-data/lake-large-100.ppm lake-large-output-100.ppm"); // NOLINT(*-env33-c)
//   EXPECT_EQ(result, 0);
// }

//Small 100 to 1000
TEST(ImageAOSTests, Resize8_100to1000_Test) {
  setInFile("../../test-data/lake-small-100.ppm");
  setOutFile("lake-small-output-1000.ppm");
  Image_Attributes newImageData = {.magic_word = "", .width=1000, .height=1000, .intensity = 0};
  aos_resize(newImageData);

  const int result = system("diff -q ../../test-data/lake-small-1000.ppm lake-small-output-1000.ppm"); // NOLINT(*-env33-c)
  EXPECT_EQ(result, 0);
}

//Small 100 to 1000
TEST(ImageAOSTests, Resize8_1000to100_Test) {
  setInFile("../../test-data/lake-small-1000.ppm");
  setOutFile("lake-small-output-100.ppm");
  Image_Attributes newImageData = {.magic_word = "", .width=100, .height=100, .intensity = 0};
  aos_resize(newImageData);

  const int result = system("diff -q ../../test-data/lake-small-100.ppm lake-small-output-100.ppm"); // NOLINT(*-env33-c)
  EXPECT_EQ(result, 0);
}

TEST(ImageAOSTests, CutFreqTest) {

}

TEST(ImageAOSTests, CompressTest) {

}