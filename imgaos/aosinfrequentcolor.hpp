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
    int count;

    bool operator==(const color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
};

void populatePixels_8(vector<color>& pixels, const Image_Attributes& photoData, ifstream& inFile);
void populatePixels_16(vector<color>& pixels, const Image_Attributes& photoData, ifstream& inFile);
vector<color> countColors(const vector<color>& pixels);
void sortColors(vector<color>& pixels);
double colorDistance(const color& c1, const color& c2);
void changeInfrequentColors(vector<color>& colorList, int n);
void writeBinary_8(const vector<color>& pixels, const Image_Attributes& photoData, ofstream& outputFilePath);
void writeBinary_16(const vector<color>& pixels, const Image_Attributes& photoData, ofstream& outputFilePath);

#endif //AOSINFREQUENTCOLOR_HPP
