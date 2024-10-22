//
// Created by finnb on 10/21/2024.
//

#include "utility.hpp"
using namespace std;

struct Image_Attributes {
    std::string magic_word;
    int width, height, intensity;
};

std::vector<std::string> get_image_metadata (ifstream& imageFile) {
    string magic_word, width, height, intensity;
    imageFile >> magic_word >> width >> height >> intensity;
    vector<std::string> output = {magic_word, width, height, intensity};
    return output;
}
