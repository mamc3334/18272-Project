//
// Created by finnb on 10/7/2024.
//

#include "binaryio.hpp"


std::uint16_t read_binary16 (std::istream & input) {
    std::uint16_t value;

    // Converts pointer to a 16-bit integer to a pointer to a character
    // NOLINTNEXTLINE(cppcoreguidelines−pro−type−reinterpret−cast)
    char* two_bytes = reinterpret_cast<char*> (&value);
    // Copies sizeof(value) bits from the input stream into the two_bytes char*
    input.read(two_bytes, sizeof(value));
    return value;
}

std::uint16_t read_little_endian_binary16 (std::istream & input) {
    std::uint8_t first = read_binary8(input);
    std::uint8_t second = read_binary8(input);
    std::uint16_t value = (second << 8) | first;
    return value;
}

void write_binary16 (std::ostream & output, std::uint16_t const & value) {
    char const* two_bytes = reinterpret_cast<char const*>(&value);
    // NOLINTNEXTLINE(cppcoreguidelines−pro−type−reinterpret−cast)
    output.write(two_bytes, sizeof(value));
}

void write_little_endian_binary16 (std::ostream & output, std::uint16_t const & value)
{
    write_binary8(output, static_cast<uint8_t>(value&0xFF));
    write_binary8(output, static_cast<uint8_t>(value>>8));
}

std::uint8_t read_binary8 (std::istream & input) {
    std::uint8_t value;

    // Converts pointer to a 16-bit integer to a pointer to a character
    // NOLINTNEXTLINE(cppcoreguidelines−pro−type−reinterpret−cast)
    char* byte = reinterpret_cast<char*> (&value);
    // Copies sizeof(value) bits from the input stream into the two_bytes char*
    input.read(byte, sizeof(value));
    return value;
}

void write_binary8 (std::ostream & output, std::uint8_t const & value) {
    char const* byte = reinterpret_cast<char const*>(&value);
    // NOLINTNEXTLINE(cppcoreguidelines−pro−type−reinterpret−cast)
    output.write(byte, sizeof(value));
}