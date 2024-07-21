#include "inputs/day02.h"

#include <algorithm>
#include <cassert>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <gtest/gtest.h>
#include <tao/pegtl.hpp>

#include "Utils.h"

namespace
{

namespace rng = std::ranges;
namespace vw = std::views;

enum class Color
{
	red,
	green,
	blue,
};

struct CubeSet
{
	Color color{};
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

struct State
{
	Games games;
	Game tempGame;
	CubeSet tempCubeSet;
};

struct NumberRule : pegtl::plus<pegtl::digit>
{};

struct GameNumberRule : NumberRule
{};

struct ColorCountRule : NumberRule
{};

struct ColorValueRule
	: pegtl::sor<TAO_PEGTL_STRING("red"), TAO_PEGTL_STRING("blue"), TAO_PEGTL_STRING("green")>
{};

struct CubeSetItemRule
	: public pegtl::seq<pegtl::blank, ColorCountRule, pegtl::blank, ColorValueRule>
{};

struct GameRule
	: public pegtl::seq<
		  TAO_PEGTL_STRING("Game "),
		  GameNumberRule,
		  pegtl::one<':'>,
		  pegtl::list<CubeSetItemRule, pegtl::one<',', ';'>>,
		  pegtl::eolf>
{};

struct Grammar : pegtl::must<pegtl::until<pegtl::eof, GameRule>>
{};

template<typename Rule>
struct Action : pegtl::nothing<Rule>
{};

template<>
struct Action<GameNumberRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempGame.id = std::stoi(in.string());
	}
};

template<>
struct Action<ColorCountRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempCubeSet.count = std::stoi(in.string());
	}
};

template<>
struct Action<ColorValueRule>
{
	template<typename ActionInput>
	static void apply(const ActionInput& in, State& state)
	{
		state.tempCubeSet.color = parseColor(in.string());
	}

	static Color parseColor(std::string_view color)
	{
		if (color == "red")
			return Color::red;
		else if (color == "green")
			return Color::green;
		else if (color == "blue")
			return Color::blue;

		std::unreachable();
	}
};

template<>
struct Action<CubeSetItemRule>
{
	static void apply0(State& state)
	{
		state.tempGame.sets.push_back(state.tempCubeSet);
		state.tempCubeSet = {};
	}
};

template<>
struct Action<GameRule>
{
	static void apply0(State& state)
	{
		state.games.push_back(std::move(state.tempGame));
		state.tempGame = {};
	}
};

Games parse(std::string_view input)
{
	State state;
	pegtl::memory_input in{input, ""};
	pegtl::parse<Grammar, Action>(in, state);
	return state.games;
}

} // namespace Parsing

struct MaxCount
{
	int red{};
	int green{};
	int blue{};
};

MaxCount getMaxCount(const CubeSets& sets)
{
	auto getMaxForColor = [&](Color color) {
		auto filtered = sets | vw::filter([&](const CubeSet& set) { return set.color == color; });
		assert(!filtered.empty());
		return rng::max(filtered | vw::transform(&CubeSet::count));
	};

	return MaxCount{
		.red = getMaxForColor(Color::red),
		.green = getMaxForColor(Color::green),
		.blue = getMaxForColor(Color::blue)};
}

int solvePart1(std::string_view input)
{
	const Games games = Parsing::parse(input);
	constexpr int maxRed = 12;
	constexpr int maxGreen = 12;
	constexpr int maxBlue = 12;
	return Utils::sum(
		games | vw::filter([](const Game& game) {
			const MaxCount maxCount = getMaxCount(game.sets);
			return maxCount.red <= maxRed && maxCount.green <= maxGreen && maxCount.blue <= maxBlue;
		})
		| vw::transform(&Game::id));
}

int solvePart2(std::string_view input)
{
	const Games games = Parsing::parse(input);
	return Utils::sum(games | vw::transform([](const Game& game) {
						  const MaxCount maxCount = getMaxCount(game.sets);
						  return maxCount.red * maxCount.green * maxCount.blue;
					  }));
}

TEST(day02, test)
{
	EXPECT_EQ(solvePart1(day02::sample), 8);
	EXPECT_EQ(solvePart1(day02::input), 2348);

	EXPECT_EQ(solvePart2(day02::sample), 2286);
	EXPECT_EQ(solvePart2(day02::input), 76008);
}

} // anonymous namespace
