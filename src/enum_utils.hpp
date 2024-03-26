#ifndef __ENUM_UTILS_HPP__
#define __ENUM_UTILS_HPP__

#include <string_view>
#include "external/magic_enum.hpp"

namespace prim
{
    template<class T>
    inline std::string_view enum_str(T enumValue)
    {
        return magic_enum::enum_name(enumValue);
    }
}

#endif // __ENUM_UTILS_HPP__