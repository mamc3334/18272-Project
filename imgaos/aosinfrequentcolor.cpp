#include "aosinfrequentcolor.hpp"
#include "../common/binaryio.hpp"
#include "../common/utility.hpp"
#include "KDTree.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

void populatePixels_8(vector<smallColor> &pixels, const Image_Attributes& photoData, ifstream& inFile)
{
    pixels.resize(static_cast<size_t>(photoData.width) * static_cast<size_t>(photoData.height));
    for(unsigned int i = 0; i < (photoData.height * photoData.width); i++){
        pixels[i] = {.r=BINARY::read_binary8(inFile), .g=BINARY::read_binary8(inFile), .b=BINARY::read_binary8(inFile)};
    }
}

void populatePixels_16(vector<bigColor> &pixels, const Image_Attributes& photoData, ifstream& inFile)
{
    pixels.resize(static_cast<size_t>(photoData.width) * static_cast<size_t>(photoData.height));
    for(unsigned int i = 0; i < (photoData.height * photoData.width); i++){
        pixels[i] = {.r=BINARY::read_binary16(inFile), .g=BINARY::read_binary16(inFile), .b=BINARY::read_binary16(inFile)};
    }
}

// Updated countColors function using unordered_map for color frequencies
unordered_map<smallColor, int, colorHash_8> countColors_8(const vector<smallColor>& pixels) {
    unordered_map<smallColor, int, colorHash_8> colorMap;

    for (const auto& pixel : pixels) {
        colorMap[pixel]++;  // Increment the count for the color in the map
    }

    return colorMap;
}

unordered_map<bigColor, int, colorHash_16> countColors_16(const vector<bigColor>& pixels) {
    unordered_map<bigColor, int, colorHash_16> colorMap;

    for (const auto& pixel : pixels) {
        colorMap[pixel]++;  // Increment the count for the color in the map
    }

    return colorMap;
}


double colorDistance_8(const smallColor& color1, const smallColor& color2) {
    return (((color2.r - color1.r) * (color2.r - color1.r)) + ((color2.g - color1.g) * (color2.g - color1.g)) + ((color2.b - color1.b) * (color2.b - color1.b)));
}

double colorDistance_16(const bigColor& color1, const bigColor& color2) {
    return (((color2.r - color1.r) * (color2.r - color1.r)) + ((color2.g - color1.g) * (color2.g - color1.g)) + ((color2.b - color1.b) * (color2.b - color1.b)));
}


void changeInfrequentColors_8(std::vector<smallColor>& pixels, const size_t n) {
    unordered_map<smallColor, int, colorHash_8> colorMap = countColors_8(pixels);
    if (n >= colorMap.size()) {
        std::fill(pixels.begin(), pixels.end(), smallColor{.r=0, .g=0, .b=0});
        return;
    }
    std::vector<std::pair<smallColor, int>> colorFreqList(colorMap.begin(), colorMap.end());
    std::nth_element(colorFreqList.begin(),colorFreqList.begin() + static_cast<std::vector<std::pair<smallColor, int>>::difference_type>(n),colorFreqList.end(),
        [](const std::pair<smallColor, int>& one, const std::pair<smallColor, int>& two) {
            if (one.second != two.second) {
                return one.second < two.second; // Primary comparison: frequency
            }
            // Tie-breaking: lexicographic order by smallColor (b, g, r)
            if (one.first.b != two.first.b) {
              return one.first.b < two.first.b;
            }
            if (one.first.g != two.first.g) {
              return one.first.g < two.first.g;
            }
            return one.first.r < two.first.r;
        });
    std::vector<smallColor> infrequentColors;
    for (size_t i = 0; i < n; ++i) {
        infrequentColors.push_back(colorFreqList[i].first);
    }
    std::vector<smallColor> frequentColors;
    for (size_t i = n; i < colorFreqList.size(); ++i) {
        frequentColors.push_back(colorFreqList[i].first);
    }
    KDTreeSmallColor const kdTree(frequentColors);
    std::unordered_map<smallColor, smallColor, colorHash_8> colorReplacementMap;
    for (const smallColor& infrequentColor : infrequentColors) {
        smallColor const closestColor = kdTree.nearestNeighbor(infrequentColor);
        colorReplacementMap[infrequentColor] = closestColor;
    }
    for (auto& pixel : pixels) {
        if (colorReplacementMap.find(pixel) != colorReplacementMap.end()) {
            pixel = colorReplacementMap[pixel];
        }
    }
}

void changeInfrequentColors_16(std::vector<bigColor>& pixels, const size_t n) {
    unordered_map<bigColor, int, colorHash_16> colorMap = countColors_16(pixels);
    if (n >= colorMap.size()) {
        std::fill(pixels.begin(), pixels.end(), bigColor{.r=0, .g=0, .b=0});
        return;
    }
    std::vector<std::pair<bigColor, int>> colorFreqList(colorMap.begin(), colorMap.end());
    std::nth_element(colorFreqList.begin(), colorFreqList.begin() + static_cast<std::vector<std::pair<bigColor, int>>::difference_type>(n), colorFreqList.end(),
        [](const std::pair<bigColor, int>& one, const std::pair<bigColor, int>& two) {
            if (one.second != two.second) {
                return one.second < two.second;
            }

            if (one.first.b != two.first.b) {
              return one.first.b < two.first.b;
            }
            if (one.first.g != two.first.g) {
              return one.first.g < two.first.g;
            }
            return one.first.r < two.first.r;
        });
    std::vector<bigColor> infrequentColors;
    for (size_t i = 0; i < n; ++i) {
        infrequentColors.push_back(colorFreqList[i].first);
    }
    std::vector<bigColor> frequentColors;
    for (size_t i = n; i < colorFreqList.size(); ++i) {
        frequentColors.push_back(colorFreqList[i].first);
    }
    KDTreeBigColor const kdTree(frequentColors);
    std::unordered_map<bigColor, bigColor, colorHash_16> colorReplacementMap;
    for (const bigColor& infrequentColor : infrequentColors) {
        bigColor const closestColor = kdTree.nearestNeighbor(infrequentColor);
        colorReplacementMap[infrequentColor] = closestColor;
    }
    for (auto& pixel : pixels) {
        if (colorReplacementMap.find(pixel) != colorReplacementMap.end()) {
            pixel = colorReplacementMap[pixel];
        }
    }
}

void writeBinary_8(const vector<smallColor>& pixels, ofstream& outFile) {
    for (const auto& pixel : pixels) {
        BINARY::write_binary8(outFile, static_cast<uint8_t>(pixel.r));
        BINARY::write_binary8(outFile, static_cast<uint8_t>(pixel.g));
        BINARY::write_binary8(outFile, static_cast<uint8_t>(pixel.b));
    }
}

void writeBinary_16(const vector<bigColor>& pixels, ofstream& outFile) {
    for (const auto& pixel : pixels) {
        BINARY::write_binary16(outFile, static_cast<uint16_t>(pixel.r));
        BINARY::write_binary16(outFile, static_cast<uint16_t>(pixel.g));
        BINARY::write_binary16(outFile, static_cast<uint16_t>(pixel.b));
    }
}
