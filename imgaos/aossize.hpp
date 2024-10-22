#ifndef AOSSIZE_HPP
#define AOSSIZE_HPP

#include "aoscommon.hpp"
#include "../common/binaryio.hpp"
#include <vector>
#include <fstream>
using namespace std;

void aossize_old_photo_16(vector<vector<bigColor>>& pixelArray, int rows, int cols, ifstream& inFile);
void aossize_old_photo_8(vector<vector<smallColor>>& pixelArray, int rows, int cols, ifstream& inFile);

void aossize_resize_16(vector<vector<bigColor>>& pixelArray, int oRows, int oCols, int nRows, int nCols, ofstream& outFile);
void aossize_resize_8(vector<vector<smallColor>>& pixelArray, int oRows, int oCols, int nRows, int nCols, ofstream& outFile);

bigColor interpolate_16(vector<vector<bigColor>>& pixelArray, double x, double y, double xl, double xh, double yl, double yh);
smallColor interpolate_8(vector<vector<smallColor>>& pixelArray, double x, double y, double xl, double xh, double yl, double yh);
#endif //AOSSIZE_HPP