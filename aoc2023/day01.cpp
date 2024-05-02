#include <algorithm>
#include <cassert>
#include <charconv>
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
        const auto number =
            std::string{digits.front()} + std::string{digits.back()};
        int value{};
        std::from_chars(number.data(), number.data() + number.size(), value);
        return value;
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

constexpr int calculatePart2(std::string_view input) {
  std::string s{input};
  replace(s, "one", "one1one");
  replace(s, "two", "two2two");
  replace(s, "three", "three3three");
  replace(s, "four", "four4four");
  replace(s, "five", "five5five");
  replace(s, "six", "six6six");
  replace(s, "seven", "seven7seven");
  replace(s, "eight", "eight8eight");
  replace(s, "nine", "nine9nine");
  return calculatePart1(s);
}

static_assert(calculatePart1(day01::sample_part1) == 142);
static_assert(calculatePart2(day01::sample_part2) == 281);

static_assert(calculatePart1(day01::input) == 54601);
static_assert(calculatePart2(day01::input) == 54078);

} // anonymous namespace
