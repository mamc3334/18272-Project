//
// Created by finnb on 10/7/2024.
//

#include "binaryio.hpp"

void readMetaDataFromFile(string filePath, bool close)
{
    //TODO: Quickly open file and fetch metadata
    //TODO: store in accessible variables for use by aos and soa
    oMagicChars = ;
    oWidth = ;
    oHeight = ;
    oIntensity = ;

    /* TODO: if close is set to true (ie only info) then close file and return
    *  If false do not close, post req should go to aos or soa read immediately.
    */
    if(close)
    {
        //TODO
        //post req
    }
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