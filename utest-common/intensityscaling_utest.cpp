//
// Created by eloim on 10/11/2024.
//
#include <gtest/gtest.h>
#include "../common/intensityscaling.hpp"
#include "../common/binaryio.hpp"
#include "../common/utility.hpp"
#include "../common/utility.cpp"
#include <vector>
#include <fstream>


//Tests for both cases of the "intensity_smaller_255" function

TEST(IntensityScalingTests, IntensitySmaller255_to_IntensitySmaller255) {
    vector<int> const data = {255,100,6};

    ofstream inputFile("input_test.ppm", ios::binary);
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
    vector<int> const data = {128,350,6};

    ofstream inputFile("input_test.ppm", ios::binary);
    //This function is the one in charge of reading and writing so we omit the info of the file "P6 2 1 ..."
    inputFile << "P6\n1 2\n128\n";
    write_binary8(inputFile, 100);
    write_binary8(inputFile, 74);
    write_binary8(inputFile, 18);
    write_binary8(inputFile, 123);
    write_binary8(inputFile, 88);
    write_binary8(inputFile, 32);
    inputFile.close();

    ifstream input("input_test.ppm", ios::binary);
    ofstream output("output_test.ppm", ios::binary);

    output << "P6\n1 2\n350\n";

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

    uint16_t r1 = read_binary16(outputCheck);
    uint16_t g1 = read_binary16(outputCheck);
    uint16_t b1 = read_binary16(outputCheck);
    uint16_t r2 = read_binary16(outputCheck);
    uint16_t g2 = read_binary16(outputCheck);
    uint16_t b2 = read_binary16(outputCheck);

    EXPECT_EQ(r1, 273);
    EXPECT_EQ(g1, 202);
    EXPECT_EQ(b1, 49);
    EXPECT_EQ(r2, 336);
    EXPECT_EQ(g2, 240);
    EXPECT_EQ(b2, 87);

    outputCheck.close();
}

//Tests for both cases of the "intensity_greater_255" function

TEST(IntensityScalingTests, IntensityGreater255_to_IntensityGreater255) {
    vector<int> const data = {432,1634,6};

    ofstream inputFile("input_test.ppm", ios::binary);
    //This function is the one in charge of reading and writing so we omit the info of the file "P6 2 1 ..."
    inputFile << "P6\n1 2\n432\n";
    write_binary16(inputFile, 407);
    write_binary16(inputFile, 38);
    write_binary16(inputFile, 384);
    write_binary16(inputFile, 314);
    write_binary16(inputFile, 265);
    write_binary16(inputFile, 106);
    inputFile.close();

    ifstream input("input_test.ppm", ios::binary);
    ofstream output("output_test.ppm", ios::binary);

    output << "P6\n1 2\n1634\n";

    string line;
    for(int i = 0; i < 3; i++) {
        getline(input, line);
    }

    intensity_greater_255(data, input, output);
    input.close();
    output.close();

    ifstream outputCheck("output_test.ppm", ios::binary);
    for(int i = 0; i < 3; i++) {
        getline(outputCheck, line);
    }

    uint16_t r1 = read_binary16(outputCheck);
    uint16_t g1 = read_binary16(outputCheck);
    uint16_t b1 = read_binary16(outputCheck);
    uint16_t r2 = read_binary16(outputCheck);
    uint16_t g2 = read_binary16(outputCheck);
    uint16_t b2 = read_binary16(outputCheck);

    EXPECT_EQ(r1, 1539);
    EXPECT_EQ(g1, 143);
    EXPECT_EQ(b1, 1452);
    EXPECT_EQ(r2, 1187);
    EXPECT_EQ(g2, 1002);
    EXPECT_EQ(b2, 400);

    outputCheck.close();
}

TEST(IntensityScalingTests, IntensityGreater255_to_IntensitySmaller255) {
    vector<int> const data = {12543,98,6};

    ofstream inputFile("input_test.ppm", ios::binary);
    //This function is the one in charge of reading and writing so we omit the info of the file "P6 2 1 ..."
    inputFile << "P6\n1 2\n12543\n";
    write_binary16(inputFile, 10131);
    write_binary16(inputFile, 5089);
    write_binary16(inputFile, 3997);
    write_binary16(inputFile, 49);
    write_binary16(inputFile, 5390);
    write_binary16(inputFile, 4728);
    inputFile.close();

    ifstream input("input_test.ppm", ios::binary);
    ofstream output("output_test.ppm", ios::binary);

    output << "P6\n1 2\n98\n";

    string line;
    for(int i = 0; i < 3; i++) {
        getline(input, line);
    }

    intensity_greater_255(data, input, output);
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

    EXPECT_EQ(r1, 79);
    EXPECT_EQ(g1, 39);
    EXPECT_EQ(b1, 31);
    EXPECT_EQ(r2, 0);
    EXPECT_EQ(g2, 42);
    EXPECT_EQ(b2, 36);

    outputCheck.close();
}

//Tests for the function "read_image_intensity_scaling", which reads from the original file and writes in the output file

TEST(IntensityScalingTests, ReadImage) {
    ofstream inputFile("input_test.ppm", ios::binary);
    inputFile << "P6\n1 2\n255\n";
    write_binary8(inputFile, 100);
    write_binary8(inputFile, 150);
    write_binary8(inputFile, 200);
    write_binary8(inputFile, 50);
    write_binary8(inputFile, 75);
    write_binary8(inputFile, 100);
    inputFile.close();

    setInFile("input_test.ppm");
    setOutFile("output_test.ppm");

    read_image_intensity_scaling(100);

    ifstream outputFile(getOutFile());
    string line;
    getline(outputFile, line);
    EXPECT_EQ(line, "P6");
    getline(outputFile, line);
    EXPECT_EQ(line, "1 2");
    getline(outputFile, line);
    EXPECT_EQ(line, "100");
    outputFile.close();

    ifstream outputFile2(getOutFile(), ios::binary);
    for(int i = 0; i < 3; i++) {
        getline(outputFile2, line);
    }

    uint8_t r1 = read_binary8(outputFile2);
    uint8_t g1 = read_binary8(outputFile2);
    uint8_t b1 = read_binary8(outputFile2);
    uint8_t r2 = read_binary8(outputFile2);
    uint8_t g2 = read_binary8(outputFile2);
    uint8_t b2 = read_binary8(outputFile2);

    EXPECT_EQ(r1, 39);
    EXPECT_EQ(g1, 58);
    EXPECT_EQ(b1, 78);
    EXPECT_EQ(r2, 19);
    EXPECT_EQ(g2, 29);
    EXPECT_EQ(b2, 39);

    outputFile2.close();
}