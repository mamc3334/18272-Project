//
// Created by finnb on 10/7/2024.
//

#ifndef PROGARGS_HPP
#define PROGARGS_HPP

#include <fstream>
#include <vector>
using namespace std;

constexpr int InfoArgs = 4;
constexpr int MaxLevelArgs = 5;
constexpr int ResizeArgs = 6;
constexpr int CutFreqArgs = 5;
constexpr int CompressArgs = 4;
constexpr int MaxIntensity = 65535;

void prog_paths(const string& imagePath, const string& outFile);

void prog_info(int argc);

void prog_maxlevel(int argc, const vector<string> & args);

void prog_resize(int argc, const vector<string> & args);

void prog_cutfreq(int argc, const vector<string> & args);

void prog_compress(int argc);

#endif //PROGARGS_HPP
