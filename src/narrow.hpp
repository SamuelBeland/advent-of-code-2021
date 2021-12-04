#pragma once

#include <cassert>

#include <type_traits>

#if defined(NDEBUG)
//==============================================================================
/** Does a static_cast.
 *
 * On debug builds, it also verifies that the original value is preserved. */
template<typename To, typename From>
constexpr To narrow(From const & value) noexcept
{
    return static_cast<To>(value);
}
#else
//==============================================================================
/** Does a static_cast.
 *
 * On Windows and Linux debug builds, it also verifies that the original value is preserved. */
template<typename To, typename From>
[[nodiscard]] constexpr To narrow(From const & value)
{
    static_assert(std::is_scalar_v<From> && std::is_scalar_v<To>, "narrow() can only be used with scalar types.");

    auto const result{ static_cast<To>(value) };

    if constexpr (std::is_signed_v<From> != std::is_signed_v<To>) {
        // If you hit this assertion, it means that you tried casting a negative value into an unsigned type.
        assert(value >= 0);
        // If you hit this assertion, it means that you tried casting a positive value into a signed type that was to
        // narrow for it.
        assert(result >= 0);
    }

    auto const sanity_check{ static_cast<From>(result) };

    // If you hit this assertion, it either means that you tried casting a value into a type that was too narrow for it
    // or that you loss precision when going to of from a floating point type.
    assert(sanity_check == value);

    return result;
}
#endif