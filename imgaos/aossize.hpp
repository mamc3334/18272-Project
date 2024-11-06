#ifndef AOSSIZE_HPP
#define AOSSIZE_HPP

#include "../common/utility.hpp"
#include <vector>
#include <fstream>
using namespace std;

void aossize_old_photo_16(vector<vector<bigColor>>& pixelArray, const Image_Attributes& OldPhotoData, ifstream& inFile);
void aossize_old_photo_8(vector<vector<smallColor>>& pixelArray, const Image_Attributes& OldPhotoData, ifstream& inFile);

void aossize_resize_16(const vector<vector<bigColor>>& pixelArray, const Image_Attributes& OldPhotoData, const Image_Attributes& NewPhotoData, ofstream& outFile);
void aossize_resize_8(const vector<vector<smallColor>>& pixelArray, const Image_Attributes& OldPhotoData, const Image_Attributes& NewPhotoData, ofstream& outFile);

bigColor interpolate_16(const vector<vector<bigColor>>& pixelArray, const Coords& coords);
smallColor interpolate_8(const vector<vector<smallColor>>& pixelArray, const Coords& coords);
#endif //AOSSIZE_HPP