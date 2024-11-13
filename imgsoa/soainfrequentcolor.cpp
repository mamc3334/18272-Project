// Created by ryanb on 10/22/2024.

#include "soainfrequentcolor.hpp"
#include "../common/binaryio.hpp"
#include "../common/utility.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;


//Populates pixel data from input image (one byte per RGB value)
void populatePixels_8(ImageData& imageData, const Image_Attributes& photoData, ifstream& inFile) {
    imageData.width = photoData.width;
    imageData.height = photoData.height;
    int totalPixels = photoData.width * photoData.height;

    imageData.red.resize(totalPixels);
    imageData.green.resize(totalPixels);
    imageData.blue.resize(totalPixels);

    for (int i = 0; i < totalPixels; ++i) {
        imageData.red[i] = read_binary8(inFile);
        imageData.green[i] = read_binary8(inFile);
        imageData.blue[i] = read_binary8(inFile);
    }
    inFile.close();
}

//Populates pixel data from input image (two bytes per RGB value)
void populatePixels_16(ImageData& imageData, const Image_Attributes& photoData, ifstream& inFile) {
    imageData.width = photoData.width;
    imageData.height = photoData.height;
    int totalPixels = photoData.width * photoData.height;

    imageData.red.resize(totalPixels);
    imageData.green.resize(totalPixels);
    imageData.blue.resize(totalPixels);

    for (int i = 0; i < totalPixels; ++i) {
        imageData.red[i] = read_binary16(inFile);
        imageData.green[i] = read_binary16(inFile);
        imageData.blue[i] = read_binary16(inFile);
    }
    inFile.close();
}

//Counts unique colors and their frequencies
ImageData countColors(const ImageData& imageData) {
    ImageData colorList;
    int totalPixels = imageData.width * imageData.height;

    for (int i = 0; i < totalPixels; ++i) {
        bool found = false;
        for (int j = 0; j < colorList.red.size(); ++j) {
            if (colorList.red[j] == imageData.red[i] &&
                colorList.green[j] == imageData.green[i] &&
                colorList.blue[j] == imageData.blue[i]) {
                colorList.count[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            colorList.red.push_back(imageData.red[i]);
            colorList.green.push_back(imageData.green[i]);
            colorList.blue.push_back(imageData.blue[i]);
            colorList.count.push_back(1);
        }
    }
    return colorList;
}

//Sort the colors by count, then by RGB values
void sortColors(ImageData& colorList) {
    int totalColors = colorList.red.size();
    vector<int> indices(totalColors);

    for (int i = 0; i < totalColors; ++i) {
        indices[i] = i;
    }
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        if (colorList.count[a] != colorList.count[b]) return colorList.count[a] < colorList.count[b];
        if (colorList.red[a] != colorList.red[b]) return colorList.red[a] < colorList.red[b];
        if (colorList.green[a] != colorList.green[b]) return colorList.green[a] < colorList.green[b];
        return colorList.blue[a] < colorList.blue[b];
    });

    ImageData sortedList = colorList;
    for (int i = 0; i < totalColors; ++i) {
        sortedList.red[i] = colorList.red[indices[i]];
        sortedList.green[i] = colorList.green[indices[i]];
        sortedList.blue[i] = colorList.blue[indices[i]];
        sortedList.count[i] = colorList.count[indices[i]];
    }
    colorList = sortedList;
}

//Calculate Euclidean distance between two colors
double colorDistance(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2) {
    return sqrt(pow(r2 - r1, 2) + pow(g2 - g1, 2) + pow(b2 - b1, 2));
}

//Replace the least frequent colors with the closest color (determined by Euclidian distance)
void changeInfrequentColors(ImageData& imageData, int n) {
    ImageData colorList = countColors(imageData);
    sortColors(colorList);

    for (int i = 0; i < n; ++i) {
        uint8_t targetR = colorList.red[i];
        uint8_t targetG = colorList.green[i];
        uint8_t targetB = colorList.blue[i];

        int minDistance = 100000; //arbitrary big number
        int closestIndex = -1;

        for (int j = n; j < colorList.red.size(); ++j) {
            double distance = colorDistance(targetR, targetG, targetB,
                                            colorList.red[j], colorList.green[j], colorList.blue[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = j;
            }
        }

        if (closestIndex != -1) {
            for (int k = 0; k < imageData.red.size(); ++k) {
                if (imageData.red[k] == targetR && imageData.green[k] == targetG && imageData.blue[k] == targetB) {
                    imageData.red[k] = colorList.red[closestIndex];
                    imageData.green[k] = colorList.green[closestIndex];
                    imageData.blue[k] = colorList.blue[closestIndex];
                }
            }
        }
    }
}

//Write modified pixel data to binary output file using write_binary8 (one byte per RGB value)
void writeBinary_8(const ImageData& imageData, const Image_Attributes& photoData, const string& outputFilePath) {
    ofstream outFile(outputFilePath, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    outFile << "P6\n" << photoData.width << " " << photoData.height << "\n255\n";

    for (int i = 0; i < imageData.red.size(); ++i) {
        write_binary8(outFile, imageData.red[i]);
        write_binary8(outFile, imageData.green[i]);
        write_binary8(outFile, imageData.blue[i]);
    }

    outFile.close();
    cout << "Image written to " << outputFilePath << endl;
}

//Write modified pixel data to binary output file using write_binary16 (two bytes per RGB value)
void writeBinary_16(const ImageData& imageData, const Image_Attributes& photoData, const string& outputFilePath) {
    ofstream outFile(outputFilePath, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    outFile << "P6\n" << photoData.width << " " << photoData.height << "\n" << photoData.intensity << "\n";

    for (int i = 0; i < imageData.red.size(); ++i) {
        write_binary16(outFile, imageData.red[i]);
        write_binary16(outFile, imageData.green[i]);
        write_binary16(outFile, imageData.blue[i]);
    }

    outFile.close();
}
