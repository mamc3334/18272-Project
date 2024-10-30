//
// Created by mcgaf on 10/20/2024.
//
#include "aossize.hpp"
#include "../common/binaryio.hpp"
using namespace std;

void aossize_old_photo_16(vector<vector<bigColor>>& pixelArray, const unsigned int rows, const unsigned int cols, ifstream& inFile)
{
    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            pixelArray[i][j]= {read_binary16(inFile), read_binary16(inFile), read_binary16(inFile)};
        }
    }
}

void aossize_old_photo_8(vector<vector<smallColor>>& pixelArray, const unsigned int rows, const unsigned int cols, ifstream& inFile)
{
    for(unsigned int i = 0; i < rows; i++){
        for(unsigned int j = 0; j < cols; j++){
            pixelArray[i][j]= {read_binary8(inFile), read_binary8(inFile), read_binary8(inFile)};
        }
    }
}

void aossize_resize_16(vector<vector<bigColor>>& pixelArray, const unsigned int oRows, const unsigned int oCols, int nRows, int nCols, ofstream& outFile)
{
    for(int i = 0; i < nRows; i++)
    {
        float y = static_cast<float>(i)*static_cast<float>(oRows)/static_cast<float>(nRows);
        float yl = floor(y);
        float yh = ceil(y);
        for(int j = 0; j < nCols; j++){
            float x = static_cast<float>(j)*static_cast<float>(oCols)/static_cast<float>(nCols);
            float xl = floor(x);
            float xh = ceil(x);
            bigColor pixel = interpolate_16(pixelArray,x,y,xl,xh,yl,yh);
            write_binary16(outFile, pixel.r);
            write_binary16(outFile, pixel.g);
            write_binary16(outFile, pixel.b);
        }
    }
}

void aossize_resize_8(vector<vector<smallColor>>& pixelArray, int oRows, int oCols, int nRows, int nCols, ofstream& outFile)
{
    for(int i = 0; i < nRows; i++){
        float y = static_cast<float>(i)*static_cast<float>(oRows)/static_cast<float>(nRows);
        float yl = floor(y);
        float yh = ceil(y);
        for(int j = 0; j < nCols; j++){
            float x = static_cast<float>(j)*static_cast<float>(oCols)/static_cast<float>(nCols);
            float xl = floor(x);
            float xh = ceil(x);
            smallColor pixel = interpolate_8(pixelArray,x,y,xl,xh,yl,yh);
            write_binary8(outFile, pixel.r);
            write_binary8(outFile, pixel.g);
            write_binary8(outFile, pixel.b);
        }
    }
}

bigColor interpolate_16(const vector<vector<bigColor>>& pixelArray, const float x, const float y, const float xl, const float xh, const float yl, const float yh)
{
    bigColor pixelTL = pixelArray[static_cast<unsigned int>(yl)][static_cast<unsigned int>(xl)];
    bigColor pixelTR = pixelArray[static_cast<unsigned int>(yl)][static_cast<unsigned int>(xh)];
    bigColor pixelBL = pixelArray[static_cast<unsigned int>(yh)][static_cast<unsigned int>(xl)];
    bigColor pixelBR = pixelArray[static_cast<unsigned int>(yh)][static_cast<unsigned int>(xh)];
    uint16_t topR = static_cast<uint16_t>(pixelTL.r*(x-xl) + pixelTR.r*(xh-x));
    uint16_t topG = static_cast<uint16_t>(pixelTL.g*(x-xl) + pixelTR.g*(xh-x));
    uint16_t topB = static_cast<uint16_t>(pixelTL.b*(x-xl) + pixelTR.b*(xh-x));
    uint16_t botR = static_cast<uint16_t>(pixelBL.r*(x-xl) + pixelBR.r*(xh-x));
    uint16_t botG = static_cast<uint16_t>(pixelBL.g*(x-xl) + pixelBR.g*(xh-x));
    uint16_t botB = static_cast<uint16_t>(pixelBL.b*(x-xl) + pixelBR.b*(xh-x));
    bigColor pixelTop = {topR, topG, topB};
    bigColor pixelBot = {botR, botG, botB};
    uint16_t finalR = static_cast<uint16_t>(pixelTop.r*(y-yl) + pixelBot.r*(yh-y));
    uint16_t finalG = static_cast<uint16_t>(pixelTop.g*(y-xl) + pixelBot.g*(yh-x));
    uint16_t finalB = static_cast<uint16_t>(pixelTop.b*(y-xl) + pixelBot.b*(xh-x));
    return {finalR, finalG, finalB};
}

smallColor interpolate_8(const vector<vector<smallColor>>& pixelArray, const float x, const float y, const float xl, const float xh, const float yl, const float yh)
{
    smallColor pixelTL = pixelArray[static_cast<unsigned int>(yl)][static_cast<unsigned int>(xl)];
    smallColor pixelTR = pixelArray[static_cast<unsigned int>(yl)][static_cast<unsigned int>(xh)];
    smallColor pixelBL = pixelArray[static_cast<unsigned int>(yh)][static_cast<unsigned int>(xl)];
    smallColor pixelBR = pixelArray[static_cast<unsigned int>(yh)][static_cast<unsigned int>(xh)];
    uint8_t topR = static_cast<uint8_t>(pixelTL.r*(x-xl) + pixelTR.r*(xh-x));
    uint8_t topG = static_cast<uint8_t>(pixelTL.g*(x-xl) + pixelTR.g*(xh-x));
    uint8_t topB = static_cast<uint8_t>(pixelTL.b*(x-xl) + pixelTR.b*(xh-x));
    uint8_t botR = static_cast<uint8_t>(pixelBL.r*(x-xl) + pixelBR.r*(xh-x));
    uint8_t botG = static_cast<uint8_t>(pixelBL.g*(x-xl) + pixelBR.g*(xh-x));
    uint8_t botB = static_cast<uint8_t>(pixelBL.b*(x-xl) + pixelBR.b*(xh-x));
    smallColor pixelTop = {topR, topG, topB};
    smallColor pixelBot = {botR, botG, botB};
    uint8_t finalR = static_cast<uint8_t>(pixelTop.r*(y-yl) + pixelBot.r*(yh-y));
    uint8_t finalG = static_cast<uint8_t>(pixelTop.g*(y-xl) + pixelBot.g*(yh-x));
    uint8_t finalB = static_cast<uint8_t>(pixelTop.b*(y-xl) + pixelBot.b*(xh-x));
    return {finalR, finalG, finalB};
}