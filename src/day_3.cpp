//--- Day 3: Binary Diagnostic ---
// The submarine has been making some odd creaking noises, so you ask it to produce a diagnostic report just in case.
//
// The diagnostic report (your puzzle input) consists of a list of binary numbers which, when decoded properly, can tell
// you many useful things about the conditions of the submarine. The first parameter to check is the power consumption.
//
// You need to use the binary numbers in the diagnostic report to generate two new binary numbers (called the gamma rate
// and the epsilon rate). The power consumption can then be found by multiplying the gamma rate by the epsilon rate.
//
// Each bit in the gamma rate can be determined by finding the most common bit in the corresponding position of all
// numbers in the diagnostic report. For example, given the following diagnostic report:
//
// 00100
// 11110
// 10110
// 10111
// 10101
// 01111
// 00111
// 11100
// 10000
// 11001
// 00010
// 01010
//
// Considering only the first bit of each number, there are five 0 bits and seven 1 bits. Since the most common bit is
// 1, the first bit of the gamma rate is 1.
//
// The most common second bit of the numbers in the diagnostic report is 0, so the second bit of the gamma rate is 0.
//
// The most common value of the third, fourth, and fifth bits are 1, 1, and 0, respectively, and so the final three bits
// of the gamma rate are 110.
//
// So, the gamma rate is the binary number 10110, or 22 in decimal.
//
// The epsilon rate is calculated in a similar way; rather than use the most common bit, the least common bit from each
// position is used. So, the epsilon rate is 01001, or 9 in decimal. Multiplying the gamma rate (22) by the epsilon rate
// (9) produces the power consumption, 198.
//
// Use the binary numbers in your diagnostic report to calculate the gamma rate and epsilon rate, then multiply them
// together. What is the power consumption of the submarine? (Be sure to represent your answer in decimal, not binary.)

#include "StringView.hpp"
#include "utils.hpp"

#include "StaticVector.hpp"
#include <numeric>

namespace
{
constexpr std::size_t MAX_BITS = 12;

using value_t = unsigned;
using bit_count_t = unsigned;
using exploded_value_t = aoc::StaticVector<bit_count_t, MAX_BITS>;
using samples_t = std::vector<exploded_value_t>;

auto constexpr parse_value = [](char const c) -> bit_count_t {
    assert(c == '0' || c == '1');
    return c == '0' ? 0 : 1;
};

auto constexpr parse_number = [](aoc::StringView const string) -> exploded_value_t {
    exploded_value_t result(string.size());
    std::ranges::transform(string, result.begin(), parse_value);
    return result;
};

auto constexpr parse_samples
    = [](aoc::StringView const string) -> samples_t { return string.split_transform(parse_number, '\n'); };

auto constexpr calculate_mode = [](samples_t const & samples) -> exploded_value_t {
    auto const half{ samples.size() / 2 };
    auto const is_over_half = [&](bit_count_t const value) -> bit_count_t { return value > half ? 1 : 0; };

    auto const sum{
        std::reduce(samples.cbegin(), samples.cend(), exploded_value_t{ samples.front().size() }, std::plus())
    };
    exploded_value_t result{ sum.size() };
    std::ranges::transform(sum, result.begin(), is_over_half);
    return result;
};

auto constexpr get_mask
    = [](std::size_t const size) -> value_t { return ~(std::numeric_limits<value_t>::max() << size); };

auto constexpr implode_value = [](exploded_value_t const & exploded) -> value_t {
    assert(std::ranges::all_of(exploded, [](auto const & value) { return value == 0 || value == 1; }));
    value_t result{};
    for (auto const & it : exploded) {
        result *= 2;
        if (it != 0) {
            result += 1;
        }
    }
    return result;
};

auto constexpr extract_gamma_and_epsilon_rates = [](exploded_value_t const & value) -> std::tuple<value_t, value_t> {
    auto const gamma{ implode_value(value) };
    auto const epsilon{ (~gamma) & get_mask(value.size()) };
    return std::make_tuple(gamma, epsilon);
};

} // namespace

//==============================================================================
std::string day_3_a(const char * input_file_path)
{
    auto const input{ aoc::read_file(input_file_path) };
    auto const samples{ parse_samples(input) };
    auto const mode{ calculate_mode(samples) };
    auto const [gamma, epsilon] = extract_gamma_and_epsilon_rates(mode);
    auto const result{ gamma * epsilon };

    return std::to_string(result);
}

//==============================================================================
std::string day_3_b(const char * input_file_path)
{
    return "0";
}