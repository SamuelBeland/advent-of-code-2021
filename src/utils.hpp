#pragma once

#include "StringView.hpp"

#include <array>
#include <string>
#include <vector>

namespace aoc
{
//==============================================================================
std::string read_file(char const * path);

//==============================================================================
template<typename Separator>
std::vector<aoc::StringView> split(StringView const & string, Separator const & separator)
{
    return string.split(separator);
}

} // namespace aoc