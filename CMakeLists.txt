cmake_minimum_required(VERSION 3.28)
project(aoc2023 CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_GENERATOR "Ninja")
add_compile_options(
  -pedantic
  -Wall
  -Wextra
)

include(CTest)

find_package(GTest CONFIG REQUIRED)
find_package(pegtl CONFIG REQUIRED)

add_subdirectory(src)
