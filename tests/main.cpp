#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <resources.hpp>

//==============================================================================
TEST_CASE("day_1_a")
{
    REQUIRE(day_1_a(inputs::TEST_1_A_1) == "7");
    REQUIRE(day_1_a(inputs::DAY_1) == "1532");
}

TEST_CASE("day_1_b")
{
    REQUIRE(day_1_b(inputs::TEST_1_A_1) == "5");
    REQUIRE(day_1_b(inputs::DAY_1) == "1571");
}

//==============================================================================
TEST_CASE("day_2_a")
{
    REQUIRE(day_2_a(inputs::TEST_2_A_1) == "150");
    REQUIRE(day_2_a(inputs::DAY_2) == "2019945");
}

TEST_CASE("day_2_b")
{
    REQUIRE(day_2_b(inputs::TEST_2_A_1) == "900");
    REQUIRE(day_2_b(inputs::DAY_2) == "1599311480");
}

//==============================================================================
TEST_CASE("day_3_a")
{
    REQUIRE(day_3_a(inputs::TEST_3_A_1) == "198");
    // REQUIRE(day_3_a(inputs::DAY_3) == "");
}

// TEST_CASE("day_3_b")
//{
//    REQUIRE(day_3_b(inputs::TEST_3_A_1) == "");
//    REQUIRE(day_3_b(inputs::DAY_3) == "");
//}

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
