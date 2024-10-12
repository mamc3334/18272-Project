//
// Created by finnb on 10/7/2024.
//
using namespace std;
#include <vector>
#include "imageaos.hpp"
#include <iostream>
#include <fstream>
#include "../common/binaryio.hpp"

std::vector<Color> imgColors;

void read_image_template (string filename) {
      ifstream imageFile(filename);
      if(!imageFile.is_open()) {
            cerr << "Failed to open file\n";
            exit(-1);
      }

      string magic_word, width, height, intensity;
      imageFile >> magic_word >> width >> height >> intensity;
      cout << magic_word << ", " << width << ", " << height << ", and " << intensity << "\n";
}
