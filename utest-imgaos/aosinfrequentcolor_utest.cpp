/*
#include "../imgaos/aosinfrequentcolor.hpp"
#include "../imgaos/KDTree.hpp"
#include "common/binaryio.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <random>
#include <gtest/gtest.h>

TEST(AosInfrequentColorTest, ChangeInfrequentColors16) {
    std::vector<bigColor> pixels = {{1000, 2000, 3000}, {1000, 2000, 3000}, {4000, 5000, 6000}};
    changeInfrequentColors_16(pixels, 1);

    bigColor expected = {1000, 2000, 3000};//the only color

    for (const auto& pixel : pixels) {
        ASSERT_TRUE(pixel == expected);
    }
}

TEST(AosInfrequentColorTest, ChangeInfrequentColors8) {
    std::vector<smallColor> pixels = {{100, 200, 100}, {100, 200, 100}, {200, 200, 200}};
    changeInfrequentColors_8(pixels, 1);

    smallColor expected = {100, 200, 100};//the only color

    for (const auto& pixel : pixels) {
        ASSERT_TRUE(pixel == expected);
    }
}



TEST(AosInfrequentColorTest, CountColors16) {
    std::vector<bigColor> pixels = {{100, 200, 300}, {100, 200, 300}, {400, 500, 600}};
    auto colorMap = countColors_16(pixels);

    bigColor firstColor =  {100, 200, 300};
    bigColor secondColor = {400, 500, 600};

    ASSERT_EQ(colorMap.size(), 2);
    EXPECT_EQ(colorMap[firstColor], 2);
    EXPECT_EQ(colorMap[secondColor], 1);
}

TEST(AosInfrequentColorTest, CountColors8) {
    std::vector<smallColor> pixels = {{10, 20, 30}, {10, 20, 30}, {40, 50, 60}};
    auto colorMap = countColors_8(pixels);

    smallColor firstColor =  {10, 20, 30};
    smallColor secondColor = {40, 50, 60};

    ASSERT_EQ(colorMap.size(), 2);
    EXPECT_EQ(colorMap[firstColor], 2);
    EXPECT_EQ(colorMap[secondColor], 1);
}



TEST(AosInfrequentColorTest, ColorDistance8) {
    smallColor c1 = {10, 20, 30};
    smallColor c2 = {40, 50, 60};
    double distance = colorDistance_8(c1, c2);

    EXPECT_EQ(distance, 2700);  // (40-10)^2 + (50-20)^2 + (60-30)^2
}

TEST(AosInfrequentColorTest, ColorDistance16) {
    bigColor c1 = {100, 200, 300};
    bigColor c2 = {400, 500, 600};
    double distance = colorDistance_16(c1, c2);

    EXPECT_EQ(distance, 270000);  // (40-10)^2 + (50-20)^2 + (60-30)^2
}
*/
