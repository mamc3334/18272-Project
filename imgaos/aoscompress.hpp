//
// Created by finnb on 10/22/2024.
//

#ifndef AOSCOMPRESS_HPP
#define AOSCOMPRESS_HPP

#include<fstream>
#include "../common/utility.hpp"
#include <cstdint>
#include <vector>
#include <unordered_map>

using namespace std;

void compress(ifstream& inFile, ofstream& outFile);

bool contains_smallColor(vector<smallColor> vec, smallColor element);
bool contains_bigColor(vector<bigColor> vec, bigColor element);

//no longer used?
// template <typename T> bool index_of_1b(vector<T> vec, T& element, uint8_t& index);
// template <typename T> bool index_of_2b(vector<T> vec, T& element, uint16_t& index);
// template <typename T> bool index_of_4b(vector<T> vec, T& element, int& index);

void get_small_colors(ifstream& inFile, vector<smallColor>& colors, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels);
void get_big_colors(ifstream& inFile, vector<bigColor>& colors, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels);

uint8_t getIndexByteLength(size_t colorSize);

void write_metadata(ofstream& outFile, const Image_Attributes& metadata);
void write_small_colors(ofstream& outFile, vector<smallColor>& colors);
void write_big_colors(ofstream& outFile, vector<bigColor>& colors);

void write_small_pixels(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels, uint8_t indexByteLength);
void write_small_pixels_1b(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels);
void write_small_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels);
void write_small_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels);

void write_big_pixels(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels, uint8_t indexByteLength);
void write_big_pixels_1b(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels);
void write_big_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels);
void write_big_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels);
void write_big_pixels(ifstream& infile, ofstream& outfile, unordered_map<bigColor, int>& colorIndexMap, uint8_t numPixels);
// void uncompress(ifstream& inFile, ofstream& outFile);

#endif //AOSCOMPRESS_HPP
