#include "inputs/day09.h"

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <functional>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

namespace
{

namespace vw = std::ranges::views;

using std::int64_t;

int64_t solve(std::string_view input, std::invocable<std::vector<int64_t>> auto getValue)
{
	return std::ranges::fold_left(
		input | vw::split('\n') | vw::transform([&](auto&& line) {
			std::vector<int64_t> history =
				line | vw::split(' ') | vw::transform([](auto&& value) {
					return static_cast<int64_t>(std::stoll(value | std::ranges::to<std::string>()));
				})
				| std::ranges::to<std::vector>();
			return getValue(std::move(history));
		}),
		0,
		std::plus<>{});
}

int64_t solvePart1(std::string_view input)
{
	constexpr auto getNextValue = [](std::vector<int64_t> history) {
		int64_t result = 0;
		while (!std::ranges::all_of(history, [](int v) { return v == 0; }))
		{
			result += history.back();
			history = history | vw::slide(2)
				| vw::transform([](auto&& range) { return range[1] - range[0]; })
				| std::ranges::to<std::vector>();
		}
		return result;
	};

	return solve(input, getNextValue);
}

int64_t solvePart2(std::string_view input)
{
	constexpr auto getPrevValue = [](std::vector<int64_t> history) {
		int64_t result = 0;
		int64_t sign = 1;
		while (!std::ranges::all_of(history, [](int v) { return v == 0; }))
		{
			result += sign * history.front();
			sign *= -1;
			history = history | vw::slide(2)
				| vw::transform([](auto&& range) { return range[1] - range[0]; })
				| std::ranges::to<std::vector>();
		}
		return result;
	};

	return solve(input, getPrevValue);
}

TEST(day09, test)
{
	EXPECT_EQ(solvePart1(day09::sample), 114);
	EXPECT_EQ(solvePart1(day09::input), 1887980197);

	EXPECT_EQ(solvePart2(day09::sample), 2);
	EXPECT_EQ(solvePart2(day09::input), 990);
}

} // anonymous namespace
