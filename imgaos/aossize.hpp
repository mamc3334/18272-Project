#ifndef AOSSIZE_HPP
#define AOSSIZE_HPP

#include "aoscommon.hpp"
#include "../common/binaryio.hpp"
#include <vector>
#include <fstream>
using namespace std;

void aossize_old_photo_16(vector<vector<bigColor>>& pixelArray, const int rows, const int cols, ifstream& inFile);
void aossize_old_photo_8(vector<vector<smallColor>>& pixelArray, const int rows, const int cols, ifstream& inFile);

#endif //AOSSIZE_HPP