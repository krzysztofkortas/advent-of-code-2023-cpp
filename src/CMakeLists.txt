add_executable(aoc2023)

target_sources(aoc2023 PUBLIC
  day01.cpp
  day02.cpp
  day03.cpp
  day04.cpp
  day05.cpp
  day06.cpp
  day07.cpp
  day09.cpp
  day10.cpp
  day11.cpp
  day13.cpp
  day14.cpp
  day15.cpp
  day16.cpp
)

target_link_libraries(aoc2023 PRIVATE
  GTest::gtest_main
  taocpp::pegtl
)

include(GoogleTest)
gtest_discover_tests(aoc2023)
