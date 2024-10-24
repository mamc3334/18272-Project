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

void compress(ifstream& inFile, ofstream& outFile) {
    Image_Attributes metadata = get_image_metadata(inFile);
    validate_metadata(metadata);
    int intensity = metadata.intensity;
    int numPixels = metadata.width*metadata.height;
    if(intensity <= 255) { // use smallColor
        vector<smallColor> colors;
        get_small_colors(inFile, colors, numPixels);
        uint8_t indexByteLength = getIndexByteLength(colors.size());
        write_metadata(outFile, metadata);
        write_small_colors(inFile, outFile, metadata, colors);
        write_small_pixels(inFile, outFile, colors, numPixels);
    } else { //intensity > 255, use bigColor
        vector<bigColor> colors;
        get_big_colors(inFile, colors, numPixels);
        uint8_t indexByteLength = getIndexByteLength(colors.size());
		write_metadata(outFile, metadata);
        write_big_colors(inFile, outFile, metadata, colors);
        write_big_pixels(inFile, outFile, colors, numPixels);
    }
}


template <typename T> bool contains(vector<T> vec, T& element) {
  for(int i = 0; i < vec.size(); i++) {
		if(vec[i] == element) {
			return true;
		}
	}
	return false;
}

// Gets index of an element in a vector with less than 2^8 elements
//TODO: Should we assert that this does not go out of bounds?

template <typename T> uint8_t index_of_1b(vector<T> vec, T& element) {
	for(uint8_t i = 0; i < vec.size(); i++) {
		if(vec[i] == element) {
			return i;
		}
	}
	return -1;
}

template <typename T> uint16_t index_of_2b(vector<T> vec, T& element) {
	for(uint16_t i = 0; i < vec.size(); i++) {
		if(vec[i] == element) {
			return i;
		}
	}
	return -1;
}

template <typename T> int index_of_4b(vector<T> vec, T& element) {
	for(int i = 0; i < vec.size(); i++) {
		if(vec[i] == element) {
			return i;
		}
	}
    return -1;
}



/*
TODO: Instead of for loop, should this be a while loop to ensure no reading errors?
 */


void get_small_colors(ifstream& inFile, vector<smallColor>& colors, int numPixels) {
    for(int i = 0; i < numPixels; i++) {
        uint8_t red = read_binary8(inFile);
        uint8_t green = read_binary8(inFile);
        uint8_t blue = read_binary8(inFile);
        smallColor color = {red, green, blue};
		if(contains<smallColor>(colors, color)) {
			colors.push_back(color);
		}
    }
}


void get_big_colors(ifstream& inFile, vector<bigColor>& colors, int numPixels) {
    for(int i = 0; i < numPixels; i++) {
        uint16_t red = read_binary16(inFile);
        uint16_t green = read_binary16(inFile);
        uint16_t blue = read_binary16(inFile);
        bigColor color = {red, green, blue};
		if(contains<bigColor>(colors, color)) {
			colors.push_back(color);
		}
    }
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

// Writes metadata to output file

void write_metadata(ofstream& outFile, Image_Attributes& metadata) {
	outFile << "C6 " << metadata.width << " " << metadata.height << " " << metadata.intensity << " ";
}




// Writes sequence of colors, using 3 bytes to match intensity <= 255

void write_small_colors(ifstream& inFile, ofstream& outFile, vector<smallColor>& colors, uint8_t indexByteLength) {
    outFile << colors.size() << "\n";
    for(int i = 0; i < colors.size(); i++) {
    	smallColor color = colors[i];
    	write_binary8(outFile, color.r);
    	write_binary8(outFile, color.g);
    	write_binary8(outFile, color.b);
    }
}


// Writes sequence of colors, using 6 bytes to match intensity > 255

void write_big_colors(ifstream& inFile, ofstream& outFile, vector<bigColor>& colors, uint8_t indexByteLength) {
	outFile << colors.size() << "\n";
    for(int i = 0; i < colors.size(); i++) {
      bigColor color = colors[i];
      write_binary16(outFile, color.r);
      write_binary16(outFile, color.g);
      write_binary16(outFile, color.b);
    }
}


// Writes sequence of indexes corresponding to locations in the color vector, using the proper number of bytes per index

void write_small_pixels(ifstream& inFile, ofstream& outFile, vector<smallColor>& colors, int numPixels, uint8_t indexByteLength) {
    if (indexByteLength == 1) {
    	write_small_pixels_1b(inFile, outFile, colors, numPixels);
    } else if (indexByteLength == 2) {
		write_small_pixels_2b(inFile, outFile, colors, numPixels);
    } else if (indexByteLength == 4) {
    	write_small_pixels_4b(inFile, outFile, colors, numPixels);
    } else {
    	cerr << "Error: Incorrect indexByteLength: " << indexByteLength << "\n";  
    }
}

void write_small_pixels_1b(ifstream& inFile, ofstream& outFile, vector<smallColor>& colors, int numPixels) {
	for(int i = 0; i < numPixels; i++) {
        uint8_t red = read_binary8(inFile);
        uint8_t green = read_binary8(inFile);
        uint8_t blue = read_binary8(inFile);
        smallColor color = {red, green, blue};
        uint8_t index = index_of_1b(colors, color);
		if(index != -1) {
			write_binary8(outFile, index);
		} else {
        	cerr << "Invalid color index: " << index << "\n";
            exit(1);
		}
    }
}

void write_small_pixels_2b(ifstream& inFile, ofstream& outFile, vector<smallColor>& colors, int numPixels) {
	for(int i = 0; i < numPixels; i++) {
        uint8_t red = read_binary8(inFile);
        uint8_t green = read_binary8(inFile);
        uint8_t blue = read_binary8(inFile);
        smallColor color = {red, green, blue};
        uint8_t index = index_of_1b(colors, color);
		if(index != -1) {
			write_binary16(outFile, index);
		} else {
        	cerr << "Invalid color index: " << index << "\n";
            exit(1);
		}
    }
}

void write_small_pixels_4b(ifstream& inFile, ofstream& outFile, vector<smallColor>& colors, int numPixels) {
	for(int i = 0; i < numPixels; i++) {
        uint8_t red = read_binary8(inFile);
        uint8_t green = read_binary8(inFile);
        uint8_t blue = read_binary8(inFile);
        smallColor color = {red, green, blue};
        uint8_t index = index_of_1b(colors, color);
		if(index != -1) {
			write_binary32(outFile, index);
		} else {
        	cerr << "Invalid color index: " << index << "\n";
            exit(1);
		}
    }
}

void write_big_pixels_1b(ifstream& inFile, ofstream& outFile, vector<smallColor>& colors, int numPixels) {
	for(int i = 0; i < numPixels; i++) {
        uint8_t red = read_binary8(inFile);
        uint8_t green = read_binary8(inFile);
        uint8_t blue = read_binary8(inFile);
        smallColor color = {red, green, blue};
        uint8_t index = index_of_1b(colors, color);
		if(index != -1) {
			write_binary8(outFile, index);
		} else {
        	cerr << "Invalid color index: " << index << "\n";
            exit(1);
		}
    }
}

void write_big_pixels_2b(ifstream& inFile, ofstream& outFile, vector<smallColor>& colors, int numPixels) {
	for(int i = 0; i < numPixels; i++) {
        uint8_t red = read_binary8(inFile);
        uint8_t green = read_binary8(inFile);
        uint8_t blue = read_binary8(inFile);
        smallColor color = {red, green, blue};
        uint8_t index = index_of_1b(colors, color);
		if(index != -1) {
			write_binary16(outFile, index);
		} else {
        	cerr << "Invalid color index: " << index << "\n";
            exit(1);
		}
    }
}

void write_big_pixels_4b(ifstream& inFile, ofstream& outFile, vector<smallColor>& colors, int numPixels) {
	for(int i = 0; i < numPixels; i++) {
        uint8_t red = read_binary8(inFile);
        uint8_t green = read_binary8(inFile);
        uint8_t blue = read_binary8(inFile);
        smallColor color = {red, green, blue};
        uint8_t index = index_of_1b(colors, color);
		if(index != -1) {
			write_binary32(outFile, index);
		} else {
        	cerr << "Invalid color index: " << index << "\n";
            exit(1);
		}
    }
}

