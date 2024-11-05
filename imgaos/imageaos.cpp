//
// Created by finnb on 10/7/2024.
//
#include "imageaos.hpp"
#include "aoscommon.hpp"
#include "aossize.hpp"
#include "../common/utility.hpp"
#include <vector>
#include <iostream>
using namespace std;

void aos_resize(Image_Attributes& newImageData)
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes oldImageData = get_image_oldImageData(imageFile);
    ofstream outputImageFile(getOutFile());
    if(!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }
    newImageData.intensity = oldImageData.intensity;
    newImageData.magic_word = oldImageData.magic_word;
    outputImageFile << newImageData.magic_word << "\n" << newImageData.width << "\n" << newImageData.height << "\n" << newImageData.intensity << "\n";
    if(newImageData.intensity > 255)
    {
        vector<vector<bigColor>> oldPhoto(oldImageData.height, vector<bigColor>(oldImageData.width));
        aossize_old_photo_16(oldPhoto, oldImageData, imageFile);
        aossize_resize_16(oldPhoto, oldImageData, newImageData, outputImageFile);
    }
    else
    {
        vector<vector<smallColor>> sOldPhoto(oldImageData.height, vector<smallColor>(oldImageData.width));
        aossize_old_photo_8(sOldPhoto, oldImageData, imageFile);
        aossize_resize_8(sOldPhoto, oldImageData, newImageData, outputImageFile);
    }
}

void aos_cutfreq()
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes oldImageData = get_image_oldImageData(imageFile);
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
    const Image_Attributes oldImageData = get_image_oldImageData(imageFile);
    /* TODO: Compress
        * maybe similar to cutfreq
        *
     */
}