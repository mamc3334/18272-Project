//
// Created by finnb on 10/7/2024.
//
#include "imagesoa.hpp"
#include <vector>
#include <iostream>
using namespace std;

void soa_resize(Image_Attributes& NewImageData)
{
    ifstream imageFile(getInFile());
    if(!imageFile.is_open()) {
        cerr << "Failed to open file\n";
        exit(-1);
    }
    const Image_Attributes OldImageData = get_image_metadata(imageFile);
    ofstream outputImageFile(getOutFile());
    if(!outputImageFile.is_open()) {
        cerr << "Failed to open output file\n";
        exit(-1);
    }
    NewImageData.magic_word = OldImageData.magic_word;
    NewImageData.intensity = OldImageData.intensity;
    outputImageFile << NewImageData.magic_word << "\n" << NewImageData.width << "\n" << NewImageData.height << "\n" << NewImageData.intensity << "\n";
    if(NewImageData.intensity > IntensityCutoff)
    {
        bigArray oldImage;
        soasize_old_image_16(oldImage, OldImageData, imageFile);
        soasize_resize_16(oldImage, OldImageData, NewImageData, outputImageFile);
    }
    else
    {
        smallArray oldImage;
        soasize_old_image_8(oldImage, OldImageData, imageFile);
        soasize_resize_8(oldImage, OldImageData, NewImageData, outputImageFile);
    }
    imageFile.close();
    outputImageFile.close();
}

void soa_cutfreq(int num) {
  //TODO
  cout <<num<<endl;
  //TEMP
}


void soa_compress() {
  //TODO
}
