//
// Created by finnb on 10/7/2024.
//

#include "binaryio.hpp"

void readMetaDataFromFile(string filePath)
{
    //TODO: Quickly open file and fetch metadata
    //TODO: store in accessible variables for use by aos and soa
    oMagicChars = ;
    oWidth = ;
    oHeight = ;
    oIntensity = ;
}

string getMagicChars()
{
    return oMagicChars;
}
int getWidth()
{
    return oWidth;
}
int getHeight()
{
    return oHeight;
}
int getIntensity()
{
    return oIntensity;
}