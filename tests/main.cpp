#define CATCH_CONFIG_MAIN
#include <catch2.hpp>

#include <resources.hpp>

//==============================================================================
TEST_CASE("day_1_a")
{
    REQUIRE(day_1_a(inputs::TEST_1_A_1) == "7");
    REQUIRE(day_1_a(inputs::DAY_1) == "1532");
}

//==============================================================================
TEST_CASE("day_1_b")
{
    REQUIRE(day_1_b(inputs::TEST_1_A_1) == "5");
    REQUIRE(day_1_b(inputs::DAY_1) == "1571");
}

//==============================================================================
#ifdef NDEBUG
TEST_CASE("Benchmarks")
{
    for (auto day_it{ DAYS.crbegin() }; day_it != DAYS.crend(); ++day_it) {
        BENCHMARK(day_it->name) { return day_it->function(); };
    }

    BENCHMARK("ALL")
    {
        std::string result;
        for (auto const & day : DAYS) {
            result.append(day.function());
        }
        return result;
    };
}
#endif
