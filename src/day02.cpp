#include "inputs/day02.h"

#include <algorithm>
#include <functional>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

namespace
{

namespace vw = std::ranges::views;

enum class Color
{
	red,
	green,
	blue,
};

struct CubeSet
{
	Color color;
	int count{};
};

using CubeSets = std::vector<CubeSet>;

struct Game
{
	int id{};
	CubeSets sets;
};

using Games = std::vector<Game>;

namespace Parsing
{

namespace pegtl = tao::pegtl;

Color parseColor(std::string_view color)
{
	if (color == "red")
		return Color::red;
	if (color == "green")
		return Color::green;
	if (color == "blue")
		return Color::blue;

	std::unreachable();
}

struct Number : pegtl::plus<pegtl::digit>
{
};

struct GameNumber : Number
{
};

struct ColorCount : Number
{
};

struct ColorValue
	: pegtl::sor<TAO_PEGTL_STRING("red"), TAO_PEGTL_STRING("blue"), TAO_PEGTL_STRING("green")>
{
};

struct CubeSetItem : public pegtl::seq<pegtl::blank, ColorCount, pegtl::blank, ColorValue>
{
};

struct Line
	: public pegtl::seq<
		  TAO_PEGTL_STRING("Game "),
		  GameNumber,
		  pegtl::one<':'>,
		  pegtl::list<CubeSetItem, pegtl::one<',', ';'>>,
		  pegtl::eolf>
{
};

struct File : pegtl::must<pegtl::until<pegtl::eof, Line>>
{
};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{
};

template<>
struct Action<GameNumber>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, Games& games)
	{
		assert(!games.empty());
		games.back().id = std::stoi(in.string());
	}
};

template<>
struct Action<ColorCount>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, Games& games)
	{
		assert(!games.empty());
		auto& sets = games.back().sets;
		assert(!sets.empty());
		sets.back().count = std::stoi(in.string());
	}
};

template<>
struct Action<ColorValue>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, Games& games)
	{
		assert(!games.empty());
		auto& sets = games.back().sets;
		assert(!sets.empty());
		sets.back().color = parseColor(in.string());
	}
};

template<typename Rule>
struct Control : pegtl::normal<Rule>
{
};

template<>
struct Control<Line> : pegtl::normal<Line>
{
	template<typename ParseInput>
	static void start(ParseInput&, Games& games)
	{
		games.emplace_back();
	}
};

template<>
struct Control<CubeSetItem> : pegtl::normal<CubeSetItem>
{
	template<typename ParseInput>
	static void start(ParseInput&, Games& games)
	{
		assert(!games.empty());
		games.back().sets.emplace_back();
	}
};

Games parse(std::string_view input)
{
	Games games;
	pegtl::memory_input in{input, ""};
	pegtl::parse<File, Action, Control>(in, games);
	return games;
}

} // namespace Parsing

struct MaxCount
{
	int red;
	int green;
	int blue;
};

MaxCount getMaxCount(const CubeSets& sets)
{
	auto getMaxForColor = [&](Color color) {
		auto filtered = sets | vw::filter([&](const CubeSet& set) { return set.color == color; });
		assert(!filtered.empty());
		return std::ranges::max(filtered, {}, &CubeSet::count).count;
	};

	return {
		.red = getMaxForColor(Color::red),
		.green = getMaxForColor(Color::green),
		.blue = getMaxForColor(Color::blue)};
}

int solvePart1(std::string_view input)
{
	const auto games = Parsing::parse(input);
	return std::ranges::fold_left(
		games | vw::filter([](const Game& game) {
			const auto max = getMaxCount(game.sets);
			return max.red <= 12 && max.green <= 13 && max.blue <= 14;
		}) | vw::transform(&Game::id),
		0,
		std::plus{});
}

int solvePart2(std::string_view input)
{
	const auto games = Parsing::parse(input);
	return std::ranges::fold_left(
		games | vw::transform([](const Game& game) {
			const auto max = getMaxCount(game.sets);
			return max.red * max.green * max.blue;
		}),
		0,
		std::plus{});
}

TEST(day02, test)
{
	EXPECT_EQ(solvePart1(day02::sample), 8);
	EXPECT_EQ(solvePart1(day02::input), 2348);

	EXPECT_EQ(solvePart2(day02::sample), 2286);
	EXPECT_EQ(solvePart2(day02::input), 76008);
}

} // anonymous namespace
