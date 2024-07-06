#include "inputs/day06.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <ranges>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

namespace
{

namespace vw = std::ranges::views;

using std::int64_t;

struct Race
{
	int64_t time{};
	int64_t distance{};
};

using Races = std::vector<Race>;

namespace Parsing
{

namespace pegtl = tao::pegtl;

using Times = std::vector<int64_t>;
using Distances = std::vector<int64_t>;

struct State
{
	Times times;
	Distances distances;
};

struct SeparatorRule : pegtl::plus<pegtl::blank>
{};

struct NumberRule : pegtl::plus<pegtl::digit>
{};

struct TimeRule : NumberRule
{};

struct DistanceRule : NumberRule
{};

struct TimeLineRule
	: pegtl::seq<
		  TAO_PEGTL_STRING("Time:"),
		  SeparatorRule,
		  pegtl::list<TimeRule, SeparatorRule>,
		  pegtl::eol>
{};

struct DistanceLineRule
	: pegtl::seq<
		  TAO_PEGTL_STRING("Distance:"),
		  SeparatorRule,
		  pegtl::list<DistanceRule, SeparatorRule>,
		  pegtl::eolf>
{};

struct Grammar : pegtl::must<TimeLineRule, DistanceLineRule>
{};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{};

template<>
struct Action<TimeRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.times.push_back(std::stoll(in.string()));
	}
};

template<>
struct Action<DistanceRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.distances.push_back(std::stoll(in.string()));
	}
};

Races parsePart1(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<Grammar, Action>(in, state);

	return vw::zip(state.times, state.distances) | vw::transform([](auto&& elem) {
			   return Race{.time = std::get<0>(elem), .distance = std::get<1>(elem)};
		   })
		| std::ranges::to<std::vector>();
}

Race parsePart2(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<Grammar, Action>(in, state);

	constexpr auto joinValues = vw::transform([](int64_t val) { return std::to_string(val); })
		| vw::join | std::ranges::to<std::string>();
	return Race{
		.time = std::stoll(state.times | joinValues),
		.distance = std::stoll(state.distances | joinValues)};
}

} // namespace Parsing

int64_t getWinnings(const Race& race)
{
	const auto delta = race.time * race.time - 4 * race.distance;
	const auto left = (static_cast<double>(race.time) - std::sqrt(delta)) / 2;
	const auto right = (static_cast<double>(race.time) + std::sqrt(delta)) / 2;
	const auto excludeLeft = left == std::floor(left) ? 1 : 0;
	const auto excludeRight = right == std::floor(right) ? 1 : 0;

	return static_cast<int64_t>(std::floor(right)) - static_cast<int64_t>(std::ceil(left)) + 1
		- excludeLeft - excludeRight;
}

int64_t solvePart1(std::string_view input)
{
	const Races races = Parsing::parsePart1(input);
	return std::ranges::fold_left(races | vw::transform(getWinnings), 1, std::multiplies<>{});
}

int64_t solvePart2(std::string_view input)
{
	const Race race = Parsing::parsePart2(input);
	return getWinnings(race);
}

TEST(day06, test)
{
	EXPECT_EQ(solvePart1(day06::sample), 288);
	EXPECT_EQ(solvePart1(day06::input), 2344708);

	EXPECT_EQ(solvePart2(day06::sample), 71503);
	EXPECT_EQ(solvePart2(day06::input), 30125202);
}

} // anonymous namespace
