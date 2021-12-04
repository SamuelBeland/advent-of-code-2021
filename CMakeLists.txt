cmake_minimum_required(VERSION 3.16)

project(ADVENT_OF_CODE_2021)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

add_subdirectory("lib/catch2")

# This copies the default input text files. 
# It also configures a header file containing the basic function
#  signatures and the paths to the input files.
add_subdirectory("resources")

include_directories("include" "${CMAKE_BINARY_DIR}/resources")

add_library(adventlib STATIC)
target_sources(adventlib PRIVATE
    "src/utils.hpp"      "src/utils.cpp"
    "src/StringView.hpp" "src/StringView.cpp"
    "src/narrow.hpp"

    "src/day_1.cpp")

add_executable(main)
target_sources(main PRIVATE "src/main.cpp")
target_link_libraries(main adventlib)

add_executable(tests)
target_sources(tests PRIVATE "tests/main.cpp")
target_link_libraries(tests adventlib catch2)
