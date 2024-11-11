//
// Created by eloim on 10/11/2024.
//
#include <gtest/gtest.h>
#include "../common/intensityscaling.hpp"
#include "../common/binaryio.hpp"
#include <vector>
#include <fstream>


//Tests for both cases of the "intensity_smaller_255" function

TEST(IntensityScalingTests, IntensitySmaller255_to_IntensitySmaller255) {
    vector<int> const data = {255,100,6};

    ofstream inputFile("input_test.ppm", ios::binary);
    //This function is the one in charge of reading and writing so we omit the info of the file "P6 2 1 ..."
    inputFile << "P6\n1 2\n255\n";
    write_binary8(inputFile, 100);
    write_binary8(inputFile, 150);
    write_binary8(inputFile, 200);
    write_binary8(inputFile, 50);
    write_binary8(inputFile, 75);
    write_binary8(inputFile, 100);
    inputFile.close();

    ifstream input("input_test.ppm", ios::binary);
    ofstream output("output_test.ppm", ios::binary);

    output << "P6\n1 2\n100\n";

    string line;
    for(int i = 0; i < 3; i++) {
        getline(input, line);
    }

    intensity_smaller_255(data, input, output);
    input.close();
    output.close();

    ifstream outputCheck("output_test.ppm", ios::binary);
    for(int i = 0; i < 3; i++) {
        getline(outputCheck, line);
    }

    uint8_t r1 = read_binary8(outputCheck);
    uint8_t g1 = read_binary8(outputCheck);
    uint8_t b1 = read_binary8(outputCheck);
    uint8_t r2 = read_binary8(outputCheck);
    uint8_t g2 = read_binary8(outputCheck);
    uint8_t b2 = read_binary8(outputCheck);

    EXPECT_EQ(r1, 39);  // 100 * 100/255 ≈ 39
    EXPECT_EQ(g1, 58);  // 150 * 100/255 ≈ 59
    EXPECT_EQ(b1, 78);  // 200 * 100/255 ≈ 78
    EXPECT_EQ(r2, 19);  // 50 * 100/255 ≈ 20
    EXPECT_EQ(g2, 29);  // 75 * 100/255 ≈ 29
    EXPECT_EQ(b2, 39);  // 100 * 100/255 ≈ 39

    outputCheck.close();
}

TEST(IntensityScalingTests, IntensitySmaller255_to_IntensityGreater255) {

}

//Tests for both cases of the "intensity_greater_255" function

TEST(IntensityScalingTests, IntensityGreater255_to_IntensitySmaller255) {

}

TEST(IntensityScalingTests, IntensityGreater255_to_IntensityGreater255) {

}

//Tests for the function "read_image_intensity_scaling", which reads from the original file and writes in the output file

