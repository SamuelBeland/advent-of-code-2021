// --- Day 2: Dive! ---
// Now, you need to figure out how to pilot this thing.
//
// It seems like the submarine can take a series of commands like forward 1, down 2, or up 3:
//
// forward X increases the horizontal position by X units.
// down X increases the depth by X units.
// up X decreases the depth by X units.
//
// Note that since you're on a submarine, down and up affect your depth, and so they have the opposite result of what
// you might expect.
//
// The submarine seems to already have a planned course (your puzzle input). You should probably figure out where it's
// going. For example:
//
// forward 5
// down 5
// forward 8
// up 3
// down 8
// forward 2
//
// Your horizontal position and depth both start at 0. The steps above would then modify them as follows:
//
// forward 5 adds 5 to your horizontal position, a total of 5.
// down 5 adds 5 to your depth, resulting in a value of 5.
// forward 8 adds 8 to your horizontal position, a total of 13.
// up 3 decreases your depth by 3, resulting in a value of 2.
// down 8 adds 8 to your depth, resulting in a value of 10.
// forward 2 adds 2 to your horizontal position, a total of 15.
//
// After following these instructions, you would have a horizontal position of 15 and a depth of 10. (Multiplying these
// together produces 150.)

// Calculate the horizontal position and depth you would have after following the planned course. What do you get if you
// multiply your final horizontal position by your final depth?

#include "StringView.hpp"
#include "utils.hpp"

namespace
{
using value_t = int;

enum class Direction { forward, down, up };

[[nodiscard]] Direction parse_direction(aoc::StringView const string) noexcept(!aoc::detail::IS_DEBUG)
{
    if (string == "forward") {
        return Direction::forward;
    }
    if (string == "down") {
        return Direction::down;
    }
    assert(string == "up");
    return Direction::up;
}

struct Displacement {
    Direction direction;
    value_t value;

    [[nodiscard]] static Displacement parse(aoc::StringView const string) noexcept(!aoc::detail::IS_DEBUG)
    {
        Displacement result;
        aoc::StringView direction_string;
        string.scan("{} {}", direction_string, result.value);
        result.direction = parse_direction(direction_string);
        return result;
    }
};

struct NoAim {
};

struct UseAim {
    value_t aim;
};

template<typename Aim>
struct Position_ : Aim {
    value_t x;
    value_t y;

    void apply_displacement(Displacement const & displacement) noexcept
    {
        static constexpr auto IS_AIM = std::is_base_of_v<UseAim, Position_>;
        auto const & value{ displacement.value };
        switch (displacement.direction) {
        case Direction::forward:
            x += value;
            if constexpr (IS_AIM) {
                y += aim * value;
            }
            return;
        case Direction::down:
            if constexpr (IS_AIM) {
                aim += value;
                return;
            }
            y += value;
            return;
        case Direction::up:
            if constexpr (IS_AIM) {
                aim -= value;
                return;
            }
            y -= value;
            return;
        }
        assert(false);
    }
};

template<typename Aim>
std::string day_2(char const * input_file_path) noexcept(!aoc::detail::IS_DEBUG)
{
    auto const input{ aoc::read_file(input_file_path) };
    aoc::StringView const view{ input };
    auto const displacements{ view.iterate_transform(Displacement::parse, '\n') };
    Position_<Aim> position{};
    for (auto const displacement : displacements) {
        position.apply_displacement(displacement);
    }
    auto const result{ position.x * position.y };
    return std::to_string(result);
}

} // namespace

//==============================================================================
std::string day_2_a(const char * input_file_path)
{
    return day_2<NoAim>(input_file_path);
}

//==============================================================================
std::string day_2_b(const char * input_file_path)
{
    return day_2<UseAim>(input_file_path);
}