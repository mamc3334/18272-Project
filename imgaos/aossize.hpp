#ifndef AOSSIZE_HPP
#define AOSSIZE_HPP

#include "../common/utility.hpp"
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

void aossize_old_photo_16(vector<vector<bigColor>>& pixelArray, unsigned int rows, unsigned int cols, ifstream& inFile);
void aossize_old_photo_8(vector<vector<smallColor>>& pixelArray, unsigned int rows, unsigned int cols, ifstream& inFile);

void aossize_resize_16(vector<vector<bigColor>>& pixelArray, unsigned int oRows, unsigned int oCols, int nRows, int nCols, ofstream& outFile);
void aossize_resize_8(vector<vector<smallColor>>& pixelArray, unsigned int oRows, unsigned int oCols, int nRows, int nCols, ofstream& outFile);

bigColor interpolate_16(vector<vector<bigColor>>& pixelArray, float x, float y, float xl, float xh, float yl, float yh);
smallColor interpolate_8(vector<vector<smallColor>>& pixelArray, float x, float y, float xl, float xh, float yl, float yh);
#endif //AOSSIZE_HPP