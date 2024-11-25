//
// Created by mcgaf on 10/20/2024.
//
#include "aossize.hpp"
#include "../common/binaryio.hpp"
#include <cmath>
#include <iostream>

using namespace std;

/* This function stores the binary data from the input ppm file into a 2D pixel array.
 * This function is for images with max intensity greater than 255 thus requiring two bytes per color.
 * Inputs:
 *    pixelArray is the 2D array passed by reference to store the input image
 *    OldPhotoData is the struct that contains the metadata of the input image
 *    inFile is the input ppm file that contains the binary data containing the pixel information
 */
void aossize_old_photo_16(vector<vector<bigColor>>& pixelArray, const Image_Attributes& OldPhotoData, ifstream& inFile)
{
    for(unsigned int i = 0; i < OldPhotoData.height; i++){
        for(unsigned int j = 0; j < OldPhotoData.width; j++){
            pixelArray[i][j]= {.r=BINARY::read_binary16(inFile), .g=BINARY::read_binary16(inFile), .b=BINARY::read_binary16(inFile)};
        }
    }
    //close input image file stream after reading
    inFile.close();
}

/* This function stores the binary data from the input ppm file into a 2D pixel array.
 * This function is for images with max intensity less than 255 thus requiring one byte per color.
 * Inputs:
 *    pixelArray is the 2D vector passed by reference to store the input image.
 *    OldPhotoData is the struct that contains the metadata of the input image.
 *    inFile is the input ppm file that contains the binary data containing the pixel information.
 */
void aossize_old_photo_8(vector<vector<smallColor>>& pixelArray, const Image_Attributes& OldPhotoData, ifstream& inFile)
{
    for(unsigned int i = 0; i < OldPhotoData.height; i++){
        for(unsigned int j = 0; j < OldPhotoData.width; j++){
            pixelArray[i][j]= {.r=BINARY::read_binary8(inFile), .g=BINARY::read_binary8(inFile), .b=BINARY::read_binary8(inFile)};
        }
    }
    //close input image file stream after reading
    inFile.close();
}

/* This function completes the primary object of the resize capability.
 * This function is for images with max intensity greater than 255 thus requiring two bytes per color.
 * Inputs:
 *    pixelArray is the 2D vector populated with the input image data.
 *    OldPhotoData is the struct that contains the metadata of the input image.
 *    NewPhotoData is the struct that contains the metadata of the new resized image.
 *    outFile is the file stream where the resized data will be printed to as the resize process occurs
 */
void aossize_resize_16(const vector<vector<bigColor>>& pixelArray, const Image_Attributes& OldPhotoData, const Image_Attributes& NewPhotoData, ofstream& outFile)
{
    for(unsigned int i = 0; i < NewPhotoData.height; i++)
    {
        // map y-coord or row
        const float y_map = static_cast<float>(i)*static_cast<float>(OldPhotoData.height-1)/static_cast<float>(NewPhotoData.height-1);
        const float y_lo = floor(y_map);
        const float y_hi = ceil(y_map);
        for(unsigned int j = 0; j < NewPhotoData.width; j++){
            // map x-coord or col
            const float x_map = static_cast<float>(j)*static_cast<float>(OldPhotoData.width-1)/static_cast<float>(NewPhotoData.width-1);
            const float x_lo = floor(x_map);
            const float x_hi = ceil(x_map);
            const Coords coords = {.x_map=x_map,.x_lo=x_lo,.x_hi=x_hi,.y_map=y_map,.y_lo=y_lo,.y_hi=y_hi};
            // generate new pixel using bilinear interpolation of 4 nearest pixels.
            const bigColor pixel = interpolate_16(pixelArray, coords);
            BINARY::write_binary16(outFile, pixel.r);
            BINARY::write_binary16(outFile, pixel.g);
            BINARY::write_binary16(outFile, pixel.b);
        }
    }
    //close output file stream after populating
    outFile.close();
}

/* This function completes the primary object of the resize capability.
 * This function is for images with max intensity less than 255 thus requiring one byte per color.
 * Inputs:
 *    pixelArray is the 2D vector populated with the input image data.
 *    OldPhotoData is the struct that contains the metadata of the input image.
 *    NewPhotoData is the struct that contains the metadata of the new resized image.
 *    outFile is the file stream where the resized data will be printed to as the resize process occurs
 */
void aossize_resize_8(const vector<vector<smallColor>>& pixelArray, const Image_Attributes& OldPhotoData, const Image_Attributes& NewPhotoData, ofstream& outFile)
{
    for(unsigned int i = 0; i < NewPhotoData.height; i++){
        // map y coord or row
        const float y_map = static_cast<float>(i)*static_cast<float>(OldPhotoData.height-1)/static_cast<float>(NewPhotoData.height-1);
        const float y_lo = floor(y_map);
        const float y_hi = ceil(y_map);
        for(unsigned int j = 0; j < NewPhotoData.width; j++){
            // map x coord or col
            const float x_map = static_cast<float>(j)*static_cast<float>(OldPhotoData.width-1)/static_cast<float>(NewPhotoData.width-1);
            const float x_lo = floor(x_map);
            const float x_hi = ceil(x_map);
            const Coords coords = {.x_map=x_map,.x_lo=x_lo,.x_hi=x_hi,.y_map=y_map,.y_lo=y_lo,.y_hi=y_hi};
            // generate new pixel using bilinear interpolation
            const smallColor pixel = interpolate_8(pixelArray, coords);
            BINARY::write_binary8(outFile, pixel.r);
            BINARY::write_binary8(outFile, pixel.g);
            BINARY::write_binary8(outFile, pixel.b);
        }
    }
    //close output file stream after populating
    outFile.close();
}

/* This function uses bilinear interpolation to calculate the new RGB intensities for a pixel
 * This function is for images with max intensity greater than 255 thus requiring two bytes per color.
 * Inputs:
 *    pixelArray is the 2D vector populated with the input image data.
 *    coords is the struct that contains floats for the location of the mapped location and surrounding pixels.
 */
bigColor interpolate_16(const vector<vector<bigColor>>& pixelArray, const Coords& coords)
{
  // used for weighting the distance from the mapped spot to the nearest pixels
  const float frac_x = coords.x_map - coords.x_lo;
  const float frac_y = coords.y_map - coords.y_lo;

  //find 4 closest pixels
  const bigColor pixelTL = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_lo)];
  const bigColor pixelTR = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_hi)];
  const bigColor pixelBL = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_lo)];
  const bigColor pixelBR = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_hi)];

  //first round of interpolation - x
  const float topR = (static_cast<float>(pixelTL.r)*(1-frac_x)) + (static_cast<float>(pixelTR.r)*frac_x);
  const float topG = (static_cast<float>(pixelTL.g)*(1-frac_x)) + (static_cast<float>(pixelTR.g)*frac_x);
  const float topB = (static_cast<float>(pixelTL.b)*(1-frac_x)) + (static_cast<float>(pixelTR.b)*frac_x);
  const float botR = (static_cast<float>(pixelBL.r)*(1-frac_x)) + (static_cast<float>(pixelBR.r)*frac_x);
  const float botG = (static_cast<float>(pixelBL.g)*(1-frac_x)) + (static_cast<float>(pixelBR.g)*frac_x);
  const float botB = (static_cast<float>(pixelBL.b)*(1-frac_x)) + (static_cast<float>(pixelBR.b)*frac_x);

  //Second round of interpolation - y
  const auto finalR = static_cast<uint16_t>(round((topR*(1-frac_y)) + (botR*frac_y)));
  const auto finalG = static_cast<uint16_t>(round((topG*(1-frac_y)) + (botG*frac_y)));
  const auto finalB = static_cast<uint16_t>(round((topB*(1-frac_y)) + (botB*frac_y)));

  return {.r=finalR, .g=finalG, .b=finalB};
}

/* This function uses bilinear interpolation to calculate the new RGB intensities for a pixel
 * This function is for images with max intensity less than 255 thus requiring one byte per color.
 * Inputs:
 *    pixelArray is the 2D vector populated with the input image data.
 *    coords is the struct that contains floats for the location of the mapped location and surrounding pixels.
 */
smallColor interpolate_8(const vector<vector<smallColor>>& pixelArray, const Coords& coords)
{
  // used for weighting the distance from the mapped spot to the nearest pixels
  const float frac_x = coords.x_map - coords.x_lo;
  const float frac_y = coords.y_map - coords.y_lo;

  //find 4 closet pixels
  const smallColor pixelTL = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_lo)];
  const smallColor pixelTR = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_hi)];
  const smallColor pixelBL = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_lo)];
  const smallColor pixelBR = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_hi)];

  //first round of interpolation - x
  const float topR = (static_cast<float>(pixelTL.r)*(1-frac_x)) + (static_cast<float>(pixelTR.r)*frac_x);
  const float topG = (static_cast<float>(pixelTL.g)*(1-frac_x)) + (static_cast<float>(pixelTR.g)*frac_x);
  const float topB = (static_cast<float>(pixelTL.b)*(1-frac_x)) + (static_cast<float>(pixelTR.b)*frac_x);
  const float botR = (static_cast<float>(pixelBL.r)*(1-frac_x)) + (static_cast<float>(pixelBR.r)*frac_x);
  const float botG = (static_cast<float>(pixelBL.g)*(1-frac_x)) + (static_cast<float>(pixelBR.g)*frac_x);
  const float botB = (static_cast<float>(pixelBL.b)*(1-frac_x)) + (static_cast<float>(pixelBR.b)*frac_x);

  //second round of interpolation - y
  const auto finalR = static_cast<uint8_t>(round((topR*(1-frac_y)) + (botR*frac_y)));
  const auto finalG = static_cast<uint8_t>(round((topG*(1-frac_y)) + (botG*frac_y)));
  const auto finalB = static_cast<uint8_t>(round((topB*(1-frac_y)) + (botB*frac_y)));

  return {.r=finalR, .g=finalG, .b=finalB};
}