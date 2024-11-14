//
// Created by finnb on 10/22/2024.
//

#include "aoscompress.hpp"

#include <iomanip>

#include "../common/utility.hpp"
#include "../common/binaryio.hpp"
#include <vector>
#include <unordered_map>

using namespace std;

// Overarching compression function, reads input and writes complete output to output file

// TODO: How to check if the size of colors is greater than 2^32? Does vector already have an error if that happens?

void compress(ifstream& inFile, ofstream& outFile) {

	ifstream input("../../images/deer-small.ppm");
	Image_Attributes actual = get_image_metadata(input);
	for(int i = 0; i < 1000; i++){
		cout << static_cast<int>(read_binary8(input)) << " " << static_cast<int>(read_binary8(input)) << " " << static_cast<int>(read_binary8(input))<<endl;
	}

	cout << "Compressing..." << endl;
    Image_Attributes metadata = get_image_metadata(inFile);
    //validate_metadata(metadata.magic_word, metadata.width, metadata.height, metadata.intensity);
    int intensity = metadata.intensity;
    unsigned int numPixels = metadata.width*metadata.height;
	numPixels = 100;
	cout << "Pixel number: " << numPixels << endl;
    if(intensity <= 255) { // use smallColor
        vector<smallColor> colors;
    	unordered_map<smallColor, int> colorIndexMap;
        get_small_colors(inFile, colors, colorIndexMap, numPixels);
        uint8_t indexByteLength = getIndexByteLength(colors.size());
        write_metadata(outFile, metadata);
        write_small_colors(outFile, colors);

    	inFile.close();
    	ifstream inFile2(getInFile());
    	get_image_metadata(inFile2);

        write_small_pixels(inFile, outFile, colorIndexMap, numPixels, indexByteLength);
    } else { //intensity > 255, use bigColor
        vector<bigColor> colors;
    	unordered_map<bigColor, int> colorIndexMap;
    	get_big_colors(inFile, colors, colorIndexMap, numPixels);
    	uint8_t indexByteLength = getIndexByteLength(colors.size());
    	write_metadata(outFile, metadata);
    	write_big_colors(outFile, colors);

    	inFile.close();
    	ifstream inFile2(getInFile());
    	get_image_metadata(inFile2);

    	write_big_pixels(inFile, outFile, colorIndexMap, numPixels, indexByteLength);
    }
}


// Populates colors vector with list of 3-byte RGB values from inFile

void get_small_colors(ifstream& inFile, vector<smallColor>& colors, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels) {
	int index = 0;
	for(unsigned int i = 0; i < numPixels; i++) {
        uint8_t red = read_binary8(inFile);
        uint8_t green = read_binary8(inFile);
        uint8_t blue = read_binary8(inFile);
        smallColor color = {red, green, blue};
		if(colorIndexMap.find(color) == colorIndexMap.end()) {
			cout << "Unique color " << unsigned(red) << " " << unsigned(green) << " " << unsigned(blue) << endl;
			colorIndexMap[color] = index;
			colors.push_back(color);
			index++;
		} else {
			cout << "Duplicate color " << unsigned(red) << " " << unsigned(green) << " " << unsigned(blue) << endl;
		}
    }
}

// Populates colors vector with list of 6-byte RGB values from inFile

void get_big_colors(ifstream& inFile, vector<bigColor>& colors, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels) {
	int index = 0;
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t red = read_binary16(inFile);
		uint16_t green = read_binary16(inFile);
		uint16_t blue = read_binary16(inFile);
		bigColor color = {red, green, blue};
		if(colorIndexMap.find(color) == colorIndexMap.end()) {
			colorIndexMap[color] = index;
			colors.push_back(color);
			index++;
		}
	}
}


// Returns the number of bytes required to fully express the index of a color

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

// Writes metadata to output file

void write_metadata(ofstream& outFile, Image_Attributes& metadata) {
	outFile << "C6 " << metadata.width << " " << metadata.height << " " << metadata.intensity << " ";
}




// Writes sequence of colors, using 3 bytes to match intensity <= 255

void write_small_colors(ofstream& outFile, vector<smallColor>& colors) {
    outFile << colors.size() << "\n";
    for(size_t i = 0; i < colors.size(); i++) {
    	smallColor color = colors[i];
    	outFile << color.r << color.g << color.b;
    }
}


// Writes sequence of colors, using 6 bytes to match intensity > 255

void write_big_colors(ofstream& outFile, vector<bigColor>& colors) {
	outFile << colors.size() << "\n";
    for(size_t i = 0; i < colors.size(); i++) {
		bigColor color = colors[i];
    	outFile << std::setw(5) << std::setfill('0') << color.r << " "
			   << std::setw(5) << std::setfill('0') << color.g << " "
			   << std::setw(5) << std::setfill('0') << color.b << "\n";
    }
}


// Writes sequence of indexes corresponding to locations in the color vector, using the proper number of bytes per index

void write_small_pixels(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels, uint8_t indexByteLength) {
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
        uint8_t red = read_binary8(inFile);
        uint8_t green = read_binary8(inFile);
        uint8_t blue = read_binary8(inFile);
        smallColor color = {red, green, blue};
		int index32 = colorIndexMap[color];
        uint8_t index = static_cast<uint8_t>(index32);
		write_binary8(outFile, index);
    }
}

void write_small_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint8_t red = read_binary8(inFile);
		uint8_t green = read_binary8(inFile);
		uint8_t blue = read_binary8(inFile);
		smallColor color = {red, green, blue};
		int index32 = colorIndexMap[color];
		uint16_t index = static_cast<uint16_t>(index32);
		write_binary16(outFile, index);
	}
}

void write_small_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<smallColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint8_t red = read_binary8(inFile);
		uint8_t green = read_binary8(inFile);
		uint8_t blue = read_binary8(inFile);
		smallColor color = {red, green, blue};
		int index = colorIndexMap[color];
		write_binary32(outFile, index);
	}
}

void write_big_pixels(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels, uint8_t indexByteLength) {
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
		uint16_t red = read_binary16(inFile);
		uint16_t green = read_binary16(inFile);
		uint16_t blue = read_binary16(inFile);
		bigColor color = {red, green, blue};
		int index32 = colorIndexMap[color];
		uint8_t index = static_cast<uint8_t>(index32);
		write_binary8(outFile, index);
	}
}

void write_big_pixels_2b(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t red = read_binary16(inFile);
		uint16_t green = read_binary16(inFile);
		uint16_t blue = read_binary16(inFile);
		bigColor color = {red, green, blue};
		int index32 = colorIndexMap[color];
		uint16_t index = static_cast<uint16_t>(index32);
		write_binary16(outFile, index);
	}
}

void write_big_pixels_4b(ifstream& inFile, ofstream& outFile, unordered_map<bigColor, int>& colorIndexMap, unsigned int numPixels) {
	for(unsigned int i = 0; i < numPixels; i++) {
		uint16_t red = read_binary16(inFile);
		uint16_t green = read_binary16(inFile);
		uint16_t blue = read_binary16(inFile);
		bigColor color = {red, green, blue};
		int index = colorIndexMap[color];
		write_binary32(outFile, index);
	}
}