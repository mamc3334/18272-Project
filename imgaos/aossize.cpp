//
// Created by mcgaf on 10/20/2024.
//
using namespace std;
#include <vector>
#include "aossize.hpp"
#include <iostream>
#include <fstream>

bigColor[][] aossize_read_old_uint16(metadata.height, metadata.width, imageFile)
{
    if(meta.intensity > 255)
    {
        bigColor pixelArray[meta.height][meta.width];
        for(int i = 0; i < meta.height; i++)
        {
            for(int j = 0; j < meta.width; j++)
            {
                pixelArray[i][j]= {read_binary16(in), read_binary16(in), read_binary16(in)};
            }
        }
    }
    return pixelArray;
}
