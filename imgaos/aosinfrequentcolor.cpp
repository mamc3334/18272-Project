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
    pixels.resize(photoData.width * photoData.height);
    for(unsigned int i = 0; i < (photoData.height * photoData.width); i++){
        pixels[i] = {.r=read_binary8(inFile), .g=read_binary8(inFile), .b=read_binary8(inFile)};
    }
}

void populatePixels_16(vector<bigColor> &pixels, const Image_Attributes& photoData, ifstream& inFile)
{
    pixels.resize(photoData.width * photoData.height);
    for(unsigned int i = 0; i < (photoData.height * photoData.width); i++){
        pixels[i] = {.r=read_binary16(inFile), .g=read_binary16(inFile), .b=read_binary16(inFile)};
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


double colorDistance_8(const smallColor& c1, const smallColor& c2) {
    return ((c2.r - c1.r) * (c2.r - c1.r) + (c2.g - c1.g) * (c2.g - c1.g) + (c2.b - c1.b) * (c2.b - c1.b));
}

double colorDistance_16(const bigColor& c1, const bigColor& c2) {
    return ((c2.r - c1.r) * (c2.r - c1.r) + (c2.g - c1.g) * (c2.g - c1.g) + (c2.b - c1.b) * (c2.b - c1.b));
}


void changeInfrequentColors_8(std::vector<smallColor>& pixels, const size_t n) {
    // Count color frequencies
    unordered_map<smallColor, int, colorHash_8> colorMap = countColors_8(pixels);

    // If `n` is greater than or equal to the number of unique colors, replace all colors with black
    if (n >= colorMap.size()) {
        std::fill(pixels.begin(), pixels.end(), smallColor{0, 0, 0});
        return;
    }

    // Build a min-heap to find the n least frequent colors
    std::vector<std::pair<smallColor, int>> colorFreqList(colorMap.begin(), colorMap.end());
    std::nth_element(
        colorFreqList.begin(),
        colorFreqList.begin() + static_cast<std::vector<std::pair<smallColor, int>>::difference_type>(n),
        colorFreqList.end(),
        [](const std::pair<smallColor, int>& a, const std::pair<smallColor, int>& b) {
            if (a.second != b.second) {
                return a.second < b.second; // Primary comparison: frequency
            }
            // Tie-breaking: lexicographic order by smallColor (b, g, r)
            if (a.first.b != b.first.b) return a.first.b < b.first.b;
            if (a.first.g != b.first.g) return a.first.g < b.first.g;
            return a.first.r < b.first.r;
        });

    // Extract the n least frequent colors
    std::vector<smallColor> infrequentColors;
    for (size_t i = 0; i < n; ++i) {
        infrequentColors.push_back(colorFreqList[i].first);
    }

    // Store the remaining colors as frequent colors
    std::vector<smallColor> frequentColors;
    for (size_t i = n; i < colorFreqList.size(); ++i) {
        frequentColors.push_back(colorFreqList[i].first);
    }
    // Construct KDTree with frequent colors
    KDTreeSmallColor kdTree(frequentColors);

    // Map each infrequent color to the closest frequent color
    std::unordered_map<smallColor, smallColor, colorHash_8> colorReplacementMap;
    for (const smallColor& infrequentColor : infrequentColors) {
        smallColor closestColor = kdTree.nearestNeighbor(infrequentColor);
        colorReplacementMap[infrequentColor] = closestColor;
    }

    // Replace infrequent colors in the pixels using the replacement map
    for (auto& pixel : pixels) {
        if (colorReplacementMap.find(pixel) != colorReplacementMap.end()) {
            pixel = colorReplacementMap[pixel];
        }
    }
}

void changeInfrequentColors_16(std::vector<bigColor>& pixels, const size_t n) {
    // Count color frequencies
    unordered_map<bigColor, int, colorHash_16> colorMap = countColors_16(pixels);

    // If `n` is greater than or equal to the number of unique colors, replace all colors with black
    if (n >= colorMap.size()) {
        std::fill(pixels.begin(), pixels.end(), bigColor{0, 0, 0});
        return;
    }

    // Build a min-heap to find the n least frequent colors
    std::vector<std::pair<bigColor, int>> colorFreqList(colorMap.begin(), colorMap.end());
    std::nth_element(
        colorFreqList.begin(),
        colorFreqList.begin() + static_cast<std::vector<std::pair<bigColor, int>>::difference_type>(n),
        colorFreqList.end(),
        [](const std::pair<bigColor, int>& a, const std::pair<bigColor, int>& b) {
            if (a.second != b.second) {
                return a.second < b.second;
            }

            if (a.first.b != b.first.b) return a.first.b < b.first.b;
            if (a.first.g != b.first.g) return a.first.g < b.first.g;
            return a.first.r < b.first.r;
        });

    // Extract the n least frequent colors
    std::vector<bigColor> infrequentColors;
    for (size_t i = 0; i < n; ++i) {
        infrequentColors.push_back(colorFreqList[i].first);
    }

    // Store the remaining colors as frequent colors
    std::vector<bigColor> frequentColors;
    for (size_t i = n; i < colorFreqList.size(); ++i) {
        frequentColors.push_back(colorFreqList[i].first);
    }

    // Construct KDTree with frequent colors
    KDTreeBigColor kdTree(frequentColors);

    // Map each infrequent color to the closest frequent color
    std::unordered_map<bigColor, bigColor, colorHash_16> colorReplacementMap;
    for (const bigColor& infrequentColor : infrequentColors) {
        bigColor closestColor = kdTree.nearestNeighbor(infrequentColor);
        colorReplacementMap[infrequentColor] = closestColor;
    }

    // Replace infrequent colors in the pixels using the replacement map
    for (auto& pixel : pixels) {
        if (colorReplacementMap.find(pixel) != colorReplacementMap.end()) {
            pixel = colorReplacementMap[pixel];
        }
    }
}

void writeBinary_8(const vector<smallColor>& pixels, ofstream& outFile) {
    for (const auto& pixel : pixels) {
        write_binary8(outFile, static_cast<uint8_t>(pixel.r));
        write_binary8(outFile, static_cast<uint8_t>(pixel.g));
        write_binary8(outFile, static_cast<uint8_t>(pixel.b));
    }
}

void writeBinary_16(const vector<bigColor>& pixels, ofstream& outFile) {
    for (const auto& pixel : pixels) {
        write_binary16(outFile, static_cast<uint16_t>(pixel.r));
        write_binary16(outFile, static_cast<uint16_t>(pixel.g));
        write_binary16(outFile, static_cast<uint16_t>(pixel.b));
    }
}
