//
// Created by ryanb on 10/22/2024.
//

#ifndef AOSINFREQUENTCOLOR_HPP
#define AOSINFREQUENTCOLOR_HPP

#include "../common/binaryio.hpp"
#include "../common/utility.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

struct color {
    int r, g, b;

    bool operator==(const color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
};

struct colorHash {
    size_t operator()(const color& c) const {
        return hash<int>()(c.r) ^ hash<int>()(c.g) ^ hash<int>()(c.b);
    }
};

void populatePixels_8(vector<color>& pixels, const Image_Attributes& photoData, ifstream& inFile);
void populatePixels_16(vector<color>& pixels, const Image_Attributes& photoData, ifstream& inFile);
unordered_map<color, int, colorHash> countColors(const vector<color>& pixels);
void sortColors(vector<color>& pixels);
double colorDistance(const color& c1, const color& c2);
void changeInfrequentColors(vector<color>& colorList, const size_t n);
void writeBinary_8(const vector<color>& pixels, ofstream& outFile);
void writeBinary_16(const vector<color>& pixels, ofstream& outFile);

#endif //AOSINFREQUENTCOLOR_HPP
