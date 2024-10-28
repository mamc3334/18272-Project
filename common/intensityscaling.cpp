<<<<<<< HEAD
#include "intensityscaling.h"

=======
>>>>>>> origin/main
#include "utility.hpp"
//
// Created by eloim on 22/10/2024.
//
using namespace std;
#include <iostream>
#include <fstream>
#include "binaryio.hpp"


<<<<<<< HEAD
void intensity_smaller_255(const vector<int> & data, const ifstream & inputImageFile, const ofstream & outputImageFile);

void intensity_greater_255(const vector<int> & data, const ifstream & inputImageFile, const ofstream & outputImageFile);

=======
>>>>>>> origin/main
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
<<<<<<< HEAD
    auto [magic_word, width, height, intensity] = get_image_metadata(inputImageFile);
    outputImageFile << magic_word << "\n" << width << "\n" << height << "\n" << intensity << "\n";
    int colors = 3*width*height;
    vector<int> data = {intensity, newIntensity, colors};
    if(intensity <= 255){
        intensity_smaller_255(data, inputImageFile, outputImageFile);
    }else{ //intensity > 255
        intensity_greater_255(data, inputImageFile, outputImageFile);
    }
}

void intensity_smaller_255(const vector<int> & data, istream inputImageFile, ostream outputImageFile) {
    if(data[1] <= 255){
        for(int i = 0;i < data[2]; i ++){
            const uint8_t oldColor = read_binary8 (inputImageFile);
            const auto newColor = static_cast<uint8_t>((oldColor*data[1])/data[0]);
            write_binary8 (outputImageFile, newColor);
        }
    }else{ //newIntensity > 255
        for(int i = 0;i < data[2]; i ++){
            const uint8_t oldColor = read_binary8 (inputImageFile);
            const auto newColor = static_cast<uint16_t>((oldColor*data[1])/data[0]);
            write_binary16 (outputImageFile, newColor);
        }
    }
};

void intensity_greater_255(const vector<int> & data, istream inputImageFile, ostream outputImageFile) {
    if(data[1] <= 255){
        for(int i = 0;i < data[2]; i ++){
            const uint16_t oldColor = read_binary16 (inputImageFile);
            const auto newColor = static_cast<uint8_t>((oldColor*data[1])/data[0]);
            write_binary8 (outputImageFile, newColor);
        }
    }else{ //newIntensity > 255
        for(int i = 0;i < data[2]; i ++){
            const uint16_t oldColor = read_binary16 (inputImageFile);
            const auto newColor = static_cast<uint16_t>((oldColor*data[1])/data[0]);
            write_binary16 (outputImageFile, newColor);
        }
    }
};
=======
    string magic_word;
    int width, height, intensity;
    inputImageFile >> magic_word >> width >> height >> intensity;
    outputImageFile << magic_word << "\n" << width << "\n" << height << "\n" << newIntensity << "\n";

    int colors = 3*width*height;
    if(intensity <= 255){
        if(newIntensity <= 255){
            for(int i = 0;i < colors; i ++){
                uint8_t x = read_binary8 (inputImageFile);
                uint8_t newColor = (x*newIntensity)/intensity;
                write_binary8 (outputImageFile, newColor);
            }
        }else{ //newIntensity > 255
            for(int i = 0;i < colors; i ++){
                uint8_t x = read_binary8 (inputImageFile);
                uint16_t newColor = (x*newIntensity)/intensity;
                write_binary16 (outputImageFile, newColor);
            }
        }
    }else{ //intensity > 255
        if(newIntensity <= 255){
            for(int i = 0;i < colors; i ++){
                uint16_t x = read_binary16 (inputImageFile);
                uint8_t newColor = (x*newIntensity)/intensity;
                write_binary8 (outputImageFile, newColor);
            }
        }else{ //newIntensity > 255
            for(int i = 0;i < colors; i ++){
                uint16_t x = read_binary16 (inputImageFile);
                uint16_t newColor = (x*newIntensity)/intensity;
                write_binary16 (outputImageFile, newColor);
            }
        }
    }
}
>>>>>>> origin/main
