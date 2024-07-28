#include "inputs/day09.h"

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

constexpr auto transformHistory()
{
	return vw::slide(2) | vw::transform([](auto&& range) { return range[1] - range[0]; })
		| rng::to<std::vector>();
}

int64_t solve(std::string_view input, std::invocable<std::vector<int64_t>> auto getValue)
{
	return Utils::sum(input | vw::split('\n') | vw::transform([&](auto&& line) {
		std::vector<int64_t> history = line | vw::split(' ') | vw::transform([](auto&& value) {
			return static_cast<int64_t>(std::stoll(value | rng::to<std::string>()));
		}) | rng::to<std::vector>();
		return getValue(std::move(history));
	}));
}

int64_t solvePart1(std::string_view input)
{
	constexpr auto getNextValue = [](std::vector<int64_t> history) {
		int64_t result = 0;
		while (!rng::all_of(history, [](int v) { return v == 0; }))
		{
			result += history.back();
			history = history | transformHistory();
		}
		return result;
	};

	return solve(input, getNextValue);
}

int64_t solvePart2(std::string_view input)
{
	constexpr auto getPrevValue = [](std::vector<int64_t> history) {
		int64_t result = 0;
		for (int64_t sign = 1; !rng::all_of(history, [](int v) { return v == 0; }); sign *= -1)
		{
			result += sign * history.front();
			history = history | transformHistory();
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
