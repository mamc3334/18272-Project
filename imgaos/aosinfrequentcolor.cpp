//
// Created by ryanb on 10/22/2024.
//

#include "aosinfrequentcolor.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
//make a blank vector to store colors
//iterate through pixels
//if the pixel (the r, g, b value) is not in the vector, add it
//if the pixel (the r, g, b value) is in the vector, increase it's count
//sort the vector by count
//replace the n least frequent (lowest count) pixels with the most similar pixel determined by euclidian (Sqrt((r2-r1)^2+((g2-g1)^2+(b2-b1)^2))
struct Color {
    int r, g, b;
    int count;

    // Equality operator to check if two colors are the same
    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
};

void populatePixels(vector<color> &pixels, const Image_Attributes& photoData, ifstream& inFile)
{
    for(unsigned int i = 0; i < (photoData.height*photoData.width); i++){
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
std::sort(pixels.begin(), pixels.end(), [](const Color& a, const Color& b) {
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

//Calculate the difference between two colors based on euclidian difference
double colorDistance(const Color& c1, const Color& c2) {
    return sqrt(pow(c2.r - c1.r, 2) + pow(c2.g - c1.g, 2) + pow(c2.b - c1.b, 2));
}


//Iterate through each element of colorList to compare the selected color to every other color
//Start at the n'th element and work backwards
void changeInfrequentColors(vector<Color>& colorList, int n) {
	for (auto i = n; i > 0; i--) {
		int min, int index = 0
		for (auto i = n; i < colorList.size(); i++) {
			if (min > colordistance(colorList[n-i], colorList[i])){
				min = colordistance(colorList[n-i], colorList[i]);
				index = i
				};
		colorList[i] = colorList[index];

		}

}


void writeToPPM(const vector<Color>& pixels, const Image_Attributes& photoData, const string& outputFilePath) {
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
	vector<Color> pixels;
	populatePixels(pixels, photoData, inFile);

	// Number of least frequent colors to remove
	int n = 5;

	// Replace least frequent colors in the image
	changeInfrequentColors(pixels, n);

	// Output to new PPM file
	writeToPPM(pixels, photoData, "output_image.ppm");

	return 0;
}
#include "aosinfrequentcolor.hpp"
