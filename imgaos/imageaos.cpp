//
// Created by finnb on 10/7/2024.
//
using namespace std;
#include <vector>
#include "imageaos.hpp"
#include <iostream>
#include <fstream>

void aos_readBytes(){
      char currChar;
      currChar = imageFile.get();
      if(currChar != 'P' && currChar != 'C') {
            cerr << "Invalid magic number:\t" << currChar << "\n";
      }
      currChar = imageFile.get();
      if(currChar != '6') {
            cerr << "Invalid magic number:\t" << currChar << "\n";
      }

      // Get width

      // Get height

      // Get intensity


      // This won't work
      while (imageFile.get(currChar)) {
            int r, g, b;
            r = int(currChar);
            imageFile.get(currChar);
            g = int(currChar);
            imageFile.get(currChar);
            b = int(currChar);
            Color pixel = {r, g, b};
            imgColors.push_back(pixel);
      }
}
