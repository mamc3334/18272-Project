//
// Created by finnb on 10/7/2024.
//

#ifndef BINARYIO_HPP
#define BINARYIO_HPP
#include <string>
using namespace std;

void readMetaDataFromFile(string filePath);
string getMagicChars();
int getWidth();
int getHeight();
int getIntensity();

#endif //BINARYIO_HPP
