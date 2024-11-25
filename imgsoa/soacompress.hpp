//
// Created by mcgaf on 10/25/2024.
//

#ifndef SOACOMPRESS_HPP
#define SOACOMPRESS_HPP

//
// Created by finnb on 10/22/2024.
//

#ifndef AOSCOMPRESS_HPP
#define AOSCOMPRESS_HPP

#include<iostream>
#include<fstream>
#include "../common/utility.hpp"
#include <cstdint>
#include <vector>
#include <unordered_map>

using namespace std;

void compress(ifstream& inFile, ofstream& outFile);

void get_small_colors(ifstream& inFile, vector<uint8_t>& reds, vector<uint8_t>& greens, vector<uint8_t>& blues, unordered_map<tuple<const uint8_t, const uint8_t, const uint8_t>, int>& colorIndexMap, unsigned int numPixels);
void get_big_colors(ifstream& inFile, vector<uint16_t>& reds, vector<uint16_t>& greens, vector<uint16_t>& blues, unordered_map<tuple<const uint16_t, const uint16_t, const uint16_t>, int>& colorIndexMap, unsigned int numPixels);

uint8_t getIndexByteLength(size_t colorSize);

void write_metadata(ofstream& outFile, Image_Attributes const & metadata);
void write_small_colors(ofstream& outFile, vector<uint8_t>& reds, vector<uint8_t>& greens, vector<uint8_t>& blues);
void write_big_colors(ofstream& outFile, vector<uint16_t>& reds, vector<uint16_t>& greens, vector<uint16_t>& blues);

void write_small_pixels(ifstream& inFile, ofstream& outFile, unsigned int numPixels, unordered_map<tuple<uint8_t, uint8_t, uint8_t>, int>& colorIndexMap, uint8_t indexByteLength);
void write_small_pixels_1b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<const uint8_t, const uint8_t, const uint8_t>, int>& colorIndexMap, unsigned int numPixels);
void write_small_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<const uint8_t, const uint8_t, const uint8_t>, int>& colorIndexMap, unsigned int numPixels);
void write_small_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<const uint8_t, const uint8_t, const uint8_t>, int>& colorIndexMap, unsigned int numPixels);

void write_big_pixels(ifstream& inFile, ofstream& outFile, unsigned int numPixels, unordered_map<tuple<uint16_t, uint16_t, uint16_t>, int>& colorIndexMap, uint8_t indexByteLength);
void write_big_pixels_1b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<const uint16_t, const uint16_t, const uint16_t>, int>& colorIndexMap, unsigned int numPixels);
void write_big_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<uint16_t const, uint16_t const, uint16_t const>, int>& colorIndexMap, unsigned int numPixels);
void write_big_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<uint16_t const, uint16_t const, uint16_t const>, int>& colorIndexMap, unsigned int numPixels);

#endif //AOSCOMPRESS_HPP


#endif //SOACOMPRESS_HPP
