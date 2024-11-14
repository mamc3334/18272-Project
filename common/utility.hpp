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

// These hashing algorithms were written by ChatGPT
// Gets std hash of uint8_t/uint16_t for all three color copmonents, shifts so they don't overlap, XORs
// Adds to namespace std for use in unordered set/map
namespace std {
    template <>
    struct hash<smallColor> {
        std::size_t operator()(const smallColor& color) const {
            // Combine hash values of red, green, and blue components
            return (std::hash<uint8_t>()(color.r) << 16) ^
                   (std::hash<uint8_t>()(color.g) << 8) ^
                    std::hash<uint8_t>()(color.b);
        }
    };

    template <>
    struct hash<bigColor> {
        std::size_t operator()(const bigColor& color) const {
            // Combine hash values of red, green, and blue components
            return (std::hash<uint16_t>()(color.r) << 32) ^
                   (std::hash<uint16_t>()(color.g) << 16) ^
                    std::hash<uint16_t>()(color.b);
        }
    };
}


inline string inFile, outFile;

void validate_metadata (const string& word, int width, int height, int intensity);
Image_Attributes get_image_metadata (ifstream& imageFile);
void displayInfo();
string getInFile();
string getOutFile();
void setInFile(const string& name);
void setOutFile(const string& name);

#endif //UTILITY_HPP
