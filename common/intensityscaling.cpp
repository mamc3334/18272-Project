
//
// Created by eloim on 22/10/2024.
//
using namespace std;
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "intensityscaling.hpp"
#include "utility.hpp"
#include "binaryio.hpp"

void intensity_smaller_255(const vector<int> & data, ifstream &inputImageFile, ofstream &outputImageFile) {
    const float scalingFactor = static_cast<float>(data[1]) / static_cast<float>(data[0]);
    if(data[1] <= IntensityCutoff){
        for(int i = 0;i < data[2]; i ++){
            const uint8_t oldColor = read_binary8 (inputImageFile);
            const auto newColor = static_cast<uint8_t>(oldColor*scalingFactor);
            write_binary8 (outputImageFile, newColor);
        }
    }else{ //newIntensity > 255
        for(int i = 0;i < data[2]; i ++){
            const uint8_t oldColor = read_binary8 (inputImageFile);
            const auto newColor = static_cast<uint16_t>(oldColor*scalingFactor);
            write_binary16 (outputImageFile, newColor);
        }
    }
}

void intensity_greater_255(const vector<int> & data, ifstream &inputImageFile, ofstream &outputImageFile) {
    const int scalingFactor = data[1]/data[0];
    if(data[1] <= IntensityCutoff){
        for(int i = 0;i < data[2]; i ++){
            const uint16_t oldColor = read_binary16 (inputImageFile);
            const auto newColor = static_cast<uint8_t>(oldColor*scalingFactor);
            write_binary8 (outputImageFile, newColor);
        }
    }else{ //newIntensity > 255
        for(int i = 0;i < data[2]; i ++){
            const uint16_t oldColor = read_binary16 (inputImageFile);
            const auto newColor = static_cast<uint16_t>(oldColor*scalingFactor);
            write_binary16 (outputImageFile, newColor);
        }
    }
}

void read_image_intensity_scaling (int newIntensity){
    ifstream inputImageFile(getInFile());
    if(!inputImageFile.is_open()) {
        cerr << "Failed to open input file\n";
        exit(-1);
    }

    ofstream outputImageFile(getOutFile());
    if(!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }

    auto [magic_word, width, height, intensity] = get_image_metadata(inputImageFile);
    outputImageFile << magic_word << "\n" << width << " " << height << "\n" << newIntensity << "\n";

    const int colors = static_cast<int>(3*width*height);
    const vector data = {intensity, newIntensity, colors};

    if(intensity <= IntensityCutoff){
        intensity_smaller_255(data, inputImageFile, outputImageFile);
    }else{ //intensity > 255
        intensity_greater_255(data, inputImageFile, outputImageFile);
    }
}