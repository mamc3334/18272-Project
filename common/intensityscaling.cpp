//
// Created by eloim on 22/10/2024.
//
using namespace std;
#include <iostream>
#include <fstream>
#include "binaryio.hpp"


void read_image_intensity_scaling (string inputFilename, string outputFilename, int newIntensity){
    ifstream inputImageFile(inputFilename);
    if(!inputImageFile.is_open()) {
        cerr << "Failed to open input file\n";
        exit(-1);
    }
    ofstream outputImageFile(outputFilename);
    if(!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }
    string magic_word;
    int width, height, intensity;
    inputImageFile >> magic_word >> width >> height >> intensity;
    outputImageFile << magic_word << "\n" << width << "\n" << height << "\n" << intensity << "\n";
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