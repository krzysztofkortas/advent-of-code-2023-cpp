add_executable(aoc2023)

target_sources(aoc2023 PUBLIC
  day01.cpp
)

target_link_libraries(aoc2023 PRIVATE
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(aoc2023)
