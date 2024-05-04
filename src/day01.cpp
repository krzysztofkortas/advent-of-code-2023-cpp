#include <algorithm>
#include <cassert>
#include <functional>
#include <ranges>
#include <string_view>

#include "inputs/day01.h"

namespace {

namespace vw = std::ranges::views;

using namespace std::literals;

constexpr int calculatePart1(std::string_view input) {
  return std::ranges::fold_left(
      input | vw::split('\n') | vw::transform([&](auto &&line) {
        auto digits =
            line | vw::filter([](char c) { return c >= '0' && c <= '9'; });
        assert(!digits.empty());
        return 10 * (digits.front() - '0') + (digits.back() - '0');
      }),
      0, std::plus<>{});
}

constexpr void replace(std::string &str, std::string_view pattern,
                       std::string_view replacement) {
  auto pos = str.find(pattern);
  while (pos != std::string::npos) {
    str.replace(pos, pattern.length(), replacement);
    pos = str.find(pattern, pos + replacement.length());
  }
}

constexpr std::string getModifiedLine(std::string str) {
  replace(str, "one", "one1one");
  replace(str, "two", "two2two");
  replace(str, "three", "three3three");
  replace(str, "four", "four4four");
  replace(str, "five", "five5five");
  replace(str, "six", "six6six");
  replace(str, "seven", "seven7seven");
  replace(str, "eight", "eight8eight");
  replace(str, "nine", "nine9nine");
  return str;
}

constexpr int calculatePart2(std::string_view input) {
  return std::ranges::fold_left(
      input | vw::split('\n') | vw::transform([&](auto &&line) {
        auto digits = getModifiedLine(line | std::ranges::to<std::string>()) |
                      vw::filter([](char c) { return c >= '0' && c <= '9'; });
        assert(!digits.empty());
        return 10 * (digits.front() - '0') + (digits.back() - '0');
      }),
      0, std::plus<>{});
}

static_assert(calculatePart1(day01::sample_part1) == 142);
static_assert(calculatePart2(day01::sample_part2) == 281);

static_assert(calculatePart1(day01::input) == 54601);
static_assert(calculatePart2(day01::input) == 54078);

} // anonymous namespace
