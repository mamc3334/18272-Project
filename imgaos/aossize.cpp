//
// Created by mcgaf on 10/20/2024.
//
#include "aossize.hpp"
#include "../common/binaryio.cpp"
#include <cmath>

using namespace std;

void aossize_old_photo_16(vector<vector<bigColor>>& pixelArray, const Image_Attributes& OldPhotoData, ifstream& inFile)
{
    for(unsigned int i = 0; i < OldPhotoData.height; i++){
        for(unsigned int j = 0; j < OldPhotoData.width; j++){
            pixelArray[i][j]= {.r=read_binary16(inFile), .g=read_binary16(inFile), .b=read_binary16(inFile)};
        }
    }
    inFile.close();
}

void aossize_old_photo_8(vector<vector<smallColor>>& pixelArray, const Image_Attributes& OldPhotoData, ifstream& inFile)
{
    for(unsigned int i = 0; i < OldPhotoData.height; i++){
        for(unsigned int j = 0; j < OldPhotoData.width; j++){
            pixelArray[i][j]= {.r=read_binary8(inFile), .g=read_binary8(inFile), .b=read_binary8(inFile)};
        }
    }
    inFile.close();
}

void aossize_resize_16(const vector<vector<bigColor>>& pixelArray, const Image_Attributes& OldPhotoData, const Image_Attributes& NewPhotoData, ofstream& outFile)
{
    for(unsigned int i = 0; i < NewPhotoData.height; i++)
    {
        const float y_map = static_cast<float>(i)*static_cast<float>(OldPhotoData.height)/static_cast<float>(NewPhotoData.height);
        const float y_lo = floor(y_map);
        const float y_hi = ceil(y_map);
        for(unsigned int j = 0; j < NewPhotoData.width; j++){
            const float x_map = static_cast<float>(j)*static_cast<float>(OldPhotoData.width)/static_cast<float>(NewPhotoData.width);
            const float x_lo = floor(x_map);
            const float x_hi = ceil(x_map);
            const Coords coords = {.x_map=x_map,.x_lo=x_lo,.x_hi=x_hi,.y_map=y_map,.y_lo=y_lo,.y_hi=y_hi};
            const bigColor pixel = interpolate_16(pixelArray, coords);
            write_binary16(outFile, pixel.r);
            write_binary16(outFile, pixel.g);
            write_binary16(outFile, pixel.b);
        }
    }
    outFile.close();
}

void aossize_resize_8(const vector<vector<smallColor>>& pixelArray, const Image_Attributes& OldPhotoData, const Image_Attributes& NewPhotoData, ofstream& outFile)
{
    for(unsigned int i = 0; i < NewPhotoData.height; i++){
        const float y_map = static_cast<float>(i)*static_cast<float>(OldPhotoData.height)/static_cast<float>(NewPhotoData.height);
        const float y_lo = floor(y_map);
        const float y_hi = ceil(y_map);
        for(unsigned int j = 0; j < NewPhotoData.width; j++){
            const float x_map = static_cast<float>(j)*static_cast<float>(OldPhotoData.width)/static_cast<float>(NewPhotoData.width);
            const float x_lo = floor(x_map);
            const float x_hi = ceil(x_map);
            const Coords coords = {.x_map=x_map,.x_lo=x_lo,.x_hi=x_hi,.y_map=y_map,.y_lo=y_lo,.y_hi=y_hi};
            const smallColor pixel = interpolate_8(pixelArray, coords);
            write_binary8(outFile, pixel.r);
            write_binary8(outFile, pixel.g);
            write_binary8(outFile, pixel.b);
        }
    }
    outFile.close();
}

bigColor interpolate_16(const vector<vector<bigColor>>& pixelArray, const Coords& coords)
{
  const float frac_x = coords.x_map - coords.x_lo;
  const float frac_y = coords.y_map - coords.y_lo;
  const bigColor pixelTL = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_lo)];
  const bigColor pixelTR = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_hi)];
  const bigColor pixelBL = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_lo)];
  const bigColor pixelBR = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_hi)];
  const float topR = (pixelTL.r*(1-frac_x)) + (pixelTR.r*frac_x);
  const float topG = (pixelTL.g*(1-frac_x)) + (pixelTR.g*frac_x);
  const float topB = (pixelTL.b*(1-frac_x)) + (pixelTR.b*frac_x);
  const float botR = (pixelBL.r*(1-frac_x)) + (pixelBR.r*frac_x);
  const float botG = (pixelBL.g*(1-frac_x)) + (pixelBR.g*frac_x);
  const float botB = (pixelBL.b*(1-frac_x)) + (pixelBR.b*frac_x);
  const auto finalR = static_cast<uint16_t>(round((topR*(1-frac_y)) + (botR*frac_y)));
  const auto finalG = static_cast<uint16_t>(round((topG*(1-frac_y)) + (botG*frac_y)));
  const auto finalB = static_cast<uint16_t>(round((topB*(1-frac_y)) + (botB*frac_y)));
  return {.r=finalR, .g=finalG, .b=finalB};
}

smallColor interpolate_8(const vector<vector<smallColor>>& pixelArray, const Coords& coords)
{
  const float frac_x = coords.x_map - coords.x_lo;
  const float frac_y = coords.y_map - coords.y_lo;
  const smallColor pixelTL = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_lo)];
  const smallColor pixelTR = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_hi)];
  const smallColor pixelBL = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_lo)];
  const smallColor pixelBR = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_hi)];
  const float topR = (pixelTL.r*(1-frac_x)) + (pixelTR.r*frac_x);
  const float topG = (pixelTL.g*(1-frac_x)) + (pixelTR.g*frac_x);
  const float topB = (pixelTL.b*(1-frac_x)) + (pixelTR.b*frac_x);
  const float botR = (pixelBL.r*(1-frac_x)) + (pixelBR.r*frac_x);
  const float botG = (pixelBL.g*(1-frac_x)) + (pixelBR.g*frac_x);
  const float botB = (pixelBL.b*(1-frac_x)) + (pixelBR.b*frac_x);
  const auto finalR = static_cast<uint8_t>(round((topR*(1-frac_y)) + (botR*frac_y)));
  const auto finalG = static_cast<uint8_t>(round((topG*(1-frac_y)) + (botG*frac_y)));
  const auto finalB = static_cast<uint8_t>(round((topB*(1-frac_y)) + (botB*frac_y)));
  return {.r=finalR, .g=finalG, .b=finalB};
}