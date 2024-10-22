//
// Created by finnb on 10/22/2024.
//

#include "aoscompress.hpp"
#include "../common/utility.hpp"

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


/*
TODO:
Read through all pixels of the input file
    On each read, check if the color exists in the color vector already
        If not, add that color to the vector
 */

void get_small_colors(ifstream& infile, vector<smallColor>& colors) {

}


void get_big_colors(ifstream& infile, vector<bigColor>& colors) {

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