//
// Created by mcgaf on 10/25/2024.
//

#ifndef SOACOMMON_HPP
#define SOACOMMON_HPP
#include <cstdint>
#include <vector>
#include <tuple>
using namespace std;

struct bigArray
{
    vector<uint16_t> r;
    vector<uint16_t> g;
    vector<uint16_t> b;
};
struct smallArray
{
    vector<uint8_t> r;
    vector<uint8_t> g;
    vector<uint8_t> b;
};

#endif //SOACOMMON_HPP
