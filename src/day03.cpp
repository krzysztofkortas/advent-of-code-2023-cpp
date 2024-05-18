#include <algorithm>
#include <cctype>
#include <functional>
#include <print>
#include <ranges>
#include <regex>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

#include "inputs/day03.h"

#include <iostream>

namespace {

namespace vw = std::ranges::views;

struct Pos {
  std::int64_t row{};
  std::int64_t col{};
};

struct Number {
  Pos pos;
  std::string value;
};

using Numbers = std::vector<Number>;

Numbers getNumbers(std::string_view input) {
  Numbers numbers;
  std::regex regex(R"(\d+)");
  for (auto &&[row, line] : input | vw::split('\n') | vw::enumerate) {
    std::string s = line | std::ranges::to<std::string>();
    std::smatch match;
    std::int64_t col = 0;
    while (std::regex_search(s, match, regex)) {
      col += match.position();
      numbers.push_back(
          {.pos = {.row = row, .col = col}, .value = match.str()});
      col += match.length();
      s = match.suffix();
    }
  }
  return numbers;
}

std::vector<Pos> getSymbolPositions(std::string_view input) {
  std::vector<Pos> positions;
  for (auto &&[row, line] : input | vw::split('\n') | vw::enumerate) {
    for (auto &&[col, c] : line | vw::enumerate) {
      if (!std::isdigit(c) && c != '.')
        positions.push_back({.row = row, .col = col});
    }
  }

  return positions;
}

int solvePart1(std::string_view input) {
  auto numbers = getNumbers(input);
  auto symbolPositions = getSymbolPositions(input);
  return std::ranges::fold_left(
      numbers | vw::filter([&symbolPositions](const Number &number) {
        auto numberPos = number.pos;
        for (auto symbolPos : symbolPositions) {
          if (std::llabs(symbolPos.row - numberPos.row) <= 1 &&
              symbolPos.col + 1 >= numberPos.col &&
              symbolPos.col <= numberPos.col + number.value.length()) {
            return true;
          }
        }
        return false;
      }) | vw::transform([](const Number &number) {
        return std::stoi(number.value);
      }),
      0, std::plus<>{});
}

std::vector<Pos> getAsterisksPositions(std::string_view input) {
  std::vector<Pos> positions;
  for (auto &&[row, line] : input | vw::split('\n') | vw::enumerate) {
    for (auto &&[col, c] : line | vw::enumerate) {
      if (c == '*')
        positions.push_back({.row = row, .col = col});
    }
  }

  return positions;
}

int solvePart2(std::string_view input) {
  auto numbers = getNumbers(input);
  auto asterisks = getAsterisksPositions(input);

  return std::ranges::fold_left(
      asterisks | vw::transform([&numbers](const Pos &asteriskPos) {
        std::vector<Number> adjacentNumbers;
        for (auto number : numbers) {
          auto numberPos = number.pos;
          if (std::llabs(asteriskPos.row - numberPos.row) <= 1 &&
              asteriskPos.col + 1 >= numberPos.col &&
              asteriskPos.col <= numberPos.col + number.value.length()) {
            adjacentNumbers.push_back(number);
          }
        }
        return std::make_tuple(asteriskPos, adjacentNumbers);
      }) | vw::filter([](const auto &t) {
        auto &&[asterisk, adjacentNumbers] = t;
        return adjacentNumbers.size() == 2;
      }) | vw::transform([](const auto &t) {
        auto &&[asterisk, adjacentNumbers] = t;
        return std::stoi(adjacentNumbers[0].value) *
               std::stoi(adjacentNumbers[1].value);
      }),
      0, std::plus<>{});
}

TEST(day03, test) {
  EXPECT_EQ(solvePart1(day03::sample), 4361);
  EXPECT_EQ(solvePart1(day03::input), 530849);

  EXPECT_EQ(solvePart2(day03::sample), 467835);
  EXPECT_EQ(solvePart2(day03::input), 84900879);
}

} // anonymous namespace