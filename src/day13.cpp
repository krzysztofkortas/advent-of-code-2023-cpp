#include <algorithm>
#include <concepts>
#include <cstdint>
#include <functional>
#include <optional>
#include <ranges>
#include <span>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

#include "inputs/day13.h"

namespace {

namespace vw = std::ranges::views;

using std::int64_t;
using std::operator""sv;

using Pattern = std::vector<std::string>;

int64_t getHorizontalReflection(const Pattern &pattern,
                                std::optional<int64_t> ignore = std::nullopt) {
  for (auto i : vw::iota(1z, std::ssize(pattern))) {
    const auto size = std::min(i, std::ssize(pattern) - i);
    const auto upper = std::span{pattern}.subspan(i - size, size);
    const auto bottom = std::span{pattern}.subspan(i, size);
    if (std::ranges::equal(upper, bottom | vw::reverse) && 100 * i != ignore)
      return 100 * i;
  }
  return 0;
}

int64_t getVerticalReflection(const Pattern &pattern,
                              std::optional<int64_t> ignore = std::nullopt) {
  const auto transposed =
      vw::iota(0z, std::ssize(pattern.at(0))) | vw::transform([&](int64_t col) {
        return pattern | vw::transform([col](const std::string &line) {
                 return line.at(col);
               });
      }) |
      std::ranges::to<Pattern>();

  for (auto i : vw::iota(1z, std::ssize(transposed))) {
    const auto size = std::min(i, std::ssize(transposed) - i);
    const auto upper = std::span{transposed}.subspan(i - size, size);
    const auto bottom = std::span{transposed}.subspan(i, size);
    if (std::ranges::equal(upper, bottom | vw::reverse) && i != ignore)
      return i;
  }
  return 0;
}

int64_t solve(std::string_view input,
              std::invocable<Pattern> auto getReflection) {
  return std::ranges::fold_left(
      input | vw::split("\n\n"sv) | vw::transform([&](auto &&pattern) {
        return getReflection(pattern | vw::split('\n') |
                             std::ranges::to<Pattern>());
      }),
      0, std::plus<>{});
  return 1;
}

int64_t getReflection(const Pattern &pattern) {
  return getHorizontalReflection(pattern) + getVerticalReflection(pattern);
}

int64_t solvePart1(std::string_view input) {
  return solve(input, getReflection);
}

int64_t getReflection2(const Pattern &pattern) {
  const auto oldResult = getReflection(pattern);
  auto pattern2 = pattern;

  for (const auto &[rowIndex, row] : pattern | vw::enumerate) {
    for (const auto &[colIndex, c] : row | vw::enumerate) {
      pattern2[rowIndex][colIndex] = (c == '.' ? '#' : '.');
      if (auto horizontalResult = getHorizontalReflection(pattern2, oldResult))
        return horizontalResult;
      if (auto verticalResult = getVerticalReflection(pattern2, oldResult))
        return verticalResult;

      pattern2[rowIndex][colIndex] = c;
    }
  }

  return 0;
}

int64_t solvePart2(std::string_view input) {
  return solve(input, getReflection2);
}

TEST(day13, test) {
  EXPECT_EQ(solvePart1(day13::sample), 405);
  EXPECT_EQ(solvePart1(day13::input), 31265);

  EXPECT_EQ(solvePart2(day13::sample), 400);
  EXPECT_EQ(solvePart2(day13::input), 39359);
}

} // anonymous namespace