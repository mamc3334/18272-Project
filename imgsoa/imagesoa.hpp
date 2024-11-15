//
// Created by mcgaf on 10/25/2024.
//

#ifndef IMAGESOA_HPP
#define IMAGESOA_HPP
#include "soasize.hpp"
#include "soainfrequentcolor.hpp"
#include "soacompress.hpp"
#include "../common/utility.hpp"
#include "soacommon.hpp"

void soa_resize(Image_Attributes& NewImageData);

void soa_cutfreq(size_t num);

void soa_compress();

#endif //IMAGESOA_HPP
