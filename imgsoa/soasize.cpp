//
// Created by mcgaf on 10/25/2024.
//

#include "soasize.hpp"
#include <cmath>
#include <sys/stat.h>
#include "../common/binaryio.hpp"

void soasize_old_photo_16(bigArray& photo, const unsigned int size, ifstream& inFile)
{
    int count=0;
    while(count<size){
        photo.r.push_back(read_binary16(inFile));
        photo.g.push_back(read_binary16(inFile));
        photo.b.push_back(read_binary16(inFile));
        count++;
    }
}

void soasize_old_photo_8(smallArray& photo, const unsigned int size, ifstream& inFile)
{
    int count=0;
    while(count<size){
        photo.r.push_back(read_binary8(inFile));
        photo.g.push_back(read_binary8(inFile));
        photo.b.push_back(read_binary8(inFile));
        count++;
    }
}

void soasize_resize_16(const bigArray& photo, const int oRows, const int oCols, const int nRows, const int nCols, ofstream& outFile)
{
    for(int i = 0; i < nRows; i++)
    {
        const float y_new = static_cast<float>(i)*static_cast<float>(oRows)/static_cast<float>(nRows);
        const float y_low = floor(y_new);
        const float y_hi = ceil(y_new);
        for(int j = 0; j < nCols; j++)
        {
            const float x_new= static_cast<float>(j)*static_cast<float>(oCols)/static_cast<float>(nCols);
            const float x_low = floor(x_new);
            const float x_hi = ceil(x_new);
            const bigColor pixel = interpolate_16(photo,x_new,y_new,x_low,x_hi,y_low,y_hi);
            write_binary16(outFile, pixel.r);
            write_binary16(outFile, pixel.g);
            write_binary16(outFile, pixel.b);
        }
    }
}

void soasize_resize_8(const smallArray& photo, const int oRows, const int oCols, const int nRows, const int nCols, ofstream& outFile)
{
    for(int i = 0; i < nRows; i++){
        const float y_new= static_cast<float>(i)*static_cast<float>(oRows)/static_cast<float>(nRows);
        const float y_low = floor(y_new);
        const float y_hi = ceil(y_new);
        for(int j = 0; j < nCols; j++){
            const float x_new= static_cast<float>(j)*static_cast<float>(oCols)/static_cast<float>(nCols);
            const float x_low = floor(x_new);
            const float x_hi = ceil(x_new);
            const smallColor pixel = interpolate_8(photo,x_new,y_new,x_low,x_hi,y_low,y_hi);
            write_binary8(outFile, pixel.r);
            write_binary8(outFile, pixel.g);
            write_binary8(outFile, pixel.b);
        }
    }
}

bigColor interpolate_16(const bigArray & photo, const float x_new, const float y_new, const float x_low, const float x_hi, const float y_low, const float y_hi)
{
    const uint16_t redTL = photo.r[static_cast<unsigned int>(x_low*y_low)];
    const uint16_t redTR = photo.r[static_cast<unsigned int>(x_hi*y_low)];
    const uint16_t redBL = photo.r[static_cast<unsigned int>(x_low*y_hi)];
    const uint16_t redBR = photo.r[static_cast<unsigned int>(x_hi*y_hi)];
    const float redTop = (redTL*(x_new-x_low)) + (redTR*(x_hi-x_new));
    const float redBot = (redBL*(x_new-x_low)) + (redBR*(x_hi-x_new));
    const auto redFin = static_cast<uint16_t>((redTop*(y_new-y_low)) + (redBot*(y_hi-y_new)));
    const uint16_t greenTL = photo.g[static_cast<unsigned int>(x_low*y_low)];
    const uint16_t greenTR = photo.g[static_cast<unsigned int>(x_hi*y_low)];
    const uint16_t greenBL = photo.g[static_cast<unsigned int>(x_low*y_hi)];
    const uint16_t greenBR = photo.g[static_cast<unsigned int>(x_hi*y_hi)];
    const float greenTop = (greenTL*(x_new-x_low)) + (greenTR*(x_hi-x_new));
    const float greenBot = (greenBL*(x_new-x_low)) + (greenBR*(x_hi-x_new));
    const auto greenFin = static_cast<uint16_t>((greenTop*(y_new-y_low)) + (greenBot*(y_hi-y_new)));
    const uint16_t blueTL = photo.b[static_cast<unsigned int>(x_low*y_low)];
    const uint16_t blueTR = photo.b[static_cast<unsigned int>(x_hi*y_low)];
    const uint16_t blueBL = photo.b[static_cast<unsigned int>(x_low*y_hi)];
    const uint16_t blueBR = photo.b[static_cast<unsigned int>(x_hi*y_hi)];
    const float blueTop = (blueTL*(x_new-x_low)) + (blueTR*(x_hi-x_new));
    const float blueBot = (blueBL*(x_new-x_low)) + (blueBR*(x_hi-x_new));
    const auto blueFin = static_cast<uint16_t>((blueTop*(y_new-y_low)) + (blueBot*(y_hi-y_new)));
    return {.r=redFin,.g=greenFin,.b=blueFin};
}

smallColor interpolate_8(const smallArray & photo, const float x_new, const float y_new, const float x_low, const float x_hi, const float y_low, float y_hi)
{
    const uint8_t redTL = photo.r[static_cast<unsigned int>(x_low*y_low)];
    const uint8_t redTR = photo.r[static_cast<unsigned int>(x_hi*y_low)];
    const uint8_t redBL = photo.r[static_cast<unsigned int>(x_low*y_hi)];
    const uint8_t redBR = photo.r[static_cast<unsigned int>(x_hi*y_hi)];
    const float redTop = (redTL*(x_new-x_low)) + (redTR*(x_hi-x_new));
    const float redBot = (redBL*(x_new-x_low)) + (redBR*(x_hi-x_new));
    const auto redFin = static_cast<uint8_t>((redTop*(y_new-y_low)) + (redBot*(y_hi-y_new)));
    const uint8_t greenTL = photo.g[static_cast<unsigned int>(x_low*y_low)];
    const uint8_t greenTR = photo.g[static_cast<unsigned int>(x_hi*y_low)];
    const uint8_t greenBL = photo.g[static_cast<unsigned int>(x_low*y_hi)];
    const uint8_t greenBR = photo.g[static_cast<unsigned int>(x_hi*y_hi)];
    const float greenTop = (greenTL*(x_new-x_low)) + (greenTR*(x_hi-x_new));
    const float greenBot = (greenBL*(x_new-x_low)) + (greenBR*(x_hi-x_new));
    const auto greenFin = static_cast<uint8_t>((greenTop*(y_new-y_low)) + (greenBot*(y_hi-y_new)));
    const uint8_t blueTL = photo.b[static_cast<unsigned int>(x_low*y_low)];
    const uint8_t blueTR = photo.b[static_cast<unsigned int>(x_hi*y_low)];
    const uint8_t blueBL = photo.b[static_cast<unsigned int>(x_low*y_hi)];
    const uint8_t blueBR = photo.b[static_cast<unsigned int>(x_hi*y_hi)];
    const float blueTop = (blueTL*(x_new-x_low)) + (blueTR*(x_hi-x_new));
    const float blueBot = (blueBL*(x_new-x_low)) + (blueBR*(x_hi-x_new));
    const auto blueFin = static_cast<uint8_t>((blueTop*(y_new-y_low)) + (blueBot*(y_hi-y_new)));
    return {.r=redFin,.g=greenFin,.b=blueFin};
}