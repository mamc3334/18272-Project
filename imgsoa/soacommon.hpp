//
// Created by mcgaf on 10/25/2024.
//

#ifndef SOACOMMON_HPP
#define SOACOMMON_HPP
#include <cstdint>
#include <tuple>
using namespace std;

struct photo16
{
    uint16_t r[];
    uint16_t g[];
    uint16_t b[];
};
struct photo8
{
    uint8_t r[];
    uint8_t g[];
    uint8_t b[];
};

#endif //SOACOMMON_HPP
