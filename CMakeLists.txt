cmake_minimum_required(VERSION 3.16)

project(ADVENT_OF_CODE_2021)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# This copies the default input text files.
# It also configures a header file containing the basic function
# signatures and the paths to the input files.
add_subdirectory("resources")

include_directories("include" "${CMAKE_BINARY_DIR}/resources")

add_library(adventlib STATIC)
target_sources(adventlib PRIVATE "src/utils.hpp"
                                 "src/utils.cpp"
                                 "src/StringView.hpp"
                                 "src/StringView.cpp"
                                 "src/narrow.hpp"
                                 "src/StaticVector.hpp"
                                 "src/day_1.cpp"
                                 "src/day_2.cpp"
                                 "src/day_3.cpp"
)

add_executable(main)
target_sources(main PRIVATE "src/main.cpp")
target_link_libraries(main adventlib)

add_executable(tests)
target_sources(tests PRIVATE "tests/main.cpp")

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(tests PRIVATE Catch2::Catch2
                                    adventlib)
