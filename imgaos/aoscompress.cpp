//
// Created by finnb on 10/22/2024.
//

#include "aoscompress.hpp"

#include <iomanip>

#include "../common/utility.hpp"
#include "../common/binaryio.hpp"
#include <vector>
#include <unordered_map>
#include<iostream>


using namespace std;

// Overarching compression function, reads input and writes complete output to output file

void compress(ifstream& inFile, ofstream& outFile) {
    Image_Attributes const metadata = get_image_metadata(inFile);
    //validate_metadata(metadata.magic_word, metadata.width, metadata.height, metadata.intensity);
    int const intensity = metadata.intensity;
    unsigned int const numPixels = metadata.width*metadata.height;
    if(intensity <= IntensityCutoff) { // use smallColor
        vector<smallColor> colors;
    	unordered_map<smallColor, int> colorIndexMap;
        get_small_colors(inFile, numPixels, colors, colorIndexMap);
        uint8_t const indexByteLength = getIndexByteLength(colors.size());
    	write_metadata(outFile, metadata);
        write_small_colors(outFile, colors);

    	inFile.close();
    	ifstream inFile2(getInFile());
    	get_image_metadata(inFile2);

        write_small_pixels(inFile, outFile, numPixels, colorIndexMap, indexByteLength);
    } else { //intensity > 255, use bigColor
        vector<bigColor> colors;
    	unordered_map<bigColor, int> colorIndexMap;
    	get_big_colors(inFile, numPixels, colors, colorIndexMap);
    	uint8_t const indexByteLength = getIndexByteLength(colors.size());
    	write_metadata(outFile, metadata);
    	write_big_colors(outFile, colors);

    	inFile.close();
    	ifstream inFile2(getInFile());
    	get_image_metadata(inFile2);

    	write_big_pixels(inFile, outFile, numPixels, colorIndexMap, indexByteLength);
    }
}


// Populates colors vector with list of 3-byte RGB values from inFile

void get_small_colors(ifstream& inFile, unsigned int numPixels, vector<smallColor>& colors, unordered_map<smallColor, int>& colorIndexMap){
	int index = 0;
	for(unsigned int i = 0; i < numPixels; i++) {
        uint8_t const red = read_binary8(inFile);
        uint8_t const green = read_binary8(inFile);
        uint8_t const blue = read_binary8(inFile);
        smallColor const color = {.r=red, .g=green, .b=blue};
	  if(colorIndexMap.find(color) == colorIndexMap.end()) {
	    colorIndexMap[color] = index;
	    colors.push_back(color);
	    index++;
	  }
    }
}

// Populates colors vector with list of 6-byte RGB values from inFile

void get_big_colors(ifstream& inFile, unsigned int numPixels, vector<bigColor>& colors, unordered_map<bigColor, int>& colorIndexMap){
	int index = 0;
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t const red = read_binary16(inFile);
		uint16_t const green = read_binary16(inFile);
		uint16_t const blue = read_binary16(inFile);
		bigColor const color = {.r=red, .g=green, .b=blue};
	  if(colorIndexMap.find(color) == colorIndexMap.end()) {
	    colorIndexMap[color] = index;
	    colors.push_back(color);
	    index++;
	  }
	}
}


// Returns the number of bytes required to fully express the index of a color

uint8_t getIndexByteLength(size_t colorSize) {
  if (colorSize > (1 << ByteCutoff4)) { // colorSize > 2^16
      return 4;
  } if (colorSize > (1 << ByteCutoff2)) {  // colorSize > 2^8
      return 2;
  } // colorSize < 2^8
  return 1;

}


// Writes metadata to output file

void write_metadata(ofstream& outFile, Image_Attributes const & metadata) {
	outFile << "C6 " << metadata.width << " " << metadata.height << " " << metadata.intensity << " ";
}




// Writes sequence of colors, using 3 bytes to match intensity <= 255

void write_small_colors(ofstream& outFile, vector<smallColor>& colors) {
    outFile << std::dec << colors.size() << "\n";
    for(auto color : colors) {
    	outFile << color.r << color.g << color.b;
    }
}


// Writes sequence of colors, using 6 bytes to match intensity > 255

void write_big_colors(ofstream& outFile, vector<bigColor>& colors) {
  outFile << std::dec << colors.size() << "\n";
  for(auto color : colors) {
    constexpr int padding = 5;
    outFile << std::setw(padding) << std::setfill('0') << color.r << " "
			   << std::setw(padding) << std::setfill('0') << color.g << " "
			   << std::setw(padding) << std::setfill('0') << color.b << "\n";
  }
}


// Writes sequence of indexes corresponding to locations in the color vector, using the proper number of bytes per index

void write_small_pixels(ifstream& inFile, ofstream& outFile, unsigned int numPixels, unordered_map<smallColor, int>& colorIndexMap, uint8_t indexByteLength){
    if (indexByteLength == 1) {
    	write_small_pixels_1b(inFile, outFile, colorIndexMap, numPixels);
    } else if (indexByteLength == 2) {
		write_small_pixels_2b(inFile, outFile, colorIndexMap, numPixels);
    } else if (indexByteLength == 4) {
    	write_small_pixels_4b(inFile, outFile, colorIndexMap, numPixels);
    } else {
    	cerr << "Error: Incorrect indexByteLength: " << indexByteLength << "\n";  
    }
}



void write_small_pixels_1b(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
        const uint8_t red = read_binary8(inFile);
        const uint8_t green = read_binary8(inFile);
        const uint8_t blue = read_binary8(inFile);
        const smallColor color = {.r=red, .g=green, .b=blue};
        int const index32 = colorIndexMap[color];
	auto const index = static_cast<uint8_t>(index32);
	write_binary8(outFile, index);
    }
}

void write_small_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
	        uint8_t const red = read_binary8(inFile);
		uint8_t const green = read_binary8(inFile);
		uint8_t const blue = read_binary8(inFile);
		smallColor const color = {.r=red, .g=green, .b=blue};
		int const index32 = colorIndexMap[color];
		auto index = static_cast<uint16_t>(index32);
		write_binary16(outFile, index);
	}
}

void write_small_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint8_t const red = read_binary8(inFile);
		uint8_t const green = read_binary8(inFile);
		uint8_t const blue = read_binary8(inFile);
		smallColor const color = {.r=red, .g=green, .b=blue};
		int const index = colorIndexMap[color];
		write_binary32(outFile, index);
	}
}

void write_big_pixels(ifstream& inFile, ofstream& outFile, unsigned int numPixels, unordered_map<bigColor, int>& colorIndexMap, uint8_t indexByteLength){
	if (indexByteLength == 1) {
		write_big_pixels_1b(inFile, outFile, colorIndexMap, numPixels);
	} else if (indexByteLength == 2) {
		write_big_pixels_2b(inFile, outFile, colorIndexMap, numPixels);
	} else if (indexByteLength == 4) {
		write_big_pixels_4b(inFile, outFile, colorIndexMap, numPixels);
	} else {
		cerr << "Error: Incorrect indexByteLength: " << indexByteLength << "\n";
	}
}



void write_big_pixels_1b(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t const red = read_binary16(inFile);
		uint16_t const green = read_binary16(inFile);
		uint16_t const blue = read_binary16(inFile);
		bigColor const color = {.r=red, .g=green, .b=blue};
		int const index32 = colorIndexMap[color];
		auto const index = static_cast<uint8_t>(index32);
		write_binary8(outFile, index);
	}
}

void write_big_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t const red = read_binary16(inFile);
		uint16_t const green = read_binary16(inFile);
		uint16_t const blue = read_binary16(inFile);
		bigColor const color = {.r=red, .g=green, .b=blue};
		int const index32 = colorIndexMap[color];
		auto const index = static_cast<uint16_t>(index32);
		write_binary16(outFile, index);
	}
}

void write_big_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t const red = read_binary16(inFile);
		uint16_t const green = read_binary16(inFile);
		uint16_t const blue = read_binary16(inFile);
		bigColor const color = {.r=red, .g=green, .b=blue};
		int const index = colorIndexMap[color];
		write_binary32(outFile, index);
	}
}
