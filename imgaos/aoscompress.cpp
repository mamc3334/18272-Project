//
// Created by finnb on 10/22/2024.
//

#include "aoscompress.hpp"
#include "../common/utility.hpp"
#include "../common/binaryio.hpp"
#include <vector>

using namespace std;

// Overarching compression function, reads input and writes complete output to output file

// TODO: How to check if the size of colors is greater than 2^32? Does vector already have an error if that happens?

void compress(ifstream& infile, ofstream& outfile) {
    Image_Attributes metadata = get_image_metadata(infile);
    validate_metadata(metadata);
    int intensity = metadata.intensity;
    if(intensity <= 255) { // use smallColor
        vector<smallColor> colors;
        get_small_colors(infile, colors);
        uint8_t indexByteLength = getIndexByteLength(colors.size());
        write_small_colors(infile, outfile, metadata, colors, indexByteLength);
    } else { //intensity > 255, use bigColor
        vector<bigColor> colors;
        get_big_colors(infile, colors);
        uint8_t indexByteLength = getIndexByteLength(colors.size());
        write_big_colors(infile, outfile, metadata, colors, indexByteLength);
    }
}

// Could combine these using some sort of template typename
bool contains_small_color(vector<smallColor>& colors, smallColor& color) {
	for(int i = 0; i < colors.size(); i++) {
		if(colors[i] == color) {
			return true;
		}
	}
	return false;
}

bool contains_big_color(vector<bigColor>& colors, bigColor& color) {
	for(int i = 0; i < colors.size(); i++) {
		if(colors[i] == color) {
			return true;
		}
	}
	return false;
}

/*
TODO:
Pass in metadata to get width and height
Read through all pixels of the input file
    On each read, check if the color exists in the color vector already
        If not, add that color to the vector
 */

void get_small_colors(ifstream& inFile, vector<smallColor>& colors, Image_Attributes& metadata) {
	int numColors = 3*metadata.width*metadata.height;
    for(int i = 0; i < numColors; i++) {
        uint8_t color = read_binary8(inFile);
		if(contains_small_color(colors, color)) {
			colors.push_back(color);
		}
    }
}


void get_big_colors(ifstream& infile, vector<bigColor>& colors, Image_Attributes& metadata) {

}


uint8_t getIndexByteLength(size_t colorSize) {
  if (colorSize > (1 << 16)) { // colorSize > 2^16
      return 4;
  } else if (colorSize > (1 << 8)) {  // colorSize > 2^8
      return 2;
  } else { // colorSize < 2^8
      return 1;
  }
}

/*
TODO:
Write new magic word, width, height, intensity
Write length of color vector
Write pixel indices using the correct length (indexByteLength)
 */

void write_small_colors(ifstream& infile, ofstream& outfile, Image_Attributes& metadata, vector<smallColor>& colors, uint8_t indexByteLength) {

}

void write_big_colors(ifstream& infile, ofstream& outfile, Image_Attributes& metadata, vector<bigColor>& colors, uint8_t indexByteLength) {

}