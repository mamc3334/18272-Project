//
// Created by finnb on 10/7/2024.
//

#ifndef IMAGEAOS_HPP
#define IMAGEAOS_HPP
#include "../common/progargs.hpp"


#include <vector>
#include <string>

struct Color {
    int r, g, b;
};

struct Image_Attributes {
    std::string magic_word;
    int width, height, intensity;
};

std::vector<std::string> get_image_metadata (std::string filename);


#endif //IMAGEAOS_HPP
