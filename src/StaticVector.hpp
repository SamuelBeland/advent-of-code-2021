#pragma once

#include "StringView.hpp"

namespace aoc
{
//==============================================================================
template<typename T, size_t CAPACITY>
class StaticVector
{
    std::array<T, CAPACITY> m_data;
    size_t m_size{};

    static_assert(std::is_trivially_destructible<T>::value, "StaticVector value type must be trivially destructible.");

public:
    //==============================================================================
    StaticVector() = default;
    explicit StaticVector(std::size_t const initial_size) : m_data(), m_size(initial_size) {}
    ~StaticVector() = default;
    StaticVector(StaticVector const &) = default;
    StaticVector(StaticVector &&) = default;
    StaticVector & operator=(StaticVector const &) = default;
    StaticVector & operator=(StaticVector &&) = default;
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
    T & push_back(T const & new_element) noexcept(!aoc::detail::IS_DEBUG)
    {
        assert(m_size < CAPACITY);
        return m_data[m_size++] = new_element;
    }
    T & push_back(T && new_element) noexcept(!aoc::detail::IS_DEBUG)
    {
        assert(m_size < CAPACITY);
        return m_data[m_size++] = std::forward<T>(new_element);
    }
    [[nodiscard]] constexpr StaticVector operator+(StaticVector const & other) noexcept(!aoc::detail::IS_DEBUG)
    {
        assert(m_size == other.m_size);
        auto result{ *this };
        std::transform(result.cbegin(), result.cend(), other.cbegin(), result.begin(), std::plus());
        return result;
    }
    void resize(std::size_t const size) noexcept(!aoc::detail::IS_DEBUG) { m_size = size; }
    //==============================================================================
    [[nodiscard]] size_t size() const noexcept { return m_size; }
};

} // namespace aoc