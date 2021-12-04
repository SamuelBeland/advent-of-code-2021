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

//==============================================================================
template<typename T, size_t MAX_SIZE>
class Static_Vector
{
    std::array<T, MAX_SIZE> m_data;
    size_t m_size{};

    static_assert(std::is_trivially_destructible<T>::value, "Static_Vector value type must be trivially destructible.");

public:
    //==============================================================================
    using value_type = T;
    //==============================================================================
    [[nodiscard]] auto begin() noexcept { return m_data.begin(); }
    [[nodiscard]] auto end() noexcept { return m_data.begin() + m_size; }
    [[nodiscard]] auto begin() const noexcept { return m_data.begin(); }
    [[nodiscard]] auto end() const noexcept { return m_data.begin() + m_size; }
    [[nodiscard]] auto cbegin() const noexcept { return m_data.cbegin(); }
    [[nodiscard]] auto cend() const noexcept { return m_data.cbegin() + m_size; }
    //==============================================================================
    T & push_back(T const & new_element) noexcept(!detail::IS_DEBUG)
    {
        assert(m_size < MAX_SIZE);
        return m_data[m_size++] = new_element;
    }
    T & push_back(T && new_element) noexcept(!detail::IS_DEBUG)
    {
        assert(m_size < MAX_SIZE);
        return m_data[m_size++] = std::forward<T>(new_element);
    }
    //==============================================================================
    [[nodiscard]] size_t size() const noexcept { return m_size; }
};

} // namespace aoc