//
// Created by finnb on 10/22/2024.
//

#ifndef AOSCOMMON_HPP
#define AOSCOMMON_HPP
#include <iostream>
using namespace std;

struct smallColor{
    uint8_t r, g, b;

    bool operator==(const smallColor &other) const{
      return r == other.r && g == other.g && b == other.b;
    }
};
struct bigColor{
    uint16_t r, g, b;

    bool operator==(const bigColor &other) const{
        return r == other.r && g == other.g && b == other.b;
    }
};



#endif //AOSCOMMON_HPP
