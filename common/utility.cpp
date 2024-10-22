//
// Created by finnb on 10/21/2024.
//

#include "utility.hpp"

Image_Attributes get_image_metadata(ifstream& imageFile)
{
    string magic_word;
    int width, height, intensity;
    imageFile >> magic_word >> width >> height >> intensity;
    Image_Attributes output = {magic_word, width, height, intensity};
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
    cout << "Display Info" << endl;
    /* TODO: display metadata to stdout
     * Open file, use get line, print meta data
     * Do we need to verify file has correct magic number?
     * This will be similar duplicate as first steps for aos/soa file reads
     */
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes metadata = get_image_metadata(imageFile);
    imageFile.close();
    // TODO: Check bounds of metadata vector?
    // TODO: Check if metadata is valid: magic number, are there min/max width, height, intensity
    cout <<
        "Input:   " << getInFile() << "\n" <<
            "Output:   " << getOutFile() << "\n" <<
                "Operation:   " << "info\n" <<
                    "Magic Word:  " << metadata.magic_word <<
                        "Image Size:   " << metadata.width << "x" << metadata.height << "\n" <<
                            "Max Level:   " << metadata.intensity << "\n";

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
    cout << "Display Info" << endl;
    /* TODO: display metadata to stdout
     * Open file, use get line, print meta data
     * Do we need to verify file has correct magic number?
     * This will be similar duplicate as first steps for aos/soa file reads
     */
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes metadata = get_image_metadata(imageFile);
    imageFile.close();
    // TODO: Check bounds of metadata vector?
    // TODO: Check if metadata is valid: magic number, are there min/max width, height, intensity
    cout <<
        "Input:   " << getInFile() << "\n" <<
            "Output:   " << getOutFile() << "\n" <<
                "Operation:   " << "info\n" <<
                    "Magic Word:  " << metadata.magic_word <<
                        "Image Size:   " << metadata.width << "x" << metadata.height << "\n" <<
                            "Max Level:   " << metadata.intensity << "\n";

}