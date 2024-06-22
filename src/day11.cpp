#include <algorithm>
#include <cstdint>
#include <ranges>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

#include "inputs/day11.h"

namespace {

namespace vw = std::ranges::views;

using std::int64_t;

using Grid = std::vector<std::string>;

struct Galaxy {
  int64_t row{};
  int64_t col{};
};

using Galaxies = std::vector<Galaxy>;

std::vector<int64_t> getEmptyRows(const Grid &grid) {
  return grid | vw::enumerate | vw::filter([](const auto &p) {
           const auto &[index, line] = p;
           return !line.contains('#');
         }) |
         vw::keys | std::ranges::to<std::vector>();
}

std::vector<int64_t> getEmptyColumns(const Grid &grid) {
  return vw::iota(0z, std::ssize(grid.at(0))) |
         vw::filter([&](std::size_t col) {
           return !std::ranges::any_of(grid, [col](const std::string &line) {
             return line.at(col) == '#';
           });
         }) |
         std::ranges::to<std::vector>();
}

Galaxies getGalaxies(const Grid &grid) {
  Galaxies result;
  for (const auto &[row, line] : grid | vw::enumerate) {
    for (const auto &[col, c] : line | vw::enumerate) {
      if (c == '#')
        result.emplace_back(row, col);
    }
  }

  return result;
}

int64_t getDistance(int64_t lhs, int64_t rhs, const std::vector<int64_t> &empty,
                    int64_t emptyMultiplier) {
  const auto min = std::min(lhs, rhs);
  const auto max = std::max(lhs, rhs);

  auto result = max - min;
  for (int64_t x : empty) {
    if (x >= min && x <= max)
      result += emptyMultiplier - 1;
  }

  return result;
}

int64_t calculate(std::string_view input, int64_t emptyMultiplier) {
  const Grid grid = input | vw::split('\n') | std::ranges::to<Grid>();

  const auto galaxies = getGalaxies(grid);
  const auto emptyRows = getEmptyRows(grid);
  const auto emptyColumns = getEmptyColumns(grid);

  int64_t result = 0;

  for (const auto &leftGalaxy : galaxies) {
    for (const auto &rightGalaxy : galaxies) {
      result += getDistance(leftGalaxy.row, rightGalaxy.row, emptyRows,
                            emptyMultiplier);
      result += getDistance(leftGalaxy.col, rightGalaxy.col, emptyColumns,
                            emptyMultiplier);
    }
  }

  return result / 2;
}

int64_t solvePart1(std::string_view input) { return calculate(input, 2); }

int64_t solvePart2(std::string_view input) { return calculate(input, 1000000); }

TEST(day11, test) {
  EXPECT_EQ(solvePart1(day11::sample), 374);
  EXPECT_EQ(solvePart1(day11::input), 9795148);

  EXPECT_EQ(solvePart2(day11::sample), 82000210);
  EXPECT_EQ(solvePart2(day11::input), 650672493820);
}

} // anonymous namespace