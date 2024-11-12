//
// Created by ryanb on 10/22/2024.
//

#include "aosinfrequentcolor.hpp"
#include "../common/binaryio.hpp"
#include "../common/utility.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;
//make a blank vector to store colors
//iterate through pixels
//if the pixel (the r, g, b value) is not in the vector, add it
//if the pixel (the r, g, b value) is in the vector, increase it's count
//sort the vector by count
//replace the n least frequent (lowest count) pixels with the most similar pixel determined by euclidian (Sqrt((r2-r1)^2+((g2-g1)^2+(b2-b1)^2))


void populatePixels(vector<color> &pixels, const Image_Attributes& photoData, ifstream& inFile)
{
    pixels.resize(photoData.width * photoData.height);
    for(int i = 0; i < (photoData.height*photoData.width); i++){
        pixels[i]= {.r=read_binary8(inFile), .g=read_binary8(inFile), .b=read_binary8(inFile)};
        }
    inFile.close();
}

vector<color> countColors(const vector<color>& pixels) {
    vector<color> colorList;

    for (const auto& pixel : pixels) {
        auto it = find(colorList.begin(), colorList.end(), pixel);
        if (it != colorList.end()) {
            // If the color is already in the vector, increase its count
            it->count++;
        } else {
            // If the color is not in the vector, add it with a count of 1
            color newColor = pixel;
            newColor.count = 1;
            colorList.push_back(newColor);
        }
    }
    return colorList;
}

//Sort the pixels first by count, then by red, then by green, then by blue
void sortColors(vector<color>& pixels) {
	std::sort(pixels.begin(), pixels.end(), [](const color& a, const color& b) {
    	// First, sort by count (frequency) in ascending order
    	if (a.count != b.count) {
    	    return a.count < b.count;
    	}
    	// If counts are the same, sort by red value
    	if (a.r != b.r) {
        	return a.r < b.r;
    	}
    	// If red values are the same, sort by green value
    	if (a.g != b.g) {
       		return a.g < b.g;
    	}
    	// If green values are the same, sort by blue value
    	return a.b < b.b;
	});
}
//Calculate the difference between two colors based on euclidian difference
double colorDistance(const color& c1, const color& c2) {
    return sqrt(pow(c2.r - c1.r, 2) + pow(c2.g - c1.g, 2) + pow(c2.b - c1.b, 2));
}


//Iterate through each element of colorList to compare the selected color to every other color
//Start at the n'th element and work backwards
// Replace the n least frequent colors with their closest remaining color
void changeInfrequentColors(vector<color>& pixels, int n) {
    // Count color frequencies and sort by least frequent
    vector<color> colorList = countColors(pixels);
    sortColors(colorList);

    // Process only the n least frequent colors
    for (int i = 0; i < n; ++i) {
        color& targetColor = colorList[i];
        int minDistance = 100000;//arbitrary big number
        int closestIndex = -1;

        // Find the closest color among more frequent colors
        for (int j = n; j < colorList.size(); ++j) {
            double distance = colorDistance(targetColor, colorList[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = j;
            }
        }

        // Replace each instance of the infrequent color in pixels with the closest color
        if (closestIndex != -1) {
            for (auto& pixel : pixels) {
                if (pixel == targetColor) {
                    pixel = colorList[closestIndex];
                }
            }
        }
    }
}

void writeToPPM(const vector<color>& pixels, const Image_Attributes& photoData, const string& outputFilePath){
    ofstream outFile(outputFilePath, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    // PPM header
    outFile << "P6\n";
    outFile << photoData.width << " " << photoData.height << "\n";
    outFile << "255\n"; // Max color value

    // Write RGB pixel data
    for (const auto& pixel : pixels) {
        outFile.put(static_cast<unsigned char>(pixel.r));
        outFile.put(static_cast<unsigned char>(pixel.g));
        outFile.put(static_cast<unsigned char>(pixel.b));
    }

    outFile.close();
    cout << "Image written to " << outputFilePath << endl;
}

//TO BE FINISHED
int main(int argc, char* argv[]) {
	Image_Attributes photoData;
	ifstream inFile("path_to_image.ppm", ios::binary);
	if (!inFile.is_open()) {
	    cerr << "Error: Unable to open file.\n";
	    return 1;
	}

	// Initialize and populate pixels
	vector<color> pixels;
	populatePixels(pixels, photoData, inFile);

	// Number of least frequent colors to remove
	/int n = 5;

	// Replace least frequent colors in the image
	changeInfrequentColors(pixels, n);

	// Output to new PPM file
	writeToPPM(pixels, photoData, "output_image.ppm");

	return 0;
}
