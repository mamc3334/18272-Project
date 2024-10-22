//
// Created by finnb on 10/7/2024.
//
using namespace std;
#include <vector>
#include "imageaos.hpp"
#include <iostream>

std::vector<Color> imgColors;

void aos_read_bytes(const Image_Attributes& meta, ifstream& in) {
    /* TODO: should be using getByte?
        * use metadata width and height and intensity
        * Consider cache access
     */
}

void aos_maxlevel()
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes metadata = get_image_metadata(imageFile);
    aos_read_bytes(metadata, imageFile);
    /* TODO: Intensity scaling to new max value
        * Case 1: (easy) original and new intensity < 255
            * 3 bytes/pixel
        * Case 2: (medium) original and new intensity > 255
            * 6 bytes/pixel - little-endian
        * Case 3: (hard) original < 255, new > 255
            * 3 bytes/pixel -> 6 bytes/pixel
        * Case 4: (hard) original > 255, new < 255
            * 6 bytes/pixel -> 3 bytes/pixel
            *
/*test
void read_image_IntensityScaling (string inputFilename, string outputFilename, int newIntensity) {
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
    string magic_word, width, height, intensity;
    inputImageFile >> magic_word >> width >> height >> intensity;
    outputImageFile << magic_word << "\n" << width << "\n" << height << "\n" << intensity << "\n";
    int colors = 3*width*height;
    if(intensity <= 255){
        if(newIntensity <= 255){
            for(int i = 0;i < colors: i ++){
                uint8_t x = read_binary8 (inputImageFile);
                uint8_t newColor = (x*newIntensity)/intensity;
                write_binary8 (outputImageFile, newColor);
            }
        }else{ //newIntensity > 255
            for(int i = 0;i < colors: i ++){
                uint8_t x = read_binary8 (inputImageFile);
                uint16_t newColor = (x*newIntensity)/intensity;
                write_binary16 (outputImageFile, newColor);
            }
        }
    }else{ //intensity > 255
        if(newIntensity <= 255){
            for(int i = 0;i < colors: i ++){
                uint16_t x = read_binary16 (inputImageFile);
                uint8_t newColor = (x*newIntensity)/intensity;
                write_binary8 (outputImageFile, newColor);
            }
        }else{ //newIntensity > 255
            for(int i = 0;i < colors: i ++){
                uint16_t x = read_binary16 (inputImageFile);
                uint16_t newColor = (x*newIntensity)/intensity;
                write_binary16 (outputImageFile, newColor);
            }
        }
    }
}
     */
}

void aos_resize()
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes metadata = get_image_metadata(imageFile);
    aos_read_bytes(metadata, imageFile);
    /* TODO: Size scaling
        * Cases: Smaller to bigger
        * Use same process -> map target(new) onto original
        * Map target onto orginal
        * Find xL, xH, yL, yH of original for each pixel in target(new) image
        * triple interpolation x, y, x-y
     */
}

void aos_cutfreq()
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes metadata = get_image_metadata(imageFile);
    /* TODO: Remove least used colors
        *
        *
     */
}

void aos_compress()
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes metadata = get_image_metadata(imageFile);
    /* TODO: Compress
        * maybe similar to cutfreq
        *
     */
}