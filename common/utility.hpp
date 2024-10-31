//
// Created by finnb on 10/21/2024.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
using namespace std;

#ifndef UTILITY_HPP
#define UTILITY_HPP

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
    bool operator==(const smallColor &other) const {
        return (r == other.r && g == other.g && b == other.b);
    }
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
