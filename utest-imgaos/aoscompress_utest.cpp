#include <cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h>
#include "../imgaos/aoscompress.hpp"  // Include your common header file
#include "../utest-common/utest-helpers.hpp"

TEST(AOSCompressTests, containsSmallColorTest){
    vector<smallColor> colors = {
                                    smallColor(255, 0, 0),
                                    smallColor(0, 255, 0),
                                    smallColor(0, 0, 255),
                                    smallColor(255, 0, 255),
                                    smallColor(0, 255, 255),
                                    smallColor(255, 0, 255)
                                };

    smallColor targetColor = smallColor(0, 255, 0);
    bool found = contains_smallColor(colors, targetColor);
    bool expectedFound = true;

    EXPECT_EQ(found, expectedFound);
}