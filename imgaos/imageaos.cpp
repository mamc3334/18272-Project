//
// Created by finnb on 10/7/2024.
//
#include "imageaos.hpp"
#include "aossize.hpp"
#include "aoscompress.hpp"
#include "aosinfrequentcolor.hpp"
#include "utility.hpp"
#include "KDTree.hpp"
#include <vector>
#include <iostream>
#include <sys/stat.h>
using namespace std;

/* This is the general function that handles both cases for aosresize using the input of the new width and height
 */
void aos_resize(Image_Attributes& newImageData)
{
    // open input image
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    // read input image metadata
    const Image_Attributes oldImageData = get_image_metadata(imageFile);
    //open output stream
    ofstream outputImageFile(getOutFile());
    if(!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }
    //set new image metadata that is unchanged from user input
    newImageData.intensity = oldImageData.intensity;
    newImageData.magic_word = oldImageData.magic_word;
    //print metadata to output file
    outputImageFile << newImageData.magic_word << "\n" << newImageData.width << " " << newImageData.height << "\n" << newImageData.intensity << "\n";
    if(newImageData.intensity > IntensityCutoff)
    {
        //r,g,b represented by uint16_t
        vector<vector<bigColor>> oldPhoto(oldImageData.height, vector<bigColor>(oldImageData.width));
        //read input image
        aossize_old_photo_16(oldPhoto, oldImageData, imageFile);
        //resize image and print output
        aossize_resize_16(oldPhoto, oldImageData, newImageData, outputImageFile);
    }
    else
    {
        //r,g,b represented by uint8_t
        vector<vector<smallColor>> sOldPhoto(oldImageData.height, vector<smallColor>(oldImageData.width));
        //read input image
        aossize_old_photo_8(sOldPhoto, oldImageData, imageFile);
        //resize image and print output
        aossize_resize_8(sOldPhoto, oldImageData, newImageData, outputImageFile);
    }
}

void aos_cutfreq(size_t num) {
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes photoData = get_image_metadata(imageFile);

    ofstream outputImageFile(getOutFile());
    if(!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }
    outputImageFile << photoData.magic_word << "\n" << photoData.width << " " << photoData.height << "\n" << photoData.intensity << "\n";

    if(photoData.intensity > IntensityCutoff){
        vector<bigColor> pixels;
        populatePixels_16(pixels, photoData, imageFile);
        changeInfrequentColors_16(pixels, num);
        writeBinary_16(pixels, outputImageFile);
    }
    else{
        vector<smallColor> pixels;
        populatePixels_8(pixels, photoData, imageFile);
        changeInfrequentColors_8(pixels, num);
        writeBinary_8(pixels, outputImageFile);
    }
}

void aos_compress()
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    ofstream outputImageFile(getOutFile());
    if(!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }

    compress(imageFile, outputImageFile);
    /* TODO: Compress
        * maybe similar to cutfreq
        *
     */
}