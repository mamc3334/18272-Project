//
// Created by mcgaf on 10/25/2024.
//

#include "soacompress.hpp"

#include <iomanip>

#include "../common/utility.hpp"
#include "../common/binaryio.hpp"
#include <vector>
#include <unordered_map>
#include <tuple>

using namespace std;

// Overarching compression function, reads input and writes complete output to output file

void compress(ifstream& inFile, ofstream& outFile) {
    Image_Attributes const metadata = get_image_metadata(inFile);
    //validate_metadata(metadata.magic_word, metadata.width, metadata.height, metadata.intensity);
    int const intensity = metadata.intensity;
    unsigned int const numPixels = metadata.width*metadata.height;
    if(intensity <= IntensityCutoff) { // use smallColor
        vector<uint8_t> reds;
        vector<uint8_t> greens;
        vector<uint8_t> blues;
    	unordered_map<tuple<uint8_t, uint8_t, uint8_t>, int> const colorIndexMap;
        get_small_colors(inFile, reds, greens, blues, colorIndexMap, numPixels);
        uint8_t const indexByteLength = getIndexByteLength(reds.size());
    	write_metadata(outFile, metadata);
        write_small_colors(outFile, reds, greens, blues);

    	inFile.close();
    	ifstream inFile2(getInFile());
    	get_image_metadata(inFile2);

        write_small_pixels(inFile, outFile, colorIndexMap, numPixels, indexByteLength);
    } else { //intensity > 255, use bigColor
    	vector<uint16_t> reds;
    	vector<uint16_t> greens;
    	vector<uint16_t> blues;
    	unordered_map<tuple<uint16_t, uint16_t, uint16_t>, int> const colorIndexMap;
    	get_big_colors(inFile, reds, greens, blues, colorIndexMap, numPixels);
    	uint8_t const indexByteLength = getIndexByteLength(reds.size());
    	write_metadata(outFile, metadata);
    	write_big_colors(outFile, reds, greens, blues);

    	inFile.close();
    	ifstream inFile2(getInFile());
    	get_image_metadata(inFile2);

    	write_big_pixels(inFile, outFile, colorIndexMap, numPixels, indexByteLength);
    }
}


// Populates colors vector with list of 3-byte RGB values from inFile

void get_small_colors(ifstream& inFile, vector<uint8_t>& reds, vector<uint8_t>& greens, vector<uint8_t>& blues, unordered_map<tuple<const uint8_t, const uint8_t, const uint8_t>, int>& colorIndexMap, unsigned int numPixels) {
	int index = 0;
	for(unsigned int i = 0; i < numPixels; i++) {
        uint8_t const red = BINARY::read_binary8(inFile);
        uint8_t const green = BINARY::read_binary8(inFile);
        uint8_t const blue = BINARY::read_binary8(inFile);
        tuple<const uint8_t, const uint8_t, const uint8_t> const color = {red, green, blue};
		if (!colorIndexMap.contains(color)) {
			colorIndexMap[color] = index;
			reds.push_back(red);
			greens.push_back(green);
			blues.push_back(blue);
			index++;
		}
    }
}

// Populates colors vector with list of 6-byte RGB values from inFile

void get_big_colors(ifstream& inFile, vector<uint16_t>& reds, vector<uint16_t>& greens, vector<uint16_t>& blues, unordered_map<tuple<const uint16_t, const uint16_t, const uint16_t>, int>& colorIndexMap, unsigned int numPixels) {
	int index = 0;
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t const red = BINARY::read_binary16(inFile);
		uint16_t const green = BINARY::read_binary16(inFile);
		uint16_t const blue = BINARY::read_binary16(inFile);
		tuple<const uint16_t, const uint16_t, const uint16_t> const color = {red, green, blue};
		if (!colorIndexMap.contains(color)) {
			colorIndexMap[color] = index;
			reds.push_back(red);
			greens.push_back(green);
			blues.push_back(blue);
			index++;
		}
	}
}


// Returns the number of bytes required to fully express the index of a color

uint8_t getIndexByteLength(size_t colorSize) {
  if (colorSize > ByteCutoff4) {  // colorSize > 2^16
    return 4;
  }
  if (colorSize > ByteCutoff2) {  // colorSize > 2^8
    return 2;
  }
  // colorSize < 2^8
  return 1;
}


// Writes metadata to output file

void write_metadata(ofstream& outFile, Image_Attributes const & metadata) {
	outFile << "C6 " << metadata.width << " " << metadata.height << " " << metadata.intensity << " ";
}




// Writes sequence of colors, using 3 bytes to match intensity <= 255

void write_small_colors(ofstream& outFile, vector<uint8_t>& reds, vector<uint8_t>& greens, vector<uint8_t>& blues) {
    outFile << std::dec << reds.size() << "\n";
    for(size_t i = 0; i < reds.size(); i++) {
    	outFile << reds[i] << greens[i] << blues[i];
    }
}


// Writes sequence of colors, using 6 bytes to match intensity > 255

void write_big_colors(ofstream& outFile, vector<uint16_t>& reds, vector<uint16_t>& greens, vector<uint16_t>& blues) {
	outFile << std::dec << reds.size() << "\n";
  for (size_t i = 0; i < reds.size(); i++) {
    constexpr int padding = 5;
    outFile << std::setw(padding) << std::setfill('0') << reds[i] << " "
			   << std::setw(padding) << std::setfill('0') << greens[i] << " "
			   << std::setw(padding) << std::setfill('0') << blues[i] << "\n";
    }
}


// Writes sequence of indexes corresponding to locations in the color vector, using the proper number of bytes per index

void write_small_pixels(ifstream& inFile, ofstream& outFile, unsigned int numPixels, unordered_map<tuple<uint8_t, uint8_t, uint8_t>, int>& colorIndexMap, uint8_t indexByteLength) {
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



void write_small_pixels_1b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<const uint8_t, const uint8_t, const uint8_t>, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
        uint8_t const red = BINARY::read_binary8(inFile);
        uint8_t const green = BINARY::read_binary8(inFile);
        uint8_t const blue = BINARY::read_binary8(inFile);
        tuple<const uint8_t, const uint8_t, const uint8_t> const color = {red, green, blue};
		int const index32 = colorIndexMap[color];
        auto index = static_cast<uint8_t>(index32);
		BINARY::write_binary8(outFile, index);
    }
}

void write_small_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<const uint8_t, const uint8_t, const uint8_t>, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint8_t const red = BINARY::read_binary8(inFile);
		uint8_t const green = BINARY::read_binary8(inFile);
		uint8_t const blue = BINARY::read_binary8(inFile);
		tuple<const uint8_t, const uint8_t, const uint8_t> const color = {red, green, blue};
		int const index32 = colorIndexMap[color];
		auto index = static_cast<uint16_t>(index32);
		BINARY::write_binary16(outFile, index);
	}
}

void write_small_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<const uint8_t, const uint8_t, const uint8_t>, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint8_t const red = BINARY::read_binary8(inFile);
		uint8_t const green = BINARY::read_binary8(inFile);
		uint8_t const blue = BINARY::read_binary8(inFile);
		tuple<const uint8_t, const uint8_t, const uint8_t> const color = {red, green, blue};
		int const index = colorIndexMap[color];
		BINARY::write_binary32(outFile, index);
	}
}

void write_big_pixels(ifstream& inFile, ofstream& outFile, unsigned int numPixels, unordered_map<tuple<uint16_t, uint16_t, uint16_t>, int>& colorIndexMap, uint8_t indexByteLength) {
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



void write_big_pixels_1b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<const uint16_t, const uint16_t, const uint16_t>, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t const red = BINARY::read_binary16(inFile);
		uint16_t const green = BINARY::read_binary16(inFile);
		uint16_t const blue = BINARY::read_binary16(inFile);
		tuple<const uint16_t, const uint16_t, const uint16_t> const color = {red, green, blue};
		int const index32 = colorIndexMap[color];
		auto index = static_cast<uint8_t>(index32);
		BINARY::write_binary8(outFile, index);
	}
}

void write_big_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<uint16_t const, uint16_t const, uint16_t const>, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t const red = BINARY::read_binary16(inFile);
		uint16_t const green = BINARY::read_binary16(inFile);
		uint16_t const blue = BINARY::read_binary16(inFile);
		tuple<uint16_t const, uint16_t const, uint16_t const> const color = {red, green, blue};
		int const index32 = colorIndexMap[color];
		auto index = static_cast<uint16_t>(index32);
		BINARY::write_binary16(outFile, index);
	}
}

void write_big_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<tuple<uint16_t const, uint16_t const, uint16_t const>, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t const red = BINARY::read_binary16(inFile);
		uint16_t const green = BINARY::read_binary16(inFile);
		uint16_t const blue = BINARY::read_binary16(inFile);
		tuple<uint16_t const, uint16_t const, uint16_t const> const color = {red, green, blue};
		int const index = colorIndexMap[color];
		BINARY::write_binary32(outFile, index);
	}
}