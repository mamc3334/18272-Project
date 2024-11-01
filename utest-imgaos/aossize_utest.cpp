#include <cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h>
#include "../imgaos/aossize.hpp"  // Include your common header file

TEST(AOSSizeTests, Old16Test){
    const unsigned int rows = 5;
    const unsigned int cols = 7;
    vector<vector<bigColor>> pixelArray(rows, vector<bigColor>(cols));



    aossize_old_photo_16(pixelArray, rows, cols, mockDataFile);

    EXPECT_EQ(pixelArray[0][0], bigColor{10, 20, 30});
    EXPECT_EQ(pixelArray[0][1], bigColor{40, 50, 60});
    EXPECT_EQ(pixelArray[1][0], bigColor{70, 80, 90});
    EXPECT_EQ(pixelArray[1][1], bigColor{100, 110, 120});
}

TEST(AOSSizeTests, Old8Test){

}

TEST(AOSSizeTests, Resize16Test) {

}

TEST(AOSSizeTests, Resize8Test) {

}

TEST(AOSSizeTests, Interpolate16Test) {

}

TEST(AOSSizeTests, Interpolate8Test) {

}