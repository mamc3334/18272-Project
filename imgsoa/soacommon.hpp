//
// Created by mcgaf on 10/25/2024.
//

#ifndef SOACOMMON_HPP
#define SOACOMMON_HPP
#include <cstdint>
#include <vector>
using namespace std;

struct bigArray
{
    vector<uint16_t> r;
    vector<uint16_t> g;
    vector<uint16_t> b;

    bool operator==(const bigArray& other) const {
        return (r == other.r && g == other.g && b == other.b);
    }
};
struct smallArray
{
    vector<uint8_t> r;
    vector<uint8_t> g;
    vector<uint8_t> b;

    bool operator==(const smallArray& other) const {
        return (r == other.r && g == other.g && b == other.b);
    }
};

#endif //SOACOMMON_HPP
