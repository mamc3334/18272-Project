#include <cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h>
#include "../imgaos/aoscompress.hpp"  // Include your common header file
#include "../utest-common/utest-helpers.hpp"
#include "common/binaryio.hpp"

TEST(AOSCompressTests, containsSmallColorTest) {
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
    const vector<uint8_t> values = {
        100, 150, 200,
        255, 255, 255,
        255, 255, 255,
        100, 100, 100,
        255, 0, 0,
        255, 0, 255,
        255, 255, 255,
        100, 150, 200,
        0, 0, 0,
        200, 200, 200
    };

    ofstream writeMockFile("smallColors_input.bin", std::ios::binary);

    ASSERT_TRUE(writeMockFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        write_binary8(writeMockFile, value);
    }

    writeMockFile.close();

    ifstream mockFile("smallColors_input.bin");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    unsigned int numPixels = 10;
    vector<smallColor> colors;
    get_small_colors(mockFile, colors, numPixels);
    vector<smallColor> expectedColors = {
        smallColor(100, 150, 200),
        smallColor(255, 255, 255),
        smallColor(100, 100, 100),
        smallColor(255, 0, 0),
        smallColor(255, 0, 255),
        smallColor(0, 0, 0),
        smallColor(200, 200, 200)
    };
    EXPECT_EQ(colors, expectedColors);
}


TEST (AOSCompressTests, get_big_colorsTest) {
    const vector<uint16_t> values = {
        1000, 1500, 2000,
        400, 400, 400,
        400, 400, 400,
        100, 100, 100,
        255, 0, 0,
        255, 0, 255,
        400, 400, 400             ,
        1000, 1500, 2000,
        0, 0, 0,
        200, 200, 200
    };

    ofstream writeMockFile("bigColors_input.bin", std::ios::binary);

    ASSERT_TRUE(writeMockFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        write_binary16(writeMockFile, value);
    }

    writeMockFile.close();

    ifstream mockFile("bigColors_input.bin");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    unsigned int numPixels = 10;
    vector<bigColor> colors;
    get_big_colors(mockFile, colors, numPixels);
    vector<bigColor> expectedColors = {
        bigColor(1000, 1500, 2000),
        bigColor(400, 400, 400),
        bigColor(100, 100, 100),
        bigColor(255, 0, 0),
        bigColor(255, 0, 255),
        bigColor(0, 0, 0),
        bigColor(200, 200, 200)
    };
    EXPECT_EQ(colors, expectedColors);
}


TEST (AOSCompressTests, getIndexByteLengthTest) {
    size_t colorSize = 5;
    uint8_t indexByteLength = getIndexByteLength(colorSize);
    EXPECT_EQ(indexByteLength, 1);
    colorSize = 257;
    indexByteLength = getIndexByteLength(colorSize);
    EXPECT_EQ(indexByteLength, 2);
    colorSize = 65537;
    indexByteLength = getIndexByteLength(colorSize);
    EXPECT_EQ(indexByteLength, 4);
}

TEST (AOSCompressTests, write_metadataTest) {
    Image_Attributes oldMetadata = {"P6", 100, 300, 400};
    ofstream writeMockFile("write_metadataTestOutput.ppm");
    ASSERT_TRUE(writeMockFile.is_open()) << "Failed to open test data\n";
    write_metadata(writeMockFile, oldMetadata);
    writeMockFile.close();
    ifstream mockFile("write_metadataTestOutput.ppm");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    std::string magic_word;
    int width, height;
    int intensity;
    std::string expected_magic_word = "C6";
    int expectedWidth = 100, expectedHeight = 300;
    int expectedIntensity = 400;
    mockFile >> magic_word >> width >> height >> intensity;
    EXPECT_EQ(magic_word, expected_magic_word);
    EXPECT_EQ(width, expectedWidth);
    EXPECT_EQ(height, expectedHeight);
    EXPECT_EQ(intensity, expectedIntensity);
}

TEST (AOSCompressTests, write_small_colorsTest) {
    ofstream writeMockFile("write_small_colorsTestOutput.ppm");
    ASSERT_TRUE(writeMockFile.is_open()) << "Failed to open test data\n";
    vector<smallColor> expectedColors = {
        smallColor(100, 150, 200),
        smallColor(255, 255, 255),
        smallColor(100, 100, 100),
        smallColor(255, 0, 0),
        smallColor(255, 0, 255),
        smallColor(0, 0, 0),
        smallColor(200, 200, 200)
    };

    write_small_colors(writeMockFile, expectedColors);
    writeMockFile.close();

    ifstream mockFile("write_small_colorsTestOutput.ppm");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    int numIndices;
    mockFile >> numIndices;
    uint8_t r, g, b;
    vector<smallColor> colors;
    for (int i = 0; i < numIndices; i++) {
        mockFile >> r >> g >> b;
        colors.push_back(smallColor(r, g, b));
    }
    EXPECT_EQ(numIndices, 7);
    EXPECT_EQ(colors, expectedColors);
}

TEST (AOSCompressTests, write_big_colorsTest) {
    ofstream writeMockFile("write_big_colorsTestOutput.ppm");
    ASSERT_TRUE(writeMockFile.is_open()) << "Failed to open test data\n";
    vector<bigColor> expectedColors = {
        bigColor(1000, 1500, 2000),
        bigColor(400, 400, 400),
        bigColor(100, 100, 100),
        bigColor(255, 0, 0),
        bigColor(255, 0, 255),
        bigColor(0, 0, 0),
        bigColor(200, 200, 200)
    };


    write_big_colors(writeMockFile, expectedColors);
    writeMockFile.close();

    ifstream mockFile("write_big_colorsTestOutput.ppm");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    int numIndices;
    mockFile >> numIndices;
    uint16_t r, g, b;
    vector<bigColor> colors;
    for (int i = 0; i < numIndices; i++) {
        mockFile >> r >> g >> b;
        colors.push_back(bigColor(r, g, b));
    }
    EXPECT_EQ(numIndices, 7);
    EXPECT_EQ(colors, expectedColors);
}

TEST (AOSCompressTests, write_small_pixels_1bTest) {
    const vector<uint8_t> values = {
        100, 150, 200,
        255, 255, 255,
        255, 255, 255,
        100, 100, 100,
        255, 0, 0,
        255, 0, 255,
        255, 255, 255,
        100, 150, 200,
        0, 0, 0,
        200, 200, 200
    };

    vector<smallColor> colors = {
        smallColor(100, 150, 200),
        smallColor(255, 255, 255),
        smallColor(100, 100, 100),
        smallColor(255, 0, 0),
        smallColor(255, 0, 255),
        smallColor(0, 0, 0),
        smallColor(200, 200, 200)
    };

    const unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_small_pixels_1bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        write_binary8(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_small_pixels_1bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_small_pixels_1bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_small_pixels_1b(mockInputFile, writeMockOutputFile, colors, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_small_pixels_1bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    uint8_t index;
    vector<uint8_t> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = read_binary8(mockOutputFile);
        indices.push_back(index);
    }

    vector<uint8_t> expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}

TEST (AOSCompressTests, write_small_pixels_2bTest) {
    const vector<uint8_t> values = {
        100, 150, 200,
        255, 255, 255,
        255, 255, 255,
        100, 100, 100,
        255, 0, 0,
        255, 0, 255,
        255, 255, 255,
        100, 150, 200,
        0, 0, 0,
        200, 200, 200
    };

    vector<smallColor> colors = {
        smallColor(100, 150, 200),
        smallColor(255, 255, 255),
        smallColor(100, 100, 100),
        smallColor(255, 0, 0),
        smallColor(255, 0, 255),
        smallColor(0, 0, 0),
        smallColor(200, 200, 200)
    };

    const unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_small_pixels_2bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        write_binary8(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_small_pixels_2bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_small_pixels_2bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_small_pixels_2b(mockInputFile, writeMockOutputFile, colors, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_small_pixels_2bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    uint16_t index;
    vector<uint16_t> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = read_binary16(mockOutputFile);
        indices.push_back(index);
    }

    vector<uint16_t> expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}

TEST (AOSCompressTests, write_small_pixels_4bTest) {
    const vector<uint8_t> values = {
        100, 150, 200,
        255, 255, 255,
        255, 255, 255,
        100, 100, 100,
        255, 0, 0,
        255, 0, 255,
        255, 255, 255,
        100, 150, 200,
        0, 0, 0,
        200, 200, 200
    };

    vector<smallColor> colors = {
        smallColor(100, 150, 200),
        smallColor(255, 255, 255),
        smallColor(100, 100, 100),
        smallColor(255, 0, 0),
        smallColor(255, 0, 255),
        smallColor(0, 0, 0),
        smallColor(200, 200, 200)
    };

    const unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_small_pixels_4bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        write_binary8(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_small_pixels_4bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_small_pixels_4bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_small_pixels_4b(mockInputFile, writeMockOutputFile, colors, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_small_pixels_4bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    int index;
    vector<int> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = read_binary32(mockOutputFile);
        indices.push_back(index);
    }

    vector<int> expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}


TEST (AOSCompressTests, write_big_pixels_1bTest) {
    const vector<uint16_t> values = {
        1000, 1500, 2000,
        400, 400, 400,
        400, 400, 400,
        100, 100, 100,
        255, 0, 0,
        255, 0, 255,
        400, 400, 400             ,
        1000, 1500, 2000,
        0, 0, 0,
        200, 200, 200
    };

    vector<bigColor> colors = {
        bigColor(1000, 1500, 2000),
        bigColor(400, 400, 400),
        bigColor(100, 100, 100),
        bigColor(255, 0, 0),
        bigColor(255, 0, 255),
        bigColor(0, 0, 0),
        bigColor(200, 200, 200)
    };


    const unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_big_pixels_1bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        write_binary16(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_big_pixels_1bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_big_pixels_1bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_big_pixels_1b(mockInputFile, writeMockOutputFile, colors, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_big_pixels_1bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    uint8_t index;
    vector<uint8_t> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = read_binary8(mockOutputFile);
        indices.push_back(index);
    }

    vector<uint8_t> expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}

TEST (AOSCompressTests, write_big_pixels_2bTest) {
    const vector<uint16_t> values = {
        1000, 1500, 2000,
        400, 400, 400,
        400, 400, 400,
        100, 100, 100,
        255, 0, 0,
        255, 0, 255,
        400, 400, 400             ,
        1000, 1500, 2000,
        0, 0, 0,
        200, 200, 200
    };

    vector<bigColor> colors = {
        bigColor(1000, 1500, 2000),
        bigColor(400, 400, 400),
        bigColor(100, 100, 100),
        bigColor(255, 0, 0),
        bigColor(255, 0, 255),
        bigColor(0, 0, 0),
        bigColor(200, 200, 200)
    };

    const unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_big_pixels_2bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        write_binary16(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_big_pixels_2bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_big_pixels_2bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_big_pixels_2b(mockInputFile, writeMockOutputFile, colors, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_big_pixels_2bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    uint16_t index;
    vector<uint16_t> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = read_binary16(mockOutputFile);
        indices.push_back(index);
    }

    vector<uint16_t> expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}

TEST (AOSCompressTests, write_big_pixels_4bTest) {
    const vector<uint16_t> values = {
        1000, 1500, 2000,
        400, 400, 400,
        400, 400, 400,
        100, 100, 100,
        255, 0, 0,
        255, 0, 255,
        400, 400, 400             ,
        1000, 1500, 2000,
        0, 0, 0,
        200, 200, 200
    };

    vector<bigColor> colors = {
        bigColor(1000, 1500, 2000),
        bigColor(400, 400, 400),
        bigColor(100, 100, 100),
        bigColor(255, 0, 0),
        bigColor(255, 0, 255),
        bigColor(0, 0, 0),
        bigColor(200, 200, 200)
    };

    const unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_big_pixels_4bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        write_binary16(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_big_pixels_4bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_big_pixels_4bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_big_pixels_4b(mockInputFile, writeMockOutputFile, colors, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_big_pixels_4bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    int index;
    vector<int> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = read_binary32(mockOutputFile);
        indices.push_back(index);
    }

    vector<int> expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}