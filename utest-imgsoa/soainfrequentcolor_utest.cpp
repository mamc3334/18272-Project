#include "../imgsoa/soainfrequentcolor.hpp"
#include "common/binaryio.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <random>
#include <gtest/gtest.h>


// NOLINTBEGIN(*-magic-numbers)
TEST(SoAInfrequentColorTest, ChangeInfrequentColors8) {
    SoA_8 pixels = {.r={10, 10, 20}, .g={20, 20, 30}, .b={30, 30, 40}};

    // Mark 1 color as infrequent (replace with black)
    changeInfrequentColors_8(pixels, 1);

    // Verify that 1 color was replaced with black
    EXPECT_EQ(pixels.r[2], 0);
    EXPECT_EQ(pixels.g[2], 0);
    EXPECT_EQ(pixels.b[2], 0);
}

TEST(SoAInfrequentColorTest, ChangeInfrequentColors16) {
    SoA_16 pixels = {.r={10, 10, 20}, .g={20, 20, 30}, .b={30, 30, 40}};

    changeInfrequentColors_16(pixels, 1);

    EXPECT_EQ(pixels.r[2], 0);
    EXPECT_EQ(pixels.g[2], 0);
    EXPECT_EQ(pixels.b[2], 0);
}

// NOLINTEND(*-magic-numbers)