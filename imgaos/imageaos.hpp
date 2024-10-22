//
// Created by finnb on 10/7/2024.
//

#ifndef IMAGEAOS_HPP
#define IMAGEAOS_HPP
#include "../common/progargs.hpp"
#include "../common/binaryio.hpp"


#include <vector>
#include <string>


struct smallColor{
    uint8_t r, g, b;
};
struct bigColor{
    uint16_t r, g, b;
};

void aos_maxlevel(int newIntensity)

void aos_resize();

void aos_cutfreq();

void aos_compress();

#endif //IMAGEAOS_HPP
