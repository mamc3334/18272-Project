//
// Created by finnb on 10/7/2024.
//
using namespace std;
#include <vector>
#include "imageaos.hpp"
#include <iostream>
#include <fstream>

std::vector<Color> imgColors;
//Prerequisite -> readMetaDataFromFile(file, false)
void aos_readBytes(){
      //TODO: should be using getByte?


std::vector<std::string> get_image_metadata (string filename) {
      ifstream imageFile(filename);
      if(!imageFile.is_open()) {
            cerr << "Failed to open file\n";
            exit(-1);
      }

      string magic_word, width, height, intensity;
      imageFile >> magic_word >> width >> height >> intensity;
      vector<std::string> output = {width, height, intensity};
      return output;
}
