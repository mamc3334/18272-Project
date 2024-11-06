//
// Created by mcgaf on 10/20/2024.
//
#include "aossize.hpp"
#include "../common/binaryio.hpp"
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
    for(int i = 0; i < NewPhotoData.height; i++)
    {
        const float y_new = static_cast<float>(i)*static_cast<float>(OldPhotoData.height)/static_cast<float>(NewPhotoData.height);
        const float y_lo = floor(y_new);
        const float y_hi = ceil(y_new);
        for(int j = 0; j < NewPhotoData.width; j++){
            const float x_new = static_cast<float>(j)*static_cast<float>(OldPhotoData.width)/static_cast<float>(NewPhotoData.width);
            const float x_lo = floor(x_new);
            const float x_hi = ceil(x_new);
            const Coords coords = {.x_new=x_new,.x_lo=x_lo,.x_hi=x_hi,.y_new=y_new,.y_lo=y_lo,.y_hi=y_hi};
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
    for(int i = 0; i < NewPhotoData.height; i++){
        const float y_new = static_cast<float>(i)*static_cast<float>(OldPhotoData.height)/static_cast<float>(NewPhotoData.height);
        const float y_lo = floor(y_new);
        const float y_hi = ceil(y_new);
        for(int j = 0; j < NewPhotoData.width; j++){
            const float x_new = static_cast<float>(j)*static_cast<float>(OldPhotoData.width)/static_cast<float>(NewPhotoData.width);
            const float x_lo = floor(x_new);
            const float x_hi = ceil(x_new);
            const Coords coords = {.x_new=x_new,.x_lo=x_lo,.x_hi=x_hi,.y_new=y_new,.y_lo=y_lo,.y_hi=y_hi};
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
    const bigColor pixelTL = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_lo)];
    const bigColor pixelTR = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_hi)];
    const bigColor pixelBL = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_lo)];
    const bigColor pixelBR = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_hi)];
    const auto topR = static_cast<uint16_t>((pixelTL.r*(coords.x_new-coords.x_lo)) + (pixelTR.r*(coords.x_hi-coords.x_new)));
    const auto topG = static_cast<uint16_t>((pixelTL.g*(coords.x_new-coords.x_lo)) + (pixelTR.g*(coords.x_hi-coords.x_new)));
    const auto topB = static_cast<uint16_t>((pixelTL.b*(coords.x_new-coords.x_lo)) + (pixelTR.b*(coords.x_hi-coords.x_new)));
    const auto botR = static_cast<uint16_t>((pixelBL.r*(coords.x_new-coords.x_lo)) + (pixelBR.r*(coords.x_hi-coords.x_new)));
    const auto botG = static_cast<uint16_t>((pixelBL.g*(coords.x_new-coords.x_lo)) + (pixelBR.g*(coords.x_hi-coords.x_new)));
    const auto botB = static_cast<uint16_t>((pixelBL.b*(coords.x_new-coords.x_lo)) + (pixelBR.b*(coords.x_hi-coords.x_new)));
    const bigColor pixelTop = {.r=topR, .g=topG, .b=topB};
    const bigColor pixelBot = {.r=botR, .g=botG, .b=botB};
    const auto finalR = static_cast<uint16_t>((pixelTop.r*(coords.y_new-coords.y_lo)) + (pixelBot.r*(coords.y_hi-coords.y_new)));
    const auto finalG = static_cast<uint16_t>((pixelTop.g*(coords.y_new-coords.y_lo)) + (pixelBot.g*(coords.y_hi-coords.y_new)));
    const auto finalB = static_cast<uint16_t>((pixelTop.b*(coords.y_new-coords.y_lo)) + (pixelBot.b*(coords.x_hi-coords.y_new)));
    return {.r=finalR, .g=finalG, .b=finalB};
}

smallColor interpolate_8(const vector<vector<smallColor>>& pixelArray, const Coords& coords)
{
    const smallColor pixelTL = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_hi)];
    const smallColor pixelTR = pixelArray[static_cast<unsigned int>(coords.y_lo)][static_cast<unsigned int>(coords.x_hi)];
    const smallColor pixelBL = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_hi)];
    const smallColor pixelBR = pixelArray[static_cast<unsigned int>(coords.y_hi)][static_cast<unsigned int>(coords.x_hi)];
    const auto topR = static_cast<uint8_t>((pixelTL.r*(coords.x_new-coords.x_lo)) + (pixelTR.r*(coords.x_hi-coords.x_new)));
    const auto topG = static_cast<uint8_t>((pixelTL.g*(coords.x_new-coords.x_lo)) + (pixelTR.g*(coords.x_hi-coords.x_new)));
    const auto topB = static_cast<uint8_t>((pixelTL.b*(coords.x_new-coords.x_lo)) + (pixelTR.b*(coords.x_hi-coords.x_new)));
    const auto botR = static_cast<uint8_t>((pixelBL.r*(coords.x_new-coords.x_lo)) + (pixelBR.r*(coords.x_hi-coords.x_new)));
    const auto botG = static_cast<uint8_t>((pixelBL.g*(coords.x_new-coords.x_lo)) + (pixelBR.g*(coords.x_hi-coords.x_new)));
    const auto botB = static_cast<uint8_t>((pixelBL.b*(coords.x_new-coords.x_lo)) + (pixelBR.b*(coords.x_hi-coords.x_new)));
    const smallColor pixelTop = {.r=topR, .g=topG, .b=topB};
    const smallColor pixelBot = {.r=botR, .g=botG, .b=botB};
    const auto finalR = static_cast<uint8_t>((pixelTop.r*(coords.y_new-coords.y_lo)) + (pixelBot.r*(coords.y_hi-coords.y_new)));
    const auto finalG = static_cast<uint8_t>((pixelTop.g*(coords.y_new-coords.y_lo)) + (pixelBot.g*(coords.y_hi-coords.y_new)));
    const auto finalB = static_cast<uint8_t>((pixelTop.b*(coords.y_new-coords.y_lo)) + (pixelBot.b*(coords.y_hi-coords.y_new)));
    return {.r=finalR, .g=finalG, .b=finalB};
}