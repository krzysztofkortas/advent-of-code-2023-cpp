add_executable(aoc2023)

target_sources(
    aoc2023
    PRIVATE day01.cpp
            day02.cpp
            day03.cpp
            day04.cpp
            day05.cpp
            day06.cpp
            day07.cpp
            day08.cpp
            day09.cpp
            day10.cpp
            day11.cpp
            day12.cpp
            day13.cpp
            day14.cpp
            day15.cpp
            day16.cpp
            day17.cpp
            day18.cpp
            day19.cpp
            day20.cpp
            day21.cpp
            day22.cpp
            day23.cpp
            day24.cpp
            day25.cpp)

target_sources(
    aoc2023
    PRIVATE FILE_SET
            modules
            TYPE
            CXX_MODULES
            FILES
            inputs/day01.cppm
            inputs/day02.cppm
            inputs/day03.cppm
            inputs/day04.cppm
            inputs/day05.cppm
            inputs/day06.cppm
            inputs/day07.cppm
            inputs/day08.cppm
            inputs/day09.cppm
            inputs/day10.cppm
            inputs/day11.cppm
            inputs/day12.cppm
            inputs/day13.cppm
            inputs/day14.cppm
            inputs/day15.cppm
            inputs/day16.cppm
            inputs/day17.cppm
            inputs/day18.cppm
            inputs/day19.cppm
            inputs/day20.cppm
            inputs/day21.cppm
            inputs/day22.cppm
            inputs/day23.cppm
            inputs/day24.cppm
            inputs/day25.cppm
            utils.cppm)

target_link_libraries(
    aoc2023
    PRIVATE Boost::graph
            GTest::gtest_main
            taocpp::pegtl
            z3::libz3)

include(GoogleTest)
gtest_discover_tests(aoc2023)
