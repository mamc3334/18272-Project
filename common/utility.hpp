//
// Created by finnb on 10/21/2024.
//
#pragma once

#include <fstream>
#include <cstdint>
using namespace std;

#ifndef UTILITY_HPP
#define UTILITY_HPP

constexpr int IntensityCutoff = 255;

struct Coords {
  float x_map,x_lo,x_hi,y_map,y_lo,y_hi;
};

struct Image_Attributes {
    std::string magic_word;
    unsigned int width, height;
    int intensity;
};

struct smallColor{
    uint8_t r, g, b;
    bool operator==(const smallColor &other) const {
        return (r == other.r && g == other.g && b == other.b);
    }
};

struct bigColor{
    uint16_t r, g, b;
    bool operator==(const bigColor &other) const {
        return (r == other.r && g == other.g && b == other.b);
    }
};

inline string inFile, outFile;

void validate_metadata (const string& word, int width, int height, int intensity);
Image_Attributes get_image_metadata (ifstream& imageFile);
void displayInfo();
string getInFile();
string getOutFile();
void setInFile(const string& name);
void setOutFile(const string& name);

#endif //UTILITY_HPP
