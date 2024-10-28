//
// Created by finnb on 10/21/2024.
//

#include "utility.hpp"

void validate_metadata (const Image_Attributes &metadata) {
    if (metadata.width < 0 || metadata.height < 0 || metadata.intensity < 0 || metadata.magic_word != "P6") {
        cerr << "Invalid input photo file" << "\n";
        exit(1);
    }
}

Image_Attributes get_image_metadata(ifstream& imageFile)
{
    string magic_word;
    int width, height, intensity;
    imageFile >> magic_word >> width >> height >> intensity;
    Image_Attributes output = {magic_word, width, height, intensity};
    validate_metadata(output);
    return output;
}

void validate_metadata (const Image_Attributes &metadata) {
    if (metadata.width < 0 || metadata.height < 0 || metadata.intensity < 0 || metadata.magic_word != "P6") {
        cerr << "Invalid image metadata" << "\n";
        exit(1);
    }
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