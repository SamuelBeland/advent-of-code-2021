#include "StringView.hpp"

namespace aoc
{
StringView::StringView(std::string const & string) noexcept : m_data(string.data()), m_size(string.size())
{
}

std::string StringView::to_std_string() const
{
    return std::string{ m_data, m_size };
}

std::size_t StringView::count(StringView const & other) const noexcept
{
    std::size_t result{};
    auto const * element_end{ find(other) };
    while (element_end != cend()) {
        ++result;
        element_end = StringView{ element_end + other.size(), cend() }.find(other);
    }
    return result;
}

char const * StringView::find(StringView const & other) const noexcept
{
    return std::search(cbegin(), cend(), std::boyer_moore_searcher(other.cbegin(), other.cend()));
}

bool StringView::contains(StringView const & other) const noexcept
{
    return find(other) != cend();
}

StringView StringView::up_to(StringView const & other) const noexcept
{
    if (other.empty()) {
        return *this;
    }
    return StringView{ cbegin(), find(other) };
}

StringView StringView::starting_after(StringView const & other) const noexcept
{
    auto const * find_result{ find(other) };
    auto const * new_begin{ find_result == cend() ? find_result : find_result + other.size() };
    return StringView{ new_begin, cend() };
}

StringView StringView::cropped(std::size_t const amount) const noexcept(!detail::IS_DEBUG)
{
    assert(m_size >= amount * 2);
    return StringView{ cbegin() + amount, m_size - amount * 2 };
}
} // namespace aoc
