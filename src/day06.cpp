#include "inputs/day06.h"

#include <cmath>
#include <cstdint>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

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

	constexpr auto createRace = [](int64_t time, int64_t distance) {
		return Race{.time = time, .distance = distance};
	};
	return vw::zip_transform(createRace, state.times, state.distances) | rng::to<Races>();
}

Race parsePart2(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<Grammar, Action>(in, state);

	constexpr auto joinValues = vw::transform([](int64_t val) { return std::to_string(val); })
		| vw::join | rng::to<std::string>();
	return Race{
		.time = std::stoll(state.times | joinValues),
		.distance = std::stoll(state.distances | joinValues)};
}

} // namespace Parsing

int64_t getWinnings(const Race& race)
{
	const auto delta = (race.time * race.time) - (4 * race.distance);
	const auto left = (static_cast<double>(race.time) - std::sqrt(delta)) / 2;
	const auto right = (static_cast<double>(race.time) + std::sqrt(delta)) / 2;

	return static_cast<int64_t>(std::ceil(right)) - static_cast<int64_t>(std::floor(left)) - 1;
}

int64_t solvePart1(std::string_view input)
{
	const Races races = Parsing::parsePart1(input);
	return Utils::multiply(races | vw::transform(&getWinnings));
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
