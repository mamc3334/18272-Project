#include <gtest/gtest.h>
#include "../imgsoa/soacompress.hpp"  // Include your common header file
#include "../utest-common/utest-helpers.hpp"
#include "common/binaryio.hpp"

// NOLINTBEGIN(*-magic-numbers)
TEST (SOACompressTests, get_small_colorsTest) {

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
        BINARY::write_binary8(writeMockFile, value);
    }

    writeMockFile.close();

    ifstream mockFile("smallColors_input.bin");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    unsigned int const numPixels = 10;
    vector<uint8_t> reds;
    vector<uint8_t> greens;
    vector<uint8_t> blues;
    unordered_map<tuple<uint8_t, uint8_t, uint8_t>, int> colorIndexMap;
    get_small_colors(mockFile, reds, greens, blues, colorIndexMap, numPixels);
    vector<uint8_t> const expectedReds = {100, 255, 100, 255, 255, 0, 200};
    vector<uint8_t> const expectedGreens = {150, 255, 100, 0, 0, 0, 200};
    vector<uint8_t> const expectedBlues = {200, 255, 100, 0, 255, 0, 200};

    unordered_map<tuple<uint8_t, uint8_t, uint8_t>, int> expectedColorIndexMap;
    expectedColorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(100, 150, 200)] = 0;
    expectedColorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 255, 255)] = 1;
    expectedColorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(100, 100, 100)] = 2;
    expectedColorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 0, 0)] = 3;
    expectedColorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 0, 255)] = 4;
    expectedColorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(0, 0, 0)] = 5;
    expectedColorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(200, 200, 200)] = 6;
    EXPECT_EQ(reds, expectedReds);
    EXPECT_EQ(greens, expectedGreens);
    EXPECT_EQ(blues, expectedBlues);
    EXPECT_EQ(colorIndexMap, expectedColorIndexMap);
}


TEST (SOACompressTests, get_big_colorsTest) {
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
        BINARY::write_binary16(writeMockFile, value);
    }

    writeMockFile.close();

    ifstream mockFile("bigColors_input.bin");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    unsigned int const numPixels = 10;
    vector<uint16_t> reds;
    vector<uint16_t> greens;
    vector<uint16_t> blues;
    unordered_map<tuple<uint16_t, uint16_t, uint16_t>, int> colorIndexMap;
    get_big_colors(mockFile, reds, greens, blues, colorIndexMap, numPixels);
    vector<uint16_t> const expectedReds = {1000, 400, 100, 255, 255, 0, 200};
    vector<uint16_t> const expectedGreens = {1500, 400, 100, 0, 0, 0, 200};
    vector<uint16_t> const expectedBlues = {2000, 400, 100, 0, 255, 0, 200};

    unordered_map<tuple<uint16_t, uint16_t, uint16_t>, int> expectedColorIndexMap;
    expectedColorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(1000, 1500, 2000)] = 0;
    expectedColorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(400, 400,  400)] = 1;
    expectedColorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(100, 100, 100)] = 2;
    expectedColorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(255, 0, 0)] = 3;
    expectedColorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(255, 0, 255)] = 4;
    expectedColorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(0, 0, 0)] = 5;
    expectedColorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(200, 200, 200)] = 6;
    EXPECT_EQ(reds, expectedReds);
    EXPECT_EQ(greens, expectedGreens);
    EXPECT_EQ(blues, expectedBlues);
    EXPECT_EQ(colorIndexMap, expectedColorIndexMap);
}


TEST (SOACompressTests, getIndexByteLengthTest) {
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

TEST (SOACompressTests, write_metadataTest) {
    Image_Attributes const oldMetadata = {.magic_word="P6", .width=100, .height=300, .intensity=400};
    ofstream writeMockFile("write_metadataTestOutput.ppm");
    ASSERT_TRUE(writeMockFile.is_open()) << "Failed to open test data\n";
    write_metadata(writeMockFile, oldMetadata);
    writeMockFile.close();
    ifstream mockFile("write_metadataTestOutput.ppm");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    std::string magic_word;
    int width = 0;
    int height = 0;
    int intensity = 0;
    std::string const expected_magic_word = "C6";
    int const expectedWidth = 100;
    int const expectedHeight = 300;
    int const expectedIntensity = 400;
    mockFile >> magic_word >> width >> height >> intensity;
    EXPECT_EQ(magic_word, expected_magic_word);
    EXPECT_EQ(width, expectedWidth);
    EXPECT_EQ(height, expectedHeight);
    EXPECT_EQ(intensity, expectedIntensity);
}

TEST (SOACompressTests, write_small_colorsTest) {
    ofstream writeMockFile("write_small_colorsTestOutput.ppm");
    ASSERT_TRUE(writeMockFile.is_open()) << "Failed to open test data\n";
    vector<uint8_t> expectedReds = {100, 255, 100, 255, 255, 0, 200};
    vector<uint8_t> expectedGreens = {150, 255, 100, 0, 0, 0, 200};
    vector<uint8_t> expectedBlues = {200, 255, 100, 0, 255, 0, 200};

    write_small_colors(writeMockFile, expectedReds, expectedGreens, expectedBlues);
    writeMockFile.close();

    ifstream mockFile("write_small_colorsTestOutput.ppm");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    int numIndices = 0;
    mockFile >> numIndices;
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    vector<uint8_t> reds;
    vector<uint8_t> greens;
    vector<uint8_t> blues;
    for (int i = 0; i < numIndices; i++) {
        mockFile >> red >> green >> blue;
        reds.push_back(red);
        greens.push_back(green);
        blues.push_back(blue);
    }
    EXPECT_EQ(numIndices, 7);
    EXPECT_EQ(reds, expectedReds);
    EXPECT_EQ(greens, expectedGreens);
    EXPECT_EQ(blues, expectedBlues);
}

TEST (SOACompressTests, write_big_colorsTest) {
    ofstream writeMockFile("write_big_colorsTestOutput.ppm");
    ASSERT_TRUE(writeMockFile.is_open()) << "Failed to open test data\n";
    vector<uint16_t> expectedReds = {1000, 400, 100, 255, 255, 0, 200};
    vector<uint16_t> expectedGreens = {1500, 400, 100, 0, 0, 0, 200};
    vector<uint16_t> expectedBlues = {2000, 400, 100, 0, 255, 0, 200};


    write_big_colors(writeMockFile, expectedReds, expectedGreens, expectedBlues);
    writeMockFile.close();

    ifstream mockFile("write_big_colorsTestOutput.ppm");
    ASSERT_TRUE(mockFile.is_open()) << "Failed to open test data\n";
    int numIndices = 0;
    mockFile >> numIndices;
    uint16_t red = 0;
    uint16_t green = 0;
    uint16_t blue = 0;
    vector<uint16_t> reds;
    vector<uint16_t> greens;
    vector<uint16_t> blues;
    for (int i = 0; i < numIndices; i++) {
        mockFile >> red >> green >> blue;
        reds.push_back(red);
        greens.push_back(green);
        blues.push_back(blue);
    }
    EXPECT_EQ(numIndices, 7);
    EXPECT_EQ(reds, expectedReds);
    EXPECT_EQ(greens, expectedGreens);
    EXPECT_EQ(blues, expectedBlues);
}


TEST (SOACompressTests, write_small_pixels_1bTest) {
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

    unordered_map<tuple<uint8_t, uint8_t, uint8_t>, int> colorIndexMap;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(100, 150, 200)] = 0;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 255, 255)] = 1;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(100, 100, 100)] = 2;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 0, 0)] = 3;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 0, 255)] = 4;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(0, 0, 0)] = 5;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(200, 200, 200)] = 6;

    constexpr unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_small_pixels_1bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        BINARY::write_binary8(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_small_pixels_1bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_small_pixels_1bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_small_pixels_1b(mockInputFile, writeMockOutputFile, colorIndexMap, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_small_pixels_1bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    uint8_t index = 0;
    vector<uint8_t> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = BINARY::read_binary8(mockOutputFile);
        indices.push_back(index);
    }

    vector<uint8_t> const expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}

TEST (SOACompressTests, write_small_pixels_2bTest) {
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

    unordered_map<tuple<uint8_t, uint8_t, uint8_t>, int> colorIndexMap;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(100, 150, 200)] = 0;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 255, 255)] = 1;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(100, 100, 100)] = 2;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 0, 0)] = 3;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 0, 255)] = 4;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(0, 0, 0)] = 5;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(200, 200, 200)] = 6;

    constexpr unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_small_pixels_2bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        BINARY::write_binary8(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_small_pixels_2bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_small_pixels_2bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_small_pixels_2b(mockInputFile, writeMockOutputFile, colorIndexMap, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_small_pixels_2bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    uint16_t index = 0;
    vector<uint16_t> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = BINARY::read_binary16(mockOutputFile);
        indices.push_back(index);
    }

    vector<uint16_t> const expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}

TEST (SOACompressTests, write_small_pixels_4bTest) {
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

    unordered_map<tuple<uint8_t, uint8_t, uint8_t>, int> colorIndexMap;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(100, 150, 200)] = 0;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 255, 255)] = 1;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(100, 100, 100)] = 2;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 0, 0)] = 3;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(255, 0, 255)] = 4;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(0, 0, 0)] = 5;
    colorIndexMap[tuple<uint8_t, uint8_t, uint8_t>(200, 200, 200)] = 6;


    const unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_small_pixels_4bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        BINARY::write_binary8(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_small_pixels_4bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_small_pixels_4bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_small_pixels_4b(mockInputFile, writeMockOutputFile, colorIndexMap, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_small_pixels_4bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    int index = 0;
    vector<int> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = BINARY::read_binary32(mockOutputFile);
        indices.push_back(index);
    }

    vector<int> const expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}


TEST (SOACompressTests, write_big_pixels_1bTest) {
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

    unordered_map<tuple<uint16_t, uint16_t, uint16_t>, int> colorIndexMap;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(1000, 1500, 2000)] = 0;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(400, 400,  400)] = 1;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(100, 100, 100)] = 2;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(255, 0, 0)] = 3;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(255, 0, 255)] = 4;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(0, 0, 0)] = 5;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(200, 200, 200)] = 6;

    const unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_big_pixels_1bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        BINARY::write_binary16(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_big_pixels_1bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_big_pixels_1bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_big_pixels_1b(mockInputFile, writeMockOutputFile, colorIndexMap, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_big_pixels_1bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    uint8_t index = 0;
    vector<uint8_t> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = BINARY::read_binary8(mockOutputFile);
        indices.push_back(index);
    }

    vector<uint8_t> const expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}

TEST (SOACompressTests, write_big_pixels_2bTest) {
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

    unordered_map<tuple<uint16_t, uint16_t, uint16_t>, int> colorIndexMap;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(1000, 1500, 2000)] = 0;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(400, 400,  400)] = 1;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(100, 100, 100)] = 2;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(255, 0, 0)] = 3;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(255, 0, 255)] = 4;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(0, 0, 0)] = 5;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(200, 200, 200)] = 6;

    const unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_big_pixels_2bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        BINARY::write_binary16(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_big_pixels_2bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_big_pixels_2bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_big_pixels_2b(mockInputFile, writeMockOutputFile, colorIndexMap, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_big_pixels_2bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    uint16_t index = 0;
    vector<uint16_t> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = BINARY::read_binary16(mockOutputFile);
        indices.push_back(index);
    }

    vector<uint16_t> const expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}

TEST (SOACompressTests, write_big_pixels_4bTest) {
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

    unordered_map<tuple<uint16_t, uint16_t, uint16_t>, int> colorIndexMap;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(1000, 1500, 2000)] = 0;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(400, 400,  400)] = 1;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(100, 100, 100)] = 2;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(255, 0, 0)] = 3;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(255, 0, 255)] = 4;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(0, 0, 0)] = 5;
    colorIndexMap[tuple<uint16_t, uint16_t, uint16_t>(200, 200, 200)]    = 6;

    constexpr unsigned int numPixels = 10;

    ofstream writeMockInputFile("write_big_pixels_4bTestInput.ppm");
    ASSERT_TRUE(writeMockInputFile.is_open()) << "Failed to open test data\n";
    for (const auto& value : values) {
        BINARY::write_binary16(writeMockInputFile, value);
    }
    writeMockInputFile.close();
    ifstream mockInputFile("write_big_pixels_4bTestInput.ppm");
    ASSERT_TRUE(mockInputFile.is_open()) << "Failed to open test data\n";

    ofstream writeMockOutputFile("write_big_pixels_4bTestOutput.ppm");
    ASSERT_TRUE(writeMockOutputFile.is_open()) << "Failed to open test data\n";
    write_big_pixels_4b(mockInputFile, writeMockOutputFile, colorIndexMap, numPixels);

    writeMockOutputFile.close();
    ifstream mockOutputFile("write_big_pixels_4bTestOutput.ppm");
    ASSERT_TRUE(mockOutputFile.is_open()) << "Failed to open test data\n";

    int index = 0;
    vector<int> indices;
    for (size_t i = 0; i < numPixels; i++) {
        index = BINARY::read_binary32(mockOutputFile);
        indices.push_back(index);
    }

    vector<int> const expectedIndices = {
        0, 1, 1, 2, 3, 4, 1, 0, 5, 6
    };

    EXPECT_EQ(indices, expectedIndices);

}

// NOLINTEND(*-magic-numbers)