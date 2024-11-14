//
// Created by eloim on 10/11/2024.
//
#include <gtest/gtest.h>
#include "../common/utility.hpp"
#include <fstream>

//Tests for "validate_metadata"

TEST(UtilityTests, ValidateMetadata_ValidInput) {
    EXPECT_NO_THROW(validate_metadata("P6", 23, 76, 138));
}

TEST(UtilityTests, ValidateMetadata_InvalidMagicWord) {
    EXPECT_EXIT(validate_metadata("P2", 34, 79, 324),
                ::testing::ExitedWithCode(1),
                "Invalid input photo file");
}

TEST(UtilityTests, ValidateMetadata_InvalidWidth) {
    EXPECT_EXIT(validate_metadata("P6", -6, 12, 123),
                ::testing::ExitedWithCode(1),
                "Invalid input photo file");
}

TEST(UtilityTests, ValidateMetadata_InvalidHeight) {
    EXPECT_EXIT(validate_metadata("P6", 56, -98, 6542),
                ::testing::ExitedWithCode(1),
                "Invalid input photo file");
}

TEST(UtilityTests, ValidateMetadata_InvalidIntensity) {
    EXPECT_EXIT(validate_metadata("P6", 12, 43, -1745),
                ::testing::ExitedWithCode(1),
                "Invalid input photo file");
}


//Tests for "get_image_metadata"

TEST(UtilityTests, GetImageData_ValidInput) {
    ofstream inputFile("input_test.ppm");
    inputFile << "P6\n234 756\n1634\n";
    inputFile.close();

    ifstream inputFile2("input_test.ppm");

    auto [magic_word, width, height, intensity] = get_image_metadata(inputFile2);

    EXPECT_EQ(magic_word, "P6");
    EXPECT_EQ(width, 234);
    EXPECT_EQ(height, 756);
    EXPECT_EQ(intensity, 1634);

    inputFile2.close();
}
//The same result is obtained whatever the invalid metadata is
TEST(UtilityTests, GetImageMetadata_InvalidMetadata) {
    ofstream inputFile("input_test.ppm");
    inputFile << "P6\n-234 756\n1634\n";
    inputFile.close();

    ifstream inputFile2("input_test.ppm");

    EXPECT_EXIT(get_image_metadata(inputFile2),
                ::testing::ExitedWithCode(1),
                "Invalid input photo file");

    inputFile2.close();
}


//Tests for setters and getters

TEST(UtilityTests, InFileSetterGetter) {
    const string inputFile = "input_test.ppm";
    setInFile(inputFile);
    EXPECT_EQ(getInFile(), inputFile);
}

TEST(UtilityTests, OutFileSetterGetter) {
    const string outputFile = "output_test.ppm";
    setOutFile(outputFile);
    EXPECT_EQ(getOutFile(), outputFile);
}


//Tests for "displayInfo"

TEST(UtilityTests, DisplayInfo_NotOpenFile) {
    const string inputFile = "input_test_that_does_not_exist.ppm";
    setInFile(inputFile);

    EXPECT_EXIT(displayInfo(),
                ::testing::ExitedWithCode(1),
                "Failed to open file\n");
}

TEST(UtilityTests, DisplayInfo) {
    ofstream inputFile("input_test.ppm");
    inputFile << "P6\n234 756\n1634\n";
    inputFile.close();

    setInFile("input_test.ppm");
    setOutFile("output_test.ppm");

    testing::internal::CaptureStdout();
    displayInfo();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Input:   input_test.ppm"), string::npos);
    EXPECT_NE(output.find("Output:   output_test.ppm"), string::npos);
    EXPECT_NE(output.find("Operation:   info"), string::npos);
    EXPECT_NE(output.find("Magic Word:  P6"), string::npos);
    EXPECT_NE(output.find("Image Size:   234x756"), string::npos);
    EXPECT_NE(output.find("Max Level:   1634"), string::npos);
}