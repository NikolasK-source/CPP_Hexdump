/*
 * \file hexdump.hpp
 * \brief header file de::Koesling::Hexdump::Hexdump
 *
 * required compiler options:
 *          -std=c++11 (or higher)
 *
 * recommended compiler options:
 *          -O2
 *
 * Copyright (c) 2020 Nikolas Koesling
 */

#pragma once

#include <string>
#include <ostream>

namespace de {
namespace Koesling {
namespace Hexdump {

//! default line width
constexpr size_t DEFAULT_LINE_WIDTH = 80;

class Hexdump final
{
    private:
        std::string _str;
    public:
        /*! \brief creates a hex dump
         *
         * arguments:
         *      data        data field
         *      size        size of data field (in bytes)
         *      line_width  max line width of returned string
         */
        Hexdump(const void* data, size_t size, size_t line_width = DEFAULT_LINE_WIDTH);
        ~Hexdump() {};

        //! get the hex dump string
        inline const std::string& str() const;
};

template<typename T>
Hexdump get_Hexdump(T data, size_t line_width = DEFAULT_LINE_WIDTH)
{
    return Hexdump(&data, sizeof(T), line_width);
}

std::ostream& operator << (std::ostream& os, const Hexdump& hex);

inline const std::string& Hexdump::str( ) const
{
    return _str;
}

} /* namespace Hexdump */
} /* namespace Koesling */
} /* namespace de */
