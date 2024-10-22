//
// Created by mcgaf on 10/20/2024.
//
#include "aossize.hpp"
using namespace std;

void aossize_old_photo_16(vector<vector<bigColor>>& pixelArray, const int rows, const int cols, ifstream& inFile)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {

            pixelArray[i][j]= {read_binary16(inFile), read_binary16(inFile), read_binary16(inFile)};
        }
    }
}

void aossize_old_photo_8(vector<vector<smallColor>>& pixelArray, const int rows, const int cols, ifstream& inFile)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            pixelArray[i][j]= {read_binary8(inFile), read_binary8(inFile), read_binary8(inFile)};
        }
    }
}

