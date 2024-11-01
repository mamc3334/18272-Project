//
// Created by finnb on 10/7/2024.
//

#ifndef PROGARGS_HPP
#define PROGARGS_HPP

#include <iostream>
#include <fstream>
#include "utility.hpp"
using namespace std;

void prog_paths(const string& imagePath, const string& outFile);

void prog_info(int argc);

void prog_maxlevel(int argc, const vector<string> & args);

void prog_resize(int argc, const vector<string> & args);

void prog_cutfreq(int argc, const vector<string> & args);

void prog_compress(int argc);

#endif //PROGARGS_HPP
