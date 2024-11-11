//
// Created by finnb on 10/21/2024.
//

#include "utility.hpp"
#include <sys/stat.h>
#include <tuple>
using namespace std;

void validate_metadata (const string& word, const int width, const int height, const int intensity) {
    if (width < 0 || height < 0 || intensity < 0 || word != "P6") {
        cerr << "Invalid input photo file" << "\n";
        exit(1);
    }
}

Image_Attributes get_image_metadata(ifstream& imageFile)
{
    string magic_word;
    int width, height, intensity;
    imageFile >> magic_word >> width >> height >> intensity;
    validate_metadata(magic_word, width, height, intensity);
    Image_Attributes output = {magic_word, static_cast<unsigned int>(width), static_cast<unsigned int>(height), intensity};
    imageFile.ignore(256,'\n');
    return output;
}

void setInFile(const string& in)
{
    inFile = in;
}

void setOutFile(const string& out)
{
    outFile = out;
}

string getInFile()
{
    return inFile;
}

string getOutFile()
{
    return outFile;
}

void displayInfo()
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes metadata = get_image_metadata(imageFile);
    imageFile.close();
    cout <<
        "Input:   " << getInFile() << "\n" <<
            "Output:   " << getOutFile() << "\n" <<
                "Operation:   " << "info\n" <<
                    "Magic Word:  " << metadata.magic_word <<
                        "Image Size:   " << metadata.width << "x" << metadata.height << "\n" <<
                            "Max Level:   " << metadata.intensity << "\n";

}