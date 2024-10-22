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
void validate_metadata (Image_Attributes metadata);
void displayInfo();
string getInFile();
string getOutFile();
void setInFile(const string& in);
void setOutFile(const string& out);
void util_set_new_w(const int& w);
void util_set_new_h(const int& h);

#endif //UTILITY_HPP
