//
// Created by mcgaf on 10/25/2024.
//

#include "soasize.hpp"
#include <cmath>
#include <sys/stat.h>
#include "../common/binaryio.hpp"

void soasize_old_image_16(bigArray& image, const Image_Attributes& OldImageData, ifstream& inFile)
{
    int count=0;
    while(count<OldImageData.height*OldImageData.width){
        image.r.push_back(read_binary16(inFile));
        image.g.push_back(read_binary16(inFile));
        image.b.push_back(read_binary16(inFile));
        count++;
    }
}

void soasize_old_image_8(smallArray& image, const Image_Attributes& OldImageData, ifstream& inFile)
{
    int count=0;
    while(count<OldImageData.height*OldImageData.width){
        image.r.push_back(read_binary8(inFile));
        image.g.push_back(read_binary8(inFile));
        image.b.push_back(read_binary8(inFile));
        count++;
    }
}

void soasize_resize_16(const bigArray& image, const Image_Attributes& OldImageData, const Image_Attributes& NewImageData, ofstream& outFile)
{
    for(int i = 0; i < NewImageData.height; i++)
    {
        const float y_map = static_cast<float>(i)*static_cast<float>(OldImageData.height)/static_cast<float>(NewImageData.height);
        const float y_lo = floor(y_map);
        const float y_hi = ceil(y_map);
        for(int j = 0; j < NewImageData.width; j++)
        {
            const float x_map= static_cast<float>(j)*static_cast<float>(OldImageData.width)/static_cast<float>(NewImageData.width);
            const float x_lo = floor(x_map);
            const float x_hi = ceil(x_map);
            const Coords coords = {.x_map=x_map, .x_lo=x_lo, .x_hi=x_hi, .y_map=y_map, .y_lo=y_lo, .y_hi=y_hi};
            const bigColor pixel = interpolate_16(image, coords);
            write_binary16(outFile, pixel.r);
            write_binary16(outFile, pixel.g);
            write_binary16(outFile, pixel.b);
        }
    }
}

void soasize_resize_8(const smallArray& image, const Image_Attributes& OldImageData, const Image_Attributes& NewImageData, ofstream& outFile)
{
    for(int i = 0; i < NewImageData.height; i++){
        const float y_map= static_cast<float>(i)*static_cast<float>(OldImageData.height)/static_cast<float>(NewImageData.height);
        const float y_lo = floor(y_map);
        const float y_hi = ceil(y_map);
        for(int j = 0; j < NewImageData.width; j++){
            const float x_map= static_cast<float>(j)*static_cast<float>(OldImageData.width)/static_cast<float>(NewImageData.width);
            const float x_lo = floor(x_map);
            const float x_hi = ceil(x_map);
            const Coords coords = {.x_map=x_map, .x_lo=x_lo, .x_hi=x_hi, .y_map=y_map, .y_lo=y_lo, .y_hi=y_hi};
            const smallColor pixel = interpolate_8(image, coords);
            write_binary8(outFile, pixel.r);
            write_binary8(outFile, pixel.g);
            write_binary8(outFile, pixel.b);
        }
    }
}

bigColor interpolate_16(const bigArray& image, const Coords& coords)
{
    const float frac_x = coords.x_map - coords.x_lo;
    const float frac_y = coords.y_map - coords.y_lo;
    const uint16_t redTL = image.r[static_cast<unsigned int>(coords.x_lo*coords.y_lo)];
    const uint16_t redTR = image.r[static_cast<unsigned int>(coords.x_hi*coords.y_lo)];
    const uint16_t redBL = image.r[static_cast<unsigned int>(coords.x_lo*coords.y_hi)];
    const uint16_t redBR = image.r[static_cast<unsigned int>(coords.x_hi*coords.y_hi)];
    const float redTop = (redTL*(1-frac_x)) + (redTR*(frac_x));
    const float redBot = (redBL*(1-frac_x)) + (redBR*(frac_x));
    const auto redFin = static_cast<uint16_t>((redTop*(1-frac_y)) + (redBot*(frac_y)));
    const uint16_t greenTL = image.g[static_cast<unsigned int>(coords.x_lo*coords.y_lo)];
    const uint16_t greenTR = image.g[static_cast<unsigned int>(coords.x_hi*coords.y_lo)];
    const uint16_t greenBL = image.g[static_cast<unsigned int>(coords.x_lo*coords.y_hi)];
    const uint16_t greenBR = image.g[static_cast<unsigned int>(coords.x_hi*coords.y_hi)];
    const float greenTop = (greenTL*(1-frac_x)) + (greenTR*(frac_x));
    const float greenBot = (greenBL*(1-frac_x)) + (greenBR*(frac_x));
    const auto greenFin = static_cast<uint16_t>((greenTop*(1-frac_y)) + (greenBot*(frac_y)));
    const uint16_t blueTL = image.b[static_cast<unsigned int>(coords.x_lo*coords.y_lo)];
    const uint16_t blueTR = image.b[static_cast<unsigned int>(coords.x_hi*coords.y_lo)];
    const uint16_t blueBL = image.b[static_cast<unsigned int>(coords.x_lo*coords.y_hi)];
    const uint16_t blueBR = image.b[static_cast<unsigned int>(coords.x_hi*coords.y_hi)];
    const float blueTop = (blueTL*(1-frac_x)) + (blueTR*(frac_x));
    const float blueBot = (blueBL*(1-frac_x)) + (blueBR*(frac_x));
    const auto blueFin = static_cast<uint16_t>((blueTop*(1-frac_y)) + (blueBot*(frac_y)));
    return {.r=redFin,.g=greenFin,.b=blueFin};
}

smallColor interpolate_8(const smallArray& image, const Coords& coords)
{
    const float frac_x = coords.x_map - coords.x_lo;
    const float frac_y = coords.y_map - coords.y_lo;
    const uint8_t redTL = image.r[static_cast<unsigned int>(coords.x_lo*coords.y_lo)];
    const uint8_t redTR = image.r[static_cast<unsigned int>(coords.x_hi*coords.y_lo)];
    const uint8_t redBL = image.r[static_cast<unsigned int>(coords.x_lo*coords.y_hi)];
    const uint8_t redBR = image.r[static_cast<unsigned int>(coords.x_hi*coords.y_hi)];
    const float redTop = (redTL*(1-frac_x)) + (redTR*(frac_x));
    const float redBot = (redBL*(1-frac_x)) + (redBR*(frac_x));
    const auto redFin = static_cast<uint8_t>((redTop*(1-frac_y)) + (redBot*(frac_y)));
    const uint8_t greenTL = image.g[static_cast<unsigned int>(coords.x_lo*coords.y_lo)];
    const uint8_t greenTR = image.g[static_cast<unsigned int>(coords.x_hi*coords.y_lo)];
    const uint8_t greenBL = image.g[static_cast<unsigned int>(coords.x_lo*coords.y_hi)];
    const uint8_t greenBR = image.g[static_cast<unsigned int>(coords.x_hi*coords.y_hi)];
    const float greenTop = (greenTL*(1-frac_x)) + (greenTR*(frac_x));
    const float greenBot = (greenBL*(1-frac_x)) + (greenBR*(frac_x));
    const auto greenFin = static_cast<uint8_t>((greenTop*(1-frac_y)) + (greenBot*(frac_y)));
    const uint8_t blueTL = image.b[static_cast<unsigned int>(coords.x_lo*coords.y_lo)];
    const uint8_t blueTR = image.b[static_cast<unsigned int>(coords.x_hi*coords.y_lo)];
    const uint8_t blueBL = image.b[static_cast<unsigned int>(coords.x_lo*coords.y_hi)];
    const uint8_t blueBR = image.b[static_cast<unsigned int>(coords.x_hi*coords.y_hi)];
    const float blueTop = (blueTL*(1-frac_x)) + (blueTR*(frac_x));
    const float blueBot = (blueBL*(1-frac_x)) + (blueBR*(frac_x));
    const auto blueFin = static_cast<uint8_t>((blueTop*(1-frac_y)) + (blueBot*(frac_y)));
    return {.r=redFin,.g=greenFin,.b=blueFin};
}