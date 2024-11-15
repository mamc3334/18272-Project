#ifndef SOAINFREQUENTCOLOR_HPP
#define SOAINFREQUENTCOLOR_HPP

#include "../common/binaryio.hpp"
#include "../common/utility.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

// Struct to hold separate arrays for red, green, and blue channels
struct SoA_8 {
    vector<uint8_t> r, g, b;
};

struct SoA_16 {
    vector<uint16_t> r, g, b;
};

void populatePixels_8(SoA_8& pixels, const Image_Attributes& photoData, ifstream& inFile);
void populatePixels_16(SoA_16& pixels, const Image_Attributes& photoData, ifstream& inFile);
unordered_map<int, int> countColors_8(const SoA_8& pixels);
unordered_map<int, int> countColors_16(const SoA_16& pixels);
double colorDistance_8(size_t index1, size_t index2, const SoA_8& pixels);
double colorDistance_16(size_t index1, size_t index2, const SoA_16& pixels);
void changeInfrequentColors_8(SoA_8& pixels, size_t n);
void changeInfrequentColors_16(SoA_16& pixels, size_t n);
void writeBinary_8(const SoA_8& pixels, ofstream& outFile);
void writeBinary_16(const SoA_16& pixels, ofstream& outFile);

#endif // SOAINFREQUENTCOLOR_HPP
