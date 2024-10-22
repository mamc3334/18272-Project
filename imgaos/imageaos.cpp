//
// Created by finnb on 10/7/2024.
//
using namespace std;
#include <vector>
#include "imageaos.hpp"
#include <iostream>

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
        bigColor oldPhoto[][] = aossize_old_photo_16(metadata.height, metadata.width, imageFile);
        aossize_main(oldPhoto, );
    }
    else
    {
        smallColor oldPhoto[][] = aossize_old_photo_8(metadata.height, metadata.width, imageFile);
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