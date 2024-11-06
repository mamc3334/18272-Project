//
// Created by finnb on 10/21/2024.
//
#include <iostream>
#include <vector>
#include <fstream>
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
};

struct bigColor{
    uint16_t r, g, b;
};

inline string inFile, outFile;

void validate_metadata (const string& word, const int width, const int height, const int intensity);
Image_Attributes get_image_metadata (ifstream& imageFile);
void validate_metadata (Image_Attributes metadata);
void displayInfo();
string getInFile();
string getOutFile();
void setInFile(const string& in);
void setOutFile(const string& out);

#endif //UTILITY_HPP
