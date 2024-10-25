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

void soasize_old_photo_16(photo16& photo, int rows, int cols, ifstream& inFile);
void soasize_old_photo_8(photo8& photo, int rows, int cols, ifstream& inFile);

photo16 size_resize_16(photo16 photo, int oRows, int oCols, int nRows, int nCols, ofstream& outFile);
photo8 size_resize_8(photo8 photo, int oRows, int oCols, int nRows, int nCols, ofstream& outFile);

tuple<uint16_t,uint16_t,uint16_t> interpolate_16(photo16 photo, double x, double y, double xl, double xh, double yl, double yh);
tuple<uint16_t,uint16_t,uint16_t> interpolate_8(photo8 photo, double x, double y, double xl, double xh, double yl, double yh);

#endif //SOASIZE_HPP