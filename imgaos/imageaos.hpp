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

void aos_read_bytes(const Image_Attributes& meta);

void aos_maxlevel();

void aos_resize();

void aos_cutfreq();

void aos_compress();

#endif //IMAGEAOS_HPP
