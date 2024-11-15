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

/*
struct color {
    int r, g, b;

    bool operator==(const color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
};
*/

struct colorHash_8 {
    size_t operator()(const smallColor& c) const {
        return hash<int>()(c.r) ^ hash<int>()(c.g) ^ hash<int>()(c.b);
    }
};

struct colorHash_16 {
    size_t operator()(const bigColor& c) const {
        return hash<int>()(c.r) ^ hash<int>()(c.g) ^ hash<int>()(c.b);
    }
};

void populatePixels_8(vector<smallColor>& pixels, const Image_Attributes& photoData, ifstream& inFile);
void populatePixels_16(vector<bigColor>& pixels, const Image_Attributes& photoData, ifstream& inFile);
unordered_map<smallColor, int, colorHash_8> countColors_8(const vector<smallColor>& pixels);
unordered_map<bigColor, int, colorHash_16> countColors_16(const vector<bigColor>& pixels);

//void sortColors(vector<color>& pixels);
double colorDistance_8(const smallColor& c1, const smallColor& c2);
double colorDistance_16(const bigColor& c1, const bigColor& c2);

void changeInfrequentColors_8(vector<smallColor>& colorList, const size_t n);
void changeInfrequentColors_16(vector<bigColor>& colorList, const size_t n);

void writeBinary_8(const vector<smallColor>& pixels, ofstream& outFile);
void writeBinary_16(const vector<bigColor>& pixels, ofstream& outFile);

#endif //AOSINFREQUENTCOLOR_HPP
