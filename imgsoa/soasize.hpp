//
// Created by mcgaf on 10/25/2024.
//

#ifndef SOASIZE_HPP
#define SOASIZE_HPP

#include <fstream>
#include "soacommon.hpp"
#include "../common/binaryio.hpp"
#include "../common/utility.hpp"
using namespace std;

void soasize_old_photo_16(bigArray& photo, unsigned int size, ifstream& inFile);
void soasize_old_photo_8(smallArray& photo, unsigned int size, ifstream& inFile);

void soasize_resize_16(bigArray photo, unsigned int oRows, unsigned int oCols, int nRows, int nCols, ofstream& outFile);
void soasize_resize_8(smallArray photo, unsigned int oRows, unsigned int oCols, int nRows, int nCols, ofstream& outFile);

bigColor interpolate_16(bigArray photo, float x, float y, float xl, float xh, float yl, float yh);
smallColor interpolate_8(smallArray photo, float x, float y, float xl, float xh, float yl, float yh);

#endif //SOASIZE_HPP