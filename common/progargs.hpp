//
// Created by finnb on 10/7/2024.
//

#ifndef PROGARGS_HPP
#define PROGARGS_HPP

#include <iostream>
#include "binaryio.hpp"
using namespace std;

//TODO: This is wrong
const string inFile;
const string outFile;

void progPaths(string imagePath, string outFile);
string getInFile();
string getOutFile();

void info(int argc);

void displayInfo();

void maxLevel(int argc, char *argv[]);

void resize(int argc, char *argv[]);

void cutfreq(int argc, char *argv[]);

void compress(int argc);

#endif //PROGARGS_HPP
