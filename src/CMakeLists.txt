add_executable(aoc2023)

target_sources(aoc2023 PUBLIC
  day01.cpp
  day02.cpp
  day03.cpp
  day04.cpp
  day05.cpp
  day06.cpp
)

target_link_libraries(aoc2023 PRIVATE
  GTest::gtest_main
  taocpp::pegtl
)

include(GoogleTest)
gtest_discover_tests(aoc2023)
