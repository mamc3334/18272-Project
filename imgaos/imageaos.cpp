//
// Created by finnb on 10/7/2024.
//
using namespace std;
#include <vector>
#include "imageaos.hpp"
#include <iostream>

void aos_maxlevel(int newIntensity)
{
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
    if(metadata.intensity > 255)
    {
        bigColor oldPhoto[][] = aossize_read_old_uint16(metadata.height, metadata.width, imageFile);
        aossize_main(oldPhoto,, ge);
    }
    else
    {
        smallColor oldPhoto[][] = aossize_read_old_uint8(metadata.height, metadata.width, imageFile);
        aossize_main(oldPhoto, );
    }

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