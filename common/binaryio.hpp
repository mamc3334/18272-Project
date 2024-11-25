//
// Created by finnb on 10/7/2024.
//

#ifndef BINARYIO_HPP
#define BINARYIO_HPP
#include <fstream>
#include <cstdint>

std::uint16_t read_binary16 (std::istream & input);
void write_binary16 (std::ostream & output, std::uint16_t const & value);

std::uint8_t read_binary8 (std::istream & input);
void write_binary8 (std::ostream & output, std::uint8_t const & value);

void write_binary32(std::ostream & output, int const & value);
int read_binary32 (std::istream & input);
#endif //BINARYIO_HPP
