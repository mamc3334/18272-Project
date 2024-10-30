//
// Created by mcgaf on 10/25/2024.
//

#include "soasize.hpp"
#include <cmath>
#include <sys/stat.h>

void soasize_old_photo_16(bigArray& photo, unsigned int size, ifstream& inFile)
{
    unsigned int i=0;
    while(i<size){
        photo.r.push_back(read_binary16(inFile));
        photo.g.push_back(read_binary16(inFile));
        photo.b.push_back(read_binary16(inFile));
        i++;
    }
}

void soasize_old_photo_8(smallArray& photo, unsigned int size, ifstream& inFile)
{
    unsigned int i=0;
    while(i<size){
            photo.r.push_back(read_binary8(inFile));
            photo.g.push_back(read_binary8(inFile));
            photo.b.push_back(read_binary8(inFile));
    }
}

void soasize_resize_16(bigArray photo, int oRows, int oCols, int nRows, int nCols, ofstream& outFile)
{
    for(int i = 0; i < nRows; i++)
    {
        float y = static_cast<float>(i)*static_cast<float>(oRows)/static_cast<float>(nRows);
        float yl = floor(y);
        float yh = ceil(y);
        for(int j = 0; j < nCols; j++)
        {
            float x = static_cast<float>(j)*static_cast<float>(oCols)/static_cast<float>(nCols);
            float xl = floor(x);
            float xh = ceil(x);
            tuple<uint16_t, uint16_t, uint16_t> pixel = interpolate_16(photo,x,y,xl,xh,yl,yh);
            write_binary16(outFile, get<0>(pixel));
            write_binary16(outFile, get<1>(pixel));
            write_binary16(outFile, get<2>(pixel));
        }
    }
}

void soasize_resize_8(smallArray photo, int oRows, int oCols, int nRows, int nCols, ofstream& outFile)
{
    for(int i = 0; i < nRows; i++){
        float y = static_cast<float>(i)*static_cast<float>(oRows)/static_cast<float>(nRows);
        float yl = floor(y);
        float yh = ceil(y);
        for(int j = 0; j < nCols; j++){
            float x = static_cast<float>(j)*static_cast<float>(oCols)/static_cast<float>(nCols);
            float xl = floor(x);
            float xh = ceil(x);
            tuple<uint8_t, uint8_t, uint8_t> pixel = interpolate_8(photo,x,y,xl,xh,yl,yh);
            write_binary8(outFile, get<0>(pixel));
            write_binary8(outFile, get<1>(pixel));
            write_binary8(outFile, get<2>(pixel));
        }
    }
}

tuple<uint16_t, uint16_t, uint16_t> interpolate_16(bigArray photo, float x, float y, float xl, float xh, float yl, float yh)
{
    auto redTL = photo.r[static_cast<unsigned int>(xl*yl)];
    auto redTR = photo.r[static_cast<unsigned int>(xh*yl)];
    auto redBL = photo.r[static_cast<unsigned int>(xl*yh)];
    auto redBR = photo.r[static_cast<unsigned int>(xh*yh)];
    auto redTop = redTL*(x-xl) + redTR*(xh-x);
    auto redBot = redBL*(x-xl) + redBR*(xh-x);
    const uint16_t redFin = static_cast<uint16_t>(redTop*(y-yl) + redBot*(yh-y));
    auto greenTL = photo.g[static_cast<unsigned int>(xl*yl)];
    auto greenTR = photo.g[static_cast<unsigned int>(xh*yl)];
    auto greenBL = photo.g[static_cast<unsigned int>(xl*yh)];
    auto greenBR = photo.g[static_cast<unsigned int>(xh*yh)];
    auto greenTop = greenTL*(x-xl) + greenTR*(xh-x);
    auto greenBot = greenBL*(x-xl) + greenBR*(xh-x);
    const uint16_t greenFin = static_cast<uint16_t>(greenTop*(y-yl) + greenBot*(yh-y));
    auto blueTL = photo.b[static_cast<unsigned int>(xl*yl)];
    auto blueTR = photo.b[static_cast<unsigned int>(xh*yl)];
    auto blueBL = photo.b[static_cast<unsigned int>(xl*yh)];
    auto blueBR = photo.b[static_cast<unsigned int>(xh*yh)];
    auto blueTop = blueTL*(x-xl) + blueTR*(xh-x);
    auto blueBot = blueBL*(x-xl) + blueBR*(xh-x);
    const uint16_t blueFin = static_cast<uint16_t>(blueTop*(x-yl) + blueBot*(xh-y));
    return {redFin,greenFin,blueFin};
}

tuple<uint8_t, uint8_t, uint8_t> interpolate_8(smallArray photo, float x, float y, float xl, float xh, float yl, float yh)
{
    auto redTL = photo.r[static_cast<unsigned int>(xl*yl)];
    auto redTR = photo.r[static_cast<unsigned int>(xh*yl)];
    auto redBL = photo.r[static_cast<unsigned int>(xl*yh)];
    auto redBR = photo.r[static_cast<unsigned int>(xh*yh)];
    auto redTop = redTL*(x-xl) + redTR*(xh-x);
    auto redBot = redBL*(x-xl) + redBR*(xh-x);
    const uint8_t redFin = static_cast<uint8_t>(redTop*(y-yl) + redBot*(yh-y));
    auto greenTL = photo.g[static_cast<unsigned int>(xl*yl)];
    auto greenTR = photo.g[static_cast<unsigned int>(xh*yl)];
    auto greenBL = photo.g[static_cast<unsigned int>(xl*yh)];
    auto greenBR = photo.g[static_cast<unsigned int>(xh*yh)];
    auto greenTop = greenTL*(x-xl) + greenTR*(xh-x);
    auto greenBot = greenBL*(x-xl) + greenBR*(xh-x);
    const uint8_t greenFin = static_cast<uint8_t>(greenTop*(y-yl) + greenBot*(yh-y));
    auto blueTL = photo.b[static_cast<unsigned int>(xl*yl)];
    auto blueTR = photo.b[static_cast<unsigned int>(xh*yl)];
    auto blueBL = photo.b[static_cast<unsigned int>(xl*yh)];
    auto blueBR = photo.b[static_cast<unsigned int>(xh*yh)];
    auto blueTop = blueTL*(x-xl) + blueTR*(xh-x);
    auto blueBot = blueBL*(x-xl) + blueBR*(xh-x);
    const uint8_t blueFin = static_cast<uint8_t>(blueTop*(x-yl) + blueBot*(xh-y));
    return {redFin,greenFin,blueFin};
}