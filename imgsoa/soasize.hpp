//
// Created by mcgaf on 10/25/2024.
//

#ifndef SOASIZE_HPP
#define SOASIZE_HPP

#include <fstream>
#include "soacommon.hpp"
#include "../common/utility.hpp"
using namespace std;

void soasize_old_image_16(bigArray& image, const Image_Attributes& OldImageData, ifstream& inFile);
void soasize_old_image_8(smallArray& image, const Image_Attributes& OldImageData, ifstream& inFile);

void soasize_resize_16(const bigArray& image, const Image_Attributes& OldImageData, const Image_Attributes& NewImageData, ofstream& outFile);
void soasize_resize_8(const smallArray& image, const Image_Attributes& OldImageData, const Image_Attributes& NewImageData, ofstream& outFile);

bigColor interpolate_16(const bigArray& image, const Coords& coords, float width);
smallColor interpolate_8(const smallArray& image, const Coords& coords, float width);

#endif //SOASIZE_HPP