#include "soainfrequentcolor.hpp"
#include "../common/binaryio.hpp"
#include "../common/utility.hpp"
#include <cstddef>
#include <queue>

using namespace std;

// Populate pixels for 8-bit colors
void populatePixels_8(SoA_8& pixels, const Image_Attributes& photoData, ifstream& inFile) {
    auto const pixelCount = static_cast<size_t>(photoData.width) * static_cast<size_t>(photoData.height);
    pixels.r.resize(pixelCount);
    pixels.g.resize(pixelCount);
    pixels.b.resize(pixelCount);

    for (size_t i = 0; i < pixelCount; ++i) {
        pixels.r[i] = BINARY::read_binary8(inFile);
        pixels.g[i] = BINARY::read_binary8(inFile);
        pixels.b[i] = BINARY::read_binary8(inFile);
    }
}

// Populate pixels for 16-bit colors
void populatePixels_16(SoA_16& pixels, const Image_Attributes& photoData, ifstream& inFile) {
    auto const pixelCount = static_cast<size_t>(photoData.width) * static_cast<size_t>(photoData.height);
    pixels.r.resize(pixelCount);
    pixels.g.resize(pixelCount);
    pixels.b.resize(pixelCount);

    for (size_t i = 0; i < pixelCount; ++i) {
        pixels.r[i] = BINARY::read_binary16(inFile);
        pixels.g[i] = BINARY::read_binary16(inFile);
        pixels.b[i] = BINARY::read_binary16(inFile);
    }
}

unordered_map<int, int> countColors_8(const SoA_8& pixels) {
    unordered_map<int, int> colorMap;

    for (size_t i = 0; i < pixels.r.size(); ++i) {
        int const colorHash = ((pixels.r[i] & 0xFF) << 16) |
                        ((pixels.g[i] & 0xFF) << 8)  |
                        (pixels.b[i] & 0xFF);

        colorMap[colorHash]++;
    }

    return colorMap;
}

unordered_map<int, int> countColors_16(const SoA_16& pixels) {
    unordered_map<int, int> colorMap;

    for (size_t i = 0; i < pixels.r.size(); ++i) {
        int const colorHash = ((pixels.r[i] & 0xFF) << 16) |
                        ((pixels.g[i] & 0xFF) << 8)  |
                        (pixels.b[i] & 0xFF);

        colorMap[colorHash]++;
    }

    return colorMap;
}

// Compute color distance
double colorDistance_8(size_t index1, size_t index2, const SoA_8& pixels) {
    int const distanceRed = static_cast<int>(pixels.r[index2]) - static_cast<int>(pixels.r[index1]);
    int const distanceGreen = static_cast<int>(pixels.g[index2]) - static_cast<int>(pixels.g[index1]);
    int const distanceBlue = static_cast<int>(pixels.b[index2]) - static_cast<int>(pixels.b[index1]);
    return (distanceRed * distanceRed) + (distanceGreen * distanceGreen) + (distanceBlue * distanceBlue);
}

double colorDistance_16(size_t index1, size_t index2, const SoA_16& pixels) {
    int const distanceRed = static_cast<int>(pixels.r[index2]) - static_cast<int>(pixels.r[index1]);
    int const distanceGreen = static_cast<int>(pixels.g[index2]) - static_cast<int>(pixels.g[index1]);
    int const distanceBlue = static_cast<int>(pixels.b[index2]) - static_cast<int>(pixels.b[index1]);
    return (distanceRed * distanceRed) + (distanceGreen * distanceGreen) + (distanceBlue * distanceBlue);
}

// Change infrequent colors
void changeInfrequentColors_8(SoA_8& pixels, size_t n) {
    unordered_map<int, int> colorMap = countColors_8(pixels);

    if (n >= colorMap.size()) {
        fill(pixels.r.begin(), pixels.r.end(), 0);
        fill(pixels.g.begin(), pixels.g.end(), 0);
        fill(pixels.b.begin(), pixels.b.end(), 0);
        return;
    }

    vector<pair<int, int>> colorFreqList(colorMap.begin(), colorMap.end());
    nth_element(
        colorFreqList.begin(),
        colorFreqList.begin() + static_cast<vector<pair<int, int>>::difference_type>(n),
        colorFreqList.end(),
        [](const pair<int, int>& aPair, const pair<int, int>& bPair) { return aPair.second < bPair.second; });

    unordered_map<int, int> infrequentColors;
    for (size_t i = 0; i < n; ++i) {
        infrequentColors[colorFreqList[i].first] = 1;
    }

    for (size_t i = 0; i < pixels.r.size(); ++i) {
        int const colorHash = (pixels.r[i] << 16) | (pixels.g[i] << 8) | pixels.b[i];
        if (infrequentColors.find(colorHash) != infrequentColors.end()) {
            pixels.r[i] = 0;
            pixels.g[i] = 0;
            pixels.b[i] = 0;
        }
    }
}

void changeInfrequentColors_16(SoA_16& pixels, size_t n) {
    unordered_map<int, int> colorMap = countColors_16(pixels);

    if (n >= colorMap.size()) {
        fill(pixels.r.begin(), pixels.r.end(), 0);
        fill(pixels.g.begin(), pixels.g.end(), 0);
        fill(pixels.b.begin(), pixels.b.end(), 0);
        return;
    }

    vector<pair<int, int>> colorFreqList(colorMap.begin(), colorMap.end());
    nth_element(
        colorFreqList.begin(),
        colorFreqList.begin() + static_cast<vector<pair<int, int>>::difference_type>(n),
        colorFreqList.end(),
        [](const pair<int, int>& aPair, const pair<int, int>& bPair) { return aPair.second < bPair.second; });

    unordered_map<int, int> infrequentColors;
    for (size_t i = 0; i < n; ++i) {
        infrequentColors[colorFreqList[i].first] = 1;
    }

    for (size_t i = 0; i < pixels.r.size(); ++i) {
        int const colorHash = (pixels.r[i] << 16) | (pixels.g[i] << 8) | pixels.b[i];
        if (infrequentColors.contains(colorHash)) {
            pixels.r[i] = 0;
            pixels.g[i] = 0;
            pixels.b[i] = 0;
        }
    }
}

// Write binary
void writeBinary_8(const SoA_8& pixels, ofstream& outFile) {
    for (size_t i = 0; i < pixels.r.size(); ++i) {
        BINARY::write_binary8(outFile, pixels.r[i]);
        BINARY::write_binary8(outFile, pixels.g[i]);
        BINARY::write_binary8(outFile, pixels.b[i]);
    }
}

void writeBinary_16(const SoA_16& pixels, ofstream& outFile) {
    for (size_t i = 0; i < pixels.r.size(); ++i) {
        BINARY::write_binary16(outFile, pixels.r[i]);
        BINARY::write_binary16(outFile, pixels.g[i]);
        BINARY::write_binary16(outFile, pixels.b[i]);
    }
}
