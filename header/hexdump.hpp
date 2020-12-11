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

        // not usable if <array> is not included:
#ifdef _GLIBCXX_ARRAY

        //! create Hexdump from std::array
        template <typename T, unsigned long n>
        explicit inline Hexdump(const std::array<T, n>& array, size_t line_width = DEFAULT_LINE_WIDTH) :
                Hexdump(&array[0], (n * sizeof(T)), line_width) { }
#endif

        // not usable if <vector> is not included:
#if defined _GLIBCXX_VECTOR || defined _GLIBCXX_PROFILE_VECTOR || defined _GLIBCXX_DEBUG_VECTOR

        //! create Hexdump from std::vector
        template <typename T>
        explicit inline Hexdump(const std::vector<T>& vector, size_t line_width = DEFAULT_LINE_WIDTH) :
                Hexdump(&vector[0], (vector.size() * sizeof(T)), line_width) { }
#endif

        //! get the hex dump string
        inline const std::string& str() const { return _str; };
};

//! write Hexdump to output stream
inline std::ostream& operator << (std::ostream& os, const Hexdump& hex)
{
    return os << hex.str();
}

} /* namespace Hexdump */
} /* namespace Koesling */
} /* namespace de */

