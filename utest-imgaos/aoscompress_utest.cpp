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

    targetColor = smallColor(7, 7, 7);
    found = contains_smallColor(colors, targetColor);
    expectedFound = false;

    EXPECT_EQ(found, expectedFound);
}

TEST(AOSCompressTests, containsBigColorTest){
    vector<bigColor> colors = {
        bigColor(255, 0, 0),
        bigColor(0, 255, 0),
        bigColor(0, 0, 255),
        bigColor(255, 0, 255),
        bigColor(0, 255, 255),
        bigColor(255, 0, 255)
    };

    bigColor targetColor = bigColor(0, 255, 0);
    bool found = contains_bigColor(colors, targetColor);
    bool expectedFound = true;

    EXPECT_EQ(found, expectedFound);

    targetColor = bigColor(7, 7, 7);
    found = contains_bigColor(colors, targetColor);
    expectedFound = false;

    EXPECT_EQ(found, expectedFound);
}

TEST(AOSCompressTests, index_of_1bTest){
    vector<smallColor> colors = {
        smallColor(255, 0, 0),
        smallColor(0, 255, 0),
        smallColor(0, 0, 255),
        smallColor(255, 0, 255),
        smallColor(0, 255, 255),
        smallColor(255, 0, 255)
    };

    smallColor targetColor = smallColor(0, 255, 0);
    uint8_t index;
    bool found = index_of_1b<smallColor>(colors, targetColor, index);
    bool expectedFound = true;
    uint8_t expectedIndex = 1;

    EXPECT_EQ(found, expectedFound);
    EXPECT_EQ(index, expectedIndex);

    targetColor = smallColor(7, 7, 7);
    found = index_of_1b<smallColor>(colors, targetColor, index);
    expectedFound = false;
    expectedIndex = 1;

    EXPECT_EQ(found, expectedFound);
    EXPECT_EQ(index, expectedIndex);
}


TEST(AOSCompressTests, index_of_2bTest){
    vector<smallColor> colors = {
        smallColor(255, 0, 0),
        smallColor(0, 255, 0),
        smallColor(0, 0, 255),
        smallColor(255, 0, 255),
        smallColor(0, 255, 255),
        smallColor(255, 0, 255)
    };

    smallColor targetColor = smallColor(0, 255, 0);
    uint16_t index;
    bool found = index_of_2b<smallColor>(colors, targetColor, index);
    bool expectedFound = true;
    uint16_t expectedIndex = 1;

    EXPECT_EQ(found, expectedFound);
    EXPECT_EQ(index, expectedIndex);

    targetColor = smallColor(7, 7, 7);
    found = index_of_2b<smallColor>(colors, targetColor, index);
    expectedFound = false;
    expectedIndex = 1;

    EXPECT_EQ(found, expectedFound);
    EXPECT_EQ(index, expectedIndex);
}


TEST(AOSCompressTests, index_of_4bTest){
    vector<smallColor> colors = {
        smallColor(255, 0, 0),
        smallColor(0, 255, 0),
        smallColor(0, 0, 255),
        smallColor(255, 0, 255),
        smallColor(0, 255, 255),
        smallColor(255, 0, 255)
    };

    smallColor targetColor = smallColor(0, 255, 0);
    int index;
    bool found = index_of_4b<smallColor>(colors, targetColor, index);
    bool expectedFound = true;
    int expectedIndex = 1;

    EXPECT_EQ(found, expectedFound);
    EXPECT_EQ(index, expectedIndex);

    targetColor = smallColor(7, 7, 7);
    found = index_of_4b<smallColor>(colors, targetColor, index);
    expectedFound = false;
    expectedIndex = 1;

    EXPECT_EQ(found, expectedFound);
    EXPECT_EQ(index, expectedIndex);
}


TEST (AOSCompressTests, get_small_colorsTest) {

}