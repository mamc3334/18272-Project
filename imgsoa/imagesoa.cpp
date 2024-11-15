//
// Created by finnb on 10/7/2024.
//
#include "imagesoa.hpp"
#include <vector>
#include <iostream>
using namespace std;

/* This is the general function that handles both cases for the soaresize using the input of the new width and height
*/
void soa_resize(Image_Attributes& NewImageData)
{
    // open input image
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    // read input image metadata
    const Image_Attributes OldImageData = get_image_metadata(imageFile);
    //open output stream
    ofstream outputImageFile(getOutFile());
    if(!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }
    //set new image metadata that is unchanged from user input
    NewImageData.magic_word = OldImageData.magic_word;
    NewImageData.intensity = OldImageData.intensity;
    //print metadata to output file
    outputImageFile << NewImageData.magic_word << "\n" << NewImageData.width << " " << NewImageData.height << "\n" << NewImageData.intensity << "\n";
    if(NewImageData.intensity > IntensityCutoff)
    {
        //r,g,b represented by uint16_t
        bigArray oldImage;
        //read input image
        soasize_old_image_16(oldImage, OldImageData, imageFile);
        //resize image and print output
        soasize_resize_16(oldImage, OldImageData, NewImageData, outputImageFile);
    }
    else
    {
        //r,g,b represented by uint8_t
        smallArray oldImage;
        //read input image
        soasize_old_image_8(oldImage, OldImageData, imageFile);
        //resize image and print output
        soasize_resize_8(oldImage, OldImageData, NewImageData, outputImageFile);
    }
}

void soa_cutfreq(size_t num) {
    ifstream imageFile(getInFile());
    if (!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes photoData = get_image_metadata(imageFile);

    ofstream outputImageFile(getOutFile());
    if (!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }
    outputImageFile << photoData.magic_word << "\n" << photoData.width << " " << photoData.height << "\n" << photoData.intensity << "\n";

    if (photoData.intensity > IntensityCutoff) {
        SoA_16 pixels;
        populatePixels_16(pixels, photoData, imageFile);
        changeInfrequentColors_16(pixels, num);
        writeBinary_16(pixels, outputImageFile);
    } else {
        SoA_8 pixels;
        populatePixels_8(pixels, photoData, imageFile);
        changeInfrequentColors_8(pixels, num);
        writeBinary_8(pixels, outputImageFile);
    }
}




void soa_compress() {
  //TODO
}
