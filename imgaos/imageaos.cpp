#include "aoscommon.hpp"
#include "aossize.hpp"
//
// Created by finnb on 10/7/2024.
//
using namespace std;
#include <vector>
#include "imageaos.hpp"
#include <iostream>

void aos_resize(int width, int height)
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes metadata = get_image_metadata(imageFile);
    ofstream outputImageFile(getOutFile());
    if(!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }
    outputImageFile << metadata.magic_word << "\n" << width << "\n" << height << "\n" << metadata.intensity << "\n";
    if(metadata.intensity > 255)
    {
        vector<vector<bigColor>> oldPhoto(metadata.height, vector<bigColor>(metadata.width));
        aossize_old_photo_16(oldPhoto, metadata.height, metadata.width, imageFile);
        aossize_resize_16(oldPhoto, metadata.height, metadata.width, width, height, outputImageFile);
    }
    else
    {
        vector<vector<smallColor>> sOldPhoto(metadata.height, vector<smallColor>(metadata.width));
        aossize_old_photo_8(sOldPhoto, metadata.height, metadata.width, imageFile);
        aossize_resize_8(sOldPhoto, metadata.width, metadata.height, height, width, outputImageFile);
    }
    imageFile.close();
    outputImageFile.close();
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