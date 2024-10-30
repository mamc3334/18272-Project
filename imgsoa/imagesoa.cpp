//
// Created by finnb on 10/7/2024.
//
#include "../common/utility.hpp"
#include "soacommon.hpp"
#include "soasize.hpp"
#include <vector>
#include <iostream>
using namespace std;

void soa_resize(int width, int height)
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
        bigArray oldPhoto;
        soasize_old_photo_16(oldPhoto, metadata.height*metadata.width, imageFile);
        soasize_resize_16(oldPhoto, metadata.width, metadata.height, width, height, outputImageFile);
    }
    else
    {
        smallArray oldPhoto;
        soasize_old_photo_8(oldPhoto, metadata.height*metadata.width, imageFile);
        soasize_resize_8(oldPhoto, metadata.width, metadata.height, width, height, outputImageFile);
    }
    imageFile.close();
    outputImageFile.close();
}