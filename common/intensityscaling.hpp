//
// Created by eloim on 22/10/2024.
//

#ifndef INTENSITYSCALING_H
#define INTENSITYSCALING_H

#include "utility.hpp"
#include "binaryio.hpp"


void read_image_intensity_scaling (int newIntensity);
void intensity_smaller_255(const vector<int> & data, const ifstream &inputImageFile, const ofstream &outputImageFile);
void intensity_greater_255(const vector<int> & data, const ifstream &inputImageFile, const ofstream &outputImageFile);

#endif //INTENSITYSCALING_H
