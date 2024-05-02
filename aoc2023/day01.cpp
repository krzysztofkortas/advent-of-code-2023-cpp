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

static_assert(calculatePart1(day01::sample_part1) == 142);

static_assert(calculatePart1(day01::input) == 54601);

} // anonymous namespace
