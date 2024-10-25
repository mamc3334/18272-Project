//
// Created by mcgaf on 10/25/2024.
//

#include "soasize.hpp"
void soasize_old_photo_16(photo16& photo, int rows, int cols, ifstream& inFile)
{
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            photo.r.push_back(read_binary16(inFile));
            photo.g.push_back(read_binary16(inFile));
            photo.b.push_back(read_binary16(inFile));
        }
    }
}

void soasize_old_photo_8(photo8& photo, int rows, int cols, ifstream& inFile)
{
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            photo.r.push_back(read_binary8(inFile));
            photo.g.push_back(read_binary8(inFile));
            photo.b.push_back(read_binary8(inFile));
        }
    }
}

photo16 size_resize_16(photo16 photo, int oRows, int oCols, int nRows, int nCols, ofstream& outFile)
{

}

photo8 size_resize_8(photo8 photo, int oRows, int oCols, int nRows, int nCols, ofstream& outFile)
{

}

tuple<uint16_t,uint16_t,uint16_t> interpolate_16(photo16 photo, double x, double y, double xl, double xh, double yl, double yh)
{

}

tuple<uint16_t,uint16_t,uint16_t> interpolate_8(photo8 photo, double x, double y, double xl, double xh, double yl, double yh)
{

}