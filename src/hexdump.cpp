/*
 * \file hexdump.cpp
 * \brief source file de::Koesling::Hexdump::Hexdump
 *
 * required compiler options:
 *          -std=c++11 (or higher)
 *
 * recommended compiler options:
 *          -O2
 *
 * Copyright (c) 2020 Nikolas Koesling
 */

#include "hexdump.hpp"
#include <iomanip>
#include <memory>
#include <sstream>

namespace de {
namespace Koesling {
namespace Util {

typedef uint8_t byte_t;  //!< 1 byte data type

constexpr size_t MIN_LINE_WIDTH = 4;     //!< minimum line width (byte(2) + blank(1) + ascii(1) = 4)
constexpr byte_t BYTE_MASK      = 0xFF;  //!< uses as mask for the least significant byte


Hexdump::Hexdump(const void *data, size_t size, size_t line_width) {
    // not data --> no hex dump --> empty string
    if (size == 0) {
        _str = std::string();
        return;
    }

    if (line_width < MIN_LINE_WIDTH)
        throw std::invalid_argument(std::string(__PRETTY_FUNCTION__) + ": line width to small (must be at least " +
                                    std::to_string(MIN_LINE_WIDTH) + ")!");

    if (data == nullptr)
        throw std::invalid_argument(std::string(__PRETTY_FUNCTION__) + ": data must not be a null pointer!");

    // number of bytes printed per line
    // each byte printed as: 2 digits hex + blank + ASCII char ( = 4 chars )
    size_t bytes_per_line = line_width / 4;

    // ASCII output buffer
    std::unique_ptr<char[]> ascii(new char[bytes_per_line + 1]);
    ascii[bytes_per_line] = 0;  // zero (\0) termination

    // return value string stream
    std::ostringstream hex_dump;
    hex_dump << std::setfill('0') << std::hex;

    // data as byte type pointer
    auto byte_data = reinterpret_cast<const byte_t *>(data);

    size_t line_bytes = 0;  // number of bytes in the current line
    for (size_t i = 0; i < size; i++) {
        // data output
        hex_dump << std::setw(2) << (byte_data[i] & BYTE_MASK);

        // write data to ASCII buffer (invisible chars are replaced with '.')
        ascii[i % bytes_per_line] = isgraph(byte_data[i]) ? static_cast<char>(byte_data[i]) : '.';

        hex_dump << ' ';

        // output ASCII buffer and do line break (if not last line)
        if (++line_bytes >= bytes_per_line) {
            hex_dump << std::string(ascii.get());
            if ((i + 1) < size) hex_dump << std::endl;
            line_bytes = 0;
        }
    }

    // get number of bytes in incomplete last line
    size_t last_line_bytes = size % bytes_per_line;

    // output dummy bytes (if required)
    if (last_line_bytes) {
        auto dummies = bytes_per_line - last_line_bytes;  // number of dummy bytes

        hex_dump << std::setfill(' ');
        hex_dump << std::setw(static_cast<int>(dummies) * 3) << "";  // output "empty bytes"
        ascii[last_line_bytes] = 0;                                  // move zero termination
        hex_dump << std::string(ascii.get());
    }

    // store hex dump string
    _str = hex_dump.str();
}

} /* namespace Util */
} /* namespace Koesling */
} /* namespace de */
