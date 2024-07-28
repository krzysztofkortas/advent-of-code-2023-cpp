#include "inputs/day05.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <ranges>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

using std::int64_t;

struct MapItem
{
	int64_t destinationRangeStart{};
	int64_t sourceRangeStart{};
	int64_t rangeLength{};
};

using Map = std::vector<MapItem>;
using Maps = std::vector<Map>;

using Seeds = std::vector<int64_t>;

struct Almanac
{
	Seeds seeds;
	Maps maps;
};

namespace Parsing
{

namespace pegtl = tao::pegtl;

struct State
{
	Almanac almanac;
	MapItem tempMapItem;
	Map tempMap;
};

struct NumberRule : pegtl::plus<pegtl::digit>
{};

struct SeedRule : NumberRule
{};

struct SeedsRule : pegtl::seq<TAO_PEGTL_STRING("seeds: "), pegtl::list<SeedRule, pegtl::blank>>
{};

struct MapNameRule : pegtl::plus<pegtl::print>
{};

struct DestinationRangeStartRule : NumberRule
{};

struct SourceRangeStartRule : NumberRule
{};

struct RangeLengthRule : NumberRule
{};

struct MapItemRule
	: pegtl::seq<
		  DestinationRangeStartRule,
		  pegtl::blank,
		  SourceRangeStartRule,
		  pegtl::blank,
		  RangeLengthRule>
{};

struct MapRule : pegtl::seq<MapNameRule, pegtl::eol, pegtl::list<MapItemRule, pegtl::eol>>
{};

struct Grammar : pegtl::must<SeedsRule, pegtl::until<pegtl::eof, pegtl::pad<MapRule, pegtl::space>>>
{};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{};

template<>
struct Action<SeedRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.almanac.seeds.push_back(std::stoll(in.string()));
	}
};

template<>
struct Action<DestinationRangeStartRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempMapItem.destinationRangeStart = std::stoll(in.string());
	}
};

template<>
struct Action<SourceRangeStartRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempMapItem.sourceRangeStart = std::stoll(in.string());
	}
};

template<>
struct Action<RangeLengthRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempMapItem.rangeLength = std::stoll(in.string());
	}
};

template<>
struct Action<MapItemRule>
{
	static void apply0(State& state)
	{
		state.tempMap.push_back(state.tempMapItem);
	}
};

template<>
struct Action<MapRule>
{
	static void apply0(State& state)
	{
		state.almanac.maps.push_back(state.tempMap);
		state.tempMap.clear();
	}
};

Almanac parse(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<Grammar, Action>(in, state);
	return state.almanac;
}

} // namespace Parsing

int64_t getMappedSeed(const Maps& maps, int64_t seed)
{
	for (const Map& map : maps)
	{
		for (const MapItem& item : map)
		{
			if (seed >= item.sourceRangeStart && seed < item.sourceRangeStart + item.rangeLength)
			{
				seed += item.destinationRangeStart - item.sourceRangeStart;
				break;
			}
		}
	}
	return seed;
}

int64_t solvePart1(std::string_view input)
{
	const auto [seeds, maps] = Parsing::parse(input);
	return rng::min(seeds | vw::transform([&](int64_t seed) { return getMappedSeed(maps, seed); }));
}

struct SeedRange
{
	int64_t start{};
	int64_t end{};

	friend auto operator<=>(const SeedRange&, const SeedRange&) = default;
};

using SeedRanges = std::vector<SeedRange>;

SeedRanges convertSingleRange(const SeedRange& seedRange, const Map& map)
{
	SeedRanges convertedRanges;
	SeedRanges originalRanges;

	for (const MapItem& mapItem : map)
	{
		const int64_t diff = mapItem.destinationRangeStart - mapItem.sourceRangeStart;
		const int64_t rangeStart = std::max(seedRange.start, mapItem.sourceRangeStart);
		const int64_t rangeEnd =
			std::min(seedRange.end, mapItem.sourceRangeStart + mapItem.rangeLength);
		if (rangeStart < rangeEnd)
		{
			originalRanges.emplace_back(rangeStart, rangeEnd);
			convertedRanges.emplace_back(rangeStart + diff, rangeEnd + diff);
		}
	}

	rng::sort(originalRanges);
	int64_t currentValue = seedRange.start;
	for (const SeedRange& r : originalRanges)
	{
		if (r.start > currentValue)
			convertedRanges.emplace_back(currentValue, r.start);
		currentValue = r.end;
	}
	if (currentValue != seedRange.end)
		convertedRanges.emplace_back(currentValue, seedRange.end);

	return convertedRanges;
}

SeedRanges convert(const SeedRanges& seedRanges, const Map& map)
{
	return seedRanges | vw::transform([&](const SeedRange& seedRange) {
		return convertSingleRange(seedRange, map);
	}) | vw::join
		| rng::to<SeedRanges>();
}

int64_t solvePart2(std::string_view input)
{
	const auto [seeds, maps] = Parsing::parse(input);
	SeedRanges seedRanges = seeds | vw::chunk(2) | vw::transform([](auto&& range) {
		assert(range.size() == 2);
		return SeedRange{.start = range[0], .end = range[0] + range[1]};
	}) | rng::to<std::vector>();

	for (const Map& map : maps)
		seedRanges = convert(seedRanges, map);

	return rng::min_element(seedRanges)->start;
}

TEST(day05, test)
{
	EXPECT_EQ(solvePart1(day05::sample), 35);
	EXPECT_EQ(solvePart1(day05::input), 324724204);

	EXPECT_EQ(solvePart2(day05::sample), 46);
	EXPECT_EQ(solvePart2(day05::input), 104070862);
}

} // anonymous namespace
