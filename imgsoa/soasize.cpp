//
// Created by mcgaf on 10/25/2024.
//

#include "soasize.hpp"
#include <cmath>
#include <sys/stat.h>
#include "../common/binaryio.hpp"

/* This function stores the binary data from the input ppm file into a struct of arrays representing r,g,b.
 * This function is for images with max intensity greater than 255 thus requiring two bytes per color.
 * Inputs:
 *    image is the struct passed by reference to store the input image
 *    OldPhotoData is the struct that contains the metadata of the input image
 *    inFile is the input ppm file that contains the binary data containing the pixel information
 */
void soasize_old_image_16(bigArray& image, const Image_Attributes& OldImageData, ifstream& inFile)
{
    unsigned int count=0;
    while(count<OldImageData.height*OldImageData.width){
        image.r.push_back(BINARY::read_binary16(inFile));
        image.g.push_back(BINARY::read_binary16(inFile));
        image.b.push_back(BINARY::read_binary16(inFile));
        count++;
    }
    inFile.close();
}

/* This function stores the binary data from the input ppm file into a struct of arrays representing r,g,b.
 * This function is for images with max intensity less than 255 thus requiring one byte per color.
 * Inputs:
 *    image is the struct passed by reference to store the input image
 *    OldPhotoData is the struct that contains the metadata of the input image
 *    inFile is the input ppm file that contains the binary data containing the pixel information
 */
void soasize_old_image_8(smallArray& image, const Image_Attributes& OldImageData, ifstream& inFile)
{
    unsigned int count=0;
    while(count<OldImageData.height*OldImageData.width){
        image.r.push_back(BINARY::read_binary8(inFile));
        image.g.push_back(BINARY::read_binary8(inFile));
        image.b.push_back(BINARY::read_binary8(inFile));
        count++;
    }
    inFile.close();
}

/* This function completes the primary object of the resize capability.
 * This function is for images with max intensity greater than 255 thus requiring two bytes per color.
 * Inputs:
 *    image is the struct populated with the input image data.
 *    OldPhotoData is the struct that contains the metadata of the input image.
 *    NewPhotoData is the struct that contains the metadata of the new resized image.
 *    outFile is the file stream where the resized data will be printed to as the resize process occurs
 */
void soasize_resize_16(const bigArray& image, const Image_Attributes& OldImageData, const Image_Attributes& NewImageData, ofstream& outFile)
{
    for(unsigned int i = 0; i < NewImageData.height; i++) {
      // map y-coord or row
        const float y_map = static_cast<float>(i)*static_cast<float>(OldImageData.height-1)/static_cast<float>(NewImageData.height-1);
        const float y_lo = floor(y_map);
        const float y_hi = ceil(y_map);
        for(unsigned int j = 0; j < NewImageData.width; j++) {
            // map x-coord or col
            const float x_map= static_cast<float>(j)*static_cast<float>(OldImageData.width-1)/static_cast<float>(NewImageData.width-1);
            const float x_lo = floor(x_map);
            const float x_hi = ceil(x_map);
            const Coords coords = {.x_map=x_map, .x_lo=x_lo, .x_hi=x_hi, .y_map=y_map, .y_lo=y_lo, .y_hi=y_hi};
            // generate new pixel using bilinear interpolation of 4 nearest pixels.
            const bigColor pixel = interpolate_16(image, coords, static_cast<float>(OldImageData.width));
            BINARY::write_binary16(outFile, pixel.r);
            BINARY::write_binary16(outFile, pixel.g);
            BINARY::write_binary16(outFile, pixel.b);
        }
    }
    outFile.close();
}

/* This function completes the primary object of the resize capability.
 * This function is for images with max intensity less than 255 thus requiring one byte per color.
 * Inputs:
 *    image is the struct populated with the input image data.
 *    OldPhotoData is the struct that contains the metadata of the input image.
 *    NewPhotoData is the struct that contains the metadata of the new resized image.
 *    outFile is the file stream where the resized data will be printed to as the resize process occurs
 */
void soasize_resize_8(const smallArray& image, const Image_Attributes& OldImageData, const Image_Attributes& NewImageData, ofstream& outFile)
{
    for(unsigned int i = 0; i < NewImageData.height; i++){
        // map y coord or row
        const float y_map= static_cast<float>(i)*static_cast<float>(OldImageData.height-1)/static_cast<float>(NewImageData.height-1);
        const float y_lo = floor(y_map);
        const float y_hi = ceil(y_map);
        for(unsigned int j = 0; j < NewImageData.width; j++){
            // map x coord or col
            const float x_map= static_cast<float>(j)*static_cast<float>(OldImageData.width-1)/static_cast<float>(NewImageData.width-1);
            const float x_lo = floor(x_map);
            const float x_hi = ceil(x_map);
            const Coords coords = {.x_map=x_map, .x_lo=x_lo, .x_hi=x_hi, .y_map=y_map, .y_lo=y_lo, .y_hi=y_hi};
            // generate new pixel using bilinear interpolation
            const smallColor pixel = interpolate_8(image, coords, static_cast<float>(OldImageData.width));
            BINARY::write_binary8(outFile, pixel.r);
            BINARY::write_binary8(outFile, pixel.g);
            BINARY::write_binary8(outFile, pixel.b);
        }
    }
    outFile.close();
}

/* This function uses bilinear interpolation to calculate the new RGB intensities for a pixel
 * This function is for images with max intensity greater than 255 thus requiring two bytes per color.
 * Inputs:
 *    pixelArray is the 2D vector populated with the input image data.
 *    coords is the struct that contains floats for the location of the mapped location and surrounding pixels.
 */
bigColor interpolate_16(const bigArray& image, const Coords& coords, const float width)
{
    // used for weighting the distance from the mapped spot to the nearest pixels
    const float frac_x = coords.x_map - coords.x_lo;
    const float frac_y = coords.y_map - coords.y_lo;

    //bilinear interpolation of red
    const uint16_t redTL = image.r[static_cast<unsigned int>(coords.x_lo+(coords.y_lo*width))];
    const uint16_t redTR = image.r[static_cast<unsigned int>(coords.x_hi+(coords.y_lo*width))];
    const uint16_t redBL = image.r[static_cast<unsigned int>(coords.x_lo+(coords.y_hi*width))];
    const uint16_t redBR = image.r[static_cast<unsigned int>(coords.x_hi+(coords.y_hi*width))];
    const float redTop = (static_cast<float>(redTL)*(1-frac_x)) + (static_cast<float>(redTR)*(frac_x));
    const float redBot = (static_cast<float>(redBL)*(1-frac_x)) + (static_cast<float>(redBR)*(frac_x));
    const auto redFin = static_cast<uint16_t>(round((redTop*(1-frac_y)) + (redBot*(frac_y))));

    //bilinear interpolation of green
    const uint16_t greenTL = image.g[static_cast<unsigned int>(coords.x_lo+(coords.y_lo*width))];
    const uint16_t greenTR = image.g[static_cast<unsigned int>(coords.x_hi+(coords.y_lo*width))];
    const uint16_t greenBL = image.g[static_cast<unsigned int>(coords.x_lo+(coords.y_hi*width))];
    const uint16_t greenBR = image.g[static_cast<unsigned int>(coords.x_hi+(coords.y_hi*width))];
    const float greenTop = (static_cast<float>(greenTL)*(1-frac_x)) + (static_cast<float>(greenTR)*(frac_x));
    const float greenBot = (static_cast<float>(greenBL)*(1-frac_x)) + (static_cast<float>(greenBR)*(frac_x));
    const auto greenFin = static_cast<uint16_t>(round((greenTop*(1-frac_y)) + (greenBot*(frac_y))));

    //bilinear interpolation of blue
    const uint16_t blueTL = image.b[static_cast<unsigned int>(coords.x_lo+(coords.y_lo*width))];
    const uint16_t blueTR = image.b[static_cast<unsigned int>(coords.x_hi+(coords.y_lo*width))];
    const uint16_t blueBL = image.b[static_cast<unsigned int>(coords.x_lo+(coords.y_hi*width))];
    const uint16_t blueBR = image.b[static_cast<unsigned int>(coords.x_hi+(coords.y_hi*width))];
    const float blueTop = (static_cast<float>(blueTL)*(1-frac_x)) + (static_cast<float>(blueTR)*(frac_x));
    const float blueBot = (static_cast<float>(blueBL)*(1-frac_x)) + (static_cast<float>(blueBR)*(frac_x));
    const auto blueFin = static_cast<uint16_t>(round((blueTop*(1-frac_y)) + (blueBot*(frac_y))));

    return {.r=redFin,.g=greenFin,.b=blueFin};
}

/* This function uses bilinear interpolation to calculate the new RGB intensities for a pixel
 * This function is for images with max intensity less than 255 thus requiring one byte per color.
 * Inputs:
 *    pixelArray is the 2D vector populated with the input image data.
 *    coords is the struct that contains floats for the location of the mapped location and surrounding pixels.
 */
smallColor interpolate_8(const smallArray& image, const Coords& coords, const float width)
{
    // used for weighting the distance from the mapped spot to the nearest pixels
    const float frac_x = coords.x_map - coords.x_lo;
    const float frac_y = coords.y_map - coords.y_lo;

    //bilinear interpolation of red
    const uint8_t redTL = image.r[static_cast<unsigned int>(coords.x_lo+(coords.y_lo*width))];
    const uint8_t redTR = image.r[static_cast<unsigned int>(coords.x_hi+(coords.y_lo*width))];
    const uint8_t redBL = image.r[static_cast<unsigned int>(coords.x_lo+(coords.y_hi*width))];
    const uint8_t redBR = image.r[static_cast<unsigned int>(coords.x_hi+(coords.y_hi*width))];
    const float redTop = (static_cast<float>(redTL)*(1-frac_x)) + (static_cast<float>(redTR)*(frac_x));
    const float redBot = (static_cast<float>(redBL)*(1-frac_x)) + (static_cast<float>(redBR)*(frac_x));
    const auto redFin = static_cast<uint8_t>(round((redTop*(1-frac_y)) + (redBot*(frac_y))));

    //bilinear interpolation of green
    const uint8_t greenTL = image.g[static_cast<unsigned int>(coords.x_lo+(coords.y_lo*width))];
    const uint8_t greenTR = image.g[static_cast<unsigned int>(coords.x_hi+(coords.y_lo*width))];
    const uint8_t greenBL = image.g[static_cast<unsigned int>(coords.x_lo+(coords.y_hi*width))];
    const uint8_t greenBR = image.g[static_cast<unsigned int>(coords.x_hi+(coords.y_hi*width))];
    const float greenTop = (static_cast<float>(greenTL)*(1-frac_x)) + (static_cast<float>(greenTR)*(frac_x));
    const float greenBot = (static_cast<float>(greenBL)*(1-frac_x)) + (static_cast<float>(greenBR)*(frac_x));
    const auto greenFin = static_cast<uint8_t>(round((greenTop*(1-frac_y)) + (greenBot*(frac_y))));

    //bilinear interpolation of blue
    const uint8_t blueTL = image.b[static_cast<unsigned int>(coords.x_lo+(coords.y_lo*width))];
    const uint8_t blueTR = image.b[static_cast<unsigned int>(coords.x_hi+(coords.y_lo*width))];
    const uint8_t blueBL = image.b[static_cast<unsigned int>(coords.x_lo+(coords.y_hi*width))];
    const uint8_t blueBR = image.b[static_cast<unsigned int>(coords.x_hi+(coords.y_hi*width))];
    const float blueTop = (static_cast<float>(blueTL)*(1-frac_x)) + (static_cast<float>(blueTR)*(frac_x));
    const float blueBot = (static_cast<float>(blueBL)*(1-frac_x)) + (static_cast<float>(blueBR)*(frac_x));
    const auto blueFin = static_cast<uint8_t>(round((blueTop*(1-frac_y)) + (blueBot*(frac_y))));

    return {.r=redFin,.g=greenFin,.b=blueFin};
}