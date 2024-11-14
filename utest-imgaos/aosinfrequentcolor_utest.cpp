#include <gtest/gtest.h>
#include "../imgaos/aosinfrequentcolor.hpp"
#include "common/binaryio.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <random>


//generate a random color
color generateRandomColor() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<uint8_t> dis(0, 255);

    return {dis(gen), dis(gen), dis(gen)};
}

//generate random pixels for the image
vector<color> generateRandomPixels(int width, int height) {
    vector<color> pixels(width * height);
    for (auto &pixel : pixels) {
        pixel = generateRandomColor();
    }
    return pixels;
}

TEST(AOSInfrequentColorTest, PopulatePix8) {
    Image_Attributes photoData = {.magic_word = "", .width=2, .height=2, .intensity = 0};
    vector<color> pixels = generateRandomPixels(photoData.width, photoData.height);

    ofstream createMockFile("8_input.bin", ios::binary);
    // Write each value to the file
    for (const auto& pixel : pixels) {
        write_binary8(createMockFile, pixel);
    }
    createMockFile.close();

/*
    ifstream mockFile("Old8_input.bin");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data";
*/
    vector<color> loadedPixels;
    populatePixels_8(loadedPixels, photoData, createMockFile);

    EXPECT_EQ(loadedPixels.size(), pixels.size());

    for (size_t i = 0; i < pixels.size(); ++i) {
        EXPECT_EQ(loadedPixels[i].r, pixels[i].r);
        EXPECT_EQ(loadedPixels[i].g, pixels[i].g);
        EXPECT_EQ(loadedPixels[i].b, pixels[i].b);
    }
}

TEST(AOSInfrequentColorTest, PopulatePix16) {
    Image_Attributes photoData = {.magic_word = "", .width=2, .height=2, .intensity = 1000};
    vector<color> pixels = generateRandomPixels(photoData.width, photoData.height);

    ofstream createMockFile("16_input.bin", ios::binary);
    // Write each value to the file
    for (const auto& pixel : pixels) {
        write_binary8(createMockFile, pixel);
    }
    createMockFile.close();

    /*
        ifstream mockFile("Old8_input.bin");
        ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data";
    */
    vector<color> loadedPixels;
    populatePixels_8(loadedPixels, photoData, createMockFile);

    EXPECT_EQ(loadedPixels.size(), pixels.size());

    for (size_t i = 0; i < pixels.size(); ++i) {
        EXPECT_EQ(loadedPixels[i].r, pixels[i].r);
        EXPECT_EQ(loadedPixels[i].g, pixels[i].g);
        EXPECT_EQ(loadedPixels[i].b, pixels[i].b);
    }
}

TEST(AOSInfrequentColorTest, Counter) {
    vector<color> pixels = {{255, 0, 0}, {0, 255, 0}, {255, 0, 0}, {0, 0, 255}};
    auto result = countColors(pixels);

    // Expect unique colors in result vector
    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[0].count, 2); // Red appears twice
    EXPECT_EQ(result[1].count, 1); // Green appears once
    EXPECT_EQ(result[2].count, 1); // Blue appears once
}

TEST(AOSInfrequentColorTest, SortColors) {
    vector<color> pixels = {
        {255, 0, 0, 3}, {0, 255, 0, 1}, {0, 0, 255, 2}, {128, 128, 128, 2}
    };
    sortColors(pixels);

    EXPECT_EQ(pixels[0].count, 1); // Green should be first
    EXPECT_EQ(pixels[1].count, 2); // Blue should come next
    EXPECT_EQ(pixels[2].count, 2); // Gray should come after Blue
    EXPECT_EQ(pixels[3].count, 3); // Red should be last
}

TEST(AOSInfrequentColorTest, ColorDistance) {
    color c1 = {255, 0, 0};
    color c2 = {0, 255, 0};
    double distance = colorDistance(c1, c2);

    EXPECT_NEAR(distance, sqrt(255*255 + 255*255), 1e-5);
}

TEST(AOSInfrequentColorTest, ChangeInfrequentColors) {
    vector<color> pixels = {{255, 0, 0}, {0, 255, 0}, {255, 0, 0}, {0, 0, 255}};
    int n = 1;
    changeInfrequentColors(pixels, n);

    // Ensure that the least frequent color (blue) is replaced with a close match
    EXPECT_EQ(pixels[3], pixels[0]); // Assuming red is the closest
}

TEST(AOSInfrequentColorTest, WriteBinary8) {
    vector<color> pixels = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}};
    Image_Attributes photoData = {2, 2, 255};
    string outputPath = "test_output_8bit.ppm";

    writeBinary_8(pixels, photoData, outputPath);

    ifstream inFile(outputPath, ios::binary);
    ASSERT_TRUE(inFile.is_open());

    // Verify the header and content
    string header;
    getline(inFile, header);
    EXPECT_EQ(header, "P6");
}

TEST(AOSInfrequentColorTest, WriteBinary16) {
    vector<color> pixels = {{50000, 40000, 30000}, {30000, 20000, 10000}};
    Image_Attributes photoData = {2, 1, 65535};
    string outputPath = "test_output_16bit.ppm";

    writeBinary_16(pixels, photoData, outputPath);

    ifstream inFile(outputPath, ios::binary);
    ASSERT_TRUE(inFile.is_open());

    string header;
    getline(inFile, header);
    EXPECT_EQ(header, "P6");
}

