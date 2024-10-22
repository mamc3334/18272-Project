//
// Created by finnb on 10/21/2024.
//
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#ifndef UTILITY_HPP
#define UTILITY_HPP

struct Image_Attributes {
    std::string magic_word;
    int width, height, intensity;
};

inline string inFile, outFile;

Image_Attributes get_image_metadata (ifstream& imageFile);
void displayInfo();
string getInFile();
string getOutFile();
void setInFile(const string& in);
void setOutFile(const string& out);

#endif //UTILITY_HPP
