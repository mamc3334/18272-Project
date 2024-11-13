// image_processing.hpp
// Header file for image processing functions

#ifndef SOAINFREQUENTCOLOR_HPP
#define SOAINFREQUENTCOLOR_HPP

#include "../common/binaryio.hpp"
#include "../common/utility.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

// Structure of Arrays for storing image data
struct ImageData {
    std::vector<uint8_t> red;
    std::vector<uint8_t> green;
    std::vector<uint8_t> blue;
    std::vector<int> count;  // Frequency count for each unique color
    int width;
    int height;
};


void populatePixels_8(ImageData& imageData, const Image_Attributes& photoData, std::ifstream& inFile);
void populatePixels_16(ImageData& imageData, const Image_Attributes& photoData, std::ifstream& inFile);
ImageData countColors(const ImageData& imageData);
void sortColors(ImageData& colorList);
double colorDistance(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
void changeInfrequentColors(ImageData& imageData, int n);
void writeBinary_8(const ImageData& imageData, const Image_Attributes& photoData, const std::string& outputFilePath);
void writeBinary_16(const ImageData& imageData, const Image_Attributes& photoData, const std::string& outputFilePath);

#endif // SOAINFREQUENTCOLOR_HPP
