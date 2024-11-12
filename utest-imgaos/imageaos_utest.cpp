#include <gtest/gtest.h>
#include "../imgaos/imageaos.hpp"  // Include your common header file
#include "../common/binaryio.hpp"

//Large 2 to 4
TEST(ImageAOSTests, Resize16_2to4_Test) {
  setInFile("../../test-data/big16-2.ppm");
  setOutFile("big16-4-output.ppm");
  Image_Attributes newImageData = {.magic_word = "", .width=4, .height=4, .intensity = 1000};
  aos_resize(newImageData);

  const int result = system("diff -q ../../test-data/big16-4.ppm big16-4-output.ppm"); // NOLINT(*-env33-c)
  EXPECT_EQ(result, 0);
}

//Large 4 to 2
TEST(ImageAOSTests, Resize16_4to2_Test) {
  setInFile("../../test-data/big16-4.ppm");
  setOutFile("big16-2-output.ppm");
  Image_Attributes newImageData = {.magic_word = "", .width=2, .height=2, .intensity = 1000};
  aos_resize(newImageData);

  const int result = system("diff -q ../../test-data/big16-2.ppm big16-2-output.ppm"); // NOLINT(*-env33-c)
  EXPECT_EQ(result, 0);
}

//Small 2 to 4
TEST(ImageAOSTests, Resize8_2to4_Test) {
  setInFile("../../test-data/small8-2.ppm");
  setOutFile("small8-4-output.ppm");
  Image_Attributes newImageData = {.magic_word = "", .width=4, .height=4, .intensity = 255};
  aos_resize(newImageData);

  const int result = system("diff -q ../../test-data/small8-4.ppm small8-4-output.ppm"); // NOLINT(*-env33-c)
  EXPECT_EQ(result, 0);
}

//Small 4 to 2
TEST(ImageAOSTests, Resize8_4to2_Test) {
  setInFile("../../test-data/small8-4.ppm");
  setOutFile("small8-2-output.ppm");
  Image_Attributes newImageData = {.magic_word = "", .width=2, .height=2, .intensity = 0};
  aos_resize(newImageData);

  const int result = system("diff -q ../../test-data/small8-2.ppm small8-2-output.ppm"); // NOLINT(*-env33-c)
  EXPECT_EQ(result, 0);
}

TEST(ImageAOSTests, CutFreqTest) {

}

TEST(ImageAOSTests, CompressTest) {

}