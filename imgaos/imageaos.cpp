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